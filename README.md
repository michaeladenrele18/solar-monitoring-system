# 🌞 Arduino-Based Solar Panel & Battery Monitoring System

This project is a **dual-voltage monitoring system** designed to measure and display the real-time voltages of both a **solar panel** and a **battery** using an Arduino.  
It features **precision voltage dividers**, **ADC calibration**, and **Schottky isolation** to prevent cross-voltage interference — all displayed on an LCD screen with future plans for **cloud integration via ESP32**.

---

## 🧠 Project Overview

The goal of this project was to create an **accurate and safe voltage sensing circuit** capable of:
- Measuring **solar panel voltage (A1)** and **battery voltage (A0)** simultaneously  
- Handling voltages up to **30V** without exceeding Arduino’s 5V ADC limit  
- Displaying real-time values on a **16x2 LCD**  
- Providing **calibrated readings** using measured resistor values and long ADC settling  
- Preventing cross-voltage leakage between PV and BAT lines through **Schottky diode isolation**

---

## ⚙️ System Architecture
