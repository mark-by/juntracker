#ifndef JUNTRACKER_CABINET_H
#define JUNTRACKER_CABINET_H

#include <string>

class Cabinet {
public:
    explicit Cabinet(int id, const std::string &title, int school_id): _id(id), _schoolId(school_id), _title(title) {};

    static void save(const std::string &title, int schoolId);
    static void remove(int id);
    static Cabinet get(int id);

    int id() { return _id;}
    std::string title() { return _title;}

private:
    int _id;
    int _schoolId;
    std::string _title;
};


#endif //JUNTRACKER_CABINET_H
