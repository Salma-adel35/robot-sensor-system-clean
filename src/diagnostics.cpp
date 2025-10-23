#include "../include/diagnostics.h"
#include "../include/utils.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>


void Diagnostics::runDiagnostics(SensorManager& manager) {
    std::cout << "\n========== RUNNING DIAGNOSTICS ==========\n";
    resetReport(); 

    const auto& sensors = manager.getAllSensors();
    if (sensors.empty()) {
        std::cout << "[Diagnostics] No sensors to check." << std::endl;
        return;
    }

    report_ += "--- Diagnostics Report: " + Utils::currentDateTime() + " ---\n";
    

    std::for_each(sensors.begin(), sensors.end(), 
        [this](const auto& pair) {
            const auto& sensor = pair.second;
            std::string status_icon = "✅";
            std::string logLine;
            
            
            if (sensor->isFaulty() || sensor->getStatus() == SensorStatus::ERROR) {
                status_icon = "🚨";
                std::cout << status_icon << " " << sensor->getType() << " ID=" << sensor->getId() 
                          << " | ERROR or FAULT detected. Recalibrating..." << std::endl;

                sensor->calibrate(); 
                logLine = " -> Action: Recalibrated due to ERROR/FAULT.";
            } 
            else if (sensor->getStatus() == SensorStatus::WARNING) {
                status_icon = "⚠️";
                std::cout << status_icon << " " << sensor->getType() << " ID=" << sensor->getId() 
                          << " | WARNING: Value=" << sensor->getLastReading() << ". Monitoring." << std::endl;
                logLine = " -> Status: WARNING.";
            } 
            else {
                 std::cout << status_icon << " " << sensor->getType() << " ID=" << sensor->getId() << " | Status=OK" << std::endl;
                 logLine = " -> Status: OK.";
            }

            report_ += "[" + sensor->getType() + " ID=" + std::to_string(sensor->getId()) + "] " + logLine + "\n";
        });

    std::cout << "================== END ==================\n";
}


void Diagnostics::generateReport(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::app);
    if (ofs.is_open()) {
        ofs << report_ << "\n";
        ofs.close();
        std::cout << "[REPORT SAVED] Diagnostics report appended to " << filename << std::endl;
    } else {
        
        throw std::runtime_error("Failed to open diagnostics report file: " + filename);
    }
}
