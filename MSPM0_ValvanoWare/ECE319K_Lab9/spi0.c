/* SPI0.c - MSPM0G3507 SPI0 with RX Interrupt Support */

#include <ti/devices/msp/msp.h>
#include "../inc/SPI.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"

/* =========================
 * USER CONFIG
 * ========================= */

#define SPI0_SCLK_INDEX   PA11INDEX
#define SPI0_CS_INDEX     PA8INDEX
#define SPI0_PICO_INDEX   PB17INDEX
#define SPI0_POCI_INDEX   PA10INDEX   // MISO

// #define LCD_RST_INDEX    PB15INDEX
// #define LCD_RS_INDEX     PA13INDEX

#define LCD_RST_PIN      15
#define LCD_RS_PIN       13

/* =========================
 * GLOBAL RX BUFFER (ISR WRITES THIS)
 * ========================= */

volatile uint8_t SPI0_RxData;
volatile uint8_t SPI0_RxFlag = 0;

/* =========================
 * SPI0 INIT
 * ========================= */

void SPI0_Init(void)
{
    uint32_t busfreq = Clock_Freq();

    /* Reset + power SPI01 */
    SPI0->GPRCM.RSTCTL = 0xB1000003;
    SPI0->GPRCM.PWREN  = 0x26000001;

    /* Pin mux */
    IOMUX->SECCFG.PINCM[SPI0_SCLK_INDEX] = 0x00000083;
    IOMUX->SECCFG.PINCM[SPI0_CS_INDEX]   = 0x00000083;
    IOMUX->SECCFG.PINCM[SPI0_PICO_INDEX] = 0x00000083;
    IOMUX->SECCFG.PINCM[SPI0_POCI_INDEX] = 0x00000081;

    /* LCD pins */
    // IOMUX->SECCFG.PINCM[LCD_RST_INDEX] = 0x00000081;
    // IOMUX->SECCFG.PINCM[LCD_RS_INDEX]  = 0x00000081;

    Clock_Delay(24);

    // GPIOB->DOE31_0 |= (1 << LCD_RST_PIN);
    // GPIOA->DOE31_0 |= (1 << LCD_RS_PIN);

    // GPIOB->DOUTSET31_0 = (1 << LCD_RST_PIN);
    // GPIOA->DOUTSET31_0 = (1 << LCD_RS_PIN);
    
    /* Clock */
    SPI0->CLKSEL = 8;
    SPI0->CLKDIV = 0;

    if(busfreq <= 16000000)
        SPI0->CLKCTL = 0;
    else
        SPI0->CLKCTL = busfreq / 16000000 - 1;

    /* SPI0 config */
    SPI0->CTL0 = 0x0027;
    SPI0->CTL1 = 0x0015;

    /* =========================
     * ENABLE RX INTERRUPT
     * ========================= */

    SPI0->CPU_INT.IMASK = 0x01;   // RX interrupt enable

    NVIC_EnableIRQ(SPI0_INT_IRQn);

}

uint8_t SPI0_Transfer(uint8_t data)
{
    //while((SPI0->STAT & 0x02) == 0x00);

    SPI0->TXDATA = data;

    //while((SPI0->STAT & 0x04) == 0x00);

    return (uint8_t)SPI0->RXDATA;
}



