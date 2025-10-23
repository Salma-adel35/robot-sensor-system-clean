#ifndef LIDAR_SENSOR_H
#define LIDAR_SENSOR_H
#include "sensor.h"
#include <string>

class LidarSensor : public Sensor {
private:
   
    double noisefactor;

public:
    
    LidarSensor(int id, const std::string& name);

   
    double readData() override;
    void calibrate() override;
    void printInfo() const override;
};

#endif 
