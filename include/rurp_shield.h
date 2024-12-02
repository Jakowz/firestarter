/*
 * Project Name: Firestarter
 * Copyright (c) 2024 Henrik Olsson
 *
 * Permission is hereby granted under MIT license.
 */

#ifndef RURP_SHIELD_H
#define RURP_SHIELD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "config.h"

// Constants
#define CONFIG_VERSION  "VER05"

// Default configuration
#define ARDUINO_VCC 5.01
#define VALUE_R1 270000
#define VALUE_R2 44000

// Bit masks
#define LEAST_SIGNIFICANT_BYTE 0x01  // LEAST SIGNIFICANT BYTE
#define MOST_SIGNIFICANT_BYTE 0x02   // MOST SIGNIFICANT BYTE
#define OUTPUT_ENABLE 0x04           // OUTPUT ENABLE
#define CONTROL_REGISTER 0x08        // CONTROL REGISTER
#define USRBTN 0x10                  // USER BUTTON
#define CHIP_ENABLE 0x20             // CHIP ENABLE


// CONTROL REGISTER
#ifndef HARDWARE_REVISION
#define VPE_TO_VPP      0x01
#define A16             VPE_TO_VPP
#define A9_VPP_ENABLE   0x02
#define VPE_ENABLE      0x04
#define P1_VPP_ENABLE   0x08
#define A17             0x10
#define A18             0x20
#define RW              0x40
#define REGULATOR       0x80

#else
#define REVISION_0 0
#define REVISION_1 1
#define REVISION_2 2

#define A16             0x01
#define A9_VPP_ENABLE   0x02
#define VPE_ENABLE      0x04
#define P1_VPP_ENABLE   0x08
#define A17             0x10
#define A18             0x20
#define RW              0x40
#define REGULATOR       0x80
#define VPE_TO_VPP      0x100

#endif

#define A13             0x20

#ifndef HARDWARE_REVISION
#define register_t uint8_t
#else
#define register_t uint16_t
#endif

// Struct definition
    typedef struct  {
        char version[6];
        double vcc;
        long  r1;
        long  r2;
        uint8_t hardware_revision; 
    } rurp_configuration_t;

    // Function prototypes
    void  rurp_setup();

    void rurp_set_programmer_mode();
    void rurp_set_communication_mode();
    void rurp_log(const char* type, const char* msg);
    
    void rurp_set_data_as_output();
    void rurp_set_data_as_input();

    void rurp_set_control_pin(uint8_t pin, uint8_t state);

    void rurp_write_to_register(uint8_t reg, register_t data);
    register_t rurp_read_from_register(uint8_t reg);

    void rurp_write_data_buffer(uint8_t data);
    uint8_t rurp_read_data_buffer();

    double rurp_read_vcc();
    double rurp_read_voltage();
    double rurp_get_voltage_average();
    rurp_configuration_t* rurp_get_config();
    void rurp_save_config();
#ifdef HARDWARE_REVISION
    int rurp_get_hardware_revision();
    int rurp_get_physical_hardware_revision();
#endif

#ifdef __cplusplus
}
#endif

#endif // RURP_SHIELD_H
