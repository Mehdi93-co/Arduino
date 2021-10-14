

#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include "plugin.h"
#include "configDefines.h"

class JsonController
{
private:
    size_t _capacity = 0;
    DynamicJsonDocument *_jsonDoc;
    uint8_t _error;
    uint8_t _errorNo;

public:
    JsonController(const size_t Capacity);
    ~JsonController();
    void reset(void);
    bool isError(void);
    String processCmd(String jsonString);
    //String getValue(uint8_t cmdType, uint8_t channelNo);
    void setValueHP(JsonObject &root);
    void getValueHP(JsonObject &jsonResponse);

    void setValueLShlv(JsonObject &root);
    void getValueLShlv(JsonObject &jsonResponse);

    void setValuePEQ(JsonObject &root);
    void getValuePEQ(JsonObject &jsonResponse);

    void setValueHShlv(JsonObject &root);
    void getValueHShlv(JsonObject &jsonResponse);

    void setValueLP(JsonObject &root);
    void getValueLP(JsonObject &jsonResponse);

    void setValuePhase(JsonObject &root);
    void getValuePhase(JsonObject &jsonResponse);

    void setValueDelay(JsonObject &root);
    void getValueDelay(JsonObject &jsonResponse);

    void setValueGain(JsonObject &root);
    void getValueGain(JsonObject &jsonResponse);

    void setValueVolume(JsonObject &root);
    void getValueVolume(JsonObject &jsonResponse);

    void setValuePreset(JsonObject &root);
    void getValuePreset(JsonObject &jsonResponse);

    void setValue(JsonObject &root);

    void showCmd(void);
};

void testJsonController(void);