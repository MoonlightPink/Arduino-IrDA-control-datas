#pragma once

// パナソニック製扇風機 F-CV324

class CPanasonic_WindFan {
private:
  u8 pin;
  
  const u8 ID=0xb; // 固定

  void SendPulse(int t,bool f)
  {
    const u32 OnTime=t*842;
    if(!f){
      delayMicroseconds(OnTime);
      }else{
      const u32 EndTime=micros()+OnTime;
      while(micros()<EndTime){
        EspPD_DigitalWrite(pin,true);
        delayMicroseconds(9);
        EspPD_DigitalWrite(pin,false);
        delayMicroseconds(17);
      }
    }
  }

  void SendMultiBits(u8 Data,u8 BitsCount)
  {
    for(int idx=0;idx<BitsCount;idx++){
      SendPulse(1,true);
      const bool f=(Data&0x01)!=0x00;
      SendPulse(f?3:1,false);
      Data>>=1;
    }
  }

  void SendDataAndParity(u8 Data)
  {
    noInterrupts();
    
    SendPulse(4,true);
    SendPulse(4,false);

    SendMultiBits(ID,4);
    SendMultiBits(Data,8);
    SendMultiBits(~ID,4);
    SendMultiBits(~Data,8);
  
    SendPulse(1,true);
    interrupts();
    delay(100);
  }

public:
  void Init(const u8 _pin){
    pin=_pin;
  }
  
  void SendRaw(u8 Data)
  {
    SendDataAndParity(Data);
  }
  
  void SendPower(void) // 電源
  {
    SendDataAndParity(0x83);
  }
  void SendNatural(void) // 1/fゆらぎ
  {
    SendDataAndParity(0x73);
  }
  void SendOffTimer(void) // 切タイマー
  {
    SendDataAndParity(0x7b);
  }
  void SendWindPlus(void) // 風量+
  {
    SendDataAndParity(0x7f);
  }
  
  // 上位機種(F-CS338)には以下のコマンドもあるらしい（未確認）
  // 首振り         =0x77
  // 風量-          =0x5f
  // 明るさ控えめ   =0x57
  // 温度センサ運転 =0x67
  // 入タイマ       =0x5b
};

// Example.
// void setup(void){
//   CPanasonic_WindFan Panasonic_WindFan;
//   Panasonic_WindFan.Init(IrDAPin);
//   Panasonic_WindFan.SendPower();
// }

