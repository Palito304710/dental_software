# Dental Clinic Management System

## Overview

This project is a desktop dental clinic management system built with C++ and Qt.  
It provides tools to manage patients, appointments, doctors, and financial information within a single application.

Note:  
This repository contains the initial version of my project. I have added many features and developments since. If interested in either collaborating or discussing opportunities, feel free to reach out. This commit represents the early structure of the system.

<img width="1440" height="900" alt="image" src="https://github.com/user-attachments/assets/3ccbff93-5d68-4a20-9c9d-78e138cd3cbd" />


---

## Features

### Appointment Management
- Calendar-based appointment scheduling
- Multi-doctor schedule view
- 30-minute or 60-minute time slots
- Create and delete appointments
- Mark appointments as completed

### Patient Management
- Patient profiles with contact information
- View patient appointment history
- Edit patient information
- Track appointment payments

### Doctor Management
- Add, edit, and remove doctors
- View doctor appointment history
- Track doctor revenue and performance

### Financial Tracking
- Price per appointment
- Payment status tracking (paid / unpaid)
- Automatic revenue calculations

---

## Technology Stack

- C++17
- Qt 6 (Qt Widgets)
- SQLite
- CMake

---

## Application Structure

The application is organized into three main views:

AgendaView  
Handles appointment scheduling and the calendar interface.

PatientView  
Displays patient information, appointment history, and payment tracking.

DoctorView  
Displays doctor information, appointment statistics, and revenue tracking.

All persistent data is stored in a local SQLite database.

---

## Build Instructions

Using Qt Creator (recommended)

1. Open `CMakeLists.txt`
2. Configure the project with a Qt 6 kit
3. Build and run the application

Command line build:


mkdir build
cd build
cmake ..
cmake --build .
./untitled



---

## Contact

Again, if interested in either collaborating or discussing opportunities, feel free to reach out.
