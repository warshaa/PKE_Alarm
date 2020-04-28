/* 
 * File:   functions.c
 * Author: Mahmoud Friaa
 * Warsha
 * Mfreaaaa@gmail.com
 * youtube.com/warshatube
 * Created on November 7, 2019, 12:22 PM
 */
#include "functions.h"


void Setup (void){
//---------- TIMERS AND FREQUENCY GENERATOR SETUP ----------
    TMR1ON=0;
    TMR1CS=0;           // INTERNAL COLCK
    T1CKPS0=1;
    T1CKPS1=1;          // PRESCALER 1:8 (12MHZ/8) OVERFLOW ~=0.087S
  // -- [[ Interrupts Configurations ]] --
  TMR1IE = 1; // Timer1 Interrupt Enable Bit
  TMR1IF = 0; // Clear The Interrupt Flag Bit
  PEIE = 1;   // Peripherals Interrupts Enable Bit
  GIE = 1;    // Global Interrupts Enable Bit
   //--[ Configure The CCP Module For PWM Mode ]--
  CCP1M3 = 1;
  CCP1M2 = 1;
  TRISC2 = 0; // The CCP1 Output Pin (PWM)
  // Set The PWM Frequency
  PR2 = 23;
  // Set The PS For Timer2 (1:1 Ratio)
  T2CKPS0 = 0;
  T2CKPS1 = 0;
  // set duty cycle
  // duty cycle = 64 =  0001000000 // 0100000000
    CCP1Y = 48&1;
    CCP1X = 48&2;
    CCPR1L = 48>>2;
    TMR2ON = 0; // timer 2 off
//---------- END OF TIMERS AND FREQUENCY GENERATOR SETUP ----------

    
//---------- BANKS AND PINS SETUP ----------   
    //1 input 0 output
    TRISA=0x00;
    TRISB=0b00000001;
    TRISE=0x00;
    TRISC=0xff;
    TRISD=0xff;
    PORTA=0x00;
    PORTB=0x00;
    TRISB=0b00000001;
    PORTE=0X00;

//---------- BANKS AND PINS SETUP ---------- 
  
 // --------- TIMER 0 SETTING --------------
//    T0CS=0; // LOCAL OSCILLATOR SOURCE
//    PSA =0; // PRESCALER IN SELECTED TO TIMER 0 
//    PS0=1;  // TIMER 0 PRESCALER TO 1:256
//    PS1=1;  // TIMER 0 PRESCALER TO 1:256
//    PS2=1;  // TIMER 0 PRESCALER TO 1:256
//    GIE=1;  // SET THE GIE PIN TO ENABLE THE INTERRUPT
//    INTEDG=1; // interrupt pin RB0 rising edge
 // ------- END OF TIMER 0 SETTING ----------

}
void Lock(void){
    DoorLock1    =1;
    __delay_ms(500);
    DoorLock1    =0;
    HazardHorn (1);
}

void UnLock(void){
    DoorLock2    =1;
    __delay_ms(500);
    DoorLock2    =0;
    HazardHorn (2);
}

void AlarmStart (void){
    int Attempt =0;
    if (EngineStart){
        IGNStart=0;
        ACC=0;
        __delay_ms(300);
    }
    else{
        while (!Handbrake && !EngineStart && (Attempt < 3)){
            Attempt++;
            IGNStart=1;
            ACC=1;
            __delay_ms(3000);
            Starter = 1;
            __delay_ms(1000);
            Starter=0;
            __delay_ms(3000);
                if (EngineStart){
                    FlagAlarmStart=1;
                    Timer1Step=0;
                    TMR1ON=1;
                    break;
                }
                else if (Attempt==3) {
                    IGNStart=0;
                    ACC=0;
                }
        }}
    }

void ButtonStart (void){
     
        if ( !Brake){
//            if (IGNStart){
//                IGNStart=0;
//                ACC=0;
//                __delay_ms(200);
//                FlagTimer=1;    // TO AUTO UNLOCK AFTER SWITCH STOP THE ENGINE
//                Timer1Step=0;   // AND LEAVING THE CAR
//                TMR1ON=1;}
                IGNStart=~IGNStart;
                ACC=~ACC;
                __delay_ms(1000);
        }
        else if (!EngineStart && Brake ){
                IGNStart=1;
                ACC=1;
                __delay_ms(2000);
                Starter = 1;
                __delay_ms(1000);
                Starter=0;
                __delay_ms(3000);

    }
}

void HazardHorn (int status){

    switch (status){
                    
        case 1 :            // LOCK
            HazardWire=1;
            HornWire=1;
            __delay_ms(300);
            HazardWire=0;
            HornWire=0;

            break;
        
        case 2 :           // UNLOCK
            HazardWire=1;
            HornWire=1;
            __delay_ms(300);
            HazardWire=0;
            HornWire=0;
            __delay_ms(300);
            HazardWire=1;
            HornWire=1;
            __delay_ms(300);
            HazardWire=0;
            HornWire=0;
        break;
        case 3 :          // IGN or door switch in ARM mode
            HazardWire=1;
            HornWire=1;
            __delay_ms(200);
            HazardWire=0;
            HornWire=0;
            __delay_ms(200);
            HazardWire=1;
            HornWire=1;
            __delay_ms(200);
            HazardWire=0;
            HornWire=0;
            __delay_ms(200);
            HazardWire=1;
            HornWire=1;
            __delay_ms(200);
            HazardWire=0;
            HornWire=0;
        break;
        case 4 :        // UNLOCK IN DISARM MODE
            HazardWire=1;
            HornWire=1;
            __delay_ms(600);
            HazardWire=0;
            HornWire=0;
            __delay_ms(600);

        break;
            
    }

}
bool RFIDChecker (){ 
   TMR2ON=1;
  for(int i=0; i<=10; i++){
      
      for ( i=0;i<=15;i++){                         //PATTERN 1
         Signal1 = pattern<<1;
          TRISC2 = Signal1;
          __delay_us(250);
      }
      
      for (int  k=0;k<=15;k++){                         // PATTERN2
          Signal2 = pattern2<<1;
          TRISC2 = Signal2;
          __delay_us(250); 
      }
      
       TRISC2 = 1;                                  // SEPERATE BETWEEN 2 SIGNALS
       __delay_ms(10);
      TRISC2 = 0;
      __delay_us(3800);                             // CARRIER BURST

      for (int j=0;j<=8;j++){                          // PREAMBLE
        TRISC2 = ~TRISC2;
        __delay_us(250);
      }
      
      __delay_ms(5);
if (AlarmButton == true){
    TMR2ON=0;
    return true;}
  }
    
TMR2ON=0;

    return false;
}
