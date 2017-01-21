
/*
    Copyright (c) 2014 RedBearLab, All rights reserved.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "SPI_Master.h"

/****************** end of static functions ******************************/

SPIClass::SPIClass(void)
{
    //do nothing
}

void SPIClass::begin(uint8_t scl, uint8_t mosi, uint8_t miso)
{
    PinName nrf_scl, nrf_mosi, nrf_miso;

    nrf_scl  = Pin_Arduino_to_nRF52(scl);
    nrf_mosi = Pin_Arduino_to_nRF52(mosi);
    nrf_miso = Pin_Arduino_to_nRF52(miso);

    spi_init(&spi, nrf_mosi, nrf_miso, nrf_scl, (PinName)NC);
    /* 8-bits, MODE0, master(0)/slave(1) */
    spi_format(&spi, 8, SPI_MODE0, 0);
    /* Default speed : 1MHz */
    spi_frequency(&spi, SPI_1M);
}

void SPIClass::begin(void)
{
    begin(DEFAULT_SCK, DEFAULT_MOSI, DEFAULT_MISO);
}

void SPIClass::end(void)
{
    spi_free(&spi);
}

void SPIClass::beginTransaction(void)
{
    // Do nothing
}

uint8_t SPIClass::transfer(uint8_t data)
{
    return ((uint8_t)spi_master_write(&spi, data));
}

void SPIClass::endTransaction(void)
{
    // Do nothing
}

void SPIClass::setSPIMode(uint8_t mode)
{
    if(mode > 3)
        return;
    /* 8-bits, MODE0, master(0)/slave(1) */
    spi_format(&spi, 8, mode, 0);
}

void SPIClass::setFrequency(uint32_t speed)
{
    /* Default speed : 1MHz */
    spi_frequency(&spi, speed);
}

void SPIClass::setBitORDER(BitOrder bit)
{
    //spi_BitOrder(&spi, bit);
    //Do nothing
}


SPIClass    SPI_Master;

