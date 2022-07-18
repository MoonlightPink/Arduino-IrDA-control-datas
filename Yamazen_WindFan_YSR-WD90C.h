#pragma once

// Example: IrDA_Yamazen_WindFan_YSR_WD90C(PinIrDA,IrDA_Yamazen_WindFan_YSR_WD90C_Power);

// 山善製扇風機 動作確認機種:YSR-WD90C
static const u8 IrDA_Yamazen_WindFan_YSR_WD90C_AutoHorizontal=0xc0; // 横方向首振り
static const u8 IrDA_Yamazen_WindFan_YSR_WD90C_Timer         =0xa0; // オフタイマー
static const u8 IrDA_Yamazen_WindFan_YSR_WD90C_Power         =0x80; // 電源
static const u8 IrDA_Yamazen_WindFan_YSR_WD90C_TempSensor    =0x60; // 温度センサー連動
static const u8 IrDA_Yamazen_WindFan_YSR_WD90C_WindLevelPlus =0x40; // 風量+
static const u8 IrDA_Yamazen_WindFan_YSR_WD90C_Rhythm        =0x20; // リズム風

static void IrDA_Yamazen_WindFan_YSR_WD90C(const u8 pin,const u8 cmd)
{
  IrDA_AEHA_SendRaw(pin,0x06,0xa3,0x7f,cmd);
}

/*
static void IrDA_AEHA_SendRaw(u8 pin,u8 MakerCode1,u8 MakerCode2,u8 Data0,u8 Data1)
{
  noInterrupts();
  
  IrDA_AEHA_Send_ins_Pulse(pin,8,true);
  IrDA_AEHA_Send_ins_Pulse(pin,4,false);

  IrDA_AEHA_Send_ins_Byte(pin,MakerCode1);
  IrDA_AEHA_Send_ins_Byte(pin,MakerCode2);
  
  IrDA_AEHA_Send_ins_Byte(pin,Data0);
  IrDA_AEHA_Send_ins_Byte(pin,Data1);
  
  IrDA_AEHA_Send_ins_Pulse(pin,1,true);

  interrupts();

  delay(7); // 連続して送るときは7ms以上のオフ時間が必要
}

*/

