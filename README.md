# kWhMeter Using Blynk Platform Projects

This project is a **KWH Meter** using the **ESP8266**, **PZEM004T v3.0**, and the **Blynk** IoT platform. It monitors electrical parameters such as voltage, current, power, energy consumption, frequency, and power factor, and displays the information via both the **Serial Monitor** and a **MAX7219 LED Display**. The data is also sent to the **Blynk** app for remote monitoring. Additionally, the project includes a relay control to turn off devices when the power exceeds a specified limit.

## Features

- Real-time monitoring of voltage, current, power, energy, frequency, and power factor.
- Displays data on an LED display and the Blynk app.
- Triggers a relay when power exceeds 100W.
- Logs excessive power events using **Blynk Event Logging**.

## Hardware Requirements

- **ESP8266 (e.g., Wemos D1 Mini)** – Microcontroller for data processing and WiFi communication.
- **PZEM004T v3.0** – Sensor for measuring electrical parameters.
- **MAX7219 LED Display** – For local display of measurements.
- **Relay Module** – To control external devices based on power consumption.
- **Jumper wires** – For making connections.

## Software Requirements

- **Arduino IDE** – For programming the ESP8266.
- **Blynk Library** – For connecting to the Blynk platform.
- **LedControl Library** – For controlling the MAX7219 LED Display.
- **PZEM004Tv30 Library** – For interfacing with the PZEM004T sensor.

## Setup

1. **Install Arduino IDE** if not already installed.
2. Install the required libraries:
   - **Blynk**: [Blynk Library](https://github.com/blynkkk/blynk-library)
   - **LedControl**: [LedControl Library](https://github.com/wayoda/LedControl)
   - **PZEM004Tv30**: [PZEM004T Library](https://github.com/olehs/PZEM004T)
3. Connect the hardware as described in the wiring section below.
4. Upload the code to the ESP8266.

## Wiring Diagram

- **PZEM004T**:
  - Rx -> D3
  - Tx -> D4
- **MAX7219 LED Display**:
  - DIN -> D5
  - CLK -> D7
  - LOAD -> D6
- **Relay**:
  - Control pin -> D1

## Code Overview

### Constants and Initialization

```cpp
#define BLYNK_TEMPLATE_ID "TMPL6qa5Cegqu"
#define BLYNK_TEMPLATE_NAME "KWH Meter Projects"
#define BLYNK_AUTH_TOKEN "3NIQdx42iROeK7S_YdxAy6bLiagemadX"

char ssid[] = "Veendy-Suseno";  // WiFi SSID
char pass[] = "Admin12345";     // WiFi Password

LedControl pzemDisplay = LedControl(D5, D7, D6, 3);  // LED Display pins
PZEM004Tv30 pzem(D3, D4);  // PZEM sensor pins
const byte relay = D1;      // Relay pin
```

## Setup Function

- Initializes the serial communication, sets the brightness of the LED display, and establishes the Blynk connection.

```cpp
void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  setBrightness(5);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}
```

## Loop Function

- Reads data from the PZEM sensor.
- Updates the Blynk app and LED display with the current electrical parameters.
- Controls the relay if the power consumption exceeds 100W.
- Logs excessive power events to Blynk.

```cpp
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
```

## Example Output

Here’s an example of the serial monitor output:

```yaml
=====================================
Voltage     : 220.5V
Current     : 0.5A
Power       : 110.2W
Energy      : 5.6kWh
Frequency   : 50.0Hz
Power Factor: 0.98
=====================================

```

## Blynk App Setup

1. Add a Gauge for Power (V0).
2. Add a Gauge for Energy (V1).
3. Add an Event Logger to log power overload events.

## License

This project is licensed under the MIT License. For more information, refer to the LICENSE file.

```css

This README provides a detailed description of your project, including its features, hardware and software requirements, wiring diagram, code explanation, and Blynk setup. Let me know if you need further adjustments!

```
