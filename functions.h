/* 
 * File:   functions.c
 * Author: Mahmoud Friaa
 * Warsha
 * Mfreaaaa@gmail.com
 * youtube.com/warshatube
 * Created on November 7, 2019, 12:22 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "config.h"
#include <pic16f877a.h>
#include <stdbool.h>
#include <xc.h>


#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

// PORT B OUTPUT
#define DoorLock1       RB1  // DOOR LOCK WIRE     RELAY
#define DoorLock2       RB2  // DOOR LCOK WIRE     RELAY
#define ACC             RB3  // ACC                RELAY    ACTIVATE LOW -220mA
#define IGNStart        RB4  // IGNITION START WIRE     RELAY
#define Starter         RB5  // STARTER WIRE        RELAY
#define HazardWire      RA0  // HAZARD WIRE         RELAY
#define HornWire        RA1  // Horn
#define DomeLight       RA2   // INTERIOR LIGHT     output low
#define DisArmOutput    RA3   // extra optional output when car is Disarmed
#define ArmOutput       RA4   // extra optional output when car is Aarmed
#define ParkingLight    RA5   // PARKING LIGHT
// PORT D INPUT
#define DoorSwitch       RC1   // CHECK DOORS OPEN OR NOT  - Trigger
#define Handbrake        RC3   // CHECK HANDBRAKE ON OR NOT - Trigger
#define StartButton      RD0   // PUSH START BUTTON TO START THE ENGINE - Trigger
//#define DoorButton       RB0   // DOOR BUTTON TO ACTIVATE THE RFID ANTENNA -Trigger
#define IGN              RD2   // CHECK IGNITION ON OR NOT + Trigger
#define Nutral           RD7   // THE GEAR IS ON NUTRAL POSITION  + trigger
#define LockButton       RD3   // ALARM LOCK BUTTON SIGNAL _ trigger was RD6
#define AlarmStartButton RD4  // the start button of the alarm - trigger was rd3
#define UnLockButton     RD5   // ALARM UNLOCK BUTTON SIGNAL - trigger
#define RFIDbutton       RD6   // ALARM UNLOCK BUTTON SIGNrAL    - trigge
#define EngineStart      RC5   // CHECK IF THE ENGINE IS RUNNING OR NOT + Trigger
#define Brake            RC4   // the brake pedal                     +Trigger
#define AlarmButton      RC6   // ANY SIGNAL FROM ALARM
// ----------- signal output-----------//
//
//-------------end of signal-----------//

// CURRENTLY THE SIGNAL IS NOT CORRECT 
// JUST OUTPUTS UNODULATRD 125KHZ SIGNAL
// 125khz signal setup
/* data structure
* 3.8 mS Burst
*preamble 01010101010
* pattern1
* pattern2
* Manchester '1'=> HL , '0'=>LH
*/ 
//uint16_t pattern=  0x12; //0x12
//uint16_t pattern2= 0x34; //0x34
uint16_t Signal1=  0x00; //0x12
uint16_t Signal2=  0x00; //0x34
uint16_t pattern = 0b1001101001101010;  // 0x12 not 
uint16_t pattern2= 0b1010011001011010; // 0x34 not  

// variables
uint8_t  AlarmCounter=0;
int      Timer1Step;
bool     FlagAlarmStart=0;                    // flag for alarm start
bool     FlagTimeout=0;                      //  FLAG Auto Lock
bool     FlagTimer=0;    
bool     DoorButton;
//
void Setup(void);               // SETUP FUNCTION
void Lock(void);                // LOCK THE DOORs
void UnLock (void);             // UNLOCK THE DOORs
void AlarmStart (void);         // START THE CAR USING THE ALARM
void ButtonStart (void);        // START THE CAR USING ENGINE PUSH BUTTON
void HazardHorn (int status);   // TURN ON HAZARD AND HORN
void DISARM(void);              // DISARM MODE // THE MAIN FUNCTION IS THE ARM MODE
bool RFIDChecker (void);        // check if PKE tag is around

#endif

