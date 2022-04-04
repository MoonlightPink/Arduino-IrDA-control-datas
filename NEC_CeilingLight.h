#pragma once

class CNEC_CeilingLight {
private:
  static const u8 Ch2_OffsetFromCh1=0x80;
public:
  static const u8 CustomCode1=0x82;
  static const u8 CustomCode2=0x6d;
  static const u8 Ch1_SleepTimer30mins=0x05;
  static const u8 Ch1_SleepTimer60mins=0x06;
  static const u8 Ch1_NightLight=0x18;
  static const u8 Ch1_FullLight=0x1f;
  static const u8 Ch1_Dimming=0x16;
  static const u8 Ch1_Next=0x1a;
  static const u8 Ch1_Off=0x1e;
  static const u8 Ch2_SleepTimer30mins=Ch2_OffsetFromCh1+Ch1_SleepTimer30mins;
  static const u8 Ch2_SleepTimer60mins=Ch2_OffsetFromCh1+Ch1_SleepTimer60mins;
  static const u8 Ch2_NightLight=Ch2_OffsetFromCh1+Ch1_NightLight;
  static const u8 Ch2_FullLight=Ch2_OffsetFromCh1+Ch1_FullLight;
  static const u8 Ch2_Dimming=Ch2_OffsetFromCh1+Ch1_Dimming;
  static const u8 Ch2_Next=Ch2_OffsetFromCh1+Ch1_Next;
  static const u8 Ch2_Off=Ch2_OffsetFromCh1+Ch1_Off;
};

