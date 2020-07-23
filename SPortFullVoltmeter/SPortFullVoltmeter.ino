#define F_CPU 16000000
#include <FrSkySportSensor.h>
#include <FrSkySportSensorFlvss.h>
#include <FrSkySportSingleWireSerial.h>
#include <FrSkySportTelemetry.h>

FrSkySportSensorFlvss flvss;
FrSkySportTelemetry telemetry;

/* CONNECTIONS:
 *  TODO: show voltage divider, voltage regulator
 *  Digital Pin 2: SPort Data
 *  Analog  Pin 0: Battery Balancer 3.7V
 *  GND connected to either Battery Balancer 0V or SPORT GND
 *  RAW connected to Batter Balancer 7.4V or higher
 */

#define BATTERY_VOLTAGE_PIN A0
#define SPORT_PIN FrSkySportSingleWireSerial::SOFT_SERIAL_PIN_2

void setup()
{
  telemetry.begin(SPORT_PIN, &flvss);
}

float R1 = 3300.0;   // resistor 1 in ohms
float R2 = 1000.0;   // resistor 2 in ohms
float scalingFactor = R2 / (R1 + R2);

void loop()
{
  int voltageRaw = analogRead(BATTERY_VOLTAGE_PIN);
  voltageRaw=500;
  float batteryVoltage = voltageRaw * scalingFactor;
  flvss.setData(batteryVoltage);
  telemetry.send();
}
