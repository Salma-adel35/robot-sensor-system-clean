#include "../include/sensor_manager.h"
#include "../include/utils.h"
#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>

// allSensors_ is declared as a non-static member in the header; do not define it here.

void SensorManager::addSensor(std::shared_ptr<Sensor> sensor)
{
    int id = sensor->getId(); 
    allSensors_[id] = sensor; 
    std::cout << "[Manager] Added " << sensor->getType() << " ID=" << id << std::endl;
}

void SensorManager::removeSensor(int id)
{
    if (allSensors_.erase(id)) {
        std::cout << "[Manager] Removed sensor ID=" << id << std::endl;
    } else {
        std::cout << "[ERROR] Sensor ID=" << id << " not found." << std::endl;
    }
}

// ✅ IMPLEMENTATION: getSensor
std::shared_ptr<Sensor> SensorManager::getSensor(int id)
{
    auto it = allSensors_.find(id);
    return (it != allSensors_.end()) ? it->second : nullptr;
}

// ✅ IMPLEMENTATION: readAllSensors
void SensorManager::readAllSensors()
{
    std::cout << "\n--- Reading Sensor Data ---\n";
    // استخدام std::for_each مع lambda
    std::for_each(allSensors_.begin(), allSensors_.end(), 
        [](const auto& pair) {
            pair.second->readData();
        });
    std::cout << "--- Read Complete ---\n";
}

// ✅ IMPLEMENTATION: displayAllSensors
void SensorManager::displayAllSensors() const
{
    if (allSensors_.empty()) {
        std::cout << "No sensors registered." << std::endl;
        return;
    }
    std::cout << "\n--- All Sensors Status ---\n";
    // استخدام std::for_each مع lambda
    std::for_each(allSensors_.begin(), allSensors_.end(), 
        [](const auto& pair) {
            pair.second->printInfo();
        });
    std::cout << "--------------------------\n";
}

// ✅ IMPLEMENTATION: sortSensorsByReading
void SensorManager::sortSensorsByReading()
{
    std::vector<std::pair<int, std::shared_ptr<Sensor>>> sensorVec(allSensors_.begin(), allSensors_.end()); 

    std::sort(sensorVec.begin(), sensorVec.end(),
             [](const auto &a, const auto &b) {
                 return a.second->getLastReading() < b.second->getLastReading();
             });

    std::cout << "\n--- Sensors Sorted by Reading ---\n";
    for (const auto &pair : sensorVec)
    {
        pair.second->printInfo();
    }
}

// ✅ IMPLEMENTATION: saveLogs
void SensorManager::saveLogs(const std::string& filename) const
{
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs.is_open()) {
        std::cerr << "[ERROR] Failed to open log file: " << filename << std::endl;
        return;
    }

    ofs << "--- LOG ENTRY: " << Utils::currentDateTime() << " ---\n";
    std::for_each(allSensors_.begin(), allSensors_.end(), 
        [&ofs](const auto& pair) {
            ofs << "[" << pair.second->getType() << " ID=" << pair.second->getId() 
                << "] Reading: " << pair.second->getLastReading() << " | Status: " 
                << pair.second->statusToString() << std::endl;
        });
    ofs.close();
    std::cout << "[LOG SAVED] Data logged to " << filename << std::endl;
}

// ✅ IMPLEMENTATION: loadConfig
void SensorManager::loadConfig(const std::string& filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "[ERROR] Failed to open config file: " << filename << ". Using defaults." << std::endl;
        return;
    }
    std::string line;
    std::cout << "[Config] Loaded:\n";
    while (std::getline(ifs, line)) {
        std::cout << "  - " << line << std::endl;
    }
    ifs.close();
}

const std::unordered_map<int, std::shared_ptr<Sensor>>& SensorManager::getAllSensors() const
{
    return allSensors_;
}