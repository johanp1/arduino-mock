#include "Arduino.h"
#include <iostream>
#include <gtest/gtest.h>
#include <EEPROM.h>
#include "avr/wdt.h"

std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();
bool isrCalled = false;

ISR(interruptServiceRoutine)
{
   isrCalled = true;
}

void setup()
{  
   Serial.clear();
   arduinoStub->Reset();
   EEPROM.clear();
}
   
void teardown()
{
}

TEST(ArduinoMockTestGroup, Init)
{
   ASSERT_TRUE(arduinoStub->GetMode(0) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(1) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(2) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(3) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(4) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(5) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(6) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(7) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(8) == PinMode_Input);

   ASSERT_TRUE(Serial.available() == 0);
}

// test all overloads of Serial.print
TEST(ArduinoMockTestGroup, SerialPrint)
{
   String test_string = String("test");
   Serial.print(test_string);
   ASSERT_TRUE(Serial.getData().compare("test") == 0);

   Serial.print("bepa_123");
   ASSERT_TRUE(Serial.getData().compare("bepa_123") == 0);

   Serial.print(987);
   ASSERT_TRUE(Serial.getData().compare("987") == 0);
}

// test all overloads of Serial.println
TEST(ArduinoMockTestGroup, SerialPrintln)
{
   String test_string = String("tset");
   Serial.print(test_string);
   ASSERT_TRUE(Serial.getData().compare("tset") == 0);

   Serial.println("apa_321");
   ASSERT_TRUE(Serial.getData().compare("apa_321\n") == 0);

   Serial.println(789);
   ASSERT_TRUE(Serial.getData().compare("789\n") == 0);
}

TEST(ArduinoMockTestGroup, ReadInputPin)
{
   MockDigitalPin testPin;

   ASSERT_TRUE(testPin.MockGetMode() == PinMode_Input);
   testPin.MockSetDigitalRead(PinState_Low);
   ASSERT_TRUE(testPin.DigitalRead() == PinState_Low);

   testPin.MockSetDigitalRead(PinState_High);
   ASSERT_TRUE(testPin.DigitalRead() == PinState_High);
   ASSERT_TRUE(testPin.MockGetMode() == PinMode_Input);
}


TEST(ArduinoMockTestGroup, WriteOutputPin)
{
   MockDigitalPin testPin;
   
   testPin.SetMode(PinMode_Output);
   ASSERT_TRUE(testPin.MockGetMode() == PinMode_Output);
   ASSERT_TRUE(testPin.MockGetDigitalWrite() == PinState_Low);

   testPin.DigitalWrite(PinState_High);
   ASSERT_TRUE(testPin.MockGetDigitalWrite() == PinState_High);

   testPin.DigitalWrite(PinState_Low);
   ASSERT_TRUE(testPin.MockGetDigitalWrite() == PinState_Low);
}

TEST(ArduinoMockTestGroup, AnalogWritePin)
{
   MockDigitalPin testPin;
   
   ASSERT_TRUE(testPin.MockGetAnalogWrite() == 0);

   testPin.AnalogWrite(100);
   ASSERT_TRUE(testPin.MockGetAnalogWrite() == 100);
}

TEST(ArduinoMockTestGroup, WriteInputPin)
{
   MockDigitalPin testPin;
   
   ASSERT_TRUE(testPin.MockGetMode() == PinMode_Input);
   ASSERT_TRUE(testPin.MockGetDigitalWrite() == PinState_Low);

   testPin.DigitalWrite(PinState_High);
   ASSERT_TRUE(testPin.MockGetDigitalWrite() == PinState_High);
   ASSERT_TRUE(testPin.MockGetMode() == PinMode_InputPullUp);
}


TEST(ArduinoMockTestGroup, ArduinoReadInputPin)
{
   ASSERT_TRUE(digitalRead(0) == LOW);
   arduinoStub->SetDigitalRead(0, PinState_High);
   ASSERT_TRUE(digitalRead(0) == HIGH);
}

TEST(ArduinoMockTestGroup, ArduinoWriteOutputPin)
{
   pinMode(0, OUTPUT);
   ASSERT_TRUE(arduinoStub->GetMode(0) == OUTPUT);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(0) == PinState_Low);
   digitalWrite(0, HIGH);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(0) == PinState_High);
}

TEST(ArduinoMockTestGroup, ArduinoAnalogWritePin)
{
   ASSERT_TRUE(arduinoStub->GetAnalogWrite(0) == 0);
   analogWrite(0, 250);
   ASSERT_TRUE(arduinoStub->GetAnalogWrite(0) == 250);
}

// check that nothing catastrophic happens if index outside of bounds
TEST(ArduinoMockTestGroup, ArduinoDigitalPinOutOfBound)
{
/*   CHECK_THROWS(out_of_range, digitalWrite(9, HIGH));
   CHECK_THROWS(out_of_range, digitalRead(9));
   CHECK_THROWS(out_of_range, pinMode(9, OUTPUT));*/
}

TEST(ArduinoMockTestGroup, ReadAnalogPinBasic)
{
   MockAnalogPin testPin;

   ASSERT_TRUE(testPin.AnalogRead() == 0);

   testPin.SetAnalogVoltage(5);
   ASSERT_EQ(testPin.AnalogRead(), 1023);

   testPin.SetAnalogVoltage(0);
   ASSERT_EQ(testPin.AnalogRead(), 0);

   testPin.SetAnalogVoltage(1.2f);
   ASSERT_EQ(testPin.AnalogRead(), (unsigned int)(1023*1.2/5));

   testPin.SetAnalogVoltage(5.5f);
   ASSERT_EQ(testPin.AnalogRead(), 1023);
}

TEST(ArduinoMockTestGroup, ReadAnalogPinReferenceResolution)
{
   MockAnalogPin testPin(12, 3.3f);

   ASSERT_TRUE(testPin.AnalogRead() == 0);

   testPin.SetAnalogVoltage(3.3f);
   ASSERT_TRUE(testPin.AnalogRead() == 4095);
}

TEST(ArduinoMockTestGroup, ArduinoReadAnalogPin)
{
   ASSERT_TRUE(analogRead(0) == 0);
   arduinoStub->SetAnalogPinVoltage(0, 2.5f);
   ASSERT_TRUE(analogRead(0) == (unsigned int)(1023*2.5f/5));
}

TEST(ArduinoMockTestGroup, ArduinoReadAnalogPin2)
{
   arduinoStub->SetAnalogPinAdVal(0, 500);
   ASSERT_EQ(analogRead(0), 500);
}

// check that nothing catastrophic happens if index outside of bounds
TEST(ArduinoMockTestGroup, ArduinoAnalogPinOutOfBound)
{
   //CHECK_THROWS(out_of_range, analogRead(4));
}


TEST(ArduinoMockTestGroup, ArduinoStringConcatTests)
{
  String s = String("apa");
  
  s.concat(1);
  ASSERT_TRUE(s.compare("apa1") == 0);
  s.concat("2");
  ASSERT_TRUE(s.compare("apa12") == 0);
  s.concat((byte)3);
  ASSERT_TRUE(s.compare("apa123") == 0);
  s.concat("_");
  s.concat(3.14159f);
  ASSERT_TRUE(s.compare("apa123_3.14159") == 0);
}

TEST(ArduinoMockTestGroup, ArduinoStringEqOperatorTest)
{
   String lhs = String("apa");
   String rhs1 = String("bepa");
   String rhs2 = String("apa");

   ASSERT_FALSE(lhs == rhs1);
   ASSERT_TRUE(lhs == rhs2);
}

TEST(ArduinoMockTestGroup, ArduinoStringSetCharAtTest)
{
   String str = String("apa_bepa");
   
   str.setCharAt(3, '2');
   ASSERT_TRUE(str.s.compare("apa2bepa") == 0);

   str.setCharAt(str.s.length(), 'q'); // index > string size
   ASSERT_TRUE(str.s.compare("apa2bepa") == 0);

}

TEST(ArduinoMockTestGroup, ArduinoStringToIntTest)
{
   String str = String("54");
   ASSERT_TRUE(str.toInt() == 54);

   String str2 = String("invalid");
   ASSERT_TRUE(str2.toInt() == 0);
}

TEST(ArduinoMockTestGroup, ArduinoStringToFlaotTest)
{
   String str = String("54.0");
   ASSERT_TRUE(str.toFloat() == 54.0f);

   String str2 = String("invalid");
   ASSERT_TRUE(str2.toFloat() == 0);
}

TEST(ArduinoMockTestGroup, ArduinoTimeTest)
{
   ASSERT_TRUE(millis() == 0);
   ASSERT_TRUE(micros() == 0);

   delay(10); // 10 ms delay...

   ASSERT_TRUE(millis() == 10);
   ASSERT_TRUE(micros() == 10000);

   delayMicroseconds(1000); // 10 ms delay...

   ASSERT_TRUE(millis() == 11);
   ASSERT_TRUE(micros() == 11000);
}

TEST(ArduinoMockTestGroup, ArduinoISRtest)
{
   interruptServiceRoutine();
   ASSERT_TRUE(isrCalled);
}

TEST(ArduinoMockTestGroup, eepromWriteTest)
{
   ASSERT_TRUE(EEPROM[0] == 0);
   EEPROM.write(0, 1);
   ASSERT_TRUE(EEPROM[0] == 1);

   ASSERT_TRUE(EEPROM[1] == 0);
   EEPROM.write(1, 33);
   ASSERT_TRUE(EEPROM.read(1) == 33);

   ASSERT_TRUE(EEPROM[2] == 0);
   EEPROM.update(2, 22);
   ASSERT_TRUE(EEPROM[2] == 22);

   float a = 1.1f;
   float b = 2.2f;
   float read_back = 0.0f;

   EEPROM.put(0, a);
   EEPROM.put(sizeof(a), b);

   EEPROM.get(0, read_back);
   ASSERT_FLOAT_EQ(read_back, 1.1);
   EEPROM.get(sizeof(a), read_back);
   ASSERT_FLOAT_EQ(read_back, 2.2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}