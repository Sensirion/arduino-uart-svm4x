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
    int16_t vocIndexOffset = 0;
    int16_t learningTimeOffsetHours = 0;
    int16_t learningTimeGainHours = 0;
    int16_t gatingMaxDurationMinutes = 0;
    int16_t stdInitial = 0;
    int16_t gainFactor = 0;
    int16_t noxIndexOffset = 0;
    error = sensor.getVocTuningParameters(
        vocIndexOffset, learningTimeOffsetHours, learningTimeGainHours,
        gatingMaxDurationMinutes, stdInitial, gainFactor);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute getVocTuningParameters(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    Serial.print("vocIndexOffset: ");
    Serial.print(vocIndexOffset);
    Serial.print("\t");
    Serial.print("learningTimeOffsetHours: ");
    Serial.print(learningTimeOffsetHours);
    Serial.print("\t");
    Serial.print("learningTimeGainHours: ");
    Serial.print(learningTimeGainHours);
    Serial.print("\t");
    Serial.print("gatingMaxDurationMinutes: ");
    Serial.print(gatingMaxDurationMinutes);
    Serial.print("\t");
    Serial.print("stdInitial: ");
    Serial.print(stdInitial);
    Serial.print("\t");
    Serial.print("gainFactor: ");
    Serial.print(gainFactor);
    Serial.println();
    error = sensor.getNoxTuningParameters(
        noxIndexOffset, learningTimeOffsetHours, learningTimeGainHours,
        gatingMaxDurationMinutes, stdInitial, gainFactor);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute getNoxTuningParameters(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    Serial.print("noxIndexOffset: ");
    Serial.print(noxIndexOffset);
    Serial.print("\t");
    Serial.print("learningTimeOffsetHours: ");
    Serial.print(learningTimeOffsetHours);
    Serial.print("\t");
    Serial.print("learningTimeGainHours: ");
    Serial.print(learningTimeGainHours);
    Serial.print("\t");
    Serial.print("gatingMaxDurationMinutes: ");
    Serial.print(gatingMaxDurationMinutes);
    Serial.print("\t");
    Serial.print("stdInitial: ");
    Serial.print(stdInitial);
    Serial.print("\t");
    Serial.print("gainFactor: ");
    Serial.print(gainFactor);
    Serial.println();
    error = sensor.setVocTuningParameters(100, 12, 12, 180, 50, 230);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute setVocTuningParameters(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    error = sensor.setNoxTuningParameters(1, 12, 12, 720, 50, 230);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute setNoxTuningParameters(): ");
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