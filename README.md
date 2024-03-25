# FingerLock Git Repository

This repository contains the code and resources for the "FingerLock" project, which is a smart door lock system utilizing the following components:

- Adafruit Optical Fingerprint Sensor R307S
- 12V Solenoid Door Lock
- 20x04 Liquid Crystal Display
- 4x4 Keypad
- Arduino ATMEGA2560

## Overview

The "FingerLock" project aims to create a secure and convenient door locking mechanism by incorporating fingerprint recognition technology along with a keypad interface for additional access control. The system is designed to provide a seamless experience for users while ensuring robust security measures.

## Components

### 1. Adafruit Optical Fingerprint Sensor R307S
   This sensor is responsible for capturing and recognizing fingerprints. It provides reliable biometric authentication for accessing the door lock system.

### 2. 12V Solenoid Door Lock
   The solenoid door lock is used for physical locking and unlocking of the door. It is controlled by the Arduino microcontroller based on the authentication results.

### 3. 20x04 Liquid Crystal Display
   The LCD display provides feedback to the user regarding system status, instructions, and any relevant information during the authentication process.

### 4. 4x4 Keypad
   The keypad serves as an alternative means of access control. Users can input a passcode to unlock the door if fingerprint recognition is not desired or unavailable.

### 5. Arduino ATMEGA2560
   The Arduino microcontroller acts as the brain of the system, coordinating the operation of all components. It processes fingerprint data, manages user input from the keypad, controls the solenoid lock, and interacts with the LCD display.

## Functionality

The "FingerLock" system provides the following functionality:

1. **Fingerprint Recognition**: When a user places their finger on the scanner, the system will identify the user if their fingerprint is registered and valid.

2. **Display User ID**: Upon successful fingerprint recognition, the system will display the user ID on the LCD screen.

3. **Password Entry**: If fingerprint recognition is not available or desired, the system prompts the user to enter a password on the keypad.

4. **Password Verification**: If the entered password is correct, the system unlocks the door using the solenoid lock mechanism.

5. **Auto Lock Timeout**: After unlocking, the door remains open for 5 seconds before automatically locking again.
