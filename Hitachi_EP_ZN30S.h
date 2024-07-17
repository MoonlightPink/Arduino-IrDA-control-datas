#pragma once

// 日立製加湿空気清浄機 EP-ZN30S リモコン型番:EPR-26

class CHitachi_EP_ZN30S {
private:
  u8 pin;
  
  const u8 ID=0xb; // 固定

  void SendPulse(int t,bool f)
  {
    const u32 OnTime=t*425;
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
    IrDA_Wait();
    noInterrupts();
    
    SendPulse(8,true);
    SendPulse(4,false);

    SendMultiBits(0x01,8);
    SendMultiBits(0x10,8);
    SendMultiBits(0x00,8);
    SendMultiBits(0x48,8);
    SendMultiBits(0xb7,8);
    SendMultiBits(Data,8);
    SendMultiBits(~Data,8);
  
    SendPulse(1,true);
    SendPulse(20,false);
    SendPulse(1,true);
    interrupts();
    IrDA_Wait(500);
  }

public:
  void Init(const u8 _pin){
    pin=_pin;
  }
  
  void SendRaw(u8 Data){
    SendDataAndParity(Data);
  }
  
  void SendPowerToggle(void){ // 電源On/Off
    SendDataAndParity(0x01);
  }
  void SendMode(void){ // モード
    SendDataAndParity(0x04);
  }
  void SendWindLevel(void){ // 風量
    SendDataAndParity(0x02);
  }
  void SendTimer(void){ // タイマー
    SendDataAndParity(0x07);
  }
  void SendTurbo(void){ // 一発ターボ
    SendDataAndParity(0x0a);
  }
};

// Example.
// void setup(void){
//   CHitachi_EP_ZN30S Hitachi_EP_ZN30S;
//   Hitachi_EP_ZN30S.Init(IrDAPin);
//   Hitachi_EP_ZN30S.SendPowerToggle();
// }

