# Robotic Sensor System Simulation

**Repository Name:** `robot-sensor-system-clean`
**Project Lead:** [Salma Adel]

---

## Concise Summary and Purpose

This project is a Console-based Simulation of a robotic software architecture designed to manage multiple sensor inputs and perform diagnostic checks.

**Purpose:** The primary goal is to demonstrate practical proficiency in advanced **C++ Software Engineering principles** including **Runtime Polymorphism**, **Safe Memory Management (Smart Pointers)**, and efficient **STL container usage** for data management.

---

## Tools, Languages, and Libraries

| Component | Description |
| :--- | :--- |
| **Language** | C++ (Standard C++17) |
| **Build System** | CMake (version 3.10+) |
| **Key Libraries** | **Standard Template Library (STL)** for containers (`unordered_map`, `vector`) and algorithms (`sort`, `for_each`). |

---

## Directory and File Organization

This project uses a standard modular structure:

robot-sensor-system-clean/ ├── CMakeLists.txt # Project configuration and build rules. ├── include/ # Header files (.h) containing class declarations. │ ├── sensor.h # Base Abstract Sensor Interface. │ └── sensor_manager.h # Manager class declaration. ├── src/ # Source files (.cpp) containing function definitions. │ ├── main.cpp # The CLI menu and main execution loop. │ ├── sensor_manager.cpp # Sensor storage and management logic. │ └── utils.cpp # Implementation of helper functions (IDs, random numbers). └── data/ # Output and configuration files. ├── logs.txt # Sensor reading logs. └── config.txt # System configuration file (if implemented).\

---

## Steps to Build and Run the Project

### Prerequisites

* C++17 compliant compiler (GCC/Clang).
* CMake (version 3.10 or newer).

### Build Instructions

Execute the following commands from the project's root directory:

1.  **Create and enter the build directory:**
    ```bash
    mkdir build
    cd build
    ```
2.  **Configure CMake:**
    ```bash
    cmake ..
    ```
3.  **Compile the project:**
    ```bash
    make
    ```

### Run Instructions

Execute the final program from the `build` directory:

```bash
./robot_sensor_system

##  CLI Menu Demonstration
The system runs in a continuous loop, presenting the following options:

Option,Description,How to Use
1. Add new sensor,"Dynamically creates and registers a new sensor (Temp, Lidar, Camera).","Enter 1, then select the sensor type."
3. Read all sensors,Triggers readData() on all sensors. Automatically runs diagnostics every 3 reads.,Enter 3
5. Run diagnostics,"Immediately executes a health check, identifies ERROR sensors, and performs calibrate().",Enter 5
8. Sort sensors by reading,Uses std::sort to display a list of sensors sorted by their lastReading.,Enter 8
9. Simulate fault,"Toggles the isFaulty_ flag on a sensor by its ID, useful for testing diagnostics.","Enter 9, then the Sensor ID."
10. Exit,Terminates the application.,Enter 10




Team Members / Collaborators
Salma Adel (Core Developer, Diagnostics, CLI & Integration)
Rowan Ali (Sensor Implementation Developer)
Mohamed Fouad (System Manager Developer)
