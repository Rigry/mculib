#pragma once

#include "periph.h"

#if defined(STM32F0)
   // #include "f0_dma.h"
#elif defined(STM32F1)
   #include "f1_dma_stream.h"
#elif defined(STM32F4)
   #include "f4_dma.h"
#endif