
#include "JsonController.h"
#include <HardwareSerial.h>

/*
 * Konstruktor 
 * @parm Referece für den String von der SPI
 * @parm size des Json Doc 
*/

JsonController::JsonController(char *_InputString, const int Capacity)
{
    //StaticJsonDocument<200> doc;
    const int capacityOfFile = JSON_OBJECT_SIZE(4);
    StaticJsonBuffer<capacityOfFile> buf;
    this->_JsonObject = &buf.parseObject(_InputString);

    if (_JsonObject->success())
    {
        Serial.println("[INFO] parseObject() is succeeded");
    }
    else
    {
        Serial.println("[INFO] parseObject() is failed");
    
    }

    //DynamicJsonBuffer Jsonbuf(Capacity);
    //this->_JsonObject = Jsonbuf.parseObject(_InputString);
}

JsonController::~JsonController()
{
}

void JsonController::Serialprint()
{
    _JsonObject->printTo(Serial);
}

const char *JsonController::getstring()
{
    return this->_JsonObject->get<const char*>("date");
}