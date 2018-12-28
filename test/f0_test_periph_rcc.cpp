#define BOOST_TEST_MODULE f0_test_periph_rcc
#include <boost/test/unit_test.hpp>

#define F_CPU   48000000UL
#define STM32F030x6

#include "periph_rcc.h"
#include "timeout.h"
#include <iostream>
#include <type_traits>
#include <thread>

// dont exist in CMSIS f0, but exist in f1
#define RCC_AHBENR_DMA1EN_Msk RCC_AHBENR_DMAEN_Msk

#include "f0_f1_f4_f7_test_periph_rcc.h"
