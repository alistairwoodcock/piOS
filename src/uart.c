#include "utils.h"
#include "peripherals/uart.h"
#include "peripherals/gpio.h"

// const int baud_rate = 600;

// const int system_clock_freq = 250000000; //Hz not sure where to get this from the system

void pl_uart_send ( char c )
{
    while(get32(UART_FR) & (1 <<5)) {}
    put32(UART_DR,c);
}

char pl_uart_recv ( void )
{
    while(get32(UART_FR) & (1<<4)) {}
    return get32(UART_DR);
}

void pl_uart_send_string(char* str)
{
    for (int i = 0; str[i] != '\0'; i ++) {
        pl_uart_send((char)str[i]);
    }
}

void pl_uart_init ( void )
{
    unsigned int selector;

    selector = get32(GPFSEL1);
    selector &= ~(7<<12);                   // clean gpio14
    selector |= 4<<12;                      // set alt0 for gpio14
    selector &= ~(7<<15);                   // clean gpio15
    selector |= 4<<15;                      // set alt0 for gpio15
    put32(GPFSEL1,selector);

    put32(GPPUD,0);
    delay(150);
    put32(GPPUDCLK0,(1<<14)|(1<<15));
    delay(150);
    put32(GPPUDCLK0,0);


    //UART_DR -- Data Register
    // I think we use this to pull a byte off for
    // both transmit and receive

    //UART_FR -- I think we used this to check the status
    // of data to make sure we can read / write

    //UART_IBRD - integer part of baud rate divisor value
    // need this as part of baud rate setup

    //UART_FBRD - Fractional part of baud rate divisor value
    //  Baud rate divisor DAUDDIV = (F/(16xBaud Rage))
    //  F = UART reference clock frequence
    // required_baud_rate = 115200
    // UARTCLK = 250MHz
    // Baud Rate Divisor = (250x10^6) / (16x115200) = 135.633681
    // Baud Rate Div Fraction = ((0.633681x64)+0.5) = 41
    // Baud Rate Div Integer = 135

    //UART_LCRH - control register I think
    /*
    * 0 : 7 SPS - Stick parity select , disabled if PEN is
    * 1 : 6 WLEN - 8 bits per frame
    * 1 : 5
    * 1 : 4 FEN - FIFO Enabled
    * 0 : 3 STP2 - Two stop bits
    * 0 : 2 EPS - Even Parity, disabled if PEN is
    * 0 : 1 PEN - Parity bit, 0 disabled
    * 0 : 0 BRK - Send break, normal use is 0
    */

    //UART_CR - this is the actual control register
    // here we can enable and disable UART

    //Program the control registers as follows:
    // 1. Disable the UART (using UART_CR)
    // 2. Wait for the end of transmission or reception of the current char
    // 3. Flush the transmit FIFO by setting the FEN bit to 0 in the UART_LCRH
    // 4. Reprogram the UART_CR register
    // 5. Enable the UART

    put32(UART_ICR, 0x7ff); //clear all interrupts

    //Disable UART before doing anything
    put32(UART_CR, 0); //not sure if we should be doing put32 or make a put16
    delay(150); //not sure how long we should actually delay (if needed at all on init)
    put32(UART_LCRH, 0); //disable all things
    
    //Order of the following reg writes are important because
    //they all make up a single register
    put32(UART_IBRD, 26); //set baud rate div integer
    put32(UART_FBRD, 3); // set baud rate div fraction
    put32(UART_LCRH, 0x70); //setup line control register stuff

    put32(UART_IMSC, 0); //mask all interrupts

    put32(UART_CR, 0x301); //enable with new settings

    //Enable UART and setup properly
    //disable auto flow control
    //disable receive and transmission
    //set to 8 bit mode
    //set RTS to high
    //set the baud rate
    //enable transmission

    // put8(UART_TLCRH, );

    // put32(AUX_ENABLES,2);                   //Enable SP1  (this also enables access to it registers)
    // put32(AUX_MU_CNTL_REG,0);               //Disable auto flow control and disable receiver and transmitter (for now)
    // put32(AUX_MU_IER_REG,0);                //Disable receive and transmit interrupts
    // put32(AUX_MU_LCR_REG,3);                //Enable 8 bit mode
    // put32(AUX_MU_MCR_REG,0);                //Set RTS line to be always high
    // put32(AUX_MU_BAUD_REG,(((system_clock_freq / baud_rate) / 8) - 1)); //Set baud rate
    // put32(AUX_MU_CNTL_REG,3);               //Finally, enable transmitter and receiver
}
