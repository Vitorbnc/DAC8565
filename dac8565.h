#ifndef DAC8565_H
#define DAC8565_H

/**
* Library for communicating with DAC8565
* Vitor Barbosa, 2020
*/

#define DAC8565_SINGLE_CH_STORE  0x00
#define DAC8565_SINGLE_CH_UPDATE 0x10
#define DAC8565_SIMULT_UPDATE 0x20
#define DAC8565_BROAD_UPDATE 0x30

#define DAC8565_MAX 0x7FFF
#define DAC8565_MIN 0x8000



class DAC8565{
	public:
	DAC8565(uint8_t sync_pin, uint32_t spi_clock_freq = 16000000);
	void updateCh(uint8_t ch,int16_t data);
	//void updateAll(int16_t data);
	//void updateAll();
	
	private:
	uint8_t _cs;
	uint8_t _ldac;
	uint32_t _spi_clock;
	
};


#endif