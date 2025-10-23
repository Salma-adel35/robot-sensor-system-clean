#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H
#include "sensor.h"

class TemperatureSensor : public Sensor {
private:
    // ❌ [تعديل] تم حذف double temperature_; لأنه تكرار لـ lastReading_
    double offset_; 

public:
    // ✅ [صحيح] توقيع المُنشئ كان صحيحًا.
    TemperatureSensor(int id, const std::string& name); 
    
    // ✅ [صحيح] التجاوز صحيح.
    double readData() override;
    void calibrate() override;
    void printInfo() const override; 
};

#endif // TEMPERATURE_SENSOR_H