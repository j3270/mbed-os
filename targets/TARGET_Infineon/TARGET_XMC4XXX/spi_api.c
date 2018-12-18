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

/***************************************************************** Includes **/
#include "pinmap.h"
#include "PeripheralPins.h"
#include "xmc4_helper.h"
#include "mbed_assert.h"
#include "spi_api.h"
#include "xmc_gpio.h"
#include "xmc_spi.h"

/****************************************************************** Defines **/
#define SPI_TIMEOUT 10000000

/****************************************************************** Globals **/

/* SPI configuration */
XMC_SPI_CH_CONFIG_t spi_cfg =
{
    .baudrate = 10000,
    .bus_mode = XMC_SPI_CH_BUS_MODE_MASTER,
    .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS,
    .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE
};

/**************************************************************** Functions **/

void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel)
{

    /* Sanity check arguments */
    MBED_ASSERT(obj);

    SPIName spi_mosi = (SPIName)pinmap_peripheral(mosi, PinMap_SPI_MOSI);
    SPIName spi_miso = (SPIName)pinmap_peripheral(miso, PinMap_SPI_MISO);
    SPIName spi_sclk = (SPIName)pinmap_peripheral(sclk, PinMap_SPI_SCLK);

    SPIName spi_data = (SPIName)pinmap_merge(spi_mosi, spi_miso);
    SPIName spi_cntl = (SPIName)pinmap_merge(spi_sclk, spi_data);

    SPIName spi= (SPIName)pinmap_merge(spi_data, spi_cntl);
    MBED_ASSERT((int)spi != NC);

    /* Get MOSI, SCLK and SSEL pin alternative functions */
    uint8_t mosi_function = (uint8_t)pinmap_function(mosi, PinMap_SPI_MOSI);
    uint8_t sclk_function = (uint8_t)pinmap_function(sclk, PinMap_SPI_SCLK);

    /* Get USIC BASE address */
    XMC_USIC_CH_t *channel = ((XMC_USIC_CH_t *)spi);
    obj->channel = channel;

    /* Get MISO pin function */
    pin_io_function_t *miso_cfg = get_pin_function(miso);
    uint8_t input_stage = 0;

    /* Set UART index */
    switch ((int)obj->channel) {
    case SPI_0:
        obj->idx = 0;
        obj->dx0 = miso_cfg->usic0_ch0_dx0;
        input_stage = XMC_SPI_CH_INPUT_DIN0;
        break;
    case SPI_1:
        obj->idx = 1;
        obj->dx0 = miso_cfg->usic0_ch1_dx0;
        input_stage = XMC_SPI_CH_INPUT_DIN0;
        break;
#ifdef USIC1

    case SPI_2:
        obj->idx = 2;
        obj->dx0 = miso_cfg->usic1_ch0_dx0;
        input_stage = XMC_SPI_CH_INPUT_DIN0;
        break;
    case SPI_3:
        obj->idx = 3;
        obj->dx0 = miso_cfg->usic1_ch1_dx0;
        input_stage = XMC_SPI_CH_INPUT_DIN0;
        break;
#endif
#ifdef USIC2

    case SPI_4:
        obj->idx = 4;
        obj->dx0 = miso_cfg->usic2_ch0_dx0;
        input_stage = XMC_SPI_CH_INPUT_DIN0;
        break;
    case SPI_5:
        obj->idx = 5;
        obj->dx0 = miso_cfg->usic2_ch1_dx0;
        input_stage = XMC_SPI_CH_INPUT_DIN0;
        break;
#endif
    }

    /* Get Port Base address */
    XMC_GPIO_PORT_t *port_mosi = (XMC_GPIO_PORT_t *)XMC4_GET_PORT_BASE_FROM_NAME(mosi);
    XMC_GPIO_PORT_t *port_miso = (XMC_GPIO_PORT_t *)XMC4_GET_PORT_BASE_FROM_NAME(miso);
    XMC_GPIO_PORT_t *port_sclk = (XMC_GPIO_PORT_t *)XMC4_GET_PORT_BASE_FROM_NAME(sclk);

    /*Initialize and Start SPI*/
    XMC_SPI_CH_Init(channel, &spi_cfg);

    /*Input source selected*/
    XMC_SPI_CH_SetInputSource(channel, input_stage, obj->dx0);
    XMC_SPI_CH_SetBitOrderMsbFirst(channel);
    XMC_SPI_CH_Start(channel);

    /*GPIO configuration*/
    XMC_GPIO_SetMode(port_mosi, XMC4_GET_PIN_NBR_FROM_NAME(mosi), XMC_GPIO_MODE_OUTPUT_PUSH_PULL | (mosi_function << PORT0_IOCR0_PC0_Pos));
    XMC_GPIO_SetMode(port_sclk, XMC4_GET_PIN_NBR_FROM_NAME(sclk), XMC_GPIO_MODE_OUTPUT_PUSH_PULL | (sclk_function << PORT0_IOCR0_PC0_Pos));
    XMC_GPIO_SetMode(port_miso, XMC4_GET_PIN_NBR_FROM_NAME(miso), XMC_GPIO_MODE_INPUT_TRISTATE);
}

void spi_free(spi_t *obj)
{

    /* Sanity check arguments */
    MBED_ASSERT(obj);

    XMC_SPI_CH_Stop(obj->channel);
}

void spi_format(spi_t *obj, int bits, int mode, int slave)
{

    /* Sanity check arguments */
    MBED_ASSERT(obj);

    /* Slave mode not supported */
    if(slave){
        MBED_ASSERT("SPI: Slave mode not supported!");
        return;
    }

    /* Set number of bits per frame (1-16) */
    XMC_SPI_CH_SetWordLength(obj->channel, bits);

    /* Set mode */
    uint32_t format;
    switch(mode){
    case 0:
        /* CPOL = 0, CPHA = 0 */
        format = XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_ENABLED;
        break;
    case 1:
        /* CPOL = 0, CPHA = 1 */
        format = XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_0_DELAY_DISABLED;
        break;
    case 2:
        /* CPOL = 1, CPHA = 0 */
        format = XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_ENABLED;
        break;
    case 3:
    default:
        /* CPOL = 1, CPHA = 1 */
        format = XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_1_DELAY_DISABLED;
        break;
    }
    XMC_SPI_CH_ConfigureShiftClockOutput(obj->channel, (XMC_SPI_CH_BRG_SHIFT_CLOCK_PASSIVE_LEVEL_t)format, XMC_SPI_CH_BRG_SHIFT_CLOCK_OUTPUT_SCLK);
}

void spi_frequency(spi_t *obj, int hz)
{

    /* Sanity check arguments */
    MBED_ASSERT(obj);

    XMC_SPI_CH_SetBaudrate(obj->channel, (uint32_t)hz);
}

int  spi_master_write(spi_t *obj, int value)
{

    /* Sanity check arguments */
    MBED_ASSERT(obj);

    uint32_t timeout = SPI_TIMEOUT;

    XMC_SPI_CH_EnableSlaveSelect(obj->channel, XMC_SPI_CH_SLAVE_SELECT_1);

    /* Sending a byte*/
    XMC_SPI_CH_Transmit(obj->channel, value, XMC_SPI_CH_MODE_STANDARD);

    /* Wait till the byte has been transmitted */
    while(!(XMC_SPI_CH_GetStatusFlag(obj->channel) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION) && (timeout--));
    XMC_SPI_CH_ClearStatusFlag(obj->channel, XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION);


    XMC_SPI_CH_ClearStatusFlag(obj->channel, XMC_SPI_CH_STATUS_FLAG_MSLS_EVENT_DETECTED );
    XMC_SPI_CH_DisableSlaveSelect(obj->channel);
    while(!(XMC_SPI_CH_GetStatusFlag(obj->channel) & XMC_SPI_CH_STATUS_FLAG_MSLS_EVENT_DETECTED ) && (timeout--));
    XMC_SPI_CH_ClearStatusFlag(obj->channel, XMC_SPI_CH_STATUS_FLAG_MSLS_EVENT_DETECTED );

    //return XMC_SPI_CH_GetReceivedData(obj->channel);
    return XMC_SPI_CH_GetReceivedData(obj->channel);
}

int spi_master_block_write(spi_t *obj, const char *tx_buffer, int tx_length, char *rx_buffer, int rx_length, char write_fill)
{

    int total = (tx_length > rx_length) ? tx_length : rx_length;

    for (int i = 0; i < total; i++) {
        char out = (i < tx_length) ? tx_buffer[i] : write_fill;
        char in = spi_master_write(obj, out);
        if (i < rx_length) {
            rx_buffer[i] = in;
        }
    }

    return total;
}

int  spi_slave_receive(spi_t *obj)
{

    /* Not supported */
    return 0;
}

int  spi_slave_read(spi_t *obj)
{

    /* Not supported */
    return 0;
}

void spi_slave_write(spi_t *obj, int value)
{

    /* Not supported */
}

int  spi_busy(spi_t *obj)
{

    /* Sanity check arguments */
    MBED_ASSERT(obj);

    if(XMC_SPI_CH_GetStatusFlag(obj->channel) & XMC_SPI_CH_STATUS_FLAG_TRANSMIT_SHIFT_INDICATION){
        return 1;
    }
    return 0;
}

uint8_t spi_get_module(spi_t *obj)
{

    /* Sanity check arguments */
    MBED_ASSERT(obj);

    return obj->idx;
}

/*EOF*/
