# MagicTiva

## Description
The purpose of this library is to create a higher level of abstraction and simplify the process of developing an embedded device with TM4C123GH6PM. The library lets programmers to not worry about registers and focus on the logic of their code instead of reading endless documentation. 

The library supports use of such peripherals as GPIO, Timers, ADC, Interrupts, UART, I2C.

## Installation 
To install the library, you need to import files: MagicTiva.c, MagicTiva.h, driverlib.lib and tm4c123gh6pm.h into your project and include it in your code
```
#include "MagicTiva.h"
#include "tm4c123gh6pm.h" // device specific include file
```

## GPIO
Note that to use any pin, pinMode() has to be called first, then depending on the current mode on the pin, other functions may be used.
```
#define INPUT 0
#define OUTPUT 1
#define ANALOG 2

void pinMode(uint8_t pin, uint8_t state);
void pinPullup(uint8_t pin, bool state) // Enables pullup resistor;
void digitalWrite(uint8_t pin, bool value) // Sets the level on the pin;
bool digitalRead(uint8_t pin); // Reads the level from the pin
uint analogRead(uint8_t pin);
```


## Interrupts
To create an interrupt, you have to initialize a struct Interrupt and set the parameters for it. Then initInterrupt() initialises the interrupt, and updateInterrupt has to be called every time, you want to apply any changes. Changes can be applied by assigning values to the Timer struct.
```
#define EDGE 0
#define LEVEL 1

#define RISING 1
#define FALLING 0

#define SINGLE_EDGE_TRIGGER 0
#define DOUBLE_EDGE_TRIGGER 1

typedef struct
{
    uint8_t pin;
    bool triggerSource; // Chooses whether it is edge or level sensitive
    bool triggerType; // Chooses if one edge will trigger an interrupt or two
    bool edge; // Rising or Falling

} Interrupt;

void initInterrupt(Interrupt *intrpt, uint8_t pin);
void enableInterrupt(Interrupt *intrpt, bool value);
void updateInterrupt(Interrupt *intrpt);
```
## Timers 

```
#define PWM_MODE 0
#define ONE_SHOT_MODE 1
#define PERIODIC_MODE 2

typedef struct{
    TimerDev timerDev;
    uint8_t pin;
    uint8_t mode;
    uint frequency;
    float duty_cycle;
    bool enabled;

} Timer;

void timerInit(Timer *timer, uint8_t pin, uint8_t mode);
void timerEnable(Timer *timer, bool state);
void timerUpdate(Timer *timer);
void generateSignal(Timer *timer, bool state);
```


## Time Utilities

```
void msDelay(unsigned int ms); // creates a delay assuming core frequency is 16MHz
```
