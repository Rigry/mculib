#pragma once

#include "periph_tim.h"
#include "periph_rcc.h"
#include "pin.h"

#if defined(USE_MOCK_TIM)
using TIM = mock::TIM;
#else
using TIM = mcu::TIM;
#endif

class Encoder
{
   Pin& pin_a;
   Pin& pin_b;
   TIM& tim;
   Encoder(Pin& pin_a, Pin& pin_b, TIM& tim)
      : pin_a{pin_a}
      , pin_b{pin_b}
      , tim{tim}
   {}
public:
   template <mcu::Periph tim_, class Pin_a, class Pin_b, bool inverted = false>
   static auto& make ()
   {
      TIM::pin_static_assert<tim_, Pin_a>();
      TIM::pin_static_assert<tim_, Pin_b>();

      constexpr auto pin_mode_a = TIM::pin_mode<tim_, Pin_a>();
      constexpr auto pin_mode_b = TIM::pin_mode<tim_, Pin_b>();
      constexpr auto channel_a = TIM::channel<tim_, Pin_a>();
      constexpr auto channel_b = TIM::channel<tim_, Pin_b>();

      static Encoder encoder
      {
         Pin::make<Pin_a, pin_mode_a>(),
         Pin::make<Pin_b, pin_mode_b>(),
         mcu::make_reference<tim_>()
      };

      mcu::make_reference<mcu::Periph::RCC>().clock_enable<tim_>();

      encoder.tim.set(TIM::SlaveMode::Encoder3)
                 .template set<channel_a>(TIM::SelectionCompareMode::Input)
                 .template set<channel_b>(TIM::SelectionCompareMode::Input);
      if (inverted)
         encoder.tim.template set<channel_a>(TIM::Polarity::falling);
      encoder.tim.clear_counter()
                 .counter_enable();

      return encoder;
   }

   int16_t operator= (int16_t v){tim.set_counter(v); return *this;}
           operator  uint16_t()  {return tim.get_counter();}
   bool    operator> (int16_t v){return static_cast<int16_t> (tim.get_counter()) > v;}
};