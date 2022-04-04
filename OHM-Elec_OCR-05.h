
// オーム電機 赤外線リモコンコンセント OCR-05 リモコン信号送信テストコード
// 2021/01/25 Moonlight

// OCR-05Wは動作未確認です。

// 256通りしかないので、256回送ってリレーがONまたはOFFする数値を探してください。
// 総当たりするコードはOCR05_SendTestを参考にしてください。

static void OCR05_SendPulse(const u8 pin,u32 ontime,u32 offtime)
{
  if(ontime!=0){
    ontime+=micros();
    while(micros()<ontime){
      EspPD_DigitalWrite(pin,true);
      delayMicroseconds(9);
      EspPD_DigitalWrite(pin,false);
      delayMicroseconds(16);
    }
  }

  if(offtime!=0){ delayMicroseconds(offtime); }
}

static void OCR05_SendData(const u8 pin,u8 data)
{
  for(int loop=0;loop<3;loop++){ // 念のため3回送る
    OCR05_SendPulse(pin,2580,2670);

    const u32 ontime=830;
    
    for(int idx=0;idx<8;idx++){
      const u32 offtime=((data&1)!=0) ? 1900 : 850;
      OCR05_SendPulse(pin,ontime,offtime);
      data>>=1;
    }
    
    OCR05_SendPulse(pin,ontime,0);

    delay(5); // 念のため5ミリ秒開ける
  }
}

static void OCR05_SendOn(const u8 pin)
{
  OCR05_SendData(pin,0x3c); // 私のはこの数値でした
}

static void OCR05_SendOff(const u8 pin)
{
  OCR05_SendData(pin,0xd2); // 私のはこの数値でした
}

static void OCR05_SendTest(const u8 pin)
{
  for(int data=0;data<0x100;data++){
    Serial.println("SendData("+String(pin)+","+String(data)+");");
    OCR05_SendData(pin,data);
    delay(1000);
    yield();
  }
}

