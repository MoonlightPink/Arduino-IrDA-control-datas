#pragma once

static void IrDA_Sony_Send_ins_Pulse(u8 pin,int t,bool f)
{
  const u32 Time=t*600;
  if(!f){
    delayMicroseconds(Time);
    }else{
    const u32 EndTime=micros()+Time;
    while(micros()<EndTime){
      EspPD_DigitalWrite(pin,true);
      delayMicroseconds(9);
      EspPD_DigitalWrite(pin,false);
      delayMicroseconds(16);
    }
  }
}

static void IrDA_Sony_Send(const u8 pin,const u32 Data,const u8 DataLen,const int Repeat)
{
  noInterrupts();
  
  for(int loop=0;loop<Repeat;loop++){
    const u32 StartTime=micros();
    IrDA_Sony_Send_ins_Pulse(pin,4,true);
    IrDA_Sony_Send_ins_Pulse(pin,1,false);
    for(int idx=0;idx<DataLen;idx++){
      const u32 Tcnt=((Data&(1<<idx))!=0) ? 2 : 1;
      IrDA_Sony_Send_ins_Pulse(pin,Tcnt,true);
      IrDA_Sony_Send_ins_Pulse(pin,1,false);
    }
    const u32 SendTime=micros()-StartTime;
    const u32 RepeatFrameTime=45000;
    if(SendTime<RepeatFrameTime){ delayMicroseconds(RepeatFrameTime-SendTime); }
  }

  interrupts();
}

