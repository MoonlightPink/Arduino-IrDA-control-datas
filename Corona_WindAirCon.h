#pragma once

// コロナ製窓用エアコン用リモコン CWH

// 信号フォーマットは家製協(AEHA)フォーマットに似た独自フォーマット

class CCorona_WindAirCon {
private:
  u8 pin;
  
  const u8 CustomCode1=0x28;
  const u8 CustomCode2=0x61;

  void SendDatas(const u8 *pDatas){
    IrDA_AEHA_Send_ins_Pulse(pin,8,true);
    IrDA_AEHA_Send_ins_Pulse(pin,4,false);

    IrDA_AEHA_Send_ins_Byte(pin,pDatas[0]);
    IrDA_AEHA_Send_ins_Byte(pin,pDatas[1]);
    IrDA_AEHA_Send_ins_Byte(pin,pDatas[2]);
    IrDA_AEHA_Send_ins_Byte(pin,pDatas[3]);
    IrDA_AEHA_Send_ins_Byte(pin,pDatas[4]);
    IrDA_AEHA_Send_ins_Byte(pin,pDatas[5]);
    IrDA_AEHA_Send_ins_Byte(pin,pDatas[6]);
    
    IrDA_AEHA_Send_ins_Pulse(pin,1,true);
    IrDA_AEHA_Send_ins_Pulse(pin,26,false);
  }
  void SendData(const u8 Data1,const u8 Data2){
    IrDA_Wait();
    noInterrupts();
    
    { // 運転設定
      u8 Datas[7]={CustomCode1,CustomCode2,0x3d,Data1,0xff-Data1,Data2,0xff-Data2};
      SendDatas(Datas);
    }
    { // タイマー設定1
      u8 Datas[7]={CustomCode1,CustomCode2,0x6d,0xff,0x00,0xff,0x00};
      SendDatas(Datas);
    }
    { // タイマー設定2
      u8 Datas[7]={CustomCode1,CustomCode2,0xcd,0xff,0x00,0xff,0x00};
      SendDatas(Datas);
    }

    interrupts();
  }
  void SendDataWithPower(const bool PowerOn,const u8 Data1,const u8 Data2){
    if(PowerOn){
      SendData(Data1,Data2|(3<<4)); // 電源ON
      SendData(Data1,Data2|(1<<4)); // 継続
    }else{
      SendData(Data1,Data2|(2<<4)); // 電源OFF
    }
  }
  void SendCurrentStateWithPower(const bool PowerOn){
    u8 Data1=0x00;
    u8 Data2=0x00;
    
    //        継続   切る   入れる
    // 暖房   1:0001 2:0010 3:0011
    // ドライ 5:0101 6:0110 7:0111
    // 自動   9:1011 A:1010 B:1011 風量が4、温度が3(19-16)のときは自動
    // 冷房   9:1011 A:1010 B:1011
    // 送風   D:1101 E:1110 F:1111
    
    if(Mode==0xff){
      Data1|=4; // 風量固定
      Data2|=19-16; // 温度固定
      Data2|=2<<6; // 自動
    }else{
      Data1|=FanSpeed;
      Data2|=Temp-16;
      Data2|=Mode<<6;
    }
    
    Data1|=1<<4; // Unknown.
    if(Ventilation){ Data1|=1<<6; }
    SendDataWithPower(PowerOn,Data1,Data2);
  }

public:
  const u8 Mode_Warm=0;
  const u8 Mode_Dry=1;
  const u8 Mode_Cool=2;
  const u8 Mode_Fan=3;
  const u8 Mode_Auto=0xff;
  u8 Mode=Mode_Auto; // 運転設定
  
  const u8 FanSpeed_Auto=0;
  const u8 FanSpeed_Low=1;
  const u8 FanSpeed_Middle=2;
  const u8 FanSpeed_High=3;
  u8 FanSpeed=FanSpeed_Auto; // 風量設定
  
  u8 Temp=20; // 温度設定: 停止と自動は温度設定無し, 冷房とドライと送風は20度以上30度以下, 暖房は17℃以上30度以下
  
  bool Ventilation=false; // 換気設定: False=現在設定を維持, True=送るたびにトグル切り替え

  void Init(const u8 _pin){
    pin=_pin;
    PowerOff();
  }
  void PowerOff(){
    SendCurrentStateWithPower(false);
  }
  void PowerOnAndChangeStatus(){
    SendCurrentStateWithPower(true);
  }
};

