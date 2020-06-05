//
// Created by gg on 30.05.2020.
//

#include "cabinet.h"
#include "sql_wrapper.h"


int Cabinet::save(const std::string &title, int schoolId) {
    SqlWrapper db;

    db << "INSERT INTO cabinet(title, school_id) VALUES ('" << title << "', " << schoolId << ");";
    db.exec("Save cabinet");

    db.disconnect();

    return 0;
}

int Cabinet::update(const std::string &title, int schoolId, int cabinetId) {
    SqlWrapper db;

    db << "update cabinet set title='" << title << "', school_id=" << schoolId << " where id=" << cabinetId << ";";
    db.exec("Update cabinet");

    db.disconnect();

    return 0;
}

int Cabinet::remove(int id) {
    SqlWrapper db;
    db << "DELETE FROM cabinet WHERE id=" << id << ";";
    db.exec("Remove cabinet");
    db.disconnect();

    return 0;
}

Cabinet Cabinet::get(int id) {
    SqlWrapper db;
    db << "select * FROM cabinet WHERE id=" << id << ";";
    db.exec("Get user by username");
    db.disconnect();

    return Cabinet(
            db.get_int(0),
            db.get_str(1),
            db.get_int(2)
            );
}
