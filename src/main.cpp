#include <Arduino.h>
#include <SPI.h>
#include "define.h"

void setup()
{
  // put your setup code here, to run once:
  pinMode(user_Led, OUTPUT);
  Serial.begin(115200);

  /* SPI initialisieren 
   * SPI CLock        => 20 MHz
   * SPI Bitorder     => MSBFirst
   * SPI clk polarity => 0
   * SPI clk Phase    => 0
   * SPI Output Edge  => Falling
   * SPI Data Capture => Rising
   */

  SPIClass SPI;
  SPISettings mySettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0);
  digitalWrite(SS, HIGH);
  SPI.beginTransaction(mySettings);
  SPI.begin();

  // Print the SPI-Pins to the Serial Port
  Serial.println("[INFO] MISO: ");
  Serial.println(MISO);
  Serial.println("[INFO] SCLK: ");
  Serial.println(SCK);
  Serial.println("[INFO] MOSI: ");
  Serial.println(MOSI);
  Serial.println("[INFO] CS: ");
  Serial.println(SS);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(user_Led, 1);
  delay(100);
  digitalWrite(user_Led, 0);
  delay(100);

  uint8_t spi_data_send = 0XFF;
  uint8_t spi_data_receive = 0x00;
  digitalWrite(SS, LOW);
  Serial.println("Chip Select is Low\n");
  spi_data_receive = SPI.transfer(spi_data_send);
  digitalWrite(SS, HIGH);

  if (spi_data_receive == 0xFF)
  {
    digitalWrite(user_Led, HIGH);
    delay(1000);
    digitalWrite(user_Led, 0);
    delay(1000);
    Serial.println("Data was received\n");
    spi_data_receive = 0x00;
  }
  delay(1000);
}