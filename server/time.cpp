#include <string>
#include <sstream>


std::string GetCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int day = ltm->tm_mday;
    int month = 1 + ltm->tm_mon;
    int year = 1900 + ltm->tm_year;
    int hour = ltm->tm_hour;
    int minute = ltm->tm_min;
    
    std::string strMinute = "";
    if (minute < 10) {
        strMinute = "0" + std::to_string(minute);
    }
    else {
        strMinute = std::to_string(minute);
    }
    
    std::stringstream ss;
    ss << day << '.' << month << '.' << year << ' ' << hour << ':' << strMinute;
    return ss.str();
}
