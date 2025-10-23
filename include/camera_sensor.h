#ifndef CAMERA_SENSOR_H
#define CAMERA_SENSOR_H
#include "sensor.h"
#include <string>

class CameraSensor : public Sensor {
private:
    // ❌ [تعديل] تم حذف double fps; لأنه تكرار لـ lastReading_
    // لا نحتاج لمتغيرات خاصة هنا إلا إذا كان هناك ثابت
    const double nominalFPS_ = 30.0; // ثابت للـ calibrate

public:
    // ✅ [صحيح] توقيع المُنشئ كان صحيحًا.
    CameraSensor(int id, const std::string& name);
    
    // ✅ [صحيح] التجاوز صحيح.
    double readData() override;    
    void calibrate() override;    
    void printInfo() const override;
};

#endif // CAMERA_SENSOR_H
