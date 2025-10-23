#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <random>

namespace Utils {
    // 1. توليد ID فريد
    int generateID();

    // 2. توليد رقم عشري عشوائي
    double randomDouble(double min, double max);

    // 3. محاكاة الفرصة العشوائية (للفشل)
    bool chance(double probability);

    // 4. الحصول على التاريخ والوقت الحالي
    std::string currentDateTime();
}

#endif // UTILS_H
