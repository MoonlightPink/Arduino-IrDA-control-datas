#pragma once

// トヨトミ製ウィンドウエアコン用リモコン RC-1 （動作確認機種 TIW-A18DSE）

// 信号フォーマットは家製協(AEHA)フォーマット
// 単発コマンドは SendShortCommand を呼ぶ
// 運転制御は SendLongCommand_ を呼ぶ
// 全ての運転モードで自動風量がサポートされているわけではないようなのでコメント参照

class CToyotomi_WindAirCon {
private:
  void SendByte(const u8 pin,const u8 Data)
  {
    Serial.println(String(Data,HEX)); // デバッグ用 割り込み禁止中にシリアルに書き込んではいけない
    IrDA_AEHA_Send_ins_Byte(pin,Data);
  }
  
  const u8 CustomCode1=0x59;
  const u8 CustomCode2=0x54;

  void SendStart(const u8 pin,const u8 TopData)
  {
    noInterrupts();

    IrDA_AEHA_Send_ins_Pulse(pin,8,true);
    IrDA_AEHA_Send_ins_Pulse(pin,4,false);

    SendByte(pin,CustomCode1);
    SendByte(pin,CustomCode2);
    
    const u8 Parity=(CustomCode1&0x0f)^(CustomCode1>>4)^(CustomCode2&0x0f)^(CustomCode2>>4);
    SendByte(pin,Parity | (TopData<<4));
  }

  void SendEnd(const u8 pin)
  {
    IrDA_AEHA_Send_ins_Pulse(pin,1,true);
    
    interrupts();

    delay(7); // 連続して送るときは7ms以上のオフ時間が必要
  }
  
  void SendDataAndParity(const u8 pin,const u8 Data)
  {
    SendByte(pin,Data);
    SendByte(pin,~Data);
  }

  u8 OffTimerData0=0x00;
  u8 OffTimerData1=0x00;
  u8 OnTimerData0=0x00;
  u8 OnTimerData1=0x00;

  bool SleepMode=false;

  u8 GetModeData(const u8 Mode,const u8 FanLevel)
  {
    u8 Data=1<<7;
    if(SleepMode){ Data|=1<<6; }
    Data|=Mode<<2;
    Data|=FanLevel;
    return(Data);
  }
  
public:
  const u8 ShotCommand_Stop=0x01;
  const u8 ShotCommand_TimerCancel=0x02;
  const u8 ShotCommand_Swing=0x04;
  const u8 ShotCommand_Ion=0x08;

  void SendShortCommand(const u8 pin,const u8 ShortCommand)
  {
    SendStart(pin,0xf);
    SendByte(pin,0x02);
    SendDataAndParity(pin,ShortCommand);
    SendEnd(pin);
  }
  
  void SetSleepMode(bool _SleepMode)
  {
    // 動作未検証 OffTimerと共に使う 設定後はSendLongCommand_関数を呼ぶこと
    SleepMode=_SleepMode;
  }
  
  void SetOffTimer(float Hour)
  {
    // 動作未検証 設定後はSendLongCommand_関数を呼ぶこと
    const u16 Data=Hour*1800;
    OffTimerData0=Data&0xff;
    OffTimerData1=Data>>8;
  }
  
  void SetOnTimer(float Hour)
  {
    // 動作未検証 設定後はSendLongCommand_関数を呼ぶこと
    const u16 Data=Hour*1800;
    OnTimerData0=Data&0xff;
    OnTimerData1=Data>>8;
  }

  void SendLongCommand_ins_Body(const u8 pin,const u8 ModeData,const u8 TempData)
  {
    SendStart(pin,0x0);
    SendByte(pin,0x02);
    SendDataAndParity(pin,ModeData);
    SendDataAndParity(pin,TempData);
    SendDataAndParity(pin,OffTimerData0);
    SendDataAndParity(pin,OffTimerData1);
    SendDataAndParity(pin,OnTimerData0);
    SendDataAndParity(pin,OnTimerData1);
    SendEnd(pin);
  }
  
  void SendLongCommand_Auto(const u8 pin,const int UnknownData)
  {
    // UnknownData 不明なデータ。温度設定ボタンを押すと変わる。リモコンの液晶画面は変化無し。

    const u8 ModeData=GetModeData(0b1111,0);
    
    u8 TempData=0x00;
    switch(UnknownData){
      case -3: TempData=0x29; break;
      case -2: TempData=0x26; break;
      case -1: TempData=0x23; break;
      case 0: TempData=0x00; break;
      case 1: TempData=0x03; break;
      case 2: TempData=0x06; break;
      case 3: TempData=0x09; break;
    }
    
    SendLongCommand_ins_Body(pin,ModeData,TempData);
  }
  
  void SendLongCommand_Cooler(const u8 pin,const u8 FanLevel,const int Temp)
  {
    // FanLevel 4=自動, 3=強, 2=弱, 1=微
    // Temp 16～30度
    
    const u8 ModeData=GetModeData(0b1000,FanLevel);
    
    u8 TempData=0x00;
    if((16<=Temp)&&(Temp<=30)){ TempData=(Temp-16)*3; } // 0x00～0x2a
    
    SendLongCommand_ins_Body(pin,ModeData,TempData);
  }
  
  void SendLongCommand_Dry(const u8 pin,const int Temp)
  {
    // Temp 16～30度
    
    const u8 ModeData=GetModeData(0b0110,0);
    
    u8 TempData=0x00;
    if((16<=Temp)&&(Temp<=30)){ TempData=(Temp-16)*3; } // 0x00～0x2a
    
    SendLongCommand_ins_Body(pin,ModeData,TempData);
  }
  
  void SendLongCommand_Fan(const u8 pin,const u8 FanLevel)
  {
    // FanLevel 3=強, 2=弱, 1=微
    
    const u8 ModeData=GetModeData(0b0100,FanLevel);
    const u8 TempData=0x00;
    
    SendLongCommand_ins_Body(pin,ModeData,TempData);
  }
  
  void SendLongCommand_Circulator(const u8 pin,const u8 FanLevel)
  {
    // FanLevel 3=強, 2=弱, 1=微
    
    const u8 ModeData=GetModeData(0b0010,FanLevel);
    const u8 TempData=0x00;
    
    SendLongCommand_ins_Body(pin,ModeData,TempData);
  }
  
};

