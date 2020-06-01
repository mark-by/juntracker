#include <API.h>
#include <student.h>
#include <user.h>


std::tuple<std::string, bool> API::fetch(const std::string &key, const std::unordered_multimap<std::string, std::string> &data) {
    auto match = data.find(key);
    if (match != data.end()) {
        return {match->second, true};
    } else {
        return {"", false};
    }
}

std::string API::get(const std::string &key, const std::unordered_multimap<std::string, std::string> &data) {
    auto match = data.find(key);
    if (match != data.end()) {
        return match->second;
    } else {
        return "";
    }
}
