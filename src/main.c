#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
#include "main.h"
#include "milis.h"
//#include "delay.h"
//#include "uart1.h"
#include "max7219.h"

#define DIN_PORT GPIOB
#define DIN_PIN GPIO_PIN_1
#define CS_PORT GPIOB
#define CS_PIN GPIO_PIN_2
#define CLK_PORT GPIOB
#define CLK_PIN GPIO_PIN_3
void init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz

    GPIO_Init(DIN_PORT, DIN_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CS_PORT, CS_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CLK_PORT, CLK_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);

    init_milis();
    //init_uart1();
}

void display(uint8_t address, uint8_t data)
{
    uint8_t mask;
    LOW(CS);
    mask = 0b10000000;
    while(mask){
        if (data&mask){
            HIGH(DIN);
        }else{
            LOW(DIN);
        }
    }
        mask = mask >> 1;
    while(mask){
        if (address&mask){
            HIGH(DIN);
        }else{
            LOW(DIN);
        }
        HIGH(CLK);
        LOW(CLK);
    }
    HIGH(CS);
}

int main(void)
{
    display(DECODE_MODE, 0b11111111);
    display(SCAN_LIMIT, 0x07);
    display(INTENSITY, 1);
    display(DISPLAY_TEST, DISPLAY_TEST_OFF);
    display(SHUTDOWN,SHUTDOWN_OFF);
    uint32_t time = 0;

    init();

    while (1) {


        if (milis() - time > 333 ) {
            time = milis();
            display(DIGIT0, 0x01);
        }

    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
