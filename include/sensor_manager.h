#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <unordered_map>
#include <memory>
#include "sensor.h"
#include "utils.h"


class SensorManager 
{
private:
    
    std::unordered_map<int, std::shared_ptr<Sensor>> allSensors_; 
public:
    SensorManager() = default;
    ~SensorManager() = default;

    void addSensor(std::shared_ptr<Sensor> sensor);
    void removeSensor(int id); 
    void displayAllSensors() const;
    void readAllSensors();
    std::shared_ptr<Sensor> getSensor(int id);
    void sortSensorsByReading();
    void saveLogs(const std::string& filename) const; 
    void loadConfig(const std::string& filename);    
    
    
    const std::unordered_map<int, std::shared_ptr<Sensor>>& getAllSensors() const;
};

#endif
