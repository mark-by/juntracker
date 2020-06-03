#include <StaffAPI.h>
#include <context/context.h>

templates::Context StaffAPI::CourseSerializer(const Course& course) {
    templates::Context context;
    context.put("title", course.title());
    context.put("id", course.id());
    context.put("price", course.price());
    return context;
}

templates::Context StaffAPI::getUserData(const User &user) {
    templates::Context context;
    auto courses = user.get_courses();
    context.putArray("courses", user.get_courses(), CourseSerializer);
    context.putArray("teachers", user.get_teachers(), SimplePersonSerializer<Teacher>());
    context.putArray("cabinets", user.get_cabinets(), SimpleTitleSerializer<Cabinet>());
    return context;
}

std::string StaffAPI::getMainPage(const User &user) {
    _render.set("mainPageStaff.html");
    auto context = mainStaffData(user);
    return _render.render(context);
}

templates::Context StaffAPI::DaySerializer(const WeekDay &weekday) {
    templates::Context context;
    context.put("weekDay", weekday.weekday);
    context.put("date", weekday.date);
    context.putArray("lessons", weekday.lessons, LessonSerializer);

    return context;
}

templates::Context StaffAPI::CurrentLessonSerializer(const Lesson &lesson) {
    templates::Context context;
    context.put("title", lesson.get_course().title());
    context.put("id", lesson.id());
    context.put("cabinet", lesson.get_cabinet().title());
    auto teacher = lesson.get_teacher();
    context.put("tutor", teacher.name() + " " + teacher.surname());
    std::vector<StudentOnLesson> students;
    for (auto &student : lesson.get_students()) {
        students.emplace_back(student, lesson);
    }
    context.putArray("children", students, StudentSerializer);
    context.put("startTime", lesson.start_time());
    context.put("endTime", lesson.end_time());

    return context;
}


templates::Context StaffAPI::UserSerializer(const User &user) {
    templates::Context context;
    context.put("username", user.login());
    context.put("isAdmin", user.permission() == Permission::admin);
    return context;
}

templates::Context StaffAPI::StudentSerializer(const StudentOnLesson &student) {
    templates::Context context;
    context.put("name", student.student.name() + " " + student.student.surname());
    context.put("id", student.student.id());
    try {
        bool was = student.student.get_visit(student.lesson.id(),boost::posix_time::second_clock::universal_time()).was_in_class();
        std::cout << "ID NAME: " << student.student.name() << " " << "WAS IN CLASS: " <<  was << std::endl;
        context.put("isHere", was);
    } catch(...) {
        context.put("isHere", false);
    }

    return context;
}

templates::Context StaffAPI::LessonSerializer(const Lesson &lesson) {
    templates::Context context;
    auto course = lesson.get_course();
    context.put("title", course.title());
    context.set("cabinet", SimpleTitleSerializer<Cabinet>()(lesson.get_cabinet()));
    context.set("course", SimpleTitleSerializer<Course>()(course));
    context.put("id", lesson.id());
    context.set("teacher", SimplePersonSerializer<Teacher>()(lesson.get_teacher()));
    context.putArray("children", lesson.get_students(), SimplePersonSerializer<Student>());
    context.put("startTime", lesson.start_time());
    context.put("endTime", lesson.end_time());

    return context;
}

templates::Context StaffAPI::mainStaffData(const User &user) {
    auto context = mainScheduleStaffData(user);
    std::vector<Lesson> currentLessons;
    try {
        currentLessons = user.get_current_lessons();
    } catch(...) {}
    context.putArray("currentLessons", currentLessons, CurrentLessonSerializer);
    return context;
}


templates::Context StaffAPI::mainScheduleStaffData(const User &user) {
    templates::Context context;
    context.set("user", UserSerializer(user));
    std::vector<WeekDay> days;
    DateTime dateTime;
    for (int weekday = 0; weekday < 7; weekday++) {
        try {
            days.emplace_back(DateTime::weekdayToStr(weekday), dateTime.dateByWeekday(weekday),
                              user.get_lessons_by_weekday(weekday));
        } catch(...) {}
    }
    context.putArray("scheduleDays", days, DaySerializer);
    return context;
}

std::string StaffAPI::schedule(const User &user) {
    auto context = mainScheduleStaffData(user);
    _render.set("scheduleStaff.html");
    return _render.render(context);
}
