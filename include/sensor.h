#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>

enum class SensorStatus { OK, WARNING, ERROR };

class Sensor {
protected:
    int id_;
    std::string name_;
    std::string type_;
    std::string unit_;
    double lastReading_;
    SensorStatus status_;
    bool isFaulty_; 

public:
   
    Sensor(int id, const std::string& name, const std::string& type, const std::string& unit);

    virtual ~Sensor() = default;

    virtual double readData() = 0;
    virtual void calibrate() = 0;

    virtual void printInfo() const;


    void setFaulty(bool fault) { isFaulty_ = fault; }
    void setStatus(SensorStatus status) { status_ = status; } 

  
    int getId() const { return id_; }
    std::string getName() const { return name_; }
    std::string getType() const { return type_; }
    double getLastReading() const { return lastReading_; }
    SensorStatus getStatus() const { return status_; }
    bool isFaulty() const { return isFaulty_; }
    
    std::string statusToString() const;
};

#endif 
