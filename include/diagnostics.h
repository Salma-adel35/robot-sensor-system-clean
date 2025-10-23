#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H


#include "sensor_manager.h" 
#include <string>
#include <memory>


class Diagnostics
{
private:
    std::string report_ = "";
    
public:
    Diagnostics() = default;
    ~Diagnostics() = default;

   
    void runDiagnostics(SensorManager& manager); 
    void generateReport(const std::string &filename) const;
    void resetReport() { report_ = ""; }
};

#endif
