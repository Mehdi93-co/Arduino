
#include <string.h>
#include "JsonController.h"

/* ============================================================== */
JsonController::JsonController(const size_t Capacity)
{
    _capacity = Capacity;
    _jsonDoc = new DynamicJsonDocument(Capacity);
    reset();
}
JsonController::~JsonController()
{
    delete _jsonDoc;
}

/* ============================================================== */
void JsonController::reset(void)
{
    _error = NOERROR;
}

/* ============================================================== */
bool JsonController::isError(void)
{
    return (_error != NOERROR);
}

/* ============================================================== */
String JsonController::processCmd(String jsonString)
{
    String returnValue;
    _jsonDoc->clear();
    reset();
    deserializeJson(*_jsonDoc, jsonString);
    showCmd();
    JsonObject root = (*_jsonDoc).as<JsonObject>();
    uint8_t cmdType = root["cmdType"];
    //softMuteDAC();
    switch (cmdType)
    {
    case cmdTypeSet_HP:
        setValueHP(root);
        break;
    case cmdTypeGet_HP:
        getValueHP(root);
        break;
    case cmdTypeSet_LShlv:
        setValueLShlv(root);
        break;
    case cmdTypeGet_LShlv:
        getValueLShlv(root);
        break;
    case cmdTypeSet_PEQ:
        setValuePEQ(root);
        break;
    case cmdTypeGet_PEQ:
        getValuePEQ(root);
        break;
    case cmdTypeSet_HShlv:
        setValueHShlv(root);
        break;
    case cmdTypeGet_HShlv:
        getValueHShlv(root);
        break;
    case cmdTypeSet_LP:
        setValueLP(root);
        break;
    case cmdTypeGet_LP:
        getValueLP(root);
        break;
    case cmdTypeSet_Phase:
        setValuePhase(root);
        break;
    case cmdTypeGet_Phase:
        getValuePhase(root);
        break;
    case cmdTypeSet_Delay:
        setValueDelay(root);
        break;
    case cmdTypeGet_Delay:
        getValueDelay(root);
        break;
    case cmdTypeSet_Gain:
        setValueGain(root);
        break;
    case cmdTypeGet_Gain:
        getValueGain(root);
        break;
    case cmdTypeSet_Volume:
        setValueVolume(root);
        break;
    case cmdTypeGet_Volume:
        getValueVolume(root);
        break;
    case cmdTypeSet_Preset:
        setValuePreset(root);
        break;
    case cmdTypeGet_Preset:
        getValuePreset(root);
        break;
    default:
        break;
    }

    if (isError())
    {
        root["status"] = String("ERROR");
        //Serial.println("[ERROR NUMBER] " + String(_errorNo));
    }
    else
    {
        root.clear();
        root["status"] = String("OK");
    }

    serializeJson(root, returnValue);
    return returnValue;
    //softUnmuteDAC();
}

/* ============================================================== */
//String JsonController::getValue(uint8_t cmdType, uint8_t channelNo)
//{
//    String output;
//    _jsonDoc->clear();
//
//    uint8_t cmdType = root["cmdType"];
//    switch (cmdType)
//    {
//    case cmdTypeGet_HP:
//        getValueHp(channelNo);
//        break;
//
//    default:
//        break;
//    }
//
//    serializeJson(*_jsonDoc, output);
//    return output;
//}

/* ============================================================== */
void JsonController::showCmd(void)
{
    serializeJsonPretty(*_jsonDoc, Serial);

    Serial.println("\n[INFO] FileCapacity: " + String(_capacity));
}

/* ======================= HIGHPASS Filter ====================== */
void JsonController::setValueHP(JsonObject &root)
{
    Serial.println("[INFO] setValueHp(void):");

    uint32_t idx = static_cast<uint32_t>(root["channel"].as<String>().toInt());
    paramHP[idx].fc = root["fc"].as<String>().toFloat();
    paramHP[idx].typ = static_cast<tFilterType>(root["typ"].as<String>().toInt());
    if (root["bypass"].as<String>().toInt() == 0)
        paramHP[idx].bypass = false;
    else
        paramHP[idx].bypass = true;

    //setHighPass(idx);
}

void JsonController::getValueHP(JsonObject &jsonResponse)
{
    Serial.println("[INFO] getValueHp(void):");

    if (jsonResponse.containsKey("channel"))
    {
        _error = NOERROR;
        uint32_t offset = static_cast<uint32_t>(jsonResponse["channel"].as<String>().toInt());
        jsonResponse["typ"] = paramHP[offset].typ;
        jsonResponse["fc"] = paramHP[offset].fc;
        if (paramHP[offset].bypass)
            jsonResponse["bypass"] = String("1");
        else
            jsonResponse["bypass"] = String("0");
    }
    else
    {
        _error = ERROR;
        _errorNo = HPGet_ERROR;
    }
}
/* ===================== LOW Shelving Filter ==================== */
void JsonController::setValueLShlv(JsonObject &root) {}
void JsonController::getValueLShlv(JsonObject &jsonResponse) {}

/* ========================== Equalise ========================== */
void JsonController::setValuePEQ(JsonObject &root) {}
void JsonController::getValuePEQ(JsonObject &jsonResponse) {}

/* ==================== HIGH Shelving Filter ==================== */
void JsonController::setValueHShlv(JsonObject &root)
{
}
void JsonController::getValueHShlv(JsonObject &jsonResponse)
{
    Serial.println("[INFO] getValueHShlv(void):");

    if (jsonResponse.containsKey("channel"))
    {
        _error = NOERROR;
        uint32_t offset = static_cast<uint32_t>(jsonResponse["channel"].as<String>().toInt());
        jsonResponse["gain"] = paramHshelv[offset].gain;
        jsonResponse["fc"] = paramHshelv[offset].fc;
        jsonResponse["slope"] = paramHshelv[offset].slope;
        if (paramHshelv[offset].bypass)
            jsonResponse["bypass"] = String("1");
        else
            jsonResponse["bypass"] = String("0");
    }
    else
    {
        _error = ERROR;
        _errorNo = HshelvSet_ERROR;
    }
}

/* ======================= LOWPASS Filter ======================= */
void JsonController::setValueLP(JsonObject &root) {}
void JsonController::getValueLP(JsonObject &jsonResponse) {}

/* ============================ Phase =========================== */
void JsonController::setValuePhase(JsonObject &root) {}
void JsonController::getValuePhase(JsonObject &jsonResponse) {}

/* ============================ Delay =========================== */
void JsonController::setValueDelay(JsonObject &root) {}
void JsonController::getValueDelay(JsonObject &jsonResponse) {}

/* ============================ Gain ============================ */
void JsonController::setValueGain(JsonObject &root) {}
void JsonController::getValueGain(JsonObject &jsonResponse) {}

/* ======================== Master Volume ======================= */
void JsonController::setValueVolume(JsonObject &root) {}
void JsonController::getValueVolume(JsonObject &jsonResponse) {}

/* =========================== Preset =========================== */
void JsonController::setValuePreset(JsonObject &root) {}
void JsonController::getValuePreset(JsonObject &jsonResponse) {}

/* ============================================================== */
/*                          TEST FUNCTION                         */
/* ============================================================== */

void testJsonController(void)
{
    String output;
    String jsonStringTest = "{\"cmdType\":0,\"channel\":1,\"idx\":0,\"fc\":10, \"typ\": 1, \"bypass\": 0}";

    initUserParams();
    Serial.println("/* ======================= HIGHPASS Filter ====================== */");
    JsonController jsonctrl(200);
    output = jsonctrl.processCmd(jsonStringTest);
    Serial.println(output);

    jsonStringTest = "{\"cmdType\":1,\"idx\":0,\"channel\":1}";
    output = jsonctrl.processCmd(jsonStringTest);
    Serial.println(output);

    jsonStringTest = "{\"cmdType\":0,\"channel\":1,\"idx\":0,\"fc\":10, \"typ\": 1, \"bypass\": 0}";

    //initUserParams();
    Serial.println("/* ======================= HIGHPASS Filter ====================== */");
    output = jsonctrl.processCmd(jsonStringTest);
    Serial.println(output);

    jsonStringTest = "{\"cmdType\":1,\"idx\":0,\"channel\":1}";
    output = jsonctrl.processCmd(jsonStringTest);
    Serial.println(output);
    //Serial.println("/* ==================== HIGH Shelving Filter //==================== */");
    //jsonStringTest = "{\"cmdType\":2,\"channel\":1,\"idx\":0,//\"fc\":10, \"typ\": 1, \"bypass\": 0}";
    //output = jsonctrl.processCmd(jsonStringTest);
    //Serial.println(output);
//
    //jsonStringTest = "{\"cmdType\":3,\"idx\":0,\"channel\":1}";
    //output = jsonctrl.processCmd(jsonStringTest);
    //Serial.println(output);
}