
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

#ifndef SPI_MASTER_H_
#define SPI_MASTER_H_

#include "Arduino.h"

#define SPI_125K    125000
#define SPI_250K    250000
#define SPI_500K    500000
#define SPI_1M      1000000
#define SPI_2M      2000000
#define SPI_4M      4000000
#define SPI_8M      8000000

#define SPI_MODE0   0
#define SPI_MODE1   1
#define SPI_MODE2   2
#define SPI_MODE3   3


class SPIClass
{
public:
    /**
     * @brief The constructor
     */
    SPIClass(void);
    /**
     * @brief Init SPI module with default pins
     */
    void begin(void);
    /**
     * @brief Init SPI module with user-defined pins
     *
     * @param[in]  scl
     * @param[in]  mosi
     * @param[in]  miso
     */
    void begin(uint8_t scl, uint8_t mosi, uint8_t miso);
    /**
     * @brief DeInit the SPI module
     */
    void end(void);
    /**
     * @brief Start a transfer (Do nothing)
     */
    void beginTransaction(void);
    /**
     * @brief Transfer one byte
     *
     * @param[in]  data
     *
     * @return  The reply data
     */
    uint8_t transfer(uint8_t data);
    /**
     * @brief Finish a transfer (Do nothing)
     */
    void endTransaction(void);
    /**
     * @brief Set spi mode
     *        This also set bitOrder to MSBFIRST, so don't use setBitORDER befor this
     *
     * @param[in] mode  SPI_MODE0 : (CPOL = 0, CPHA = 0)
     *                  SPI_MODE1 : (CPOL = 0, CPHA = 1)
     *                  SPI_MODE2 : (CPOL = 1, CPHA = 0)
     *                  SPI_MODE3 : (CPOL = 1, CPHA = 1)
     */
    void setSPIMode(uint8_t mode);
    /**
     * @brief Set SPI frequency
     *
     * @param[in]  speed  SPI frequency in HZ : SPI_125K(125000)
     *                                          SPI_125K(125000)
     *                                          SPI_250K(250000)
     *                                          SPI_500K(500000)
     *                                          SPI_1M(1000000)
     *                                          SPI_2M(2000000)
     *                                          SPI_4M(4000000)
     *                                          SPI_8M(8000000)
     */
    void setFrequency(uint32_t speed );
    /**
     * @brief Set bit mode of data, only support MSBFIRST(Do nothing)
     *        This must be after setSPIMode
     *
     * @param[in] bit  MSBFIRST or LSBFIRST
     */
    void setBitORDER(BitOrder bit);

protected:

    spi_t    spi;
};

extern SPIClass     SPI_Master;

#endif
