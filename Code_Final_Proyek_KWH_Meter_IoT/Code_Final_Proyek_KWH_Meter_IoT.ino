#define BLYNK_TEMPLATE_ID "TMPL6qa5Cegqu"
#define BLYNK_TEMPLATE_NAME "KWH Meter Projects"
#define BLYNK_AUTH_TOKEN "3NIQdx42iROeK7S_YdxAy6bLiagemadX"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char ssid[] = "Veendy-Suseno";
char pass[] = "Admin12345";
BlynkTimer timer;

#include <LedControl.h>
LedControl pzemDisplay = LedControl(D5, D7, D6, 3);  //DIN ,CLK, LOAD, JUMLAH IC
#include "DisplayPZEM.h"
#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(D3, D4);

unsigned const long interval = 1000L;
unsigned long zero = 0;

const byte relay = D1;

void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  setBrightness(5);
  //  pzem.resetEnergy();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {

  Blynk.run();

  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float powerFactor = pzem.pf();

  viewVoltage(voltage);
  viewCurrent(current);
  viewPower(power);
  viewEnergy(energy);
  viewFrequency(frequency);
  viewPowerFactor(powerFactor);

  if (power > 100) {
    Serial.println("Power Melebihi Batas");
    Blynk.logEvent("power_berlebih");
    digitalWrite(relay, HIGH);
  }

  if (millis() - zero >= interval) {
    zero = millis();
    Serial.println("=====================================");
    Serial.println(String() + "Voltage\t\t: " + voltage + "V");
    Serial.println(String() + "Current\t\t: " + current + "A");
    Serial.println(String() + "Power\t\t: " + power + "W");
    Serial.println(String() + "Energy\t\t: " + String(energy, 3) + "kWh");
    Serial.println(String() + "Frequency\t: " + frequency + "Hz");
    Serial.println(String() + "Power Factor\t: " + powerFactor);
    Serial.println("=====================================");
    Serial.println();
    Blynk.virtualWrite(V0, power);
    Blynk.virtualWrite(V1, energy);
  }

}
