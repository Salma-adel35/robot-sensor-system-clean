#ifndef CAMERA_SENSOR_H
#define CAMERA_SENSOR_H
#include "sensor.h"
#include <string>

class CameraSensor : public Sensor {
private:
    
    const double nominalFPS_ = 30.0; 

public:
    
    CameraSensor(int id, const std::string& name);
    
    
    double readData() override;    
    void calibrate() override;    
    void printInfo() const override;
};

#endif 
