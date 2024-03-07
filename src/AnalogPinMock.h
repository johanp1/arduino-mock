#ifndef __ARDUINO_ANALOG_PIN_MOCK_H_
#define __ARDUINO_ANALOG_PIN_MOCK_H_

#include <cmath>

class MockAnalogPin  // the context class in state pattern
{
public:
   MockAnalogPin(unsigned const char resolution = 10, float reference_voltage = 5.0) : resolution_(resolution), reference_voltage_(reference_voltage) {ad_val_ = 0;};
   ~MockAnalogPin() {};

   unsigned int AnalogRead(void)
   {
      return ad_val_;
   };

   void SetAnalogVoltage(float const v_)
   {
      float analog_voltage = v_ <= reference_voltage_ ? v_ : reference_voltage_;
      float a = pow(2.0f, (float)resolution_) - 1;
      ad_val_ = (unsigned int)(a*analog_voltage/reference_voltage_);
   };

   void SetAnalogAdVal(unsigned ad_val)
   {
      ad_val_ = ad_val;
   }

   void SetResolution(unsigned const char resolution)
   {
      resolution_ = resolution;
   };

private:
   unsigned ad_val_;
   unsigned char resolution_;
   float reference_voltage_;
};

#endif /* __ARDUINO_ANALOG_PIN_MOCK_H_ */