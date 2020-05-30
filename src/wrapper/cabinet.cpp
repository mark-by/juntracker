//
// Created by gg on 30.05.2020.
//

#include "cabinet.h"
#include "sql_wrapper.h"


void Cabinet::save(const std::string &title, int schoolId) {
    SqlWrapper db;
    db << "INSERT INTO cabinet(title, school_id) VALUES ('" << title << "', " << schoolId << ");";

    db.exec("Save cabinet");
    db.disconnect();
}

void Cabinet::remove(int id) {
    SqlWrapper db;
    db << "DELETE FROM cabinet WHERE id=" << id << ";";
    db.exec("Remove cabinet");
    db.disconnect();
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
