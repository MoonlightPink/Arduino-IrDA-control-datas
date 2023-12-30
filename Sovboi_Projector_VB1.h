#pragma once

// Sovboi製プロジェクタ VB1

class CSovboi_Projector_VB1 {
private:
  u8 pin;
  
  const u8 Maker1=0xb8; // 固定
  const u8 Maker2=0x57; // 固定

  void SendData(u8 Data)
  {
    IrDA_NEC_Send(pin,Maker1,Maker2,Data);
    IrDA_Wait(200);
  }

public:
  void Init(const u8 _pin){
    pin=_pin;
  }
  
  void SendPower(void) // 電源
  {
    SendData(0x0c);
  }
  void SendShutdown(void) // 遮断（電源ボタン2回）
  {
    for(int i=0;i<3;i++){
      SendPower();
      delay(100);
    }
  }
  void SendMute(void) // 消音（動作未確認）
  {
    SendData(0x0d);
  }
  void SendKeystone(void) // 台形補正（動作未確認）
  {
    SendData(0x1c);
  }
  void SendDoubleCircle(void) // 二重丸（動作未確認）
  {
    SendData(0x18);
  }
  void SendBrightWiFiSetting(void) // 明るさ（WiFi設定？）（動作未確認）
  {
    SendData(0x1d);
  }
  void SendCursorUp(void) // カーソル上（動作未確認）
  {
    SendData(0x10);
  }
  void SendCursorLeft(void) // カーソル左（動作未確認）
  {
    SendData(0x11);
  }
  void SendCursorOK(void) // カーソルOK（動作未確認）
  {
    SendData(0x12);
  }
  void SendCursorRight(void) // カーソル右（動作未確認）
  {
    SendData(0x13);
  }
  void SendCursorDown(void) // カーソル下（動作未確認）
  {
    SendData(0x14);
  }
  void SendSelectInput(void) // 入力切り替え（動作未確認）
  {
    SendData(0x0e);
  }
  void SendSettings(void) // 設定（動作未確認）
  {
    SendData(0x16);
  }
  void SendBack(void) // 戻る（動作未確認）
  {
    SendData(0x17);
  }
  void SendVolumeDown(void) // 音量下（動作未確認）
  {
    SendData(0x1e);
  }
  void SendVolumeUp(void) // 音量上（動作未確認）
  {
    SendData(0x1f);
  }
};

// Example.
// void setup(void){
//   CSovboi_Projector_VB1 Sovboi_Projector_VB1;
//   Sovboi_Projector_VB1.Init(IrDAPin);
//   Sovboi_Projector_VB1.SendPower();
// }

