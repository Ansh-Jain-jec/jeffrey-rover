# JEFFREY — Joint Exploration & Field Recon Over Rough Terrain

A WiFi-controlled six-wheeled surveillance rover built on NASA's Rocker-Bogie suspension system, designed to navigate rough, uneven, obstacle-laden terrain.

## Overview

- Passive differential Rocker-Bogie linkage — keeps all six wheels in constant ground contact with no springs or active actuators
- Chassis: PVC pipes + ACP sheet
- Skid-steer drive via 6× 12V geared DC motors
- Live video streaming over WiFi (ESP32-CAM)
- Browser-based control (phone or laptop) — no app required

## Hardware

| Component | Spec |
|---|---|
| Controller | Arduino UNO R4 WiFi |
| Motor drivers | 3× L298N dual H-bridge |
| Motors | 6× 12V DC geared |
| Camera | ESP32-CAM |
| Power | 3S Li-ion battery pack |
| Drive | Skid-steer |

## Mechanical Parameters

| Parameter | Value |
|---|---|
| Overall length | ~42 cm |
| Overall width | ~30 cm |
| Ground clearance (min) | ~5 cm |
| Wheel diameter | 10 cm |
| Rocker arm length | 15 cm |
| Bogie link length | 13 cm |
| Chassis base plate (ACP) | 25 × 18 cm |
| Max climbable slope | 25° |
| Max theoretical step height | ~7.5 cm (0.75× wheel dia) |
| Estimated loaded mass | ~1.8 kg |

## Electrical Parameters

| Component | Voltage | Current |
|---|---|---|
| Arduino UNO R4 WiFi | 5V (USB) | ~0.10 A |
| ESP32-CAM | 5V | ~0.30 A (streaming) |
| L298N ×3 (quiescent) | 12V | ~0.05 A each |
| DC geared motor ×6 (typical load) | 12V | ~0.25 A each |
| DC geared motor ×6 (stall) | 12V | ~1.0 A each |

## Results

Tested on paved concrete, tiled surfaces, and platform steps:

- Chassis tilt variance as low as ±0.07°
- Body stability: 0.050σ (indoor tiled floor)
- Loose/disturbed soil: ±0.27° tilt, required ~30% PWM reduction for stable traversal

## Usage

1. Flash `jeffrey_rover.ino` to the Arduino WiFi board
2. Rover starts a WiFi access point (`RobotCar` / `12345678` by default — change before deploying)
3. Connect a phone/laptop to that network
4. Open the board's IP address (printed to Serial on boot) in a browser
5. Use Forward / Backward / Left / Right / STOP buttons to drive

## Roadmap (Phase 2)

- Autonomous obstacle avoidance
- Intrusion alert system
- Vision-based obstacle detection: ESP32-CAM + OpenCV + MobileNet-SSD
- Additional sensors: PIR, LoRa

## Keywords

Rocker-Bogie Suspension, Surveillance Rover, Arduino, ESP32-CAM, WiFi Control, Skid-Steer, L298N Motor Driver, Terrain Navigation
