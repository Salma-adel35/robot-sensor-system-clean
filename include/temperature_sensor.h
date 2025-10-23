#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H
#include "sensor.h"

class TemperatureSensor : public Sensor {
private:
  
    double offset_; 

public:
   
    TemperatureSensor(int id, const std::string& name); 
    
    
    double readData() override;
    void calibrate() override;
    void printInfo() const override; 
};

#endif 
