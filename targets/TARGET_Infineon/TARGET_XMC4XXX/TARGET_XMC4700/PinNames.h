/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

/***************************************************************** Includes **/
#include "cmsis.h"
#include "XMC4700.h"

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************** Pin Names **/
typedef enum {
    P0_0  = 0x00,
    P0_1  = 0x01,
    P0_2  = 0x02,
    P0_3  = 0x03,
    P0_4  = 0x04,
    P0_5  = 0x05,
    P0_6  = 0x06,
    P0_7  = 0x07,
    P0_8  = 0x08,
    P0_9  = 0x09,
    P0_10 = 0x0A,
    P0_11 = 0x0B,
    P0_12 = 0x0C,
    P0_13 = 0x0D,
    P0_14 = 0x0E,
    P0_15 = 0x0F,

    P1_0  = 0x10,
    P1_1  = 0x11,
    P1_2  = 0x12,
    P1_3  = 0x13,
    P1_4  = 0x14,
    P1_5  = 0x15,
    P1_6  = 0x16,
    P1_7  = 0x17,
    P1_8  = 0x18,
    P1_9  = 0x19,
    P1_10 = 0x1A,
    P1_11 = 0x1B,
    P1_12 = 0x1C,
    P1_13 = 0x1D,
    P1_14 = 0x1E,
    P1_15 = 0x1F,

    P2_0  = 0x20,
    P2_1  = 0x21,
    P2_2  = 0x22,
    P2_3  = 0x23,
    P2_4  = 0x24,
    P2_5  = 0x25,
    P2_6  = 0x26,
    P2_7  = 0x27,
    P2_8  = 0x28,
    P2_9  = 0x29,
    P2_10 = 0x2A,
    P2_11 = 0x2B,
    P2_12 = 0x2C,
    P2_13 = 0x2D,
    P2_14 = 0x2E,
    P2_15 = 0x2F,

    P3_0  = 0x30,
    P3_1  = 0x31,
    P3_2  = 0x32,
    P3_3  = 0x33,
    P3_4  = 0x34,
    P3_5  = 0x35,
    P3_6  = 0x36,
    P3_7  = 0x37,
    P3_8  = 0x38,
    P3_9  = 0x39,
    P3_10 = 0x3A,
    P3_11 = 0x3B,
    P3_12 = 0x3C,
    P3_13 = 0x3D,
    P3_14 = 0x3E,
    P3_15 = 0x3F,

    P4_0  = 0x40,
    P4_1  = 0x41,
    P4_2  = 0x42,
    P4_3  = 0x43,
    P4_4  = 0x44,
    P4_5  = 0x45,
    P4_6  = 0x46,
    P4_7  = 0x47,

    P5_0  = 0x50,
    P5_1  = 0x51,
    P5_2  = 0x52,
    P5_3  = 0x54,
    P5_4  = 0x55,
    P5_5  = 0x51,
    P5_6  = 0x56,
    P5_7  = 0x57,
    P5_8  = 0x58,
    P5_9  = 0x59,
    P5_10 = 0x5A,
    P5_11 = 0x5B,

    P6_0  = 0x60,
    P6_1  = 0x61,
    P6_2  = 0x62,
    P6_3  = 0x64,
    P6_4  = 0x65,
    P6_5  = 0x61,
    P6_6  = 0x66,

    P7_0  = 0x70,
    P7_1  = 0x71,
    P7_2  = 0x72,
    P7_3  = 0x74,
    P7_4  = 0x75,
    P7_5  = 0x71,
    P7_6  = 0x76,
    P7_7  = 0x77,
    P7_8  = 0x78,
    P7_9  = 0x79,
    P7_10 = 0x7A,
    P7_11 = 0x7B,

    P8_0  = 0x80,
    P8_1  = 0x81,
    P8_2  = 0x82,
    P8_3  = 0x84,
    P8_4  = 0x85,
    P8_5  = 0x81,
    P8_6  = 0x86,
    P8_7  = 0x87,
    P8_8  = 0x88,
    P8_9  = 0x89,
    P8_10 = 0x8A,
    P8_11 = 0x8B,

    P9_0  = 0x90,
    P9_1  = 0x91,
    P9_2  = 0x92,
    P9_3  = 0x94,
    P9_4  = 0x95,
    P9_5  = 0x91,
    P9_6  = 0x96,
    P9_7  = 0x97,
    P9_8  = 0x98,
    P9_9  = 0x99,
    P9_10 = 0x9A,
    P9_11 = 0x9B,

    P14_0  = 0xE0,
    P14_1  = 0xE1,
    P14_2  = 0xE2,
    P14_3  = 0xE3,
    P14_4  = 0xE4,
    P14_5  = 0xE5,
    P14_6  = 0xE6,
    P14_7  = 0xE7,
    P14_8  = 0xE8,
    P14_9  = 0xE9,
    P14_10 = 0xEA,
    P14_11 = 0xEB,
    P14_12 = 0xEC,
    P14_13 = 0xED,
    P14_14 = 0xEE,
    P14_15 = 0xEF,

    P15_2  = 0xF2,
    P15_3  = 0xF3,
    P15_4  = 0xF4,
    P15_5  = 0xF5,
    P15_6  = 0xF6,
    P15_7  = 0xF7,
    P15_8  = 0xF8,
    P15_9  = 0xF9,
    P15_10 = 0xFA,
    P15_11 = 0xFB,
    P15_12 = 0xFC,
    P15_13 = 0xFD,
    P15_14 = 0xFE,
    P15_15 = 0xFF,

    LED1    = P5_9,
    LED2    = P5_8,
    SW1     = P15_13,
    SW2     = P15_12,

    USBTX   = P1_5,
    USBRX   = P1_4,

    //Arduino pin names
    D0  = P2_15,
    D1  = P2_14,
    D2  = P1_0,
    D3  = P1_1,
    D4  = P1_8,
    D5  = P2_12,
    D6  = P2_11,
    D7  = P1_9,
    D8  = P1_10,
    D9  = P1_11,
    D10 = P3_10,
    D11 = P3_8,
    D12 = P3_7,
    D13 = P3_9,
    D14 = P3_15,
    D15 = P0_13,

    A0 = P14_0,
    A1 = P14_1,
    A2 = P14_2,
    A3 = P14_3,
    A4 = P14_4,
    A5 = P14_5,

    //CAN XCVR Pin Names
    CAN_TX = P1_12,
    CAN_RX = P1_13,

    //Serial Flash Memory Pin Names
    SERIAL_FLASH_CLK  = P4_2,
    SERIAL_FLASH_CS   = P4_3,
    SERIAL_FLASH_HOLD = P4_4,
    SERIAL_FLASH_WP   = P4_5,
    SERIAL_FLASH_MOSI = P4_6,
    SERIAL_FLASH_MISO = P4_7,

    //microSD Card
    SDMMC_CLK = P3_6,
    SDMMC_CMD = P3_5,
    SDMMC_D0  = P4_0,
    SDMMC_D1  = P1_6,
    SDMMC_D2  = P1_7,
    SDMMC_D3  = P4_1,

    //Pins used for ethernet TBD
    
    NC    = (int)0xFFFFFFFF
} PinName;

/*********************************************************** Pin Directions **/
typedef enum {
    PIN_INPUT,
    PIN_OUTPUT,
    PIN_INPUT_OUTPUT
} PinDirection;

/**************************************************************** Pin Modes **/
typedef enum {
    INPUT_TRISTATE = 0x0UL << PORT0_IOCR0_PC0_Pos,
    INPUT_PULL_DOWN = 0x1UL << PORT0_IOCR0_PC0_Pos,
    INPUT_PULL_UP = 0x2UL << PORT0_IOCR0_PC0_Pos,
    INPUT_SAMPLING = 0x3UL << PORT0_IOCR0_PC0_Pos,
    INPUT_INVERTED_TRISTATE = 0x4UL << PORT0_IOCR0_PC0_Pos,
    NPUT_INVERTED_PULL_DOWN = 0x5UL << PORT0_IOCR0_PC0_Pos,
    INPUT_INVERTED_PULL_UP = 0x6UL << PORT0_IOCR0_PC0_Pos,
    INPUT_INVERTED_SAMPLING = 0x7UL << PORT0_IOCR0_PC0_Pos,
    OUTPUT_PUSH_PULL = 0x80UL,
    OUTPUT_OPEN_DRAIN = 0xc0UL,
    PullNone = INPUT_TRISTATE,
    PullDefault = INPUT_TRISTATE
} PinMode;

#ifdef __cplusplus
}
#endif

#endif

/*EOF*/
