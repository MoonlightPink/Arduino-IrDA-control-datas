#pragma once

static void IrDA_NEC_Send_ins_Pulse(u8 pin,int t,bool f)
{
  const u32 OnTime=t*562;
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

static void IrDA_NEC_Send_ins_Byte(u8 pin,u8 Data)
{
  for(int idx=0;idx<8;idx++){
    IrDA_NEC_Send_ins_Pulse(pin,1,true);
    const bool f=(Data&0x01)!=0x00;
    IrDA_NEC_Send_ins_Pulse(pin,f?3:1,false);
    Data>>=1;
  }
}

static void IrDA_NEC_Send(u8 pin,u8 MakerCode1,u8 MakerCode2,u8 Data)
{
  noInterrupts();
  
  IrDA_NEC_Send_ins_Pulse(pin,16,true);
  IrDA_NEC_Send_ins_Pulse(pin,8,false);

  IrDA_NEC_Send_ins_Byte(pin,MakerCode1);
  IrDA_NEC_Send_ins_Byte(pin,MakerCode2);
  
  IrDA_NEC_Send_ins_Byte(pin,Data);
  IrDA_NEC_Send_ins_Byte(pin,~Data);
  
  IrDA_NEC_Send_ins_Pulse(pin,1,true);

  interrupts();
}

