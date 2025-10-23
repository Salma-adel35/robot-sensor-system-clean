#include "../include/temperature_sensor.h"
#include "../include/utils.h"
#include <iostream>
#include <ctime>


TemperatureSensor::TemperatureSensor(int id, const std::string& name)
    : Sensor(id, name, "Temperature", "C"), offset_(0.0) { 
        lastReading_ = 25.0;
    }

double TemperatureSensor::readData() {
    if (isFaulty_) {
        std::cout << "[ERROR] " << name_ << " sensor is faulty! Reading unreliable.\n";
        status_ = SensorStatus::ERROR;
        lastReading_ = Utils::randomDouble(500.0, 1000.0); 
        return lastReading_;
    }
    
    
    double rawReading = Utils::randomDouble(-20.0, 100.0);
    lastReading_ = rawReading + offset_;
    
    
    if (lastReading_ > 90.0) {
        status_ = SensorStatus::ERROR;
    } else if (lastReading_ > 70.0) {
        status_ = SensorStatus::WARNING;
    } else {
        status_ = SensorStatus::OK;
    }

    return lastReading_;
}

void TemperatureSensor::calibrate() {
    offset_ = 0.0;
    lastReading_ = 25.0; 
    status_ = SensorStatus::OK;
    std::cout << name_ << " sensor calibrated. Offset reset to 0.\n";
}

void TemperatureSensor::printInfo() const {
    std::cout<<std::string(30,'-')<<"Temperature Sensor"<<std::string(30,'-')<<std::endl;
    Sensor::printInfo();
    std::cout<<std::string(75,'-')<<std::endl;
}
