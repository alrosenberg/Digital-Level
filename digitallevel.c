// digitallevel.c
//lab8
// Josh Brake and David_Harris@hmc.edu
// jbrake@hmc.edu
// 1/20/2020


//edited by Alexa Rosenberg and Jade Wong
//row connected to GPIO
/*

row:     pin:       GPIO:
  1        9         16 !  
  2        14        18
  3         8       0  !
  4        12        19   !
  5         1        9  !
  6         7       11 !
  7        2        10  !

  col:   pin:    GPIO:
  1      13        20 !
  2      3         13  !
  3       4        12   !
  4      10        23
  5       6         22  !
  6      11        21 !
  7     15        17  !
  8     16        
    

    2 3 4 5 accelerometer pins



*/

#include "EasyREDVIO_ThingPlus.h"
#define LED_COUNT 7

int mapToLEDIndex(int32_t val, int32_t minv, int32_t maxv) {
    int64_t scaled = ((int64_t)(val - minv) * (LED_COUNT - 1)) / (maxv - minv); //scales based on found max and min vals in respective directsins
    if (scaled < 0) scaled = 0; //make it zero cuz i dont like negative number rows 
    if (scaled > LED_COUNT - 1) scaled = LED_COUNT - 1; //fix for zero index
    return (int)scaled;
}

int rowTOpin (int index) {
    int rowPins[7] = {16, 18, 0, 19, 9, 11, 10};
    return rowPins[index]; // selects appropriate index pin

}


int ColTOpin (int index) {
    int colPins[7] = {20, 13, 12, 23, 22, 21, 17};
    return colPins[index]; // selects appropriate index pin

}


void lightuptest(void) {
  volatile uint32_t *GPIO_OUTPUT_EN  = (uint32_t*)0x10012008;
  volatile uint32_t *GPIO_OUTPUT_VAL = (uint32_t*)0x1001200C;

  uint32_t ROW = (1 << 16) | (1 << 18) | (1 << 0) |
                      (1 << 19) | (1 << 9)  | (1 << 11) | (1 << 10);

  uint32_t COL= (1 << 20) | (1 << 13) | (1 << 12) |
                      (1 << 23) | (1 << 22) |(1 << 21) | (1 << 17);

  *GPIO_OUTPUT_EN |= ROW | COL;


  *GPIO_OUTPUT_VAL &= ~ROW; 
  *GPIO_OUTPUT_VAL |=  COL;   

  *GPIO_OUTPUT_VAL |=  (1 << 16);   // row high
  *GPIO_OUTPUT_VAL &= ~(1 << 20);   // column low

  while (1) {

  }
}


int main(void)
{    volatile uint32_t *GPIO_INPUT_VAL = (uint32_t*)0x10012000;
    volatile uint32_t *GPIO_INPUT_EN   = (uint32_t*)0x10012004;
    volatile uint32_t *GPIO_OUTPUT_EN  = (uint32_t*)0x10012008;
    volatile uint32_t *GPIO_OUTPUT_VAL = (uint32_t*)0x1001200C;

    // Enable accelerometer SPI pins
    *GPIO_INPUT_EN |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);


    uint32_t ROW = (1 << 16) | (1 << 18) | (1 << 0) |
                        (1 << 19) | (1 << 9)  | (1 << 11) | (1 << 10);

    uint32_t COL= (1 << 20) | (1 << 13) | (1 << 12) |
                        (1 << 23) | (1 << 22) |(1 << 21) | (1 << 17);

    *GPIO_OUTPUT_EN |= ROW | COL;


    *GPIO_OUTPUT_VAL &= ~ROW; 
    *GPIO_OUTPUT_VAL |=  COL;   

  
    volatile uint8_t debug;
    volatile int16_t x, y, disx, disy;

    spiInit(10, 1, 1); // Initialize SPI pins

    // Setup the LIS3DH
    spiWrite(0x20, 0x77); // highest conversion rate, all axis on
    spiWrite(0x23, 0x88); // block update, and high resolution

    // Check WHO_AM_I register. should return 0x33    
    debug = spiRead(0x0F);

    
    while(1)
    {
      // Collect the X and Y values from the LIS3DH 	
      x = spiRead(0x28) | (spiRead(0x29) << 8);
      y = spiRead(0x2A) | (spiRead(0x2B) << 8);

      int col_val = ColTOpin( mapToLEDIndex(x, -6000,  2640));  
      int row_val = rowTOpin(mapToLEDIndex(y,-15344, 15600 ));

      *GPIO_OUTPUT_VAL |=  (1 << row_val);   // row high
      *GPIO_OUTPUT_VAL &= ~(1 << col_val);   // column low

      delayLoop(100);
      *GPIO_OUTPUT_VAL &=  ~(1 << row_val);    //turns off lights 
      *GPIO_OUTPUT_VAL |= (1 << col_val);  
  }
    return 0;
}

