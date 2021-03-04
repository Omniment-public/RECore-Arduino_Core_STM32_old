
/*
    RECoreLSM6Library.cpp - RECore onboard LSM6 Library
    Copyright (c) 2021 Omniment Inc. All right reserved.

    MIT License

*/

#if defined(ARDUINO_ARCH_STM32)

#include <Arduino.h>
#include "RECoreLSM6Library.h"

//SPIClass SPI_2(26, 27, 28, 25);

void RECoreLSM6Library::init() {
    SPI_2 = new SPIClass(26, 27, 28, 25);
    SPI_2 -> beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
    SPI_2 -> begin(25);
  //SPI_2 = new SPIClass(PB15, PB14, PB13, PB12);
  //SPI_2 = new SPIClass(26, 27, 28, 25);
  //SPI_2.begin(25);
  //SPI_2.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
  //return SPI_2;

}

void RECoreLSM6Library::send_spi_data(uint8_t send_data, bool rw) {
  //rw : write -> true
  if (!rw) {
    send_data = send_data | 0x80;
  }
  SPI_2 -> transfer(send_data);
}

void RECoreLSM6Library::receive_spi_data(uint8_t* receive_data, uint8_t len) {
  for (int i = 0; i < len; i++) {
    receive_data[i] = SPI_2 -> transfer(0x00);
  }
}

bool RECoreLSM6Library::get_comp(){
    return init_comp;
}

#endif // ARDUINO_ARCH_STM32
