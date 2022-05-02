/*==============================================================================
 Project: Intro-2-Variables
 Date:    March 1, 2022
 
 This example program demonstrates the use of byte (char) constants and
 variables to count button presses and trigger actions when a limit is reached.
  
 Additional program analysis and programming activities demonstrate using bit
 (Boolean, or bool) variables to store state for operations such as preventing 
 multiple counting of a singe button press during successive program loops.
 Additional activities include the creation of a two-player rapid-clicker game,
 simulating a real-world toggle button, and counting switch contact bounce.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP410.h"         // Include UBMP4.1 constant and function definitions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Program constant definitions
const unsigned char maxCount = 50;

// Program variable definitions
unsigned char SW2Count = 0;
bool SW2Pressed = false;

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    // Code in this while loop runs repeatedly.
    while(1)
	{
        // Count SW2 button presses
        if(SW2 == 0)
        {
            LED3 = 1;
            SW2Count = SW2Count + 1;
        }
        else
        {
            LED3 = 0;
        }
        
        if(SW2Count >= maxCount)
        {
            LED4 = 1;
        }
        
        // Reset count and turn off LED D4
        if(SW3 == 0)
        {
            LED4 = 0;
            SW2Count = 0;
        }
        
        // Add a short delay to the main while loop.
        __delay_ms(10);
        
        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}

/* Program Analysis
 * 
 * 1. Can you make a two-player rapid-clicker style game using this program as 
 *    a starting point? Let's use SW5 for the second player's pushbutton so that
 *    the two players can face each other from across the UBMP4 circuit board.
 *    Duplicate SW2Count and SW2Pressed to create SW5Count and SW5Pressed
 *    variables. Then, duplicate the required if condition structures and modify
 *    the variable names to represent the second player. LED D4 can still light
 *    if player 1 is the first to reach maxCount. Use LED D5 to show if the
 *    second palyer wins. Use a logical condition statement to reset the game
 *    by clearing the count and turning off the LEDs if either SW3 or SW4 is
 *    pressed.
 * 
 *    // Code in this while loop runs repeatedly.
 *  while(1)
 *	{
 *      if(SW2 == 0 && SW2Pressed == false)
 *      {
 *          LED3 = 1;
 *          SW2Pressed = true;
 *          if(SW2Count < 255)
 *          {
 *              SW2Count = SW2Count + 1;
 *          }
 *      }
 *
 *      // Clear pressed state if released
 *      if(SW2 == 1)
 *      {
 *          LED3 = 0;
 *          SW2Pressed = false;
 *      }
 *      
 *      if(SW2Count >= maxCount)
 *      {
 *          LED4 = 1;
 *      }
 *      
 *      // Reset count and turn off LED D4
 *      if(SW2Count >= maxCount)
 *      {
 *          LED4 = 1;
 *      }
 *      else
 *      {
 *          LED4 = 0;
 *      }
 *
 *      if(SW3 == 0)
 *      {
 *          LED4 = 0;
 *          SW2Count = 0;
 *      }
 *    /////////////////////////////////////////
 *      if(SW5 == 0 && SW5Pressed == false)
 *      {
 *          LED6 = 1;
 *          SW5Pressed = true;
 *          if(SW5Count < 255)
 *          {
 *              SW5Count = SW5Count + 1;
 *          }
 *      }
 *
 *      // Clear pressed state if released
 *      if(SW5 == 1)
 *      {
 *          LED6 = 0;
 *          SW5Pressed = false;
 *      }
 *      
 *      if(SW5Count >= maxCount)
 *      {
 *          LED5 = 1;
 *      }
 *      
 *      // Reset count and turn off LED D4
 *      if(SW5Count >= maxCount)
 *      {
 *          LED5 = 1;
 *      }
 *      else
 *      {
 *          LED5 = 0;
 *      }
 *
 *      if(SW4 == 0)
 *      {
 *          LED5 = 0;
 *          SW5Count = 0;
 *      }
 *
 *      // Add a short delay to the main while loop.
 *      __delay_ms(10);
 *      
 *      // Activate bootloader if SW1 is pressed.
 *      if(SW1 == 0)
 *      {
 *          RESET();
 *      }
 *  }
 *  }
 *
 * 2. Use your knowledge of Boolean variables and logical conditions to simulate
 *    a toggle button. Each new press of the toggle button will 'toggle' an LED
 *    to its opposite state. (Toggle buttons are commonly used as push-on, 
 *    push-off power buttons in digital devices.)
 * 
 *    if(SW4 == 0 && SW4Pressed == false)
        {
            if (LED3 == 1)
            {
                LED3 = 0;
            }
            else
            {
                LED3 = 1;
            }

            if (LED4 == 1)
            {
                LED4 = 0;
            }

            else
            {
                LED4 = 1;
            }

            if (LED5 == 1)
            {
                LED5 = 0;
            }

            else
            {
                LED5 = 1;
            }

            if (LED6 == 1)
            {
                LED6 = 0;
            }

            else
            {
                LED6 = 1;
            }

            SW4Pressed = true;
        }

        //reset count
        if(SW4 == 1)
        {
            SW4Pressed = false;
        }
 *
 * 3. A multi-function button can be used to enable one action when pressed, and
 *    a second or alternate action when held. A variable that counts loop cycles
 *    can be used to determine how long a button is held (just as the first
 *    program unintentionally did, because of the loop structure). Make a
 *    multifunction button that lights one LED when a button is pressed, and
 *    lights a second LED after the button is held for more that one second.
 * 
 *    if(SW4 == 0 && secondCount == 0)
        {
            // if switch 4 is held, wait 1 second and set the second count to 1
            if (SW4 == 0)
            {
            __delay_ms(1000);
            secondCount = 1;
            }
            // if switch 4 is held for 1 second, turn on LED 3
            if (secondCount == 1)
            {
                LED3 = 1;
            }
            // if switch 4 is held, wait 1 second and set the second count to 2
            if (SW4 == 0)
            {
            __delay_ms(1000);
            secondCount = 2;
            }
            // if switch 4 is held for 2 seconds, turn on LED 4
            if (secondCount == 2)
            {
                LED4 = 1;
            }
            // if switch 4 is held, wait 1 second and set the second count to 3
            if (SW4 == 0)
            {
            __delay_ms(1000);
            secondCount = 3;
            }
            // if switch 4 is held for 3 seconds, turn on LED 5
            if (secondCount == 3)
            {
                LED5 = 0;
            }
            // if switch 4 is held, wait 1 second and set the second count to 4
            if (SW4 == 0)
            {
            __delay_ms(1000);
            secondCount = 4;
            }
            // if switch 4 is held for 4 seconds, turn on LED 6
            if (secondCount == 4)
            {
                LED6 = 1;
            }
        }

        if (SW4 == 1)
        {
            secondCount = 0;
        }

        // turn off all LEDs
        if(SW5 == 0)
        {
            LED3 = 0
            
            LED4 = 0

            LED5 = 0

            LED6 = 0
        }
 *
 * 4. Do your pushbuttons bounce? Switch bounce is the term that describes
 *    switch contacts repeatedly closing and opening before settling in their
 *    final (usually closed) state. Switch bounce in a room's light switch is
 *    not a big concern, but switch bounce can be an issue in a toggle button
 *    because the speed of a microcontroller lets it see each bounce as a new,
 *    separate event. Use a variable to count the number of times a pushbutton
 *    is pressed and display the count on the LEDs. Use a separate pushbutton
 *    to reset the count and turn off the LEDs so that the test can be repeated.
 *    To determine if your switches bounce, try pressing them at various speeds
 *    and using different amounts of force.
 * 
 *    // Count new SW4 button presses
        if(SW4 == 0 && SW4Pressed == false)
        {
            LED3 = 1;
            SW4Pressed = true;
            SW4Count = SW4Count + 1;
            if (SW4Count >= 15)
            {
                LED4 = 1;
            }
            if (SW4Count >= 30)
            {
                LED5 = 1;
            }
            if (SW4Count >= 45)
            {
                LED6 = 1;
            }
        }

        // Clear pressed state if released
        if(SW4 == 1)
        {
            LED3 = 0;
            SW4Pressed = false;
        }

        // reset isPressedCount and turn off all LEDs
        if(SW5 == 0)
        {
            SW4Count = 0;

            LED3 = 0;
            
            LED4 = 0;

            LED5 = 0;

            LED6 = 0;
        }
 *
 * 5. Did your pushbuttons bounce? Can you think of a technique similar to the
 *    multi-function button that could be implemented to make your program
 *    ignore switch bounces. Multiple switch activations within a 50ms time span
 *    might indicate switch bounce and can be safely ignored.
 *
 *    No, the pushbuttons did not bounce. Another way to make the program
 *    ignore switch bounces is putting a limit to how much the buttons
 *    can be pressed by adding a short delay.
 *
 */
