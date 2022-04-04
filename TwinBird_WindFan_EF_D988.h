#pragma once

// TwinBird製扇風機 動作確認機種:EF-D988
static const u8 IrDA_NEC_Send_TwinBird_WindFan_EFD988_Off             =0x80; // OFF
static const u8 IrDA_NEC_Send_TwinBird_WindFan_EFD988_MinusIon        =0x82; // マイナスイオン
static const u8 IrDA_NEC_Send_TwinBird_WindFan_EFD988_LouverHorizontal=0x83; // ルーバー横
static const u8 IrDA_NEC_Send_TwinBird_WindFan_EFD988_OnChangeLevel   =0x84; // ON | 風量切替
static const u8 IrDA_NEC_Send_TwinBird_WindFan_EFD988_Mode            =0x85; // モード
static const u8 IrDA_NEC_Send_TwinBird_WindFan_EFD988_Timer           =0x86; // タイマー
static const u8 IrDA_NEC_Send_TwinBird_WindFan_EFD988_LouverVertical  =0x87; // ルーバー縦

// PowerOn: 0x81, 0xe3, 0x84, 0x7b (0x84==~0x7b)

static void IrDA_NEC_Send_TwinBird_WindFan_EFD988(const u8 pin,const u8 cmd)
{
  const u8 Maker1=0x81;
  const u8 Maker2=0xe3;
  
  IrDA_NEC_Send(pin,Maker1,Maker2,cmd);
  
  delay(2); // 最低1ms以上空ける
}

