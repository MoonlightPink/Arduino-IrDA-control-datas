#pragma once

// WiMiUS製プロジェクタ 動作確認機種:P28
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_Power=0x0c;          // 電源ボタン
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_Mute=0x0d;           // 音声ミュート
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_InputSelect=0x0e;    // 入力切り替え
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_CurUp=0x10;          // カーソル上
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_CurLeft=0x11;        // カーソル左
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_CurEnter=0x12;       // 決定
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_CurRight=0x13;       // カーソル右
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_CurDown=0x14;        // カーソル下
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_Menu=0x16;           // メニュー
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_Back=0x17;           // 戻る
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_PlayPause=0x18;      // 再生一時停止
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_ZoomMode=0x1c;       // ズームモード
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_HighBrightMode=0x1d; // 高輝度モード
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_VolumeDown=0x1e;     // 音量下
static const u8 IrDA_NEC_Send_WiMiUS_Projector_P28_VolumeUp=0x1f;       // 音量上

static void IrDA_NEC_Send_WiMiUS_Projector_P28(const u8 pin,const u8 cmd)
{
  const u8 Maker1=0xb8;
  const u8 Maker2=0x57;
  
  IrDA_NEC_Send(pin,Maker1,Maker2,cmd);
}

