
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
#include "Arduino.h"
#include "Wire.h"


TwoWire::TwoWire()
{
    rx_buffer.clear();
    tx_buffer.clear();

    transfer_addr = 0;

    twi_status = UNINITIALIZED;
}

void TwoWire::begin(uint8_t scl, uint8_t sda, uint32_t speed)
{
    PinName nrf_sda;
    PinName nrf_scl;
    
    if(twi_status != UNINITIALIZED)
        return;
    
    nrf_scl = Pin_Arduino_to_nRF52(scl);
    nrf_sda = Pin_Arduino_to_nRF52(sda);

    /* Initialize i2c */
    i2c_init(&i2c, nrf_sda, nrf_scl);
    i2c_frequency(&i2c, speed);
    twi_status = INITIALIZED;
}

void TwoWire::begin(void)
{
    begin(DEFAULT_SCL, DEFAULT_SDA, TWI_FREQUENCY_100K);
}

void TwoWire::end(void)
{
    // Do nothing
}

void TwoWire::setClock(uint32_t speed)
{
    i2c_frequency(&i2c, speed);
}

void TwoWire::beginTransmission(uint8_t address)
{
    transfer_addr = (address << 1);
    tx_buffer.clear();

    twi_status = MASTER_SEND;
}

void TwoWire::beginTransmission(int address)
{
    beginTransmission((uint8_t)address);
}

/**
 * 0:success
 * 1:data too long to fit in transmit buffer
 * 2:received NACK on transmit of address
 * 3:received NACK on transmit of data
 * 4:other error
 */
int8_t TwoWire::endTransmission(bool stop)
{
    int8_t  result;
    uint8_t index;
    uint8_t buf[RING_BUFFER_MAX_SIZE];

    index = 0;
    while(tx_buffer.available()) {
        buf[index++] = tx_buffer.read();
    }
    result = i2c_write(&i2c, transfer_addr, (const char*)buf, index, stop);

    rx_buffer.clear();
    twi_status = MASTER_IDLE;

    if(index == result)
        result = 0;
    else
        result = 4;

    return result;
}

int8_t TwoWire::endTransmission(void)
{
    return endTransmission(true);
}

size_t TwoWire::write(uint8_t data)
{
    // Right status and buffer not full
    if((twi_status == MASTER_SEND) && (tx_buffer.isFull() == 0x00)) {
        tx_buffer.store(data);
        return 0x01;
    }
    else {
        return 0x00;
    }
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
    size_t index;

    index = 0x00;
    while(quantity--) {
        if(this->write(data[index]) == 0x00)
            break;
        index++;
    }
    return index;
}

uint8_t TwoWire::requestFrom(uint8_t addr, uint8_t quantity, uint8_t stop)
{
    uint8_t ret;
    uint8_t index;
    uint8_t buf[RING_BUFFER_MAX_SIZE];

    transfer_addr = (addr << 1);

    if(quantity > RING_BUFFER_MAX_SIZE)
        quantity = RING_BUFFER_MAX_SIZE;

    if(quantity > 0 ) {
        ret = i2c_read(&i2c, transfer_addr, (char*)buf, quantity, stop);
    }
    else {
        ret = 0;
    }
    // Store data to rx_buffer
    for(index=0; index<quantity; index++) {
        rx_buffer.store(buf[index]);
    }

    return ret;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
    return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
    return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
    return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

int TwoWire::available(void)
{
    return rx_buffer.available();
}
/**********************************************************************
name :
function :
**********************************************************************/
int TwoWire::read(void)
{
    return rx_buffer.read();
}
/**********************************************************************
name :
function :
**********************************************************************/
int TwoWire::peek(void)
{
    return rx_buffer.peek();
}
/**********************************************************************
name :
function :
**********************************************************************/
void TwoWire::flush(void)
{
    rx_buffer.clear();
}

TwoWire Wire;

