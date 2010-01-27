//
// Copyright 2010 Ettus Research LLC
//

#ifndef INCLUDED_USRP_UHD_USRP_DBOARD_INTERFACE_HPP
#define INCLUDED_USRP_UHD_USRP_DBOARD_INTERFACE_HPP

#include <boost/shared_ptr.hpp>
#include <stdint.h>

namespace usrp_uhd{ namespace usrp{ namespace dboard{

/*!
 * The daughter board interface to be subclassed.
 * A dboard instance interfaces with the mboard though this api. 
 * This interface provides i2c, spi, gpio, atr, aux dac/adc access.
 * Each mboard should have a specially tailored dboard interface.
 */
class interface{
public:
    typedef boost::shared_ptr<interface> sptr;

    //tells the host which device to use
    enum spi_dev_t{
        SPI_TX_DEV,
        SPI_RX_DEV
    };

    //args for writing spi data
    enum spi_push_t{
        SPI_PUSH_RISE,
        SPI_PUSH_FALL
    };

    //args for reading spi data
    enum spi_latch_t{
        SPI_LATCH_RISE,
        SPI_LATCH_FALL
    };

    //tell the host which gpio bank
    enum gpio_bank_t{
        GPIO_TX_BANK,
        GPIO_RX_BANK
    };

    //structors
    interface(void);
    virtual ~interface(void);

    /*!
     * Write to an aux dac.
     * \param which_dac the dac index 0, 1, 2, 3...
     * \param value the value to write
     */
    virtual void write_aux_dac(int which_dac, int value) = 0;

    /*!
     * Read from an aux adc.
     * \param which_adc the adc index 0, 1, 2, 3...
     * \return the value that was read
     */
    virtual int read_aux_adc(int which_adc) = 0;

    /*!
     * Set daughterboard ATR register.
     * The ATR register for a particular bank has 2 values:
     * one value when transmitting, one when receiving.
     * The mask controls which pins are controlled by ATR.
     *
     * \param bank      GPIO_TX_BANK or GPIO_RX_BANK
     * \param tx_value  16-bits, 0=FPGA input, 1=FPGA output
     * \param rx_value  16-bits, 0=FPGA input, 1=FPGA output
     * \param mask      16-bits, 0=ignore, 1=atr
     */
    virtual void set_atr_reg(gpio_bank_t bank, uint16_t tx_value, uint16_t rx_value, uint16_t mask) = 0;

    /*!
     * Set daughterboard GPIO data direction register.
     *
     * \param bank      GPIO_TX_BANK or GPIO_RX_BANK
     * \param value     16-bits, 0=FPGA input, 1=FPGA output
     * \param mask      16-bits, 0=ignore, 1=set
     */
    virtual void set_gpio_ddr(gpio_bank_t bank, uint16_t value, uint16_t mask) = 0;

    /*!
     * Set daughterboard GPIO pin values.
     *
     * \param bank     GPIO_TX_BANK or GPIO_RX_BANK
     * \param value    16 bits, 0=low, 1=high
     * \param mask     16 bits, 0=ignore, 1=set
     */
    virtual void write_gpio(gpio_bank_t bank, uint16_t value, uint16_t mask) = 0;

    /*!
     * Read daughterboard GPIO pin values
     *
     * \param bank GPIO_TX_BANK or GPIO_RX_BANK
     * \return the value of the gpio bank
     */
    virtual uint16_t read_gpio(gpio_bank_t bank) = 0;

    /*!
     * \brief Write to I2C peripheral
     * \param i2c_addr I2C bus address (7-bits)
     * \param buf the data to write
     */
    virtual void write_i2c(int i2c_addr, const std::string &buf) = 0;

    /*!
     * \brief Read from I2C peripheral
     * \param i2c_addr I2C bus address (7-bits)
     * \param len number of bytes to read
     * \return the data read if successful, else a zero length string.
     */
    virtual std::string read_i2c(int i2c_addr, size_t len) = 0;

    /*!
     * \brief Write data to SPI bus peripheral.
     *
     * \param dev which spi device
     * \param push args for writing
     * \param buf the data to write
     */
    virtual void write_spi(spi_dev_t dev, spi_push_t push, const std::string &buf) = 0;

    /*!
     * \brief Read data from SPI bus peripheral.
     *
     * \param dev which spi device
     * \param push args for reading
     * \param len number of bytes to read
     * \return the data read if sucessful, else a zero length string.
     */
    virtual std::string read_spi(spi_dev_t dev, spi_latch_t latch, size_t len) = 0;

    /*!
     * \brief Get the rate of the rx dboard clock.
     * \return the clock rate
     */
    virtual double get_rx_clock_rate(void) = 0;

    /*!
     * \brief Get the rate of the tx dboard clock.
     * \return the clock rate
     */
    virtual double get_tx_clock_rate(void) = 0;

};

}}} //namespace

#endif /* INCLUDED_USRP_UHD_USRP_DBOARD_INTERFACE_HPP */
