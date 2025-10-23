#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

// ✅ [تعديل] تضمين الكلاس المصحح
#include "sensor_manager.h" 
#include <string>
#include <memory>

// ✅ [تعديل] تغيير اسم الكلاس من diagnostics إلى Diagnostics
class Diagnostics
{
private:
    std::string report_ = "";
    
public:
    Diagnostics() = default;
    ~Diagnostics() = default;

    // ✅ [تعديل] يجب أن تأخذ مرجعًا لـ SensorManager بدلاً من أن تحتوي عليه.
    void runDiagnostics(SensorManager& manager); 
    void generateReport(const std::string &filename) const;
    void resetReport() { report_ = ""; }
};

#endif