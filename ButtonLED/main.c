/*
 * Push Botton example for the mbed LPC1768-based board.
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

//Button pin (P8 pin of LPC1768 mbed board)
#define BUTTON_PIN 6 
//LED pin(LED 1 of LPC1768 mbed board)
#define LED_PIN 18 

//Button port 
#define BUTTON_PORT LPC_GPIO0->FIOPIN
//LED port
#define LED_PORT LPC_GPIO1->FIOPIN

//Button direction
#define BUTTON_DIR LPC_GPIO0->FIODIR
//LED direction
#define LED_DIR LPC_GPIO1->FIODIR


//Helper macros
#define SET_BIT(p,bit)  ((p)|=(1<<(bit)))
#define CLR_BIT(p,bit)  ((p)&=~(1<<(bit)))
#define RD_BIT(p,bit)   ((p & (1 <<bit))>> bit)

//Global variable state of the button
volatile uint8_t button;

int main (void) 
{
    //Init GPIO
    SET_BIT(PWR_GPIO_REG ,PWR_GPIO_BIT);
    // Set pin P1.18(LED) to OUTPUT direction
    SET_BIT(LED_DIR,LED_PIN);
    //Set pin P0.6 or P8 mbed board pin (Button) to INPUT direction 
    CLR_BIT(BUTTON_DIR,BUTTON_PIN);
  

    //Main loop
    while(1)
    {

      //Read button state
      button = RD_BIT(BUTTON_PORT,BUTTON_PIN); 

      //Check button state
      if(button){

        //Turn on LED of mbed board
        CLR_BIT(LED_PORT,LED_PIN);
      }else{
        //Turn off LED of mbed board
        SET_BIT(LED_PORT,LED_PIN);
      }
    }
    return 0;
  
}