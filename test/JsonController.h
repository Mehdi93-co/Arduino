

#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class JsonController
{
private:
    size_t _capacity;
    char *InputSting;
    JsonObject *_JsonObject;

public:
    JsonController(char *_InputString, const int Capacity);
    ~JsonController();
    void Serialprint();
    const char *getstring();
};
