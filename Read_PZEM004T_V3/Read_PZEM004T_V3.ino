#include <LedControl.h>
LedControl pzemDisplay = LedControl(D5, D7, D6, 3);  //DIN ,CLK, LOAD, JUMLAH IC
#include "DisplayPZEM.h"

#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(D3, D4);

void setup() {
  Serial.begin(115200);
  setBrightness(5);
  //  pzem.resetEnergy(); // method reset PZEM004T
}

void loop() {
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float powerFactor = pzem.pf();

  Serial.println("=====================================");
  Serial.println(String() + "Voltage\t\t: " + voltage + "V");
  Serial.println(String() + "Current\t\t: " + current + "A");
  Serial.println(String() + "Power\t\t: " + power + "W");
  Serial.println(String() + "Energy\t\t: " + String(energy, 3) + "kWh");
  Serial.println(String() + "Frequency\t: " + frequency + "Hz");
  Serial.println(String() + "Power Factor\t: " + powerFactor);
  Serial.println("=====================================");
  Serial.println();

  delay(1000);

  viewVoltage(voltage);
  viewCurrent(current);
  viewPower(power);
  viewEnergy(energy);
  viewFrequency(frequency);
  viewPowerFactor(powerFactor);
}
