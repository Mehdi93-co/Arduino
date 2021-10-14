#include <Arduino.h>

#include <ArduinoJson.h>
#include "JsonController.h"

void setup()
{
  // put your setup code here, to run once:
  //JsonController TestController();
  Serial.begin(115200);
/*
  const char JsonStringTest[] = "{\"filters\":\"HP\", \"frequency\":10, \"type\": 1, \"bypass\": 0}";
  const size_t SizeOfFile = 96;
  JsonDocument *_JsonDoc;

  StaticJsonDocument<SizeOfFile> JsonDocTest;
  DynamicJsonDocument ptrJsonDocTest(SizeOfFile);
  _JsonDoc = &JsonDocTest;
  //deserializeJson(*_JsonDoc, JsonStringTest);
  deserializeJson(*_JsonDoc, JsonStringTest);
  //serializeJson(&_JsonDoc, Serial);
  serializeJson(*_JsonDoc, Serial);
  //serializeJsonPretty(_JsonDoc->getElement("HP"), printBuffer);
*/

  /* ============================================================== */
  /*                       JsonController_TEST                      */
  /* ============================================================== */

  Serial.println("[TEST] type ist:");
  testJsonController();
  
}

void loop()
{
  // put your main code here, to run repeatedly:
}