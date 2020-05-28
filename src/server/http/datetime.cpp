#include <http/datetime.h>

DateTimeConverter::DateTimeConverter(const std::string &format) {
    facet = new boost::posix_time::time_facet();
    facet->format(format.c_str());
    stream.imbue(std::locale(std::locale::classic(), facet));
}

std::string DateTimeConverter::convert(const boost::posix_time::ptime &ptime, const std::string &zone) {
    stream.str("");
    stream << ptime;
    if (!zone.empty()) {
        stream << " " << zone;
    }
    return stream.str();
}

boost::posix_time::ptime DateTimeConverter::convert(const std::string &timeStr) {
    boost::posix_time::ptime ptime;
    stream.str(timeStr);
    stream >> ptime;
    stream.str("");
    return ptime;
}

std::string DateTime::weekdayToStr(int weekday) {
    switch(weekday) {
        case 0:
            return "Понедельник";
        case 1:
            return "Вторик";
        case 2:
            return "Среда";
        case 3:
            return "Четверг";
        case 4:
            return "Пятница";
        case 5:
            return "Суббота";
        case 6:
            return "Воскресенье";
        default:
            return "";
    }
}

std::string DateTime::dateByWeekday(int weekday) {
    auto currentDayOfWeek = now.date().day_of_week();
    auto day = now + (boost::gregorian::days(weekday - currentDayOfWeek.as_number() + 1));
    DateTimeConverter converter("%d.%m.%y");
    return converter.convert(day, "");
}
