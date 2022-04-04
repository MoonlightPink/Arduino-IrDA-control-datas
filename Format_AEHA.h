#pragma once

static void IrDA_AEHA_Send_ins_Pulse(u8 pin,int t,bool f)
{
  const u32 OnTime=t*425;
  if(!f){
    delayMicroseconds(OnTime);
    }else{
    const u32 EndTime=micros()+OnTime;
    while(micros()<EndTime){
      EspPD_DigitalWrite(pin,true);
      delayMicroseconds(9);
      EspPD_DigitalWrite(pin,false);
      delayMicroseconds(17);
    }
  }
}

static void IrDA_AEHA_Send_ins_Byte(u8 pin,u8 Data)
{
  for(int idx=0;idx<8;idx++){
    IrDA_AEHA_Send_ins_Pulse(pin,1,true);
    const bool f=(Data&0x01)!=0x00;
    IrDA_AEHA_Send_ins_Pulse(pin,f?3:1,false);
    Data>>=1;
  }
}

static void IrDA_AEHA_Send(u8 pin,u8 MakerCode1,u8 MakerCode2,u8 Parity,u8 Data0,u8 Data1,u8 Data2,u8 Data3,u8 Data4,u8 Data5)
{
  noInterrupts();
  
  IrDA_AEHA_Send_ins_Pulse(pin,8,true);
  IrDA_AEHA_Send_ins_Pulse(pin,4,false);

  IrDA_AEHA_Send_ins_Byte(pin,MakerCode1);
  IrDA_AEHA_Send_ins_Byte(pin,MakerCode2);
  
  IrDA_AEHA_Send_ins_Byte(pin,Parity | (Data0<<4));
  IrDA_AEHA_Send_ins_Byte(pin,Data1);
  IrDA_AEHA_Send_ins_Byte(pin,Data2);
  IrDA_AEHA_Send_ins_Byte(pin,Data3);
  IrDA_AEHA_Send_ins_Byte(pin,Data4);
  IrDA_AEHA_Send_ins_Byte(pin,Data5);
  
  IrDA_AEHA_Send_ins_Pulse(pin,1,true);

  interrupts();

  delay(7); // 連続して送るときは7ms以上のオフ時間が必要
}

