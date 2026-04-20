/* SPI0.h - MSPM0G3507 SPI0 Driver with RX Interrupt Support */

#ifndef SPI0_H
#define SPI0_H

#include <stdint.h>
#include <ti/devices/msp/msp.h>

/* =========================
 * PUBLIC VARIABLES (ISR FLAGS)
 * ========================= */

// Last received byte from SPI0 interrupt
extern volatile uint8_t SPI0_RxData;

// Set to 1 when a new byte arrives via interrupt
extern volatile uint8_t SPI0_RxFlag;

/* =========================
 * FUNCTION PROTOTYPES
 * ========================= */

/**
 * @brief Initialize SPI0 peripheral (pins, clock, interrupts)
 */
void SPI0_Init(void);

/**
 * @brief Full-duplex SPI transfer (blocking)
 * @param data Byte to send on MOSI
 * @return Byte received from MISO
 */
uint8_t SPI0_Transfer(uint8_t data);

/**
 * @brief SPI0 interrupt handler (must be defined in SPI0.c or startup file)
 */
void SPI0_IRQHandler(void);

/**
 * @brief Optional reset function (if implemented in SPI0.c)
 */
void SPI0_Reset(void);

#endif