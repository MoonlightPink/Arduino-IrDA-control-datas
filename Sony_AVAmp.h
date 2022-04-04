#pragma once

// Sony製AVアンプ用リモコン RMT-AA401U （動作確認機種 STR-DH790）

// 信号フォーマットはSonyフォーマット (600us, 40kHz, 1/3Duty)

class CSony_AVAmp {
private:
  const int Repeat=3; // 3回送らないと認識しなかった
public:
  void Send_Sleep(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x1860,15,Repeat);
  }
  void Send_Information(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x8818,20,Repeat);
  }
  void Send_Power(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x1815,15,Repeat);
  }
  void Send_InputSelect_BlueTooth(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x28871,20,Repeat);
  }
  void Send_InputSelect_MediaBox(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x68840,20,Repeat);
  }
  void Send_InputSelect_BD_DVD(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x28816,20,Repeat);
  }
  void Send_InputSelect_SAT_CATV(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x5803,15,Repeat);
  }
  void Send_InputSelect_Game(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x187c,15,Repeat);
  }
  void Send_InputSelect_SACD_CD(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x1825,15,Repeat);
  }
  void Send_InputSelect_TV(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x186a,15,Repeat);
  }
  void Send_InputSelect_FM(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x1818,15,Repeat);
  }
  void Send_BluetoothPairing(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x28877,20,Repeat);
  }
  void Send_SoundField_2Ch_Multi(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x5847,15,Repeat);
  }
  void Send_SoundField_Movie(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x5843,15,Repeat);
  }
  void Send_SoundField_Music(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x5849,15,Repeat);
  }
  void Send_PureDirect(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x28879,20,Repeat);
  }
  void Send_FrontSurround(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x68839,20,Repeat);
  }
  void Send_NightMode(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x5820,15,Repeat);
  }
  void Send_Dimmer(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x184d,15,Repeat);
  }
  void Send_Display(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x184b,15,Repeat);
  }
  void Send_AmpMenu(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x5877,15,Repeat);
  }
  void Send_Cursor_Up(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x5878,15,Repeat);
  }
  void Send_Cursor_Down(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x5879,15,Repeat);
  }
  void Send_Cursor_Left(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x587a,15,Repeat);
  }
  void Send_Cursor_Right(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x587b,15,Repeat);
  }
  void Send_Cursor_Enter(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x180c,15,Repeat);
  }
  void Send_Back(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x887d,20,Repeat);
  }
  void Send_Home(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x1853,15,Repeat);
  }
  void Send_Option(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x8873,20,Repeat);
  }
  void Send_VolumeMute(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x1814,15,Repeat);
  }
  void Send_VolumeUp(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x1812,15,Repeat);
  }
  void Send_VolumeDown(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x1813,15,Repeat);
  }
  void Send_PlayRewind_TuningMinus(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x8833,20,Repeat);
  }
  void Send_PlayPause_TuningMemory(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x883a,20,Repeat);
  }
  void Send_PlayForward_TuningPlus(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x8834,20,Repeat);
  }
  void Send_PlayBack_PresetMinus(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x8830,20,Repeat);
  }
  void Send_PlayStop(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x8838,20,Repeat);
  }
  void Send_PlayNext_PresetPlus(const u8 pin)
  {
    IrDA_Sony_Send(pin,0x8831,20,Repeat);
  }
};

