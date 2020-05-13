#include <http/datetime.h>

DateTimeConverter::DateTimeConverter(const std::string &format) {
    facet = new boost::posix_time::time_facet();
    facet->format(format.c_str());
    stream.imbue(std::locale(std::locale::classic(), facet));
}

DateTimeConverter::~DateTimeConverter() {
    delete facet;
}

std::string DateTimeConverter::convert(const boost::posix_time::ptime &ptime, const std::string &zone) {
    stream.str("");
    stream << ptime << " " << zone;
    return stream.str();
}

boost::posix_time::ptime DateTimeConverter::convert(const std::string &timeStr) {
    boost::posix_time::ptime ptime;
    stream.str(timeStr);
    stream >> ptime;
    stream.str("");
    return ptime;
}
