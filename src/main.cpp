#include "../include/sensor_manager.h"
#include "../include/diagnostics.h"
#include "../include/utils.h"
#include "../include/temperature_sensor.h"
#include "../include/lidar_sensor.h"
#include "../include/camera_sensor.h"
#include <iostream>
#include <limits>
#include <memory>
#include <functional> 

using namespace std;


const std::string LOG_FILE = "data/logs.txt";
const std::string CONFIG_FILE = "data/config.txt";
const std::string REPORT_FILE = "data/diagnostics_report.txt";

void displayMenu() {
    cout << "\n========= ROBOT SENSOR CONTROL =========" << endl;
    cout << "1. Add new sensor" << endl;
    cout << "2. Remove sensor" << endl;
    cout << "3. Read all sensors" << endl;
    cout << "4. Display all sensors" << endl;
    cout << "5. Run diagnostics" << endl;
    cout << "6. Save logs" << endl;
    cout << "7. Load config" << endl;
    cout << "8. Sort sensors by reading" << endl;
    cout << "9. Simulate fault (Toggle by ID)" << endl;
    cout << "10. Exit" << endl;
    cout << "=========================================" << endl;
    cout << "Enter choice > ";
}

void handleInputError() {
    cerr << "[ERROR] Invalid input. Please enter a number." << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void handleAddSensor(SensorManager& manager) {
    cout << "  1. Temperature Sensor\n  2. Lidar Sensor\n  3. Camera Sensor\nEnter type choice > ";
    int type_choice;
    
    if (!(cin >> type_choice)) {
        handleInputError();
        return;
    }

    int new_id = Utils::generateID();
    shared_ptr<Sensor> new_sensor = nullptr;

    try {
        switch (type_choice) {
            
            case 1: new_sensor = make_shared<TemperatureSensor>(new_id, "Temp_" + to_string(new_id)); break;
            case 2: new_sensor = make_shared<LidarSensor>(new_id, "Lidar_" + to_string(new_id)); break;
            case 3: new_sensor = make_shared<CameraSensor>(new_id, "Cam_" + to_string(new_id)); break;
            default: cout << "[ERROR] Invalid sensor type choice." << endl; return;
        }

        if (new_sensor) {
            manager.addSensor(new_sensor);
            if (Utils::chance(0.1)) { 
                new_sensor->setFaulty(true);
                cout << "⚠️ [SIMULATION] Sensor ID=" << new_id << " initialized with a fault!" << endl;
            }
        }
    } catch (const std::exception& e) {
        cerr << "[FATAL ERROR] Exception during sensor creation: " << e.what() << endl;
    }
}

void handleIDAction(SensorManager& manager, const string& prompt, function<void(std::shared_ptr<Sensor>)> action_func) {
    cout << "Enter ID of sensor to " << prompt << ": ";
    int id;
    if (!(cin >> id)) { handleInputError(); return; }
    
    auto sensor = manager.getSensor(id);
    if (sensor) {
        action_func(sensor);
    } else {
        cout << "[ERROR] Sensor ID=" << id << " not found." << endl;
    }
}


int main() {
    
    SensorManager manager;
    Diagnostics diagnostics;
    int read_count = 0;
    
    
    manager.addSensor(make_shared<TemperatureSensor>(Utils::generateID(), "Engine Temp"));
    manager.addSensor(make_shared<LidarSensor>(Utils::generateID(), "Front Lidar"));
    manager.addSensor(make_shared<CameraSensor>(Utils::generateID(), "Side Cam"));

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        if (!(cin >> choice)) {
            handleInputError();
            continue;
        }

        try {
            switch (choice) {
                case 1: handleAddSensor(manager); break;
                case 2: 
                    handleIDAction(manager, "remove", 
                        [&](auto sensor) { manager.removeSensor(sensor->getId()); }); 
                    break;
                case 3: 
                    manager.readAllSensors(); 
                    manager.displayAllSensors(); 
                    read_count++;
                    if (read_count % 3 == 0) {
                        cout << "\n--- Scheduled Diagnostics ---\n";
                        diagnostics.runDiagnostics(manager);
                        diagnostics.generateReport(REPORT_FILE);
                    }
                    break;
                case 4: manager.displayAllSensors(); break;
                case 5: 
                    diagnostics.runDiagnostics(manager); 
                    diagnostics.generateReport(REPORT_FILE);
                    break;
                case 6: manager.saveLogs(LOG_FILE); break;
                case 7: manager.loadConfig(CONFIG_FILE); break;
                case 8: manager.sortSensorsByReading(); break;
                case 9: 
                    handleIDAction(manager, "toggle fault", 
                        [&](auto sensor) { 
                            sensor->setFaulty(!sensor->isFaulty());
                            cout << "[ACTION] Sensor ID=" << sensor->getId() << " Faulty status toggled to: " << (sensor->isFaulty() ? "TRUE" : "FALSE") << endl;
                        }); 
                    break;
                case 10: running = false; break;
                default: cout << "[ERROR] Invalid option." << endl; break;
            }
        } catch (const std::exception& e) {
            cerr << "[FATAL ERROR] An unexpected error occurred: " << e.what() << endl;
        }
    }

    cout << "Exiting simulation. Goodbye!" << endl;
    return 0;
}
