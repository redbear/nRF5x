
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

#ifndef _WIRE_H_
#define _WIRE_H_

#include "WStream.h"
#include "wiring_buffer.h"


#define TWI_FREQUENCY_100K  100000
#define TWI_FREQUENCY_250K  250000
#define TWI_FREQUENCY_400K  400000


class TwoWire : public WStream
{
public :
    enum TwoWireStatus {
        UNINITIALIZED,
        INITIALIZED,
        MASTER_IDLE,
        MASTER_SEND,
        MASTER_RECV,
        SLAVE_IDLE,
        SLAVE_RECV,
        SLAVE_SEND
    };

protected :

    Ring_Buffer rx_buffer;
    Ring_Buffer tx_buffer;

    uint8_t transfer_addr;

    i2c_t   i2c;

    TwoWireStatus twi_status;

public :
    /**
     * @brief Constructor, clear buffer and status.
     */
    TwoWire();
    /**
     * @brief Init twi with default params.
     *        Use I2C1 module, speed 100KHz
     */
    void begin(void);
    /**
     * @brief Init twi with user-defined params.
     *
     * @params[in]  scl_pin
     * @params[in]  sda_pin
     * @params[in]  speed      TWI_FREQUENCY_100K(100000)
     *                         TWI_FREQUENCY_250K(250000)
     *                         TWI_FREQUENCY_400K(400000)
     */
    void begin(uint8_t scl_pin, uint8_t sda_pin, uint32_t speed);
    /**
     * @brief DeInit twi(do nothing)
     */
    void end(void);
    /**
     * @brief Set frequency
     *
     * @params[in]  speed      TWI_FREQUENCY_100K(100000)
     *                         TWI_FREQUENCY_250K(250000)
     *                         TWI_FREQUENCY_400K(400000)
     */
    void setClock(uint32_t speed);
    /**
     * @brief Start a transmission
     *
     * @params[in]  address
     */
    void beginTransmission(uint8_t address);
    void beginTransmission(int address);
    /**
     * @brief Finish a transmission
     *        Note : Only return 0 or 4 now!!
     *
     * @return  0:success
     *          1:data too long to fit in transmit buffer
     *          2:received NACK on transmit of address
     *          3:received NACK on transmit of data
     *          4:other error
     */
    int8_t endTransmission(void);
    int8_t endTransmission(bool stop);
    /**
     * @brief Read data from slave
     *
     * @return  The length of read data
     */
    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
    uint8_t requestFrom(int, int);
    uint8_t requestFrom(int, int, int);
    /**
     * @brief Virtual functions
     */
    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *, size_t);
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);
    /**
     * @brief Write functions from Print
     */
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }

    using Print::write;
};

extern TwoWire Wire;

#endif
