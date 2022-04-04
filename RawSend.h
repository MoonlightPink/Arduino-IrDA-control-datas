#pragma once

static void IrSend(const u8 pin,const u32 datalen,const u16 data[])
{
  yield();
  noInterrupts();
  
  u32 StartTime=micros();
  for(u32 idx=0;idx<datalen/2;idx++){
    u32 ontime=data[idx*2+0];
    ontime+=StartTime;
    while(micros()<ontime){
      EspPD_DigitalWrite(pin,true);
      delayMicroseconds(9);
      EspPD_DigitalWrite(pin,false);
      delayMicroseconds(16);
    }
    StartTime=ontime;
    
    u32 offtime=data[idx*2+1];
    if(offtime==0){ break; }
    offtime+=StartTime;
    while(micros()<offtime){
    }
    StartTime=offtime;
  }
  
  interrupts();
  yield();
}

