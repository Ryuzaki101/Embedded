#include <LPC23xx.H>

void init_timer0 (void);
void start_timer0(void);
void stop_timer0(void);
void init_Port4_5(void);
void set_Port4_5(void);
void clear_Port4_5(void);

void init_timer0 (void)
{ 
  T0CTCR = 0x0;
  PCLKSEL0 |= 0xFFFFFFF3;  //Ref. Per. Clock for Timer0 = SYS_CLK/4
}

void start_timer0(void)
{
  T0PR = 0x0001; // Counter Step = PR + 1
  T0TCR = 0x02; //Reset timer0 counter and prescaler 
  T0TCR = 0x01; //Enable timer0
}

void stop_timer0(void)
{
  T0TCR = 0x0; //Disable timer0  
  //Afterwards read content of register T0TC
} 

void init_Port4_5(void)
{
  FIO4DIR |= 0x020;  // Port 4.5 as output
}

void set_Port4_5(void)
{
  FIO4PIN |= 0x020;  // set Port 4.5
} 

void clear_Port4_5(void)
{
  FIO4PIN &= 0xFFFFFFDF;  // clear Port 4.5
}  

 

