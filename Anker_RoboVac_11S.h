
// IrDA format for Anker RoboVac 11S
// 2020/12/01 Moonlight

// Data set: 48bits (6bytes)
// Byte order: Big endian

// 0..7 MakerCode (0x68)
// 8..11 Command
// 12..15 Suction power level
// 16..23 Current hours
// 24..31 Current minutes
// 32..39 Schedule time ((Hours*4)+(Minutes/15)) Disabled:0xff
// 40..47 CheckSum ((1+2+3+4+5)&0xff)

// StartBit On: 3000msecs
// StartBit Off: 3000msecs
// SendData Bit0 On: 530msecs
// SendData Bit0 Off: 460msecs
// SendData Bit1 On: 530msecs
// SendData Bit1 Off: 1450msecs
// StopBit On: 530msecs
// StopBit Off: 20000msec

// Send the same data 3 times.

// Caution. This has not been confirmed to work with time and schedule.

class CAnker_RoboVac_11S {
private:
  const u8 MakerCode=0x68;

  u8 IrSendPin=0xff;
  
  u8 CurrentHours=0;
  u8 CurrentMinutes=0;
  
  u8 CurrentSchedule=ScheduleDisabled;

  void SendIrDA_ins_sendbody(u32 ontime,u32 offtime)
  {
    const u8 pin=IrSendPin;
    
    u32 StartTime=micros();
    
    ontime+=StartTime;
    while(micros()<ontime){
      EspPD_DigitalWrite(pin,true);
      delayMicroseconds(9);
      EspPD_DigitalWrite(pin,false);
      delayMicroseconds(16);
    }
    StartTime=ontime;
    
    if(offtime!=0){
      offtime+=StartTime;
      while(micros()<offtime){
      }
    }
  }

  void SendIrDA_ins_sendbyte(u8 data)
  {
    for(int idx=0;idx<8;idx++){
      if((data&0x80)==0){
        SendIrDA_ins_sendbody(530,460);
        }else{
        SendIrDA_ins_sendbody(530,1450);
      }
      data<<=1;
    }
  }

  void SendIrDA(const u8 Command,const u8 SuctionPowerLevel)
  {
    yield();
    noInterrupts();

    for(int loop=0;loop<3;loop++){
      SendIrDA_ins_sendbody(3000,3000);

      u8 data;
      u8 checksum=0x00;

      data=MakerCode;
      checksum+=data;
      SendIrDA_ins_sendbyte(data);
      
      data=Command | SuctionPowerLevel;
      checksum+=data;
      SendIrDA_ins_sendbyte(data);
      
      data=CurrentHours;
      checksum+=data;
      SendIrDA_ins_sendbyte(data);
      
      data=CurrentMinutes;
      checksum+=data;
      SendIrDA_ins_sendbyte(data);
      
      data=CurrentSchedule;
      checksum+=data;
      SendIrDA_ins_sendbyte(data);

      SendIrDA_ins_sendbyte(checksum&0xff);
      
      SendIrDA_ins_sendbody(530,0);
      delay(20);
    }
    
    interrupts();
    yield();
    
    delay(500);
  }

public:
  const u8 SuctionPowerLevel_Stop=0x0f;
  const u8 SuctionPowerLevel_Standard=0x0e;
  const u8 SuctionPowerLevel_BoostIQ=0x0d;
  const u8 SuctionPowerLevel_Max=0x0c;

  const u8 ScheduleDisabled=0xff;

  void SetIrSendPin(const u8 _IrSendPin)
  {
    IrSendPin=_IrSendPin;
  }

  void SetCurrentTime(const u8 _CurrentHours,const u8 _CurrentMinutes)
  {
    CurrentHours=_CurrentHours;
    CurrentMinutes=_CurrentMinutes;
  }

  void SetSchedule(const u8 Hours,const u8 Minutes)
  {
    CurrentSchedule=(Hours*4)+(Minutes/15);
  }

  void SendStartAutoCleaning(const u8 SuctionPowerLevel) // 自動モードの開始
  {
    SendIrDA(0x00,SuctionPowerLevel);
  }
  void SendStartAutoCleaningStopCleaning_Start(const u8 SuctionPowerLevel) // 自動モードの開始
  {
    SendIrDA(0x50,SuctionPowerLevel);
  }
  void SendStartAutoCleaningStopCleaning_Stop(void) // 掃除の停止
  {
    SendIrDA(0x40,SuctionPowerLevel_Stop);
  }
  void SendStartSpotCleaning(void) // スポットモードの開始
  {
    SendIrDA(0x80,SuctionPowerLevel_Max);
  }
  void SendStartEdgeCleaning(void) // エッジモードの開始
  {
    SendIrDA(0x90,SuctionPowerLevel_Max);
  }
  void SendAdjustSuctionPowerLevelInAutoOrSingleRoomCleaningMode(const u8 SuctionPowerLevel) // 自動モード / シングルルームモードで吸引レベルを調整する
  {
    SendIrDA(0x10,SuctionPowerLevel);
  }
  void SendControlCleaningDirectionManually_Up(const u8 SuctionPowerLevel) // 手動で掃除の方向を調整
  {
    SendIrDA(0x20,SuctionPowerLevel);
  }
  void SendControlCleaningDirectionManually_Left(const u8 SuctionPowerLevel)
  {
    SendIrDA(0x30,SuctionPowerLevel);
  }
  void SendControlCleaningDirectionManually_Right(const u8 SuctionPowerLevel)
  {
    SendIrDA(0x60,SuctionPowerLevel);
  }
  void SendControlCleaningDirectionManually_Down(const u8 SuctionPowerLevel)
  {
    SendIrDA(0x70,SuctionPowerLevel);
  }
  void SendStartSingleRoomCleaning(const u8 SuctionPowerLevel) // シングルルームモードの開始
  {
    SendIrDA(0xa0,SuctionPowerLevel);
  }
  void SendSetCurrentTime(const u8 SuctionPowerLevel) // 現在時刻設定
  {
    SendIrDA(0xb0,SuctionPowerLevel);
  }
  void SendScheduleAutoCleaningStartTime_SetTime(const u8 SuctionPowerLevel) // 掃除の予約をする
  {
    SendIrDA(0xc0,SuctionPowerLevel);
  }
  void SendScheduleAutoCleaningStartTime_Cancel(const u8 SuctionPowerLevel) // 掃除の予約をキャンセルする
  {
    CurrentSchedule=ScheduleDisabled;
    SendIrDA(0xd0,SuctionPowerLevel);
  }
  void SendReturnRoboVacToChargingBase(void) // RoboVacを充電ステーションに戻す
  {
    SendIrDA(0xe0,SuctionPowerLevel_Stop);
  }
};

static CAnker_RoboVac_11S Anker_RoboVac_11S;

// sch cancel
// 0 68
// 1 DF
// 2 00
// 3 01
// 4 FF
// 5 47


