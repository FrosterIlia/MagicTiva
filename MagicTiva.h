#include "tm4c123gh6pm.h" // device specific include file

#define ONE_MS_TICKS 1607

//GPIO pin definitions

#define PA0 ((0 << 3) | 0)
#define PA1 (1 << 3) | 0
#define PA2 (2 << 3) | 0
#define PA3 (3 << 3) | 0
#define PA4 (4 << 3) | 0
#define PA5 (5 << 3) | 0
#define PA6 (6 << 3) | 0
#define PA7 (7 << 3) | 0

#define PB0 (0 << 3) | 1
#define PB1 (1 << 3) | 1
#define PB2 (2 << 3) | 1
#define PB3 (3 << 3) | 1
#define PB4 (4 << 3) | 1
#define PB5 (5 << 3) | 1
#define PB6 (6 << 3) | 1
#define PB7 (7 << 3) | 1

#define PC0 (0 << 3) | 2
#define PC1 (1 << 3) | 2
#define PC2 (2 << 3) | 2
#define PC3 (3 << 3) | 2
#define PC4 (4 << 3) | 2
#define PC5 (5 << 3) | 2
#define PC6 (6 << 3) | 2
#define PC7 (7 << 3) | 2

#define PD0 (0 << 3) | 3
#define PD1 (1 << 3) | 3
#define PD2 (2 << 3) | 3
#define PD3 (3 << 3) | 3
#define PD4 (4 << 3) | 3
#define PD5 (5 << 3) | 3
#define PD6 (6 << 3) | 3
#define PD7 (7 << 3) | 3

#define PE0 (0 << 3) | 4
#define PE1 (1 << 3) | 4
#define PE2 (2 << 3) | 4
#define PE3 (3 << 3) | 4
#define PE4 (4 << 3) | 4
#define PE5 (5 << 3) | 4
#define PE6 (6 << 3) | 4
#define PE7 (7 << 3) | 4

#define PF0 (0 << 3) | 5
#define PF1 (1 << 3) | 5
#define PF2 (2 << 3) | 5
#define PF3 (3 << 3) | 5
#define PF4 (4 << 3) | 5
#define PF5 (5 << 3) | 5
#define PF6 (6 << 3) | 5
#define PF7 (7 << 3) | 5

#define SET 1
#define CLEAR 0

#define HIGH 1
#define LOW 0
#define ENABLE 1
#define DISABLE 0



typedef unsigned int uint;

//GPIO

#define INPUT 0
#define OUTPUT 1
#define ANALOG 2

void pinMode(uint8_t pin, uint8_t state);
void pinPullup(uint8_t pin, bool state);
void digitalWrite(uint8_t pin, bool value);
bool digitalRead(uint8_t pin);

typedef struct{
    uint8_t pins[8];
    volatile uint32_t clock_R;
    volatile uint32_t *DIR_R;
    volatile uint32_t *DEN_R;
    volatile uint32_t *DATA_R;
    volatile uint32_t *AFSEL_R;
    volatile uint32_t *AMSEL_R;
    volatile uint32_t *PCTL_R;
    volatile uint32_t *IS_R;
    volatile uint32_t *IBE_R;
    volatile uint32_t *IEV_R;
    uint8_t int_assgn; //interrupt assignment

} Port;

//Interrupts

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

//ADC

static const uint8_t analogPins[] = { PE3, PE2, PE1, PE0, PD3, PD2, PD1, PD0,
                                      PE5, PE4, PB4, PB5 };

bool isAnalog(uint8_t pin);
uint analogRead(uint8_t pin);

//Time utilities

void msDelay(unsigned int ms);

//Timers

#define PWM_MODE 0
#define ONE_SHOT_MODE 1
#define PERIODIC_MODE 2


#define CHANNEL_A 0
#define CHANNEL_B 1

#define DEFAULT_FREQ 1000
#define DEFAULT_DUTY 50

typedef struct{
    uint8_t pin;
    uint32_t PCTL_M;
    uint32_t PCTL_TCCP;

} TimerPin;

typedef struct{
    TimerPin pin1;
    TimerPin pin2;
} TimerPins;



typedef struct
{
    volatile uint32_t clockReg;
    volatile uint32_t *CTL_R;
    volatile uint32_t *CFG_R;
    volatile uint32_t *TMR_R; //TBMR
    volatile uint32_t *TILR_R; //TAILR
    volatile uint32_t *TMATCHR_R; //TAMATCHR
    volatile uint32_t *TPWML; // TAPWML
    volatile TimerPins *pins;

    uint8_t channel;

} TimerDev;


typedef struct{
    TimerDev timerDev;
    uint8_t pin;
    uint8_t mode;
    uint frequency;
    float duty_cycle;
    bool enabled;

} Timer;

TimerDev pinToTimer(uint8_t pin);
TimerPin getTimerPin(uint8_t pin);
int getTimerNumber(uint8_t pin);

void timerInit(Timer *timer, uint8_t pin, uint8_t mode);

void timerEnable(Timer *timer, bool state);
void timerUpdate(Timer *timer);
void generateSignal(Timer *timer, bool state);

int freqToTicks(float freq);


//UART

//SPI

//I2C

//Utilities

enum ports
{
    portA = 0, portB = 1, portC = 2, portD = 3, portE = 4, portF = 5
};

void changeRegister(volatile uint32_t *reg, uint32_t value, bool operation);
uint8_t getPinNumber(uint8_t pin);
uint8_t getPort(uint8_t pin);
