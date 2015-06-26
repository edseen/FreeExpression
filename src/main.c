/*
 * main.c
 * 
 * FreeExpression firmware, main program
 *
 *
 * This file is part of FreeExpression.
 *
 * https://github.com/thetazzbot/FreeExpression
 *
 * FreeExpression is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2.
 *
 * FreeExpression is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreeExpression. If not, see http://www.gnu.org/licenses/.
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <inttypes.h>
#include <stdio.h>

#include "usb.h"
#include "keypad.h"
#include "timer.h"
#include "stepper.h"
#include "cli.h"
#include "flash.h"
#include "version.h"
#include "dial.h"
#include "hpgl.h"
#include "display.h"



void setup(void)
{
	
	//    wdt_enable( WDTO_30MS );
	usb_init();
	timer_init( );
	stepper_init( );
	display_init();
	keypad_init( );
	flash_init( );
	hpgl_init();
	dial_init( );
	sei();
	
	msleep(10);

	usb_puts(VERSION);
	display_println(VERSION );

}
int main( void )
{
	setup();
    while( 1 )
    {
        cli_poll( ); // polls ready bytes from usb and processes them
		wdt_reset( );
		if( flag_25Hz )
		{
			flag_25Hz = 0;
			
			dial_poll( );  // polls the dials and processes their state
			keypad_poll( ); // polls the keypad and executes functions
		}
		if( flag_Hz )
		{
			flag_Hz = 0;
		}
    }
	//return 0;
}
