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
  SPISettings mySettings(20000000, MSBFIRST, SPI_MODE0);
  digitalWrite(SS, HIGH);
  SPI.beginTransaction(mySettings);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(user_Led, 1);
  delay(100);
  digitalWrite(user_Led, 0);
  delay(100);

  byte spi_data_send = 0XFF;
  byte spi_data_receive;
  digitalWrite(SS, LOW);
  Serial.println("Chip Select is Low\n");
  spi_data_receive = SPI.transfer(spi_data_send);

  if (spi_data_receive == 0x0F)
  {
    digitalWrite(user_Led, HIGH);
    delay(100);
    digitalWrite(user_Led, 0);
    Serial.println("Data was received\n");
  }
  delay(1000);
}