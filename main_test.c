#include "MagicTiva.h"
#include "tm4c123gh6pm.h" // device specific include file

#define BUTTON PF4
#define SW1 BIT4

#define YELLOW (RED| GREEN)
#define WHITE (RED | GREEN | BLUE)

#define RED BIT1
#define BLUE BIT2 // blue LED connected to Port F bit 2
#define GREEN BIT3

#define JOYSTICK_Y PD2
#define JOYSTICK_X PB5

#define AIN4 BIT3  // Analog input channel 7 connects to Port D Pin 0

#define ADC_CHAN 4 // Perform analog sampling on channel 7

Interrupt myInterrupt;
Timer redPWM;

Timer greenPWM;

int main(void)
{
    // allow a few cycles for clock to start
    _delay_cycles(5);

    pinMode(PF3, OUTPUT);
    pinMode(PB3, OUTPUT);
    pinMode(PC4, OUTPUT);
    pinMode(BUTTON, INPUT);
    pinPullup(BUTTON, 1);

    pinMode(JOYSTICK_X, ANALOG);
    pinMode(JOYSTICK_Y, ANALOG);

    //Initialize the timer

    timerInit(&redPWM, PF3, PWM_MODE);
    redPWM.frequency = 1000;
    redPWM.duty_cycle = 0.03;

    timerUpdate(&redPWM);

    timerEnable(&redPWM, true);

    //Initialize green LED timer
    timerInit(&greenPWM, PC4, PWM_MODE);
    greenPWM.frequency = 1000;
    greenPWM.duty_cycle = 0.03;

    timerUpdate(&greenPWM);

    timerEnable(&greenPWM, true);


    //Initialize interrupt

    initInterrupt(&myInterrupt, PF4);
    enableInterrupt(&myInterrupt, HIGH);


    //generate PWM
    generateSignal(&greenPWM, true);
    generateSignal(&redPWM, true);

    while (1)
    {
        //generateSignal(&greenPWM, true);



    }
}

void PortFISR()
{
    msDelay(10);

    if (GPIO_PORTF_MIS_R & SW1)
    {
        generateSignal(&redPWM, false);
        digitalWrite(PF3, HIGH);
        msDelay(300);
        digitalWrite(PF3, LOW);
        generateSignal(&redPWM, true);

    }
    GPIO_PORTF_ICR_R = GPIO_PORTF_MIS_R;
    _delay_cycles(5);
}
