/**
* Library for communicating with DAC8565
* Vitor Barbosa, 2020
*/

#include "Arduino.h"
#include "dac8565.h"
#include "SPI.h"

//Teensy 3.x specific
#ifndef _kinetis_h_
#define digitalWriteFast(pin,val) digitalWrite(pin,val)
#endif

DAC8565::DAC8565(uint8_t sync_pin, uint32_t spi_clock_freq ){
	_cs = sync_pin;
	_spi_clock = spi_clock_freq;
	pinMode(_cs,OUTPUT);
	digitalWrite(_cs,HIGH);
	SPI.begin();
}

void DAC8565::updateCh(uint8_t ch,int16_t data){
		
	uint8_t buf[3];
	//1st byte LSB is power down command, keeping it zero
	buf[0] = DAC8565_SINGLE_CH_UPDATE|(ch<<1);
	buf[1] = (data>>8)&0xFF;
	buf[2] = data&0xFF;
	digitalWriteFast(_cs,LOW);
	//Datasheet specifies CPHA=1:data is sampled on falling edge, mode should be either 1 or 2
	//SPI.beginTransaction(SPISettings(16000000,MSBFIRST, SPI_MODE1));
	SPI.beginTransaction(SPISettings(_spi_clock,MSBFIRST, SPI_MODE1));
	SPI.transfer(buf,3);
	SPI.endTransaction();
	digitalWriteFast(_cs,HIGH);	
}
