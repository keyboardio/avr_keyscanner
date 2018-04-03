#pragma once

/*
 * Application considerations:
 * The ATtiny48/88 has three 8-bit ports available.
 * Two have special functionality of interest to the application:
 *     PORTB: used by ISP
 *     PORTC: used by TWI/I²C
 *
 */

#define COLS_ARE_OUTPUTS

// ROWS
#define PORT_ROWS PORTC
#define DDR_ROWS DDRC
#define PIN_ROWS PINC
#define ROW_PINMASK  (_BV(0)|_BV(1)|_BV(2)|_BV(3))
#define ROW_COUNT 4

// COLS
#define PORT_COLS PORTD
#define DDR_COLS DDRD
#define PIN_COLS PIND
#define COL_PINMASK  (_BV(0)|_BV(1)|_BV(2)|_BV(3)|_BV(4)|_BV(5)|_BV(6)|_BV(7))
#define COL_COUNT 8


#ifdef COLS_ARE_OUTPUTS

//Scanning port (rows)
#define PORT_INPUT PORT_ROWS
#define DDR_INPUT DDR_ROWS
#define PIN_INPUT PIN_ROWS
#define INPUT_PINMASK ROW_PINMASK
#define INPUT_COUNT ROW_COUNT

//Signal port (cols)
#define PORT_OUTPUT PORT_COLS
#define DDR_OUTPUT DDR_COLS
#define PIN_OUTPUT PIN_COLS
#define OUTPUT_PINMASK COL_PINMASK
#define OUTPUT_COUNT COL_COUNT

// Set data direction as output on the output pins
// Default to all output pins low

#define CONFIGURE_OUTPUT_PINS \
    PINS_HIGH(DDR_OUTPUT, OUTPUT_PINMASK); \
    PINS_LOW(PORT_OUTPUT, OUTPUT_PINMASK);

// Set the data direction for our inputs to be "input"
// Because we're reading high values, we don't want to turn on pull-ups
#define CONFIGURE_INPUT_PINS \
    PINS_LOW(DDR_INPUT, INPUT_PINMASK); \
    PINS_LOW(PORT_INPUT, INPUT_PINMASK);

#define ACTIVATE_OUTPUT_PIN(output_pin) HIGH(PORT_OUTPUT, output_pin);
#define DEACTIVATE_OUTPUT_PIN(output_pin) LOW(PORT_OUTPUT, output_pin);

#else

//Signal port (rows)
#define PORT_OUTPUT PORT_ROWS
#define DDR_OUTPUT DDR_ROWS
#define PIN_OUTPUT PIN_ROWS
#define OUTPUT_PINMASK ROW_PINMASK
#define OUTPUT_COUNT ROW_COUNT

//Scanning port (cols)
#define PORT_INPUT PORT_COLS
#define DDR_INPUT DDR_COLS
#define PIN_INPUT PIN_COLS
#define INPUT_PINMASK COL_PINMASK
#define INPUT_COUNT COL_COUNT



// Set data direction as output on the output pins
// Default to all output pins high
#define CONFIGURE_OUTPUT_PINS \
    PINS_HIGH(DDR_OUTPUT, OUTPUT_PINMASK); \
    PINS_HIGH(PORT_OUTPUT, OUTPUT_PINMASK);

// Set the data direction for our inputs to be "input"
// Turn on the pullups on the inputs
#define CONFIGURE_INPUT_PINS \
    PINS_LOW(DDR_INPUT, INPUT_PINMASK); \
    PINS_HIGH(PORT_INPUT, INPUT_PINMASK);

#define ACTIVATE_OUTPUT_PIN(output_pin) LOW(PORT_OUTPUT, output_pin);
#define DEACTIVATE_OUTPUT_PIN(output_pin) HIGH(PORT_OUTPUT, output_pin);

#endif





// AD01: lower two bits of device address
#define AD01() ((PINB & _BV(0)) |( PINB & _BV(1)))
