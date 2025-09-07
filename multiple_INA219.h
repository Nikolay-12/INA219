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
        bool present;
        uint16_t current;
    };

    //Globals
    extern module_t modules[];

    //Public methods
    void init(I2C_HandleTypeDef* hi2c);
    void colibration();
    void read_current();
}
