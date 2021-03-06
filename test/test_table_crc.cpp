#define BOOST_TEST_MODULE test_modbus_slave
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <type_traits>

#include "table_crc.h"

BOOST_AUTO_TEST_SUITE (test_suite_main)

BOOST_AUTO_TEST_CASE(crc)
{
    uint8_t buffer[256] {0};
    
    buffer[0] = 1;
    buffer[1] = 3; 
    buffer[2] = 0;
    buffer[3] = 5;
    buffer[4] = 0;
    buffer[5] = 1;

    uint16_t crc_online = 0x0B94;
    auto [low1, high1] = CRC16(&buffer[0], &buffer[6]);

    BOOST_CHECK_EQUAL(low1, 0x94);
    BOOST_CHECK_EQUAL(high1, 0x0B);

    buffer[0] = 7;
    buffer[1] = 16;
    buffer[2] = 0;
    buffer[3] = 2;
    buffer[4] = 0;
    buffer[5] = 1;
    buffer[6] = 2;
    buffer[7] = 0;
    buffer[8] = 8;

    crc_online = 0xD48D;
    auto [low2, high2] = CRC16(&buffer[0], &buffer[9]);
    BOOST_CHECK_EQUAL(low2, 0x8D);
    BOOST_CHECK_EQUAL(high2, 0xD4);

    buffer[0] = 7;
    buffer[1] = 0x10;
    buffer[2] = 0;
    buffer[3] = 2;
    buffer[4] = 0;
    buffer[5] = 3;
    buffer[6] = 6;
    buffer[7] = 0x16;
    buffer[8] = 0x26; // [7] and [8] = 5670
    buffer[9] = 0xFF;
    buffer[10] = 0xDE; // [9] and [10] = -34
    buffer[11] = 0;
    buffer[12] = 7;

    crc_online = 0x5154;
    auto [low3, high3] = CRC16(&buffer[0], &buffer[13]);
    BOOST_CHECK_EQUAL(low3, 0x54);
    BOOST_CHECK_EQUAL(high3, 0x51);
}

BOOST_AUTO_TEST_SUITE_END()
