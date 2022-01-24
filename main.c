/*******************************************************************************
 Rue's "is it alive" program for avr processors
  also makes a good skel to build your programs form.
*******************************************************************************/
 
/*



1     PB0 
2     PB1 
3     PB2 
4     PB3 
5     PB4 
6     PB5
7     PB6 
8     PB7 
9     PA0 
10    PA1  	 
11    PA2 
12    PA3  
13    PA4   
14    PA5  
15    PA6	
16    PA7
17    PC7
18    PC6
19    PC5
20    PC4
21    PC3
22    PC2
23    PC1
24    PC0
25    PD7
26    PD2
27    PD3  data line  arduino pin 3
28    PD4  clock      arduino pin 4
29    PD5  /CS        arduino pin 5
30    PD6  


*/


// manual port D bits 2 to 7


#include <avr/io.h>


#define OUTPUT             1
#define INPUT              0



  #define SetBit(BIT, PORT)     PORT |= (1<<BIT)
  #define ClearBit(BIT, PORT)   PORT &= ~(1<<BIT)
  #define IsHigh(BIT, PORT)    (PORT & (1<<BIT)) != 0
  #define IsLow(BIT, PORT)     (PORT & (1<<BIT)) == 0
  #define NOP()                 asm volatile ("nop"::)

  // Bit positions, PORTD 
  #define DATA             3
  #define SCLK             4
  #define STB              5


  #define DATAlow()              ClearBit(DATA, PORTD)
  #define SCLKlow()              ClearBit(SCLK, PORTD)
  #define STBlow()               ClearBit(STB, PORTD)

  
  #define DATAhigh()             SetBit(DATA, PORTD)
  #define SCLKhigh()             SetBit(SCLK, PORTD)
  #define STBhigh()              SetBit(STB, PORTD)


  #define pulseSCK()            SCLKlow(); NOP(); NOP(); SCLKhigh(); NOP()
  #define pulseSTB()            STBhigh(); NOP(); NOP(); STBlow()
  
  #define SendOne()             DATAhigh(); pulseSCK()
  #define SendZero()            DATAlow();  pulseSCK()
  
  void send8 (unsigned int bits);
  void Delay(unsigned int delay) ;
  void Delay2(unsigned int delay) ;


int main (void) {

  uint8_t i = 0;

  // set up directions 
  DDRB = (INPUT << PB0 | INPUT << PB1 |INPUT << PB2 |INPUT << PB3 |INPUT << PB4 |INPUT << PB5 |INPUT << PB6 |INPUT << PB7);
  DDRC = (INPUT << PC0 | INPUT << PC1 |INPUT << PC2 |INPUT << PC3 |INPUT << PC4 |INPUT << PC5 |INPUT << PC6 );
  DDRD = (INPUT << PD0 | INPUT << PD1 |INPUT << PD2 |OUTPUT << PD3 |OUTPUT << PD4 |OUTPUT << PD5 |INPUT << PD6 |INPUT << PD7);              
  
  Delay2(4);  
      
  while(1){
    send8(i);
    i++;
  //  Delay(40000);
  }

}



// send a 8bit word, msb first
void send8 (unsigned int bits) {
  uint8_t temp;  
  for( temp = (0x01); temp != 0; temp <<= 1) {    
    if ( (bits & temp) != 0 ) {    SendOne();
    } else {                       SendZero();
    }    
  } 
  pulseSTB();
}

void Delay(unsigned int delay) {
  unsigned int x;
  for (x = delay; x != 0; x--) {
    asm volatile ("nop"::); 
  }
}

void Delay2(unsigned int delay) {
  unsigned int x;
  for (x = delay; x != 0; x--) {
    Delay(65000);
  }
}


































