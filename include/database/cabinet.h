#ifndef JUNTRACKER_CABINET_H
#define JUNTRACKER_CABINET_H

#include <string>

class Cabinet {
public:
    explicit Cabinet(int id, const std::string &title, int school_id): _id(id), _schoolId(school_id), _title(title) {};

    static int save(const std::string &title, int schoolId);
    static int update(const std::string &title, int schoolId, int cabinetId);
    static int remove(int id);
    static Cabinet get(int id);

    int id() const { return _id;}
    std::string title() const { return _title;}

private:
    int _id;
    int _schoolId;
    std::string _title;
};


#endif //JUNTRACKER_CABINET_H
