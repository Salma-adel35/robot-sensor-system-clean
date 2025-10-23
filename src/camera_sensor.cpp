#include "../include/camera_sensor.h"
#include "../include/utils.h"
#include <iostream>

CameraSensor::CameraSensor(int id, const std::string& name)
    : Sensor(id, name, "Camera", "FPS") {
        lastReading_ = 30.0;
    }

double CameraSensor::readData() {
    if (isFaulty_) {
        std::cerr << "Camera " << name_ << " failed to capture frames!\n";
        status_ = SensorStatus::ERROR;
        lastReading_ = 5.0; // قيمة فشل منخفضة
        return lastReading_;
    }

    double currentFPS = Utils::randomDouble(15.0, 60.0);
    
    // تحديد الحالة
    if (currentFPS < 10.0) { // ✅ [تعديل] إضافة شرط لـ ERROR (إذا كان FPS منخفضًا جدًا)
        status_ = SensorStatus::ERROR;
    } else if (currentFPS < 20.0) {
        status_ = SensorStatus::WARNING;
    } else {
        status_ = SensorStatus::OK;
    }

    lastReading_ = currentFPS;
    return currentFPS;
}

void CameraSensor::calibrate() {
    // تم استخدام nominalFPS_ من الـ Header لتكون قيمة مرجعية
    lastReading_ = nominalFPS_; 
    std::cout << "Calibrating camera sensor " << name_ << ". FPS reset to nominal.\n";
    status_ = SensorStatus::OK;
}

void CameraSensor::printInfo() const {
    std::cout<<std::string(30,'-')<<"Camera Sensor"<<std::string(30,'-')<<std::endl;
    Sensor::printInfo();
    std::cout<<std::string(75,'-')<<std::endl;
}