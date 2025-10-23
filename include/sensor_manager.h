#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <unordered_map>
#include <memory>
#include "sensor.h"
#include "utils.h"

// ✅ [تعديل] تغيير اسم الكلاس من Sensor_Manager إلى SensorManager (CamelCase)
class SensorManager 
{
private:
    // ✅ [تعديل] حذف static inline! يجب أن تكون الخريطة عضوًا عاديًا للكلاس
    std::unordered_map<int, std::shared_ptr<Sensor>> allSensors_; 
public:
    SensorManager() = default;
    ~SensorManager() = default;

    void addSensor(std::shared_ptr<Sensor> sensor);
    void removeSensor(int id); // ✅ [تعديل] استخدام int وليس int&
    void displayAllSensors() const;
    void readAllSensors();
    std::shared_ptr<Sensor> getSensor(int id);
    void sortSensorsByReading();
    void saveLogs(const std::string& filename) const; // ✅ [تعديل] أخذ اسم الملف
    void loadConfig(const std::string& filename);    // ✅ [تعديل] أخذ اسم الملف
    
    // Getter ضروري لـ Diagnostics لاستعراض المستشعرات
    const std::unordered_map<int, std::shared_ptr<Sensor>>& getAllSensors() const;
};

#endif