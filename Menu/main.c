#include "driverlib/pin_map.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "driverlib/uart.h"

//#define PWM_FREQUENCY 55
#define PWM_FREQUENCY 1000

int main(void)
{
    volatile uint32_t ui32Load;
    volatile uint32_t ui32PWMClock;
    volatile uint32_t ui8Adjust;
    volatile uint32_t blueAdjust;

    //test variables
    volatile uint32_t sysclock;
    volatile uint32_t pwmclock;
    volatile uint32_t pwmwidth;
    volatile uint32_t pwmperiod;
    volatile uint32_t bluewidth;
    volatile uint32_t blueperiod;
    ui8Adjust = 2;
    blueAdjust = 50;


    //UART CODE
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    //END UART CODE

    SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2); //TEST2
    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    GPIOPinConfigure(GPIO_PF2_M1PWM6);

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    ui32PWMClock = SysCtlClockGet() / 4;
    ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC|PWM_GEN_MODE_DBG_RUN);
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC|PWM_GEN_MODE_DBG_RUN); //TEST2
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ui32Load);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ui32Load);

    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, (ui8Adjust*ui32Load/4000));
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, (ui8Adjust*ui32Load/4000));
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
    PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
    PWMOutputUpdateMode(PWM1_BASE, PWM_OUT_5, PWM_OUTPUT_MODE_SYNC_LOCAL);
    PWMOutputUpdateMode(PWM1_BASE, PWM_OUT_6, PWM_OUTPUT_MODE_SYNC_LOCAL);

    while(1)
    {
        //PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 64);

        //TO DECREASE PWM PULSE WIDTH
        ///if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0x00)
        if(UARTCharGet(UART0_BASE) == 'F')
        {
            UARTCharPut(UART0_BASE, 'F');
            if (ui8Adjust == 2)
            {
                ui8Adjust =2;
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, (ui8Adjust*ui32Load/4000));
                PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, false);
            }
            else{
                ui8Adjust-=1;
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, (ui8Adjust*ui32Load/4000));
            }
        }

        //TO INCREASE PWM PULSE WIDTH
        //if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0x00)
        if(UARTCharGet(UART0_BASE) == 'J')
        {
            UARTCharPut(UART0_BASE, 'J');
            if (ui8Adjust >= 100)
            {
                ui8Adjust = 100;
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, (ui8Adjust*ui32Load/4000));
                PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
            }
            else{
                ui8Adjust+= 1;
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, (ui8Adjust*ui32Load/4000));
                PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
            }

        }

        //BLUE LED
        if(UARTCharGet(UART0_BASE) == 'D')
        {
            UARTCharPut(UART0_BASE, 'D');
            if (blueAdjust == 2)
            {
                blueAdjust =2;
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, (blueAdjust*ui32Load/4000));
                PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, false);
            }
            else{
                blueAdjust-=1;
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, (blueAdjust*ui32Load/4000));
            }
        }

        if(UARTCharGet(UART0_BASE) == 'K')
        {
            UARTCharPut(UART0_BASE, 'K');
            if (blueAdjust >= 100)
            {
                blueAdjust = 100;
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, (blueAdjust*ui32Load/4000));
                PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
            }
            else{
                blueAdjust+= 1;
                PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, (blueAdjust*ui32Load/4000));
                PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
            }

        }


        //TEST VARIABLE CHECKING
        pwmclock = SysCtlPWMClockGet();
        sysclock = SysCtlClockGet();
        pwmwidth = PWMPulseWidthGet(PWM1_BASE, PWM_OUT_5);
        pwmperiod = PWMGenPeriodGet(PWM1_BASE, PWM_GEN_2);

        bluewidth = PWMPulseWidthGet(PWM1_BASE, PWM_OUT_6);
        blueperiod = PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3);
    }
}
