#include "one_wire.h"

#define SENSOR_DATA 17
#define SENSOR_POWER 16

One_wire one_wire(SENSOR_DATA);
rom_address_t address{};

void setup() {
    pinMode(SENSOR_POWER, OUTPUT);
    digitalWrite(SENSOR_POWER, HIGH);
    Serial.begin(115200);
    //stdio_init_all();
    one_wire.init();
}

void loop() {
    one_wire.single_device_read_rom(address);
    Serial.print("Address: ");
    printAddress(address);
    Serial.println();
    one_wire.convert_temperature(address, true, false);
    Serial.print("Temperature: ");
    Serial.println(one_wire.temperature(address));
    //printf("Temperature: %3.1foC\n", one_wire.temperature(address));
    sleep_ms(1000);
}

void printAddress(rom_address_t &deviceAddress) {
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress.rom[i] < 16) Serial.print("0");
    Serial.print(deviceAddress.rom[i], HEX);
  }
}
