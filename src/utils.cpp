#include "../include/utils.h"
#include <sstream>
#include <iomanip>
#include <chrono>

namespace Utils {
    // مُتغيّر ثابت لتتبع الـ ID التالي
    static int nextId = 1;
    // مُولّد الأرقام العشوائية (يتم تهيئته مرة واحدة)
    static std::random_device rd;
    static std::mt19937 gen(rd());

    int generateID() {
        return nextId++;
    }

    double randomDouble(double min, double max) {
        // توزيع الأرقام العشرية العشوائية
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }

    bool chance(double probability) {
        // اختبار عشوائي لاحتمالية معينة (بين 0.0 و 1.0)
        return randomDouble(0.0, 1.0) < probability;
    }

    std::string currentDateTime() {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::stringstream ss;
        // استخدام put_time لتنسيق الوقت
        ss << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
}
