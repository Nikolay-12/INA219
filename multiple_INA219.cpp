#include "multiple_INA219.h"
#include "ina219.h"
#include <math.h>

//PRIVATE
#define NUMBER_OF_INA219 = 3
#define MY_INA219_CAL_MAGIC 33554.4 /* Divide by ohms */
#define MY_INA219_CURRENT_LSB 1.2207E-6
uint8_t INA219_ADDRESSES[4] ={0x40, 0x41, 0x44, 0x45};

//PUBLIC

namespace Multiple_INA219
{
    //Globals
    ina219_module ina219_modules[NUMBER_OF_INA219];

	for (size_t i = 0; i < NUMBER_OF_INA219; i++)
	{
		auto& m = ina219_modules[i];
		m.addr = INA219_ADDRESSES[i];
	}
		
    //Public methods
    void init(I2C_HandleTypeDef* i2c_instance)
    {
        if (!i2c_instance) Serial.println("Failed to find INA219_01 chip");
        for (size_t i = 0; i < NUMBER_OF_INA219; i++)
        {
            auto& m = ina219_modules[i];
            m.hi2c = i2c_instance;
        }
    }

    void calibration()
    {
        uint16_t cfg = INA219_CONFIG_BVOLTAGERANGE_16V |
	             INA219_CONFIG_GAIN_1_40MV | INA219_CONFIG_BADCRES_12BIT |
	             INA219_CONFIG_SADCRES_12BIT_128S_69MS |
	             INA219_CONFIG_MODE_SVOLT_CONTINUOUS;
        for (size_t i = 0; i < NUMBER_OF_INA219; i++)
        {
            auto& m = ina219_modules[i];
            if (!m.hi2c) continue;
            m.present = INA219_Init(m.hi2c, m.addr);
            if (!m.present) continue;
            INA219_setConfig(m.hi2c, m.addr, cfg);
            INA219_setCalibration(m.hi2c, m.addr, 
				static_cast<uint16_t>(roundf(MY_INA219_CAL_MAGIC / m.r_shunt)), MY_INA219_CURRENT_LSB);
        }
    }

    void read_current()
    {
        for (size_t i = 0; i < NUMBER_OF_INA219; i++)
        {
            auto& m = ina219_modules[i];
            if (!m.present) continue;
            m.current = INA219_ReadCurrent(m.hi2c, m.addr);
        }
    }
}
