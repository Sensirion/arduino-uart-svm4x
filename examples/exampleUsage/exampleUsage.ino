/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * Generator:     sensirion-driver-generator 0.33.0
 * Product:       svm4x
 * Model-Version: 2.0.3
 */
/*
 * Copyright (c) 2023, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <Arduino.h>
#include <SensirionUartSvm4x.h>

// Adjust as needed for you Arduino board.
// [Serial, Serial1, Serial2, etc.]
#define SENSOR_SERIAL_INTERFACE Serial1

SensirionUartSvm4x sensor;

static char errorMessage[64];
static int16_t error;

void setup() {

    // initialize serial interface for logging
    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }

    // initialize serial interface for sensor communication
    SENSOR_SERIAL_INTERFACE.begin(115200);
    while (!SENSOR_SERIAL_INTERFACE) {
        delay(100);
    }

    sensor.begin(SENSOR_SERIAL_INTERFACE);

    error = sensor.deviceReset();
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute deviceReset(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    delay(2000);
    int8_t serialNumber[32] = {0};
    error = sensor.getSerialNumber(serialNumber, 32);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute getSerialNumber(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    Serial.print("serialNumber: ");
    Serial.print((const char*)serialNumber);
    Serial.println();
    int8_t productType[32] = {0};
    error = sensor.getProductType(productType, 32);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute getProductType(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    Serial.print("productType: ");
    Serial.print((const char*)productType);
    Serial.println();
    int8_t productName[8] = {0};
    error = sensor.getProductName(productName, 8);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute getProductName(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    Serial.print("productName: ");
    Serial.print((const char*)productName);
    Serial.println();
    uint8_t firmwareMajor = 0;
    uint8_t firmwareMinor = 0;
    bool firmwareDebug = false;
    uint8_t hardwareMajor = 0;
    uint8_t hardwareMinor = 0;
    uint8_t protocolMajor = 0;
    uint8_t protocolMinor = 0;
    error = sensor.getVersion(firmwareMajor, firmwareMinor, firmwareDebug,
                              hardwareMajor, hardwareMinor, protocolMajor,
                              protocolMinor);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute getVersion(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    Serial.print("firmwareMajor: ");
    Serial.print(firmwareMajor);
    Serial.print("\t");
    Serial.print("firmwareMinor: ");
    Serial.print(firmwareMinor);
    Serial.print("\t");
    Serial.print("firmwareDebug: ");
    Serial.print(firmwareDebug);
    Serial.print("\t");
    Serial.print("hardwareMajor: ");
    Serial.print(hardwareMajor);
    Serial.print("\t");
    Serial.print("hardwareMinor: ");
    Serial.print(hardwareMinor);
    Serial.print("\t");
    Serial.print("protocolMajor: ");
    Serial.print(protocolMajor);
    Serial.print("\t");
    Serial.print("protocolMinor: ");
    Serial.print(protocolMinor);
    Serial.println();
    float arg0 = 0.0;
    error = sensor.getTemperatureOffsetForRhtMeasurements(arg0);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute "
                     "getTemperatureOffsetForRhtMeasurements(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    Serial.print("arg0: ");
    Serial.print(arg0);
    Serial.println();
    error = sensor.setTemperatureOffsetForRhtMeasurements(0);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute "
                     "setTemperatureOffsetForRhtMeasurements(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    error = sensor.startMeasurement();
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute startMeasurement(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
}

void loop() {

    float aHumidity = 0.0;
    float aTemperature = 0.0;
    float aVocIndex = 0.0;
    float aNoxIndex = 0.0;
    delay(1000);
    error = sensor.readMeasuredValues(aHumidity, aTemperature, aVocIndex,
                                      aNoxIndex);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute readMeasuredValues(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    Serial.print("aHumidity: ");
    Serial.print(aHumidity);
    Serial.print("\t");
    Serial.print("aTemperature: ");
    Serial.print(aTemperature);
    Serial.print("\t");
    Serial.print("aVocIndex: ");
    Serial.print(aVocIndex);
    Serial.print("\t");
    Serial.print("aNoxIndex: ");
    Serial.print(aNoxIndex);
    Serial.println();
}
