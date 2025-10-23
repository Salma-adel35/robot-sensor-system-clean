#ifndef LIDAR_SENSOR_H
#define LIDAR_SENSOR_H
#include "sensor.h"
#include <string>

class LidarSensor : public Sensor {
private:
    // ❌ [تعديل] تم حذف double distance; لأنه تكرار لـ lastReading_
    double noisefactor;

public:
    // ✅ [صحيح] توقيع المُنشئ كان صحيحًا.
    LidarSensor(int id, const std::string& name);

    // ✅ [صحيح] التجاوز صحيح.
    double readData() override;
    void calibrate() override;
    void printInfo() const override;
};

#endif // LIDAR_SENSOR_H
