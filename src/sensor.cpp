#include "../include/sensor.h"
#include <iomanip> // لتنسيق الطباعة
#include <sstream> // إذا احتجت لـ logging

// تنفيذ المُنشئ
Sensor::Sensor(int id, const std::string& name, const std::string& type, const std::string& unit)
    : id_(id), name_(name), type_(type), unit_(unit), lastReading_(0.0), status_(SensorStatus::OK), isFaulty_(false) {}

// تنفيذ الطباعة المشتركة
void Sensor::printInfo() const {
    std::string status_str = statusToString();
    std::cout << "Sensor ID: " << id_
              << " | Name: " << name_
              << " | Type: " << type_
              << " | Value: " << std::fixed << std::setprecision(2) << lastReading_ << " " << unit_
              << " | Status: " << statusToString()
              << (isFaulty_ ? " (SIMULATED FAULT)" : "")
              << std::endl;
}

// تنفيذ تحويل الحالة إلى نص
std::string Sensor::statusToString() const {
    switch (status_) {
        case SensorStatus::OK: return "OK";
        case SensorStatus::WARNING: return "WARNING";
        case SensorStatus::ERROR: return "ERROR";
    }
    return "UNKNOWN";
}


