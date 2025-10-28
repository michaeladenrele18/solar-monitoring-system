# 🌞 Arduino-Based Solar Panel & Battery Monitoring System

This project is a **dual-voltage monitoring system** that measures and displays real-time voltages of both a **solar panel** and a **battery** using an Arduino Uno.  
It features **precision resistor dividers**, **ADC calibration**, **fuse protection**, and **Schottky diode isolation** to prevent cross-voltage interference.  
All readings are displayed on a 16x2 LCD, with future plans to send data to the **cloud via ESP32**.

---

## 🧠 Project Overview

The goal of this project was to build an **accurate and safe sensing system** for a solar setup by:
- Measuring **solar panel (A1)** and **battery (A0)** voltages simultaneously  
- Displaying live readings on a **16x2 LCD**  
- Protecting sense lines with **inline fuses**  
- Preventing voltage feedback through **Schottky isolation**  
- Using **measured resistor values** for precise calibration  
- Implementing **long ADC settling** to handle high-impedance dividers  

---

## ⚙️ System Architecture

The system continuously monitors both **solar input** and **battery storage** voltages.  
Data is processed on the Arduino and displayed locally, with the ESP32 reserved for future cloud logging.

```text
               +-----------------------------+
               |        Solar Panel          |
               +-----------------------------+
                            │
                            ▼
               +-----------------------------+
               |      Charge Controller       |
               +-----------------------------+
                   │                     │
                   ▼                     ▼
     +---------------------+   +----------------------+
     |  Inline Fuse (0.5A) |   |  Inline Fuse (0.5A)  |
     +---------------------+   +----------------------+
                   │                     │
                   ▼                     ▼
     +---------------------+   +----------------------+
     |  Panel Voltage Div. |   |  Battery Voltage Div.|
     |  (100.2k / 19.91k)  |   |   (100k / 21.9k)    |
     +---------------------+   +----------------------+
              │                        │
            (A1)                     (A0)
              \                        /
               \                      /
                ▼                    ▼
            +-----------------------------------+
            |           Arduino Uno             |
            |  - Long ADC Settling              |
            |  - Dual Voltage Calibration       |
            |  - LCD Display Output             |
            +-----------------------------------+
                         │
                         ▼
            +-----------------------------+
            |         LCD Display          |
            |  (Panel & Battery Voltage)   |
            +-----------------------------+

Future Integration:
      └──► ESP32 → Cloud Dashboard → Remote Monitoring


```
---

## ⚡ Circuit Details

### **Panel Voltage Divider**
- Rtop = 100.2kΩ  
- Rbot = 19.91kΩ (9.95k + 9.96k)  
- Rseries = 1.005kΩ  
- Scale Factor: **6.03265**

### **Battery Voltage Divider**
- Rtop = 100kΩ  
- Rbot = 21.904kΩ (1.005k + 0.999k + 9.97k + 9.93k)  
- Rseries = 0.998kΩ  
- Scale Factor: **5.565376**

Each node voltage feeds the Arduino’s analog pins (A1 for panel, A0 for battery).  
Readings are stabilized using long ADC settling times due to high-impedance dividers.

---

## 💻 Code Features

- **Long ADC Settling:** Multiple dummy reads + delay for high-impedance sources  
- **Real-Time LCD Display:** Shows both panel and battery voltages  
- **Serial Output:** Prints calibrated readings for data logging  
- **Accurate Scaling:** Uses measured resistor values for precise conversion  
- **Hardware Isolation:** Schottky diodes prevent voltage feedback through SAE connectors  

---

