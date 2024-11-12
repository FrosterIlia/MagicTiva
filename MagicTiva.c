#include "MagicTiva.h"

//GPIO

const Port ports[] = { { .pins = { PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7 },
                         .clock_R = SYSCTL_RCGCGPIO_R0, .DIR_R =
                                 &GPIO_PORTA_DIR_R,
                         .DEN_R = &GPIO_PORTA_DEN_R, .DATA_R =
                                 &GPIO_PORTA_DATA_R,
                         .AFSEL_R = &GPIO_PORTA_AFSEL_R, .AMSEL_R =
                                 &GPIO_PORTA_AMSEL_R,
                         .PCTL_R = &GPIO_PORTA_PCTL_R, .IS_R = &GPIO_PORTA_IS_R,
                         .IBE_R = &GPIO_PORTA_IBE_R, .IEV_R = &GPIO_PORTA_IEV_R,
                         .int_assgn = INT_GPIOA }, // Port A

        { .pins = { PA0, PB1, PB2, PB3, PB4, PB5, PB6, PB7 }, .clock_R =
        SYSCTL_RCGCGPIO_R1,
          .DIR_R = &GPIO_PORTB_DIR_R, .DEN_R = &GPIO_PORTB_DEN_R, .DATA_R =
                  &GPIO_PORTB_DATA_R,
          .AFSEL_R = &GPIO_PORTB_AFSEL_R, .AMSEL_R = &GPIO_PORTB_AMSEL_R,
          .PCTL_R = &GPIO_PORTB_PCTL_R, .IS_R = &GPIO_PORTB_IS_R, .IBE_R =
                  &GPIO_PORTB_IBE_R,
          .IEV_R = &GPIO_PORTB_IEV_R, .int_assgn = INT_GPIOB }, // Port B

        { .pins = { PC0, PC1, PC2, PC3, PC4, PC5, PC6, PC7 }, .clock_R =
        SYSCTL_RCGCGPIO_R2,
          .DIR_R = &GPIO_PORTC_DIR_R, .DEN_R = &GPIO_PORTC_DEN_R, .DATA_R =
                  &GPIO_PORTC_DATA_R,
          .AFSEL_R = &GPIO_PORTC_AFSEL_R, .AMSEL_R = &GPIO_PORTC_AMSEL_R,
          .PCTL_R = &GPIO_PORTC_PCTL_R, .IS_R = &GPIO_PORTC_IS_R, .IBE_R =
                  &GPIO_PORTC_IBE_R,
          .IEV_R = &GPIO_PORTC_IEV_R, .int_assgn = INT_GPIOC }, // Port C

        { .pins = { PD0, PD1, PD2, PD3, PD4, PD5, PD6, PD7 }, .clock_R =
        SYSCTL_RCGCGPIO_R3,
          .DIR_R = &GPIO_PORTD_DIR_R, .DEN_R = &GPIO_PORTD_DEN_R, .DATA_R =
                  &GPIO_PORTD_DATA_R,
          .AFSEL_R = &GPIO_PORTD_AFSEL_R, .AMSEL_R = &GPIO_PORTD_AMSEL_R,
          .PCTL_R = &GPIO_PORTD_PCTL_R, .IS_R = &GPIO_PORTD_IS_R, .IBE_R =
                  &GPIO_PORTD_IBE_R,
          .IEV_R = &GPIO_PORTD_IEV_R, .int_assgn = INT_GPIOD }, // Port D

        { .pins = { PE0, PE1, PE2, PE3, PE4, PE5, PE6, PE7 }, .clock_R =
        SYSCTL_RCGCGPIO_R4,
          .DIR_R = &GPIO_PORTE_DIR_R, .DEN_R = &GPIO_PORTE_DEN_R, .DATA_R =
                  &GPIO_PORTE_DATA_R,
          .AFSEL_R = &GPIO_PORTE_AFSEL_R, .AMSEL_R = &GPIO_PORTE_AMSEL_R,
          .PCTL_R = &GPIO_PORTE_PCTL_R, .IS_R = &GPIO_PORTE_IS_R, .IBE_R =
                  &GPIO_PORTE_IBE_R,
          .IEV_R = &GPIO_PORTE_IEV_R, .int_assgn = INT_GPIOE }, // Port E

        { .pins = { PF0, PF1, PF2, PF3, PF4, PF5, PF6, PF7 }, .clock_R =
        SYSCTL_RCGCGPIO_R5,
          .DIR_R = &GPIO_PORTF_DIR_R, .DEN_R = &GPIO_PORTF_DEN_R, .DATA_R =
                  &GPIO_PORTF_DATA_R,
          .AFSEL_R = &GPIO_PORTF_AFSEL_R, .AMSEL_R = &GPIO_PORTF_AMSEL_R,
          .PCTL_R = &GPIO_PORTF_PCTL_R, .IS_R = &GPIO_PORTF_IS_R, .IBE_R =
                  &GPIO_PORTF_IBE_R,
          .IEV_R = &GPIO_PORTF_IEV_R, .int_assgn = INT_GPIOF } }; // Port F

void pinMode(uint8_t pin, uint8_t mode)
{
    uint8_t pinNumber = getPinNumber(pin);
    uint8_t port = getPort(pin);

    if (mode == ANALOG)
    {
        if (!isAnalog(pin))
        {
            return;
        }

        //activate clock
        SYSCTL_RCGCADC_R |= SYSCTL_RCGCADC_R0;

        switch (port)
        {
        case portB:
            SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
            changeRegister(&GPIO_PORTB_AFSEL_R, pinNumber, 1);
            changeRegister(&GPIO_PORTB_DEN_R, pinNumber, 0);
            changeRegister(&GPIO_PORTB_AMSEL_R, pinNumber, 1);
            break;
        case portD:
            SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
            changeRegister(&GPIO_PORTD_AFSEL_R, pinNumber, 1);
            changeRegister(&GPIO_PORTD_DEN_R, pinNumber, 0);
            changeRegister(&GPIO_PORTD_AMSEL_R, pinNumber, 1);
            break;

        case portE:
            SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
            changeRegister(&GPIO_PORTE_AFSEL_R, pinNumber, 1);
            changeRegister(&GPIO_PORTE_DEN_R, pinNumber, 0);
            changeRegister(&GPIO_PORTE_AMSEL_R, pinNumber, 1);
            break;
        }
    }

    else
    {
        // if mode is digital
        switch (port)
        {
        case portA: // Port A
            // activate clock
            SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
            changeRegister(&GPIO_PORTA_DEN_R, pinNumber, 1);
            changeRegister(&GPIO_PORTF_DIR_R, pinNumber, 1 ? mode : 0);

            break;

        case portB:                // Port B
            // activate clock
            SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
            changeRegister(&GPIO_PORTB_DEN_R, pinNumber, 1);
            changeRegister(&GPIO_PORTF_DIR_R, pinNumber, 1 ? mode : 0);

            break;

        case portC:                // Port C
            // activate clock
            SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
            changeRegister(&GPIO_PORTC_DEN_R, pinNumber, 1);
            changeRegister(&GPIO_PORTF_DIR_R, pinNumber, 1 ? mode : 0);

            break;

        case portD:                // Port D
            // activate clock
            SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
            changeRegister(&GPIO_PORTD_DEN_R, pinNumber, 1);
            changeRegister(&GPIO_PORTF_DIR_R, pinNumber, 1 ? mode : 0);

            break;

        case portE:                // Port E
            // activate clock
            SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
            changeRegister(&GPIO_PORTE_DEN_R, pinNumber, 1);
            changeRegister(&GPIO_PORTF_DIR_R, pinNumber, 1 ? mode : 0);

            break;

        case portF:                // Port F
            // activate clock
            SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
            changeRegister(&GPIO_PORTF_DEN_R, pinNumber, 1);
            changeRegister(&GPIO_PORTF_DIR_R, pinNumber, 1 ? mode : 0);

            break;
        }
    }

}

void pinPullup(uint8_t pin, bool state)
{
    uint8_t pinNumber = getPinNumber(pin);
    uint8_t port = getPort(pin);
    switch (port)
    {
    case portA: // Port A
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
        changeRegister(&GPIO_PORTA_PUR_R, pinNumber, state);
        break;

    case portB: // Port B
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
        changeRegister(&GPIO_PORTB_PUR_R, pinNumber, state);

        break;

    case portC: // Port C
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
        changeRegister(&GPIO_PORTC_PUR_R, pinNumber, state);

        break;

    case portD: // Port D
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
        changeRegister(&GPIO_PORTD_PUR_R, pinNumber, state);

        break;

    case portE: // Port E
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
        changeRegister(&GPIO_PORTE_PUR_R, pinNumber, state);
        break;

    case portF: // Port F
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
        changeRegister(&GPIO_PORTF_PUR_R, pinNumber, state);

        break;
    }
}
void digitalWrite(uint8_t pin, bool state)
{
    uint8_t pinNumber = getPinNumber(pin);
    uint8_t port = getPort(pin);
    switch (port)
    {
    case portA: // Port A
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
        changeRegister(&GPIO_PORTA_DATA_R, pinNumber, state);
        break;

    case portB: // Port B
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
        changeRegister(&GPIO_PORTB_DATA_R, pinNumber, state);

        break;

    case portC: // Port C
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
        changeRegister(&GPIO_PORTC_DATA_R, pinNumber, state);

        break;

    case portD: // Port D
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
        changeRegister(&GPIO_PORTD_DATA_R, pinNumber, state);

        break;

    case portE: // Port E
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
        changeRegister(&GPIO_PORTE_DATA_R, pinNumber, state);

        break;

    case portF: // Port F
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
        changeRegister(&GPIO_PORTF_DATA_R, pinNumber, state);
        break;
    }
}

bool digitalRead(uint8_t pin)
{
    uint8_t pinNumber = getPinNumber(pin);
    uint8_t port = getPort(pin);
    switch (port)
    {
    case portA: // Port A
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
        if (GPIO_PORTA_DATA_R & pinNumber)
            return true;
        return false;

    case portB: // Port B
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
        if (GPIO_PORTB_DATA_R & pinNumber)
            return true;
        return false;

    case portC: // Port C
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
        if (GPIO_PORTC_DATA_R & pinNumber)
            return true;
        return false;

    case portD: // Port D
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
        if (GPIO_PORTD_DATA_R & pinNumber)
            return true;
        return false;

    case portE: // Port E
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
        if (GPIO_PORTE_DATA_R & pinNumber)
            return true;
        return false;

    case portF: // Port F
        // activate clock
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
        if (GPIO_PORTF_DATA_R & pinNumber)
            return true;
        return false;

    }
    return false;
}

void initInterrupt(Interrupt *intrpt, uint8_t pin)
{
    intrpt->triggerSource = EDGE;
    intrpt->triggerType = SINGLE_EDGE_TRIGGER;
    intrpt->edge = RISING;
    intrpt->pin = pin;
    updateInterrupt(intrpt);
    IntMasterEnable();
    uint8_t pinNumber = getPinNumber(pin);
    uint8_t port = getPort(pin);

    switch (port)
    {
    case portA:
        IntEnable(INT_GPIOA);
        break;
    case portB:
        IntEnable(INT_GPIOB);
        break;
    case portC:
        IntEnable(INT_GPIOC);
        break;
    case portD:
        IntEnable(INT_GPIOD);
        break;
    case portE:
        IntEnable(INT_GPIOE);
        break;
    case portF:
        IntEnable(INT_GPIOF);
        break;
    }

}

void enableInterrupt(Interrupt *intrpt, bool value)
{
    changeRegister(&GPIO_PORTF_IM_R, getPinNumber(intrpt->pin), value);
}

void updateInterrupt(Interrupt *intrpt)
{
    uint8_t pinNumber = getPinNumber(intrpt->pin);
    uint8_t port = getPort(intrpt->pin);

    switch (port)
    {
    case portA:
        changeRegister(&GPIO_PORTA_IS_R, pinNumber, intrpt->triggerSource); // Chooses whether it is edge or level sensitive
        changeRegister(&GPIO_PORTA_IBE_R, pinNumber, intrpt->triggerType); // Chooses if one edge will trigger an interrupt or two
        changeRegister(&GPIO_PORTA_IEV_R, pinNumber, intrpt->edge); // Chooses which edge will trigger an interrupt

        break;
    case portB:
        changeRegister(&GPIO_PORTB_IS_R, pinNumber, intrpt->triggerSource); // Chooses whether it is edge or level sensitive
        changeRegister(&GPIO_PORTB_IBE_R, pinNumber, intrpt->triggerType); // Chooses if one edge will trigger an interrupt or two
        changeRegister(&GPIO_PORTB_IEV_R, pinNumber, intrpt->edge); // Chooses which edge will trigger an interrupt
        break;
    case portC:
        changeRegister(&GPIO_PORTC_IS_R, pinNumber, intrpt->triggerSource); // Chooses whether it is edge or level sensitive
        changeRegister(&GPIO_PORTC_IBE_R, pinNumber, intrpt->triggerType); // Chooses if one edge will trigger an interrupt or two
        changeRegister(&GPIO_PORTC_IEV_R, pinNumber, intrpt->edge); // Chooses which edge will trigger an interrupt
        break;
    case portD:
        changeRegister(&GPIO_PORTD_IS_R, pinNumber, intrpt->triggerSource); // Chooses whether it is edge or level sensitive
        changeRegister(&GPIO_PORTD_IBE_R, pinNumber, intrpt->triggerType); // Chooses if one edge will trigger an interrupt or two
        changeRegister(&GPIO_PORTD_IEV_R, pinNumber, intrpt->edge); // Chooses which edge will trigger an interrupt
        break;
    case portE:
        changeRegister(&GPIO_PORTE_IS_R, pinNumber, intrpt->triggerSource); // Chooses whether it is edge or level sensitive
        changeRegister(&GPIO_PORTE_IBE_R, pinNumber, intrpt->triggerType); // Chooses if one edge will trigger an interrupt or two
        changeRegister(&GPIO_PORTE_IEV_R, pinNumber, intrpt->edge); // Chooses which edge will trigger an interrupt
        break;
    case portF:
        changeRegister(&GPIO_PORTF_IS_R, pinNumber, intrpt->triggerSource); // Chooses whether it is edge or level sensitive
        changeRegister(&GPIO_PORTF_IBE_R, pinNumber, intrpt->triggerType); // Chooses if one edge will trigger an interrupt or two
        changeRegister(&GPIO_PORTF_IEV_R, pinNumber, intrpt->edge); // Chooses which edge will trigger an interrupt
        break;
    }

}

// ADC

volatile int adcResult; // used to hold ADC result

uint analogRead(uint8_t pin)
{
    uint8_t pinNumber = getPinNumber(pin);

    if (!isAnalog(pin))
    {
        return 0;
    }

    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN3;  // disable sample sequencer 3

    // set for software trigger on sequencer 3
    ADC0_EMUX_R = (ADC0_EMUX_R & ~ADC_EMUX_EM3_M) | ADC_EMUX_EM3_PROCESSOR;

    ADC0_SSMUX3_R = pinNumber;     // select analog input channel ???
    ADC0_SSCTL3_R = ADC_SSCTL3_IE0 | ADC_SSCTL3_END0; // set for single sample and enable raw interrupt bit
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN3;  // enable sample sequencer 3

    ADC0_PSSI_R = ADC_PSSI_SS3; // start sample sequencer 3

    while ((ADC0_RIS_R & ADC_RIS_INR3) == 0)
    {
    }  // wait for conversion sequence to complete

    adcResult = ADC0_SSFIFO3_R;  // retrieve ADC conversion result

    ADC0_ISC_R = ADC_ISC_IN3;  // clear the interrupt flag

    return adcResult;
}

bool isAnalog(uint8_t pin)
{
    // check if pin is analog
    for (int i = 0; i < sizeof(analogPins) / sizeof(uint8_t); i++)
    {
        if (analogPins[i] == pin)
        {
            return true;
        }
    }
    return false;
}

// Timers

const TimerPins timerPinsTable[] = { { .pin1 = { .pin = PB6,
                                           .PCTL_M = GPIO_PCTL_PB6_M,
                                           .PCTL_TCCP = GPIO_PCTL_PB6_T0CCP0 },
                                 .pin2 = { .pin = PF0,
                                           .PCTL_M = GPIO_PCTL_PF0_M,
                                           .PCTL_TCCP = GPIO_PCTL_PF0_T0CCP0 } }, // Timer0A

        { .pin1 = { .pin = PB7, .PCTL_M = GPIO_PCTL_PB7_M, .PCTL_TCCP =
        GPIO_PCTL_PB7_T0CCP1 },
          .pin2 = { .pin = PF1, .PCTL_M = GPIO_PCTL_PF1_M, .PCTL_TCCP =
          GPIO_PCTL_PF1_T0CCP1 } }, // Timer0B

        { .pin1 = { .pin = PF2, .PCTL_M = GPIO_PCTL_PF2_M, .PCTL_TCCP =
        GPIO_PCTL_PF2_T1CCP0 },
          .pin2 = { .pin = PB4, .PCTL_M = GPIO_PCTL_PB4_M, .PCTL_TCCP =
          GPIO_PCTL_PB4_T1CCP0 } }, // Timer1A

        { .pin1 = { .pin = PF3, .PCTL_M = GPIO_PCTL_PF3_M, .PCTL_TCCP =
        GPIO_PCTL_PF3_T1CCP1 },
          .pin2 = { .pin = PB5, .PCTL_M = GPIO_PCTL_PB5_M, .PCTL_TCCP =
          GPIO_PCTL_PB5_T1CCP1 } }, // Timer1B

        { .pin1 = { .pin = PF4, .PCTL_M = GPIO_PCTL_PF4_M, .PCTL_TCCP =
        GPIO_PCTL_PF4_T2CCP0 },
          .pin2 = { .pin = PB0, .PCTL_M = GPIO_PCTL_PB0_M, .PCTL_TCCP =
          GPIO_PCTL_PB0_T2CCP0 } }, // Timer2A

        { .pin1 = { .pin = PB1, .PCTL_M = GPIO_PCTL_PB1_M, .PCTL_TCCP =
        GPIO_PCTL_PB1_T2CCP1 } }, // Timer2B

        { .pin1 = { .pin = PB2, .PCTL_M = GPIO_PCTL_PB2_M, .PCTL_TCCP =
        GPIO_PCTL_PB2_T3CCP0 } }, // Timer3A

        { .pin1 = { .pin = PB3, .PCTL_M = GPIO_PCTL_PB3_M, .PCTL_TCCP =
        GPIO_PCTL_PB3_T3CCP1 } }, // Timer3B

        { .pin1 = { .pin = PC0, .PCTL_M = GPIO_PCTL_PC0_M, .PCTL_TCCP =
        GPIO_PCTL_PC0_T4CCP0 } }, // Timer4A

        { .pin1 = { .pin = PC1, .PCTL_M = GPIO_PCTL_PC1_M, .PCTL_TCCP =
        GPIO_PCTL_PC1_T4CCP1 } }, // Timer4B

        { .pin1 = { .pin = PC2, .PCTL_M = GPIO_PCTL_PC2_M, .PCTL_TCCP =
        GPIO_PCTL_PC2_T5CCP0 } }, // Timer5A

        { .pin1 = { .pin = PC3, .PCTL_M = GPIO_PCTL_PC3_M, .PCTL_TCCP =
        GPIO_PCTL_PC3_T5CCP1 } }, // Timer5B

        { .pin1 = { .pin = PC4, .PCTL_M = GPIO_PCTL_PC4_M, .PCTL_TCCP =
        GPIO_PCTL_PC4_WT0CCP0 } }, // TimerW0A

        { .pin1 = { .pin = PC5, .PCTL_M = GPIO_PCTL_PC5_M, .PCTL_TCCP =
        GPIO_PCTL_PC5_WT0CCP1 } } // TimerW0B

};

const TimerDev timers[] = {

{ .clockReg = SYSCTL_RCGCTIMER_R0, .CTL_R = &TIMER0_CTL_R, .CFG_R =
          &TIMER0_CFG_R,
  .TMR_R = &TIMER0_TAMR_R, .TILR_R = &TIMER0_TAILR_R, .TMATCHR_R =
          &TIMER0_TAMATCHR_R,
  .TPWML = TIMER_CTL_TAPWML, .pins = &timerPinsTable[0], .channel = CHANNEL_A }, //TIMER0_A

        { .clockReg = SYSCTL_RCGCTIMER_R0, .CTL_R = &TIMER0_CTL_R, .CFG_R =
                  &TIMER0_CFG_R,
          .TMR_R = &TIMER0_TBMR_R, .TILR_R = &TIMER0_TBILR_R, .TMATCHR_R =
                  &TIMER0_TBMATCHR_R,
          .TPWML = TIMER_CTL_TBPWML, .pins = &timerPinsTable[1], .channel =
          CHANNEL_B }, //TIMER0_B

        { .clockReg = SYSCTL_RCGCTIMER_R1, .CTL_R = &TIMER1_CTL_R, .CFG_R =
                  &TIMER1_CFG_R,
          .TMR_R = &TIMER1_TAMR_R, .TILR_R = &TIMER1_TAILR_R, .TMATCHR_R =
                  &TIMER1_TAMATCHR_R,
          .TPWML = TIMER_CTL_TAPWML, .pins = &timerPinsTable[2], .channel =
          CHANNEL_A }, //TIMER1_A

        { .clockReg = SYSCTL_RCGCTIMER_R1, .CTL_R = &TIMER1_CTL_R, .CFG_R =
                  &TIMER1_CFG_R,
          .TMR_R = &TIMER1_TBMR_R, .TILR_R = &TIMER1_TBILR_R, .TMATCHR_R =
                  &TIMER1_TBMATCHR_R,
          .TPWML = TIMER_CTL_TBPWML, .pins = &timerPinsTable[3], .channel =
          CHANNEL_B }, //TIMER1_B
        { .clockReg = SYSCTL_RCGCTIMER_R2, .CTL_R = &TIMER2_CTL_R, .CFG_R =
                  &TIMER2_CFG_R,
          .TMR_R = &TIMER2_TAMR_R, .TILR_R = &TIMER2_TAILR_R, .TMATCHR_R =
                  &TIMER2_TAMATCHR_R,
          .TPWML = TIMER_CTL_TAPWML, .pins = &timerPinsTable[4], .channel =
          CHANNEL_A }, //TIMER2_A

        { .clockReg = SYSCTL_RCGCTIMER_R2, .CTL_R = &TIMER2_CTL_R, .CFG_R =
                  &TIMER2_CFG_R,
          .TMR_R = &TIMER2_TBMR_R, .TILR_R = &TIMER2_TBILR_R, .TMATCHR_R =
                  &TIMER2_TBMATCHR_R,
          .TPWML = TIMER_CTL_TBPWML, .pins = &timerPinsTable[5], .channel =
          CHANNEL_B }, //TIMER2_B

        { .clockReg = SYSCTL_RCGCTIMER_R3, .CTL_R = &TIMER3_CTL_R, .CFG_R =
                  &TIMER3_CFG_R,
          .TMR_R = &TIMER3_TAMR_R, .TILR_R = &TIMER3_TAILR_R, .TMATCHR_R =
                  &TIMER3_TAMATCHR_R,
          .TPWML = TIMER_CTL_TAPWML, .pins = &timerPinsTable[6], .channel =
          CHANNEL_A }, //TIMER3_A

        { .clockReg = SYSCTL_RCGCTIMER_R3, .CTL_R = &TIMER3_CTL_R, .CFG_R =
                  &TIMER3_CFG_R,
          .TMR_R = &TIMER3_TBMR_R, .TILR_R = &TIMER3_TBILR_R, .TMATCHR_R =
                  &TIMER3_TBMATCHR_R,
          .TPWML = TIMER_CTL_TBPWML, .pins = &timerPinsTable[7], .channel =
          CHANNEL_B }, //TIMER3_B

        { .clockReg = SYSCTL_RCGCTIMER_R4, .CTL_R = &TIMER4_CTL_R, .CFG_R =
                  &TIMER4_CFG_R,
          .TMR_R = &TIMER2_TAMR_R, .TILR_R = &TIMER4_TAILR_R, .TMATCHR_R =
                  &TIMER4_TAMATCHR_R,
          .TPWML = TIMER_CTL_TAPWML, .pins = &timerPinsTable[8], .channel =
          CHANNEL_A }, //TIMER4_A

        { .clockReg = SYSCTL_RCGCTIMER_R4, .CTL_R = &TIMER4_CTL_R, .CFG_R =
                  &TIMER4_CFG_R,
          .TMR_R = &TIMER4_TBMR_R, .TILR_R = &TIMER4_TBILR_R, .TMATCHR_R =
                  &TIMER4_TBMATCHR_R,
          .TPWML = TIMER_CTL_TBPWML, .pins = &timerPinsTable[9], .channel =
          CHANNEL_B }, //TIMER4_B

        { .clockReg = SYSCTL_RCGCTIMER_R5, .CTL_R = &TIMER5_CTL_R, .CFG_R =
                  &TIMER5_CFG_R,
          .TMR_R = &TIMER5_TAMR_R, .TILR_R = &TIMER5_TAILR_R, .TMATCHR_R =
                  &TIMER5_TAMATCHR_R,
          .TPWML = TIMER_CTL_TAPWML, .pins = &timerPinsTable[10], .channel =
          CHANNEL_A }, //TIMER5_A

        { .clockReg = SYSCTL_RCGCTIMER_R5, .CTL_R = &TIMER5_CTL_R, .CFG_R =
                  &TIMER5_CFG_R,
          .TMR_R = &TIMER5_TBMR_R, .TILR_R = &TIMER5_TBILR_R, .TMATCHR_R =
                  &TIMER5_TBMATCHR_R,
          .TPWML = TIMER_CTL_TBPWML, .pins = &timerPinsTable[11], .channel =
          CHANNEL_B }, //TIMER5_B

        //Wide Timers
        { .clockReg = SYSCTL_RCGCWTIMER_R0, .CTL_R = &WTIMER0_CTL_R, .CFG_R =
                  &WTIMER0_CFG_R,
          .TMR_R = &WTIMER0_TAMR_R, .TILR_R = &WTIMER0_TAILR_R, .TMATCHR_R =
                  &WTIMER0_TAMATCHR_R,
          .TPWML = TIMER_CTL_TAPWML, .pins = &timerPinsTable[12], .channel =
          CHANNEL_A }, //TIMERW0_A

        { .clockReg = SYSCTL_RCGCWTIMER_R0, .CTL_R = &WTIMER0_CTL_R, .CFG_R =
                  &WTIMER0_CFG_R,
          .TMR_R = &WTIMER0_TBMR_R, .TILR_R = &WTIMER0_TBILR_R, .TMATCHR_R =
                  &WTIMER0_TBMATCHR_R,
          .TPWML = TIMER_CTL_TBPWML, .pins = &timerPinsTable[13], .channel =
          CHANNEL_B }, //TIMERW0_B

        };

int freqToTicks(float freq)
{
    return 16 * 1000 * (1 / freq) - 1;
}

void timerInit(Timer *timer, uint8_t pin, uint8_t mode)
{

    timer->mode = mode;
    timer->frequency = DEFAULT_FREQ;
    timer->duty_cycle = DEFAULT_DUTY;
    timer->pin = pin;
    timer->timerDev = pinToTimer(pin);

    if (getTimerNumber(timer->pin) < 12)
    {
        SYSCTL_RCGCTIMER_R |= timer->timerDev.clockReg; // activate the clock
    }
    else
    {
        SYSCTL_RCGCWTIMER_R |= timer->timerDev.clockReg; // activate the clock
    }

    switch (mode)
    {
    case PWM_MODE:
        if (timer->timerDev.channel == CHANNEL_A)
        {
            *timer->timerDev.CTL_R &= ~TIMER_CTL_TAEN; // disable timer
            *timer->timerDev.CFG_R = TIMER_CFG_16_BIT; // configure in 16-bit mode
            *timer->timerDev.TMR_R = ((*timer->timerDev.TMR_R
                    & ~TIMER_TAMR_TAMR_M) | TIMER_TAMR_TAMR_PERIOD
                    | TIMER_TAMR_TAAMS) & ~TIMER_TAMR_TACMR; // configure in periodic mode

            *timer->timerDev.CTL_R |= TIMER_CTL_TAPWML; // inverted or not inverted
        }
        else
        {
            *timer->timerDev.CTL_R &= ~TIMER_CTL_TBEN; // disable timer
            *timer->timerDev.CFG_R = TIMER_CFG_16_BIT; // configure in 16-bit mode
            *timer->timerDev.TMR_R = ((*timer->timerDev.TMR_R
                    & ~TIMER_TBMR_TBMR_M) | TIMER_TBMR_TBMR_PERIOD
                    | TIMER_TBMR_TBAMS) & ~TIMER_TBMR_TBCMR; // configure in periodic mode

            *timer->timerDev.CTL_R |= TIMER_CTL_TBPWML;
        }

        break;

    case ONE_SHOT_MODE:

        break;

    case PERIODIC_MODE:

        break;
    }
}

const TimerDev emptyTimerDev;

void timerEnable(Timer *timer, bool state)
{
    if (timer->timerDev.channel == CHANNEL_A)
    {
        changeRegister(timer->timerDev.CTL_R, TIMER_CTL_TAEN, state);
        //*timer->timerDev.CTL_R |= TIMER_CTL_TAEN;
    }
    else
    {
        changeRegister(timer->timerDev.CTL_R, TIMER_CTL_TBEN, state);
        //*timer->timerDev.CTL_R |= TIMER_CTL_TBEN;
    }
    timer->enabled = state;
}

void timerUpdate(Timer *timer)
{

    if (timer->timerDev.channel == CHANNEL_A)
    {
        *timer->timerDev.CTL_R &= ~TIMER_CTL_TAEN; // disable timer
        *timer->timerDev.TILR_R = freqToTicks(timer->frequency); //20MHz * (1/250)
        *timer->timerDev.TMATCHR_R = *timer->timerDev.TILR_R
                * timer->duty_cycle;   // 50% duty cycle
    }
    else
    {
        *timer->timerDev.CTL_R &= ~TIMER_CTL_TBEN; // disable timer
        *timer->timerDev.TILR_R = freqToTicks(timer->frequency); //20MHz * (1/250)
        *timer->timerDev.TMATCHR_R = *timer->timerDev.TILR_R
                * timer->duty_cycle;   // 50% duty cycle
    }
    if (timer->enabled)
        timerEnable(timer, true);
}

void generateSignal(Timer *timer, bool state)
{

    uint8_t pinNumber = getPinNumber(timer->pin);
    uint8_t portNumber = getPort(timer->pin);
    TimerPin timerPin = getTimerPin(timer->pin);

    if (state)
    {
        *ports[portNumber].AFSEL_R |= pinNumber;
        *ports[portNumber].PCTL_R = (*ports[portNumber].PCTL_R
                & ~(timerPin.PCTL_M)) | timerPin.PCTL_TCCP;
    }
    else
    {
        *ports[portNumber].AFSEL_R &= ~pinNumber;
    }

}

TimerPin emptyTimerPin;

TimerPin getTimerPin(uint8_t pin)
{
    for (uint8_t i = 0; i < sizeof(timerPinsTable) / sizeof(timerPinsTable[0]);
            i++)
    {
        if (pin == timerPinsTable[i].pin1.pin)
        {
            return timerPinsTable[i].pin1;
        }
        else if (pin == timerPinsTable[i].pin2.pin)
        {
            return timerPinsTable[i].pin2;
        }
    }
    return emptyTimerPin;
}

int getTimerNumber(uint8_t pin)
{
    for (uint8_t i = 0; i < sizeof(timerPinsTable) / sizeof(timerPinsTable[0]);
            i++)

    {
        if (pin == timerPinsTable[i].pin1.pin
                || pin == timerPinsTable[i].pin2.pin)
        {
            return i;
        }
    }
    return -1;
}

TimerDev pinToTimer(uint8_t pin)
{
    for (uint8_t i = 0; i < sizeof(timerPinsTable) / sizeof(timerPinsTable[0]);
            i++)

    {
        if (pin == timerPinsTable[i].pin1.pin
                || pin == timerPinsTable[i].pin2.pin)
        {
            return timers[i];
        }
    }
    return emptyTimerDev;
}

////////////////////////////////////////////////////////////
// msDelay - Function to generate a variable delay
// Arguments: ms - The number of milliseconds for the delay
// Return Value: none
////////////////////////////////////////////////////////////
void msDelay(unsigned int ms)
{
// loop for the desired number of ms
    while (ms > 0)
    {
        int i = 0;
        for (i = 0; i <= ONE_MS_TICKS; i++)
        {
            continue;
        }
        ms--;
    }
}

uint8_t getPinNumber(uint8_t pin)
{
    return 1 << (pin >> 3);
}

uint8_t getPort(uint8_t pin)
{
    return pin & 0b00000111;
}

void changeRegister(volatile uint32_t *reg, uint32_t value, bool operation)
{
    if (operation)
        *reg |= value;
    else
        *reg &= ~value;
}
