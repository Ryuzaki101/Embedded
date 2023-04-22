#ifndef LCD_H_
#define LCD_H_

#ifndef NEUE_PLATINE
	extern void lcd_init(void );    //Initialize the LCD module per Ocular specifications
	extern void lcd_clear(void);	// Clear LCD display
	extern void lcd_printf(unsigned char*);  // Write a constant string to the LCD
	extern void lcd_gotoxy(unsigned char row, unsigned char column);
	extern void lcd_byte(char num);
	extern void lcd_int(int num);
	extern void lcd_putc(unsigned char data);
#else
	extern void lcd_init_new(void );    //Initialize the LCD module per Ocular specifications
	extern void lcd_clear_new(void);	// Clear LCD display
	extern void lcd_printf_new(unsigned char*);  // Write a constant string to the LCD
	extern void lcd_gotoxy_new(unsigned char row, unsigned char column);
	extern void lcd_byte_new(char num);
	extern void lcd_int_new(int num);
	extern void lcd_putc_new(unsigned char data);
	
	#define  lcd_init lcd_init_new
	#define  lcd_clear lcd_clear_new
	#define  lcd_printf lcd_printf_new
	#define  lcd_gotoxy lcd_gotoxy_new
	#define  lcd_byte lcd_byte_new
	#define  lcd_int lcd_int_new
	#define  lcd_putc lcd_putc_new

#endif
#endif