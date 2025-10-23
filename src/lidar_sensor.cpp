#include "../include/lidar_sensor.h"
#include "../include/utils.h"
#include <iostream>
#include <cmath> // لـ std::abs أو std::isfinite

LidarSensor::LidarSensor(int id, const std::string& name)
    : Sensor(id, name, "Lidar", "m"), noisefactor(0.1) { // ✅ [تعديل] ضبط noisefactor
        lastReading_ = 0.1;
    }  

double LidarSensor::readData() {
    if (isFaulty_) {
        std::cerr << "Lidar sensor " << name_ << " sensor is faulty! Reading 0.\n";
        lastReading_ = 0.0;
        status_ = SensorStatus::ERROR;
        return 0;
    }
    
    double baseDistance = Utils::randomDouble(0.1, 50.0);
    
    // ✅ [تعديل] تصحيح منطق الضوضاء باستخدام الدوال الصحيحة
    // يتم إنشاء عامل ضوضاء عشوائي بين -noisefactor و +noisefactor
    double noise = baseDistance * Utils::randomDouble(-noisefactor, noisefactor);
    lastReading_ = baseDistance + noise;
    
    // تحديد الحالة
    if (lastReading_ <= 0.0 || !std::isfinite(lastReading_)) {
        status_ = SensorStatus::ERROR;
    } else {
        status_ = SensorStatus::OK;
    }
    
    return lastReading_;
}

void LidarSensor::calibrate() {
    noisefactor = 0.1; // إعادة تعيين الضوضاء
    std::cout << "Calibrating Lidar sensor " << name_ << ". Noise reset.\n";
    lastReading_ = 0.1;
    status_ = SensorStatus::OK;
}

void LidarSensor::printInfo() const {
    std::cout<<std::string(30,'-')<<"Lidar Sensor"<<std::string(30,'-')<<std::endl;
    Sensor::printInfo();
    std::cout<<std::string(75,'-')<<std::endl;
}