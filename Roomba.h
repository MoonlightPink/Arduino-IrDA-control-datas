#pragma once

// 赤外線リモコン送信サンプル IR remote control sample for Roomba model.536

// http://astrobeano.blogspot.com/2013/11/raspberry-pi-ir-blaster-and-roomba-ir.html
// http://astrobeano.blogspot.com/2013/10/roomba-620-infrared-signals.html

// ref: Create Open Interface_v2.pdf Page.18

// 使用LED: 5mm赤外線LED 940nm グレー OSI5LA5113A
// 電源電圧5V, MosFet, 47Ω抵抗

// Arduino 1.8.9 ESP8266

// 38kHzの伝送波に、Duty比1/3で、1または0を送る。
// 1データ8bitsで、上位ビットから送る。
// データビットが0なら、Onを1ミリ秒、Offを3ミリ秒送る。
// データビットが1なら、Onを3ミリ秒、Offを1ミリ秒送る。

// 同じデータを、3～5回送らないと受理されない。（本物のリモコンも3回送っている）

const u8 RoombaIR_Left=129;
const u8 RoombaIR_Forward=130;
const u8 RoombaIR_Right=131;
const u8 RoombaIR_Spot=132;
const u8 RoombaIR_Max=133;
const u8 RoombaIR_Small=134;
const u8 RoombaIR_Medium=135;
const u8 RoombaIR_LargeClean=136; // 掃除を始める
const u8 RoombaIR_Pause=137;
const u8 RoombaIR_Power=138;
const u8 RoombaIR_ArcForwardLeft=139;
const u8 RoombaIR_ArcForwardRight=140;
const u8 RoombaIR_DriveStop=141;
const u8 RoombaIR_SendAll=142;
const u8 RoombaIR_SeekDock=143; // 充電台に戻る

const u8 RoombaIR_ForceField=161; // from home base.
const u8 RoombaIR_VirtualWall=162; // 立入禁止区域

const u8 RoombaIR_SendCountDef=5;

static void RoombaIR_SendData(const u8 pin,const u8 data8,const int count)
{
  for(int repeat=0;repeat<count;repeat++){
    u32 StartTime=micros();
    
    for(int idx=0;idx<8;idx++){
      bool bit=((data8 >> (7-idx)) & 1) != 0;

      StartTime+=bit ? 3000 : 1000;
      while(micros()<StartTime){
        EspPD_DigitalWrite(pin,true);
        delayMicroseconds(9);
        EspPD_DigitalWrite(pin,false);
        delayMicroseconds(16);
      }
      
      StartTime+=bit ? 1000 : 3000;
      while(micros()<StartTime){
      }
    }

    delay(50);
  }
}

