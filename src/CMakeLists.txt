add_library(arduinoMock
    arduino_stubs.cpp
    PinMock.cpp
    SerialStub.cpp
    String.cpp
    EEPROM.cpp)
target_include_directories(arduinoMock PUBLIC .)
