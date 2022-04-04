
// ASTEX AX-KH43用 赤外線リモコン送信テスト 2019/11/23
// ex> IrDA_AXKH43_Send(IrDA_OutputPin,AXKH43_IrCode_PowerToggle);

static const u8 AXKH43_MakerCode1=0x00;
static const u8 AXKH43_MakerCode2=0x7f;

static const u8 AXKH43_IrCode_PowerToggle=0x1c; // 電源(トグル)
static const u8 AXKH43_IrCode_ChangeInput=0x18; // 入力切替
static const u8 AXKH43_IrCode_Num1=0x54; // Num1
static const u8 AXKH43_IrCode_Num2=0x16; // Num2
static const u8 AXKH43_IrCode_Num3=0x15; // Num3
static const u8 AXKH43_IrCode_Num4=0x14; // Num4
static const u8 AXKH43_IrCode_Num5=0x50; // Num5
static const u8 AXKH43_IrCode_Num6=0x12; // Num6
static const u8 AXKH43_IrCode_Num7=0x11; // Num7
static const u8 AXKH43_IrCode_Num8=0x10; // Num8
static const u8 AXKH43_IrCode_Num9=0x4c; // Num9
static const u8 AXKH43_IrCode_Num10=0x0e; // Num10
static const u8 AXKH43_IrCode_Num11=0x0d; // Num11
static const u8 AXKH43_IrCode_Num12=0x0c; // Num12
static const u8 AXKH43_IrCode_DigitalTV=0x5c; // 地デジ
static const u8 AXKH43_IrCode_BS=0x58; // BS
static const u8 AXKH43_IrCode_CS=0x40; // CS
static const u8 AXKH43_IrCode_ProgramInfo=0x56; // 番組情報
static const u8 AXKH43_IrCode_ProgramList=0x1e; // 番組表
static const u8 AXKH43_IrCode_ShowDisplay=0x4e; // 画面表示
static const u8 AXKH43_IrCode_VolumePlus=0x4b; // 音量+
static const u8 AXKH43_IrCode_VolumeMinus=0x4f; // 音量-
static const u8 AXKH43_IrCode_dData=0x4a; // dデータ
static const u8 AXKH43_IrCode_Input3Digits=0x17; // 3桁入力
static const u8 AXKH43_IrCode_Mute=0x08; // 消音
static const u8 AXKH43_IrCode_ChannelUp=0x09; // チャンネル上
static const u8 AXKH43_IrCode_ChannelDown=0x05; // チャンネル下
static const u8 AXKH43_IrCode_Menu=0x49; // メニュー
static const u8 AXKH43_IrCode_SubMenu=0x02; // サブメニュー
static const u8 AXKH43_IrCode_CurLeft=0x47; // CurLeft
static const u8 AXKH43_IrCode_CurUp=0x1a; // CurUp
static const u8 AXKH43_IrCode_Ok=0x06; // 決定
static const u8 AXKH43_IrCode_CurDown=0x48; // CurDown
static const u8 AXKH43_IrCode_CurRight=0x07; // CurRight
static const u8 AXKH43_IrCode_Back=0x0a; // 戻る
static const u8 AXKH43_IrCode_End=0x88; // 終了
static const u8 AXKH43_IrCode_Blue=0x55; // Blue
static const u8 AXKH43_IrCode_Red=0x5d; // Red
static const u8 AXKH43_IrCode_Green=0x59; // Green
static const u8 AXKH43_IrCode_Yellow=0x51; // Yellow
static const u8 AXKH43_IrCode_DisplaySize=0x1f; // 画面サイズ
static const u8 AXKH43_IrCode_SubTitle=0x5e; // 字幕
static const u8 AXKH43_IrCode_ChangeAudio=0x5a; // 音声切替
static const u8 AXKH43_IrCode_Capture=0x41; // 静止
static const u8 AXKH43_IrCode_Record=0x1d; // 録画
static const u8 AXKH43_IrCode_RecordList=0x1b; // 録画リスト
static const u8 AXKH43_IrCode_Stop=0x01; // 停止
static const u8 AXKH43_IrCode_PlayPause=0x41; // 再生/一時停止
static const u8 AXKH43_IrCode_PowerSaving=0x52; // 省電力
static const u8 AXKH43_IrCode_ReservationList=0x03; // 予約リスト
static const u8 AXKH43_IrCode_Rewind=0x5f; // 早戻し
static const u8 AXKH43_IrCode_Forward=0x5b; // 早送り
static const u8 AXKH43_IrCode_Rewind10Secs=0x67; // 10秒戻し
static const u8 AXKH43_IrCode_Forward30Secs=0x66; // 30秒送り
static const u8 AXKH43_IrCode_BackChapter=0x53; // 前へ
static const u8 AXKH43_IrCode_NextChapter=0x57; // 次へ
static const u8 AXKH43_IrCode_HDMI1=0x04; // HDMI1
static const u8 AXKH43_IrCode_HDMI2=0x62; // HDMI2
static const u8 AXKH43_IrCode_HDMI3=0x63; // HDMI3
static const u8 AXKH43_IrCode_HDMI4=0x64; // HDMI4

static const u8 AXKH43_IrCode_Hidden_OffTimer=0x42; // オフタイマー (Off/30/60/90mins)
static const u8 AXKH43_IrCode_Hidden_SelectVideo=0x45; // 入力切り替えをビデオに
static const u8 AXKH43_IrCode_Hidden_Capture=0x46; // 静止(0x41)と同じ

static void IrDA_AXKH43_Send(u8 pin,u8 Data)
{
  IrDA_NEC_Send(pin,AXKH43_MakerCode1,AXKH43_MakerCode2,Data);
}

