/*
 * Blink LED example for the mbed LPC1768-based board.
 *
 * Copyright (C) 2013  Marcelo Rodrigo dos Santos Andriolli
                       marcelorsa@gmail.com
                       https://github.com/marceloandriolli
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 * 
 *
 */
#include "CMSIS/LPC17xx.h"

//Power GPIO register
#define PWR_GPIO_REG LPC_SC->PCONP
//Power GPIO pin
#define PWR_GPIO_BIT 15

//LED port
#define LED_PORT LPC_GPIO1->FIOPIN
//LED pin(LED 1 of LPC1768 mbed board)
#define LED_PIN 18 
//LED direction
#define LED_DIR LPC_GPIO1->FIODIR

//Helper macros
#define SET_BIT(p,bit)  ((p)|=(1<<(bit)))
#define CLR_BIT(p,bit)  ((p)&=~(1<<(bit)))
#define _DELAY()        for (volatile int i = 0; i < 50000; i++)


int main (void) 
{
    //Init GPIO
    SET_BIT(PWR_GPIO_REG ,PWR_GPIO_BIT);
    // Set pin P1.18(LED) to OUTPUT direction
    SET_BIT(LED_DIR,LED_PIN);
    
    //Main loop
    while(1)
    {
        //Turn on LED of mbed board
        CLR_BIT(LED_PORT,LED_PIN);
        //Delay
        _DELAY();
        //Turn off LED of mbed board
        SET_BIT(LED_PORT,LED_PIN);
        //Delay
        _DELAY();
    }
    return 0;
  
}

