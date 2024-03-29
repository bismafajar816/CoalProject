;
; Arduino.asm
;
; Created: 30/12/2023 2:36:44 pm
; Author : Wali
;


.include "m328pdef.inc"
.include "UART_Macros.inc"
.include "delay.inc"

.def UART_CHAR = r21

.org 0x00
					; UART Configuration
	SBI DDRD, PD1 ; Set PD1 (TX) as Output
	CBI PORTD, PD1 ; TX Low (initial state)
	CBI DDRD, PD0 ; Set PD0 (RX) as Input
	SBI PORTD, PD0 ; Enable Pull-up Resistor on RX
	Serial_begin ; Initialize UART Protocol
	
					; OUTPUT CONFIGURATION
	SBI DDRB, PB1 ; PB1 set as OUTPUT Pin RED LIGHT
	CBI PORTB, PB1 ; LED OFF

	SBI DDRB, PB2 ; PB2 set as OUTPUT Pin GREEN LIGHT
	CBI PORTB, PB2 ; LED OFF

	SBI DDRB, PB3 ; PB3 set as OUTPUT Pin BLUE LIGHT
	CBI PORTB, PB3 ; LED OFF
	
	SBI DDRB, PB4 ; PB3 set as OUTPUT Pin for BUZZER
	
	SBI PORTB, PB4 ; TURN BUZZER ON
	delay 1500
	delay 1500
	CBI PORTB, PB4 ; TURN BUZZER OFF
	
	SBI PORTB, PB1	;RED LED ON
	SBI PORTB, PB2	;GREEN LED ON
	SBI PORTB, PB3	;BLUE LED ON
	delay 2000
	CBI PORTB, PB1	;RED LED ON
	CBI PORTB, PB2	;GREEN LED ON
	CBI PORTB, PB3	;BLUE LED ON

MAIN:
	Serial_readChar UART_CHAR

MID:
	CPI UART_CHAR, '1'	; Yellow COLOR
    BREQ YELLOW_LED

    CPI UART_CHAR, '2'  ; Magenta COLOR
    BREQ MAGENTA_LED

	CPI UART_CHAR, '3'	; White COLOR
    BREQ WHITE_LED

	CPI UART_CHAR, '4'  ; Loop LEDs
    BREQ LOOP_LEDS

	CPI UART_CHAR, '5'  ; OFF LEDs
    BREQ LEDS_OFF
rjmp MAIN

LEDS_OFF:
	CBI PORTB, PB1	;RED LED OFF
	CBI PORTB, PB2	;GREEN LED OFF
	CBI PORTB, PB3	;BLUE LED OFF
rjmp MAIN

YELLOW_LED:
	SBI PORTB, PB1	;RED LED ON
	SBI PORTB, PB2	;GREEN LED ON
	CBI PORTB, PB3	;BLUE LED OFF
rjmp MAIN

MAGENTA_LED:
	SBI PORTB, PB1	;RED LED ON
	CBI PORTB, PB2	;GREEN LED OFF
	SBI PORTB, PB3	;BLUE LED ON
rjmp MAIN

WHITE_LED:
	SBI PORTB, PB1	;RED LED ON
	SBI PORTB, PB2	;GREEN LED ON
	SBI PORTB, PB3	;BLUE LED ON
rjmp MAIN

LOOP_LEDS:
	Serial_readChar UART_CHAR

	CPI UART_CHAR, '1'	; Yellow COLOR
    BREQ MID

    CPI UART_CHAR, '2'  ; Magenta COLOR
    BREQ MID

	CPI UART_CHAR, '3'	; White COLOR
    BREQ MID

	CPI UART_CHAR, '4'  ; Loop LEDs
    BREQ MID

	CPI UART_CHAR, '5'  ; OFF LEDs
    BREQ MID

	SBI PORTB, PB1	;RED LED ON
	CBI PORTB, PB2	;GREEN LED OFF
	CBI PORTB, PB3	;BLUE LED OFF
	
	delay 500

	CBI PORTB, PB1	;RED LED OFF
	SBI PORTB, PB2	;GREEN LED ON
	CBI PORTB, PB3	;BLUE LED OFF

	delay 500

	CBI PORTB, PB1	;RED LED OFF
	CBI PORTB, PB2	;GREEN LED OFF
	SBI PORTB, PB3	;BLUE LED ON

	delay 500

	SBI PORTB, PB1	;RED LED ON
	SBI PORTB, PB2	;GREEN LED ON
	CBI PORTB, PB3	;BLUE LED OFF

	delay 500

	SBI PORTB, PB1	;RED LED ON
	CBI PORTB, PB2	;GREEN LED OFF
	SBI PORTB, PB3	;BLUE LED ON

	delay 500

	CBI PORTB, PB1	;RED LED OFF
	SBI PORTB, PB2	;GREEN LED ON
	SBI PORTB, PB3	;BLUE LED ON

	delay 500

	SBI PORTB, PB1	;RED LED ON
	SBI PORTB, PB2	;GREEN LED ON
	SBI PORTB, PB3	;BLUE LED ON

	delay 500
	
	CBI PORTB, PB1	;RED LED OFF
	CBI PORTB, PB2	;GREEN LED OFF
	CBI PORTB, PB3	;BLUE LED OFF

	Serial_readChar UART_CHAR

	delay 500
	 
rjmp LOOP_LEDS