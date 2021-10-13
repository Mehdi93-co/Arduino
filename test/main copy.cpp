#include <ESP32SPISlave.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "JsonController.h"

ESP32SPISlave slave;

static constexpr uint32_t BUFFER_SIZE{32};
uint8_t spi_slave_tx_buf[BUFFER_SIZE] = {0xFF};
uint8_t spi_slave_rx_buf[BUFFER_SIZE];

void setup()
{
    // Input string for the JsonControllerTest
    char input[] = "{\"date\":\"08 Nov 2017\",\"high\":\"48\",\"low\":\"39\",\"text\":\"Rain\"}";
    const size_t capacity = JSON_OBJECT_SIZE(4);

    // Serial init for Debug
    Serial.begin(115200);
    delay(2000);

    /*
    * Slave initialisation
    * HSPI = CS: 15, CLK: 14, MOSI: 13, MISO: 12
    * VSPI = CS: 5, CLK: 18, MOSI: 23, MISO: 19
    */
    slave.setDataMode(SPI_MODE0);
    slave.setQueueSize(1); // transaction queue size
    //slave.begin();          // default SPI is HSPI
    slave.begin(VSPI); // you can use VSPI like this

    // Print the SPI-Pins to the Serial Port
    Serial.println("[INFO] MISO: ");
    Serial.println(MISO);
    Serial.println("[INFO] SCLK: ");
    Serial.println(SCK);
    Serial.println("[INFO] MOSI: ");
    Serial.println(MOSI);
    Serial.println("[INFO] CS: ");
    Serial.println(SS);

    
    //Jsonobj = &Ojbectbuf.
    JsonController JsonControllerTest(input, capacity);
    JsonControllerTest.Serialprint();
    Serial.println();
    Serial.println(JsonControllerTest.getstring());
}

void loop()
{
    // block until the transaction comes from master
    slave.wait(spi_slave_rx_buf, spi_slave_tx_buf, BUFFER_SIZE);

    // if transaction has completed from master,
    // available() returns size of results of transaction,
    // and buffer is automatically updated

    while (slave.available())
    {
        // show received data
        for (auto i = 0; i < BUFFER_SIZE; ++i)
            printf("%d ", spi_slave_rx_buf[i]);
        printf("\n");

        slave.pop();
    }
}