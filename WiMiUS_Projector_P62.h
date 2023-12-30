#pragma once

// WiMiUS製プロジェクタ 動作確認機種:P62
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_Power=0x0b;          // 電源ボタン
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_InputSelect=0x0c;    // 入力切り替え
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_Home=0x1a;           // HOME
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_CurEnter=0x1c;       // 決定
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_CurUp=0x50;          // カーソル上
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_CurLeft=0x51;        // カーソル左
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_CurRight=0x52;       // カーソル右
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_CurDown=0x53;        // カーソル下
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_Menu=0x17;           // メニュー
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_Back=0x15;           // 戻る
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_AutoAdjust=0xb6;     // 自動調整
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_VolumeDown=0x48;     // 音量下
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_VolumeUp=0x49;       // 音量上
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_Mute=0x14;           // ミュート
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_FocusPlus=0x56;      // フォーカス＋
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P62_FocusMinus=0x57;     // フォーカスー

static void IrDA_NEC_Send_WiMiUS_Projector_P62(const u8 pin,const u8 cmd)
{
  const u8 Maker1=0x08;
  const u8 Maker2=0xf7;
  
  IrDA_NEC_Send(pin,Maker1,Maker2,cmd);
}

