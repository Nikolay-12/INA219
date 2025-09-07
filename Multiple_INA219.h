/**
 * @file Multiple_INA219.h
 * @author Malinin Nikolai
 */

//PUBLIC

namespace Multiple_INA219
{
    struct ina219_module
    {
        I2C_HandleTypeDef* hi2c;
        uint8_t addr;
        bool present;
        uint16_t current;
    };

    //Globals
    extern ina219_module ina219_modules[];

    //Public methods
    void init(I2C_HandleTypeDef* hi2c);
    void calibration();
    void read_current();
}
