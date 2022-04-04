#pragma once

// 三菱製扇風機 動作確認機種:R30J-RM
static const u8 IrDA_AEHA_Send_Mitsubishi_WindFan_Command_Power          =0x01; // 電源
static const u8 IrDA_AEHA_Send_Mitsubishi_WindFan_Command_FastWind       =0x02; // 強
static const u8 IrDA_AEHA_Send_Mitsubishi_WindFan_Command_SwingHorizontal=0x03; // 首振り左右
static const u8 IrDA_AEHA_Send_Mitsubishi_WindFan_Command_OffTimer       =0x04; // 切タイマー
static const u8 IrDA_AEHA_Send_Mitsubishi_WindFan_Command_Mode           =0x05; // モード
static const u8 IrDA_AEHA_Send_Mitsubishi_WindFan_Command_OnTimer        =0x0a; // 入タイマー
static const u8 IrDA_AEHA_Send_Mitsubishi_WindFan_Command_NextLevel      =0x0b; // 順次強
static const u8 IrDA_AEHA_Send_Mitsubishi_WindFan_Command_PrevLevel      =0x0c; // 順次弱
static const u8 IrDA_AEHA_Send_Mitsubishi_WindFan_Command_SwingVertical  =0x0e; // 首振り上下

static void IrDA_AEHA_Send_Mitsubishi_WindFan(const u8 pin,const u8 cmd)
{
  const u8 Maker1=0x23;
  const u8 Maker2=0xcb;
  const u8 Parity=(Maker1&0x0f)^(Maker1>>4)^(Maker2&0x0f)^(Maker2>>4); // is 0x6
  const u8 Magic1=0x1;
  const u8 Magic2=0x44;
  const u8 Magic3=0x80;
  const u8 Magic4=0x89;
  const u8 CheckCode=(0x80+(cmd<<4))&0xf0;
  
  IrDA_AEHA_Send(pin,Maker1,Maker2,Parity,Magic1,Magic2,Magic3,Magic4,cmd,CheckCode);
}

