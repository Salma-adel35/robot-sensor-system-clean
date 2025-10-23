#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>

// 1. تعريف Enum لحالة المستشعر
enum class SensorStatus { OK, WARNING, ERROR };

class Sensor {
protected:
    // 2. المتغيرات المحمية (Protected Attributes)
    int id_;
    std::string name_;
    std::string type_; // مثل "Temperature", "Lidar"
    std::string unit_; // مثل "C", "m", "FPS"
    double lastReading_;
    SensorStatus status_;
    bool isFaulty_; // لمحاكاة الفشل

public:
    // المُنشئ (Constructor)
    Sensor(int id, const std::string& name, const std::string& type, const std::string& unit);

    // المُدمّر الافتراضي (Virtual Destructor) - ضروري لإدارة الذاكرة والتعدد الشكلي
    virtual ~Sensor() = default;

    // 3. الدوال الافتراضية النقية (Pure Virtual Methods) - يجب تطبيقها في الفئات المشتقة
    virtual double readData() = 0;
    virtual void calibrate() = 0;

    // 4. دالة افتراضية (Virtual Method) - يمكن للفئات المشتقة تجاوزها
    virtual void printInfo() const;

    // 5. دالة محاكاة الفشل (Set Faulty)
    void setFaulty(bool fault) { isFaulty_ = fault; }

    // دوال Getter للوصول للقراءات والحالة
    int getId() const { return id_; }
    std::string getName() const { return name_; }
    std::string getType() const { return type_; }
    double getLastReading() const { return lastReading_; }
    SensorStatus getStatus() const { return status_; }
    bool isFaulty() const { return isFaulty_; }
    
    
    // دالة مُساعدة لتحويل الحالة إلى نص (مفيدة للطباعة)
    std::string statusToString() const;
};

#endif // SENSOR_H
