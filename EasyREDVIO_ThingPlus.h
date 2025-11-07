// EasyREDVIO_ThingPlus.h
// jbrake@hmc.edu and david_harris@hmc.edu
// 02/06/2020

// This library provides an Arduino-style interface to control I/O 
// devices on a RISC-V FE310 SoC on a SparkFun RED-V board.

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Constant Definitions
///////////////////////////////////////////////////////////////////////////////

#define GPIO0_BASE  (0x10012000U)   // GPIO memory-mapped base address

#define GPIO0 ((GPIO*) GPIO0_BASE)  // Set up pointer to struct of type GPIO aligned at the base GPIO0 memory-mapped address

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1
#define GPIO_IOF0 2

///////////////////////////////////////////////////////////////////////////////
// Bitfield Structs
///////////////////////////////////////////////////////////////////////////////

typedef struct
{
    volatile uint32_t   input_val;      // (GPIO offset 0x00) Pin value
    volatile uint32_t   input_en;       // (GPIO offset 0x04) Pin input enable*
    volatile uint32_t   output_en;      // (GPIO offset 0x08) Pin output enable*
    volatile uint32_t   output_val;     // (GPIO offset 0x0C) Output value
    volatile uint32_t   pue;            // (GPIO offset 0x10) Internal pull-up enable*
    volatile uint32_t   ds;             // (GPIO offset 0x14) Pin drive strength
    volatile uint32_t   rise_ie;        // (GPIO offset 0x18) Rise interrupt enable
    volatile uint32_t   rise_ip;        // (GPIO offset 0x1C) Rise interrupt pending
    volatile uint32_t   fall_ie;        // (GPIO offset 0x20) Fall interrupt enable
    volatile uint32_t   fall_ip;        // (GPIO offset 0x24) Fall interrupt pending
    volatile uint32_t   high_ie;        // (GPIO offset 0x28) High interrupt enable
    volatile uint32_t   high_ip;        // (GPIO offset 0x2C) High interrupt pending
    volatile uint32_t   low_ie;         // (GPIO offset 0x30) Low interrupt enable
    volatile uint32_t   low_ip;         // (GPIO offset 0x34) Low interrupt pending
    volatile uint32_t   iof_en;         // (GPIO offset 0x38) HW-Driven functions enable
    volatile uint32_t   iof_sel;        // (GPIO offset 0x3C) HW-Driven functions selection
    volatile uint32_t   out_xor;        // (GPIO offset 0x40) Output XOR (invert)
    // Registers marked with * are asynchronously reset to 0. All others are synchronously reset to 0.
} GPIO;

///////////////////////////////////////////////////////////////////////////////
// Constant Definitions
///////////////////////////////////////////////////////////////////////////////

#define QSPI0_BASE  (0x10014000U)   // QSPI0 memory-mapped base address
#define SPI1_BASE   (0x10024000U)   // SPI1 memory-mapped base address
#define SPI2_BASE   (0x10034000U)   // SPI2 memory-mapped base address

///////////////////////////////////////////////////////////////////////////////
// SPI Registers
///////////////////////////////////////////////////////////////////////////////

typedef struct
{
    volatile uint32_t   div         :   12; // Divisor for serial clock. div_width bits wide
    volatile uint32_t               :   20;
} sckdiv_bits;

typedef struct
{
    volatile uint32_t   pha         :   1; // Serial clock phase
    volatile uint32_t   pol         :   1; // Serial clock polarity
    volatile uint32_t               :   30;
} sckmode_bits;

typedef struct
{
    volatile uint32_t   csid        :   32; // Chip select ID. log2(cs_width) bits wide.
} csid_bits;

typedef struct
{
    volatile uint32_t   csdef       :   32; // Chip select default value. cs_widthbits wide, reset to all 1s.
} csdef_bits;

typedef struct
{
    volatile uint32_t   mode        :   2; // Chip select mode
    volatile uint32_t               :   30;
} csmode_bits;

typedef struct
{
    volatile uint32_t   cssck       :   8; // CS to SCK Delay
    volatile uint32_t               :   8;
    volatile uint32_t   sckcs       :   8; // SCK to CS Delay
    volatile uint32_t               :   8;
} delay0_bits;

typedef struct
{
    volatile uint32_t   intercs     :   8; // Minimum CS inactive time
    volatile uint32_t               :   8;
    volatile uint32_t   interxfr    :   8; // Maximum interframe delay
    volatile uint32_t               :   8;
} delay1_bits;

typedef struct
{
    volatile uint32_t   proto       :   2; // SPI protocol
    volatile uint32_t   endian      :   1; // SPI endianness
    volatile uint32_t   dir         :   1; // SPI I/O direcation.
    volatile uint32_t               :   12;
    volatile uint32_t   len         :   4; // Number of bits per frame
    volatile uint32_t               :   12;
} fmt_bits;

typedef struct
{
    volatile uint32_t   data        :   8; // Transmit data
    volatile uint32_t               :   23;
    volatile uint32_t   full        :   1; // FIFO full flag
} txdata_bits;

typedef struct
{
    volatile uint32_t   data        :   8; // Received data
    volatile uint32_t               :   23;
    volatile uint32_t   empty       :   1; // FIFO empty flag
} rxdata_bits;

typedef struct
{
    volatile uint32_t   txmark      :   3; // Transmit watermark
    volatile uint32_t               :   29;
} txmark_bits;

typedef struct
{
    volatile uint32_t   rxmark      :   3; // Receive watermark
    volatile uint32_t               :   29;
} rxmark_bits;

typedef struct
{
    volatile uint32_t   en          :   1; // SPI Flash Mode Select
    volatile uint32_t               :   31;
} fctrl_bits;

typedef struct
{
    volatile uint32_t   cmd_en      :   1; // Enable sending of command
    volatile uint32_t   addr_len    :   3; // Number of address bytes (0 to 4)
    volatile uint32_t   pad_cnt     :   4; // Number of dummy cycles
    volatile uint32_t   cmd_proto   :   2; // Protocol for transmitting command
    volatile uint32_t   addr_proto  :   2; // Protocol for transmitting address and padding
    volatile uint32_t   data_proto  :   2; // Protocol for receiving data bytes
    volatile uint32_t               :   2;
    volatile uint32_t   cmd_code    :   8; // Value of command byte
    volatile uint32_t   pad_code    :   8; // First 8 bits to transmit during dummy cycles
} ffmt_bits;

typedef struct
{
    volatile uint32_t   txwm        :   1; // Transmit watermark enable
    volatile uint32_t   rxwm        :   1; // Receive watermark enable
    volatile uint32_t               :   30;
} ie_bits;

typedef struct
{
    volatile uint32_t   txwm        :   1; // Transmit watermark pending
    volatile uint32_t   rxwm        :   1; // Receive watermark pending
    volatile uint32_t               :   30;
} ip_bits;

typedef struct
{
    volatile sckdiv_bits    sckdiv;         // (SPI offset 0x00) Serial clock divisor
    volatile sckmode_bits   sckmode;        // (SPI offset 0x04) Serial clock mode
    volatile uint32_t       Reserved1[2];
    volatile csid_bits      csid;           // (SPI offset 0x10) Chip select ID
    volatile csdef_bits     csdef;          // (SPI offset 0x14) Chip select default
    volatile csmode_bits    csmode;         // (SPI offset 0x18) Chip select mode
    volatile uint32_t       Reserved2[3];
    volatile delay0_bits    delay0;         // (SPI offset 0x28) Delay control 0
    volatile delay1_bits    delay1;         // (SPI offset 0x2C) Delay control 1
    volatile uint32_t       Reserved3[4];
    volatile fmt_bits       fmt;            // (SPI offset 0x40) Frame format
    volatile uint32_t       Reserved4[1];
    volatile txdata_bits    txdata;         // (SPI offset 0x48) Tx FIFO data
    volatile rxdata_bits    rxdata;         // (SPI offset 0x4C) Rx FIFO data
    volatile txmark_bits    txmark;         // (SPI offset 0x50) Tx FIFO watermark
    volatile rxmark_bits    rxmark;         // (SPI offset 0x54) Rx FIFO watermark
    volatile uint32_t       Reserved5[2];
    volatile fctrl_bits     fctrl;          // (SPI offset 0x60) SPI flash interface control*
    volatile ffmt_bits      ffmt;           // (SPI offset 0x64) SPI flash instruction format*
    volatile uint32_t       Reserved6[2];
    volatile ie_bits        ie;             // (SPI offset 0x70) SPI interrupt enable
    volatile ip_bits        ip;             // (SPI offset 0x74) SPI interrupt pending
    // Registers marked * are only present on controllers with the direct-map flash interface.

} SPI;

///////////////////////////////////////////////////////////////////////////////
// SPI
///////////////////////////////////////////////////////////////////////////////

#define QSPI0 ((SPI*) QSPI0_BASE)  // Set up pointer to struct of type SPI aligned at the base QSPI0 memory-mapped address
#define SPI1  ((SPI*) SPI1_BASE)  // Set up pointer to struct of type SPI aligned at the base SPI1 memory-mapped address
#define SPI2  ((SPI*) SPI2_BASE)  // Set up pointer to struct of type SPI aligned at the base SPI2 memory-mapped address

// Delay constants
#define COUNTS_PER_MS 898

/////////////////////////////////////////////////////////////////////
// GPIO Functions
/////////////////////////////////////////////////////////////////////

void pinMode(int pin, int function)
{
    switch(function) {
        case INPUT:
            GPIO0->input_en     |= (1 << pin);   // Sets a pin as an input
            break;
        case OUTPUT:
            GPIO0->output_en    |= (1 << pin);   // Set pin as an output
            GPIO0->iof_en       &= ~(1 << pin);
            break;
        case GPIO_IOF0:
            GPIO0->iof_sel      &= ~(1 << pin);
            GPIO0->iof_en       |= (1 << pin);
    }
}

void digitalWrite(int pin, int val)
{
    if (val) GPIO0->output_val |= (1 << pin);
    else     GPIO0->output_val &= ~(1 << pin);
}

int digitalRead(int pin)
{
    return (GPIO0->input_val >> pin) & 0x1;
}

/////////////////////////////////////////////////////////////////////
// Delay Functions
/////////////////////////////////////////////////////////////////////

void delayLoop(int ms) {
	// declare counter volatile so it isn't optimized away
	// counts_per_ms empirically determined such that delayLoop(100) waits 100 ms
	volatile int i = COUNTS_PER_MS * ms;
	
	while (i--); // count down time
}

/////////////////////////////////////////////////////////////////////
// SPI Functions
/////////////////////////////////////////////////////////////////////

/* Enables the SPI peripheral and intializes its clock speed (baud rate), polarity, and phase.
 *    -- clkdivide: (0 to 2^12-1). The SPI clk will be the master clock / 2*(div+1).
 *    -- cpol: clock polarity (0: inactive state is logical 0, 1: inactive state is logical 1).
 *    -- cpha: clock phase (0: data captured on leading edge of clk and changed on next edge,
 *             1: data changed on leading edge of clk and captured on next edge)
 */
void spiInit(uint32_t clkdivide, uint32_t cpol, uint32_t cpha)
{
    // Initially assigning SPI pins (GPIO 2-5 corresponding pins 10-13) to HW I/O function 0
    pinMode(2, GPIO_IOF0); // CS0
    pinMode(3, GPIO_IOF0); // MOSI
    pinMode(4, GPIO_IOF0); // MISO
    pinMode(5, GPIO_IOF0); // SCK

    SPI1->sckdiv.div = clkdivide; // Set the clock divisor

    SPI1->sckmode.pol = cpol; // Set the polarity
    SPI1->sckmode.pha = cpha; // Set the phase
    SPI1->csid.csid = 0x0; // Set the chip ID to 0

    SPI1->csmode.mode = 2; // CS configured as HOLD mode

    SPI1->fmt.proto = 0; // Set SPI protocol to Single. DQ0 (MOSI), DQ1 (MISO)
    SPI1->fmt.endian = 0; // Send MSb first
    SPI1->fmt.dir = 0; // Set SPI direction
    SPI1->fmt.len = 8; // 8 bits per frame
    SPI1->fctrl.en = 0; // Disable SPI flash mode

    SPI1->delay1.interxfr = 0; // No delay in between frames
    SPI1->delay0.cssck = 0; // Delay (in SCK cycles) between CS and SCK start
    SPI1->delay0.sckcs = 0; // Delay (in SCK cycles) between SCK end and CS deassert

    /*  Set up watermarks in order to check whether the values are ready to be
        written or read. It seems you should be able to just read the EMPTY and
        FULL flags for the RX and TX buffers respectively, but this doesn't
        seem to work. I've given up and just use the watermarks now since they 
        work reliably. The RX watermark is set to 0 so that it triggers
        whenever we get a single byte and the TX watermark is set to 0 so that
        it is true whenever we don't have any data in the TX
    */    
    SPI1->ie.rxwm = 1; // Enable rx watermark
    SPI1->ie.txwm = 1; // Enable tx watermark

    SPI1->rxmark.rxmark = 0; // Set rx watermark (in bytes)
    SPI1->txmark.txmark = 1; // Set tx watermark (in bytes)

}

/* Transmits a character (1 byte) over SPI and returns the received character.
 *    -- send: the character to send over SPI
 *    -- return: the character received over SPI */
uint8_t spiSendReceive(uint8_t send)
{
    while(!SPI1->ip.txwm); // Wait until transmit FIFO is ready for new data
    SPI1->txdata.data = send; // Transmit the character over SPI
    while(!SPI1->ip.rxwm);
    return SPI1->rxdata.data; // Return received character
}

/* Transmits 2 characters (2 byte) over SPI and returns the received character.
 *    -- send: the character to send over SPI
 *    -- return: the character received over SPI */
uint16_t spiSendReceive16(uint16_t data)
{
    uint16_t volatile rec = 0;
    uint8_t char1, char2;

    SPI1->csmode.mode = 2; // CS configured as HOLD mode
    char1 = spiSendReceive((data & 0xFF00) >> 8);
    char2 = spiSendReceive(data & 0x00FF);
    rec = (char1 << 8) | char2;
    SPI1->csmode.mode = 0; // CS configured as AUTO mode

    return rec; // Return received character
}

void spiWrite(uint8_t address, uint8_t value)
{
	spiSendReceive16(address << 8 | value);
}

uint8_t spiRead(uint8_t address)
{
    return (uint8_t) spiSendReceive16(address << 8 | (1 << 15));
}



