/* 
 * File:   functions.c
 * Author: Mahmoud Friaa
 * Warsha
 * Mfreaaaa@gmail.com
 * youtube.com/warshatube
 * Created on November 7, 2019, 12:22 PM
 */
#include "functions.h"

int main(int argc, char** argv) {    
Setup();
while (1){ 
    if (DoorButton && RFIDChecker()){
        __delay_ms(100);   
        DoorButton =0;
        UnLock();
            if (FlagAlarmStart == 1){
                FlagAlarmStart=0;
                TMR1ON=0;}       
                DISARM();
                
    __delay_ms(1000);
    }
    while (AlarmButton){
        __delay_ms(100);
        AlarmCounter ++;
  }
  
    if(AlarmCounter >0 && AlarmCounter <15){
        AlarmCounter=0;
        UnLock();
        DISARM();
  }
    
  
  else if (AlarmCounter >= 15){
        AlarmCounter=0;
        AlarmStart();
  }

if (!DoorSwitch || IGNStart ){
        TMR1ON=1;
        Timer1Step = 0;
        IGNStart=0;
            while((!DoorSwitch || IGNStart )&&!AlarmButton && (Timer1Step < 10)){
                HazardHorn(3);
    }
}
}
    
return (EXIT_SUCCESS);
}

void DISARM(void){
    while (1){
// if ((!LockButton || DoorButton)  ){
//  if ((AlarmButton || DoorButton || FlagTimeout)  ){
      if ((AlarmButton || DoorButton)  ){
        DoorButton =0;
        __delay_ms(10);
      if (DoorSwitch && !IGNStart){
    //    FlagTimer=0;
        Lock();
        break;
      }
      else{
      HazardHorn(3);
      }
}

 if (!StartButton ){
        ButtonStart();
}

    }
    }

void __interrupt () Timer0Inetrrupt (void) {
    
    
    if (INTF){ //External Interrupt detected
            DoorButton = 1;}
    if (TMR1IF){
        Timer1Step++;
        if (FlagAlarmStart ==1 && Timer1Step==3500){
            IGNStart=0;
            ACC=0;
            FlagAlarmStart=0;
            TMR1ON=0;
        }
        else if (FlagTimer==1 && Timer1Step==60 ){
            FlagTimeout=1;
            TMR1ON=0;
        }
//        else if (Timer1Step==1000){
//            TMR1ON=0;
//        }
    }
    TMR1IF=0;
    INTF = 0;
}


