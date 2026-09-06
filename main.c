#include <xc.h>

#define _XTAL_FREQ 20000000

// CONFIGURATION BITS
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF


// LCD CONTROL PINS
#define RS RD0
#define EN RD1

void LCD_Command(unsigned char cmd);
void LCD_Data(unsigned char data);
void LCD_Init(void);
void LCD_String(const char *str);


// Send command to LCD
void LCD_Command(unsigned char cmd)
{
    PORTD = (PORTD & 0x0F) | (cmd & 0xF0);

    RS = 0;
    EN = 1;
    __delay_ms(2);
    EN = 0;

    PORTD = (PORTD & 0x0F) | ((cmd << 4) & 0xF0);

    EN = 1;
    __delay_ms(2);
    EN = 0;
}


// Send data to LCD
void LCD_Data(unsigned char data)
{
    PORTD = (PORTD & 0x0F) | (data & 0xF0);

    RS = 1;
    EN = 1;
    __delay_ms(2);
    EN = 0;

    PORTD = (PORTD & 0x0F) | ((data << 4) & 0xF0);

    EN = 1;
    __delay_ms(2);
    EN = 0;
}


// Initialize LCD
void LCD_Init(void)
{
    __delay_ms(20);

    LCD_Command(0x02);  // 4-bit mode
    LCD_Command(0x28);  // 2 lines, 5x7 matrix
    LCD_Command(0x0C);  // Display ON
    LCD_Command(0x06);  // Cursor increment
    LCD_Command(0x01);  // Clear display

    __delay_ms(2);
}


// Print string
void LCD_String(const char *str)
{
    while(*str)
    {
        LCD_Data(*str++);
    }
}


void main(void)
{
    TRISD = 0x00;   // PORTD as output
    PORTD = 0x00;

    LCD_Init();

    LCD_String("PIC16F877A");
    LCD_Command(0xC0);

    LCD_String("Digital Thermo");

    while(1);
}