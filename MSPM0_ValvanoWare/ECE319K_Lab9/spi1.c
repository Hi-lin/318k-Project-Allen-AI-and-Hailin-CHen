// /* SPI1.c - MSPM0G3507 SPI1 with RX Interrupt Support */

// #include <ti/devices/msp/msp.h>
// #include "../inc/SPI.h"
// #include "../inc/Clock.h"
// #include "../inc/LaunchPad.h"

// /* =========================
//  * USER CONFIG
//  * ========================= */

// #define SPI1_SCLK_INDEX   PB0INDEX
// #define SPI1_CS_INDEX     PB7INDEX
// #define SPI1_PICO_INDEX   PB2INDEX
// #define SPI1_POCI_INDEX   PB17INDEX   // MISO

// // #define LCD_RST_INDEX    PB15INDEX
// // #define LCD_RS_INDEX     PA13INDEX

// #define LCD_RST_PIN      15
// #define LCD_RS_PIN       13

// /* =========================
//  * GLOBAL RX BUFFER (ISR WRITES THIS)
//  * ========================= */

// volatile uint8_t SPI1_RxData;
// volatile uint8_t SPI1_RxFlag = 0;

// /* =========================
//  * SPI1 INIT
//  * ========================= */

// void SPI1_Init(void)
// {
//     uint32_t busfreq = Clock_Freq();

//     /* Reset + power SPI11 */
//     SPI1->GPRCM.RSTCTL = 0xB1000003;
//     SPI1->GPRCM.PWREN  = 0x26000001;

//     /* Pin mux */
//     IOMUX->SECCFG.PINCM[SPI1_SCLK_INDEX] = 0x00000083;
//     IOMUX->SECCFG.PINCM[SPI1_CS_INDEX]   = 0x00000083;
//     IOMUX->SECCFG.PINCM[SPI1_PICO_INDEX] = 0x00000083;
//     IOMUX->SECCFG.PINCM[SPI1_POCI_INDEX] = 0x00000083;

//     /* LCD pins */
//     // IOMUX->SECCFG.PINCM[LCD_RST_INDEX] = 0x00000081;
//     // IOMUX->SECCFG.PINCM[LCD_RS_INDEX]  = 0x00000081;

//     Clock_Delay(24);

//     // GPIOB->DOE31_0 |= (1 << LCD_RST_PIN);
//     // GPIOA->DOE31_0 |= (1 << LCD_RS_PIN);

//     // GPIOB->DOUTSET31_0 = (1 << LCD_RST_PIN);
//     // GPIOA->DOUTSET31_0 = (1 << LCD_RS_PIN);

//     /* Clock */
//     SPI1->CLKSEL = 8;
//     SPI1->CLKDIV = 0;

//     if(busfreq <= 16000000)
//         SPI1->CLKCTL = 0;
//     else
//         SPI1->CLKCTL = busfreq / 16000000 - 1;

//     /* SPI1 config */
//     SPI1->CTL0 = 0x0027;
//     SPI1->CTL1 = 0x0015;

//     /* =========================
//      * ENABLE RX INTERRUPT
//      * ========================= */

//     SPI1->CPU_INT.IMASK = 0x01;   // RX interrupt enable

//     NVIC_EnableIRQ(SPI1_INT_IRQn);

//     SPI1_Reset();
// }

// uint8_t SPI1_Transfer(uint8_t data)
// {
//     while((SPI1->STAT & 0x02) == 0x00);

//     SPI1->TXDATA = data;

//     while((SPI1->STAT & 0x04) == 0x00);

//     return (uint8_t)SPI1->RXDATA;
// }



