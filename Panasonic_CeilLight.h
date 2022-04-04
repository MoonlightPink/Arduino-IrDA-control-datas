#pragma once

// パナソニック製シーリングライト用リモコン HK9495

// 信号フォーマットは家製協(AEHA)フォーマット

class CPanasonic_CeilLight {
private:
  u8 pin;
  
  const u8 CustomCode1=0x2c;
  const u8 CustomCode2=0x52;

  void SendDataAndParity(const u8 pin,u8 Data0,u8 Data1)
  {
    noInterrupts();
    
    IrDA_AEHA_Send_ins_Pulse(pin,8,true);
    IrDA_AEHA_Send_ins_Pulse(pin,4,false);

    IrDA_AEHA_Send_ins_Byte(pin,CustomCode1);
    IrDA_AEHA_Send_ins_Byte(pin,CustomCode2);
    
    const u8 Parity=(CustomCode1&0x0f)^(CustomCode1>>4)^(CustomCode2&0x0f)^(CustomCode2>>4);

    Data0=Parity | (Data0<<4);
    
    IrDA_AEHA_Send_ins_Byte(pin,Data0);
    IrDA_AEHA_Send_ins_Byte(pin,Data1);

    IrDA_AEHA_Send_ins_Byte(pin,Data0^Data1);
    
    IrDA_AEHA_Send_ins_Pulse(pin,1,true);

    interrupts();

    delay(75); // 連続して送るときは75ms以上のオフ時間が必要
  }

public:
  void Init(const u8 _pin){
    pin=_pin;
    SendOff();
  }
  
  void SendFullWhite(void)
  {
    SendDataAndParity(pin,0x0,0x2c);
  }
  void SendFullRed(void)
  {
    SendDataAndParity(pin,0x3,0x8b);
  }
  void SendFullBlue(void)
  {
    SendDataAndParity(pin,0x3,0x8a);
  }
  void SendOff(void)
  {
    SendDataAndParity(pin,0x0,0x2f);
  }
  void SendEcoNavi(void)
  {
    SendDataAndParity(pin,0x3,0x80);
  }
  void SendOmakase(void) // おまかせ
  {
    SendDataAndParity(pin,0x3,0x65);
  }
  void SendOn(void) // 点灯(普段)
  {
    SendDataAndParity(pin,0x0,0x2d);
  }
  void SendNightLamp(void) // 常夜灯
  {
    SendDataAndParity(pin,0x0,0x2e);
  }
  void SendToBlue(void) // 白い色
  {
    SendDataAndParity(pin,0x3,0x90);
  }
  void SendToRed(void) // 暖かい色
  {
    SendDataAndParity(pin,0x3,0x91);
  }
  void SendToBright(void) // 明るい
  {
    SendDataAndParity(pin,0x0,0x2a);
  }
  void SendToDark(void) // 暗い
  {
    SendDataAndParity(pin,0x0,0x2b);
  }
  void SendEnvSetup(void) // 環境設定
  {
    SendDataAndParity(pin,0x3,0x82);
  }
  void SendBrightAdjust(void) // 明るさ調整
  {
    SendDataAndParity(pin,0x3,0x81);
  }
  void SendSetCh1(void) // 本体設定をチャンネル1に更新
  {
    SendDataAndParity(pin,0x3,0xda);
  }
  void SendSetCh2(void) // 本体設定をチャンネル2に更新
  {
    SendDataAndParity(pin,0x3,0xdb);
  }
  void SendSetCh3(void) // 本体設定をチャンネル3に更新
  {
    SendDataAndParity(pin,0x3,0xdc);
  }

  void SendToMostDark(void)
  {
    for(int loop=0;loop<18+5;loop++){ // 18回でいいけど、念のため5回余分に送る
      SendToDark();
    }
  }
  
  // SendDark関数群は、消灯状態で実行すると、指定した色調で最低輝度にする。
  void SendDarkWhite(void)
  {
    SendOff();
    SendFullWhite();
    SendToMostDark();
  }
  void SendDarkRed(void)
  {
    SendOff();
    SendFullRed();
    SendToMostDark();
  }
  void SendDarkBlue(void)
  {
    SendOff();
    SendFullBlue();
    SendToMostDark();
  }
};

