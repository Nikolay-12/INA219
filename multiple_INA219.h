/**
 * @file multiple_INA219.h
 * @author Malinin Nikolai
 */

//PUBLIC

namespace multiple_INA219
{
    struct module_t
    {
        I2C_HandleTypeDef* hi2c;
    };

    //Globals
    extern module_t modules[];

    //Public methods
    void init(I2C_HandleTypeDef* hi2c);
    void colibration(I2C_HandleTypeDef* hi2c);
    void read_current();
}
