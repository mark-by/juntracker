#ifndef JUNTRACKER_DATETIME_H
#define JUNTRACKER_DATETIME_H
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <memory>

class DateTimeConverter {
public:
    DateTimeConverter(const std::string & format = "%a, %d %b %Y %H:%M:%S");
    ~DateTimeConverter();

    std::string convert(const boost::posix_time::ptime & ptime, const std::string & zone = "GMT");
    boost::posix_time::ptime convert(const std::string & timeStr);
private:
    std::stringstream stream;
    boost::posix_time::time_facet *facet;

};

class DateTime {
public:
    DateTime() : now(boost::posix_time::second_clock::universal_time()) {}
    static std::string weekdayToStr(int weekday);
    std::string dateByWeekday(int weekday);
private:
    boost::posix_time::ptime now;

};

#endif //JUNTRACKER_DATETIME_H
