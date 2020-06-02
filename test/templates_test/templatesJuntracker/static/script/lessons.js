import Component from "./Component.js";
import Root from "./root.js";

class CreationForm extends Component {
    constructor(props) {
        super();

        window.submitSaveStudent = (event) => {
            event.preventDefault();
            const formData = new FormData(event.target);
            fetch('/api/save_student', {
                method: 'POST',
                headers: {
                    'content-type': 'application/x-www-form-urlencoded',
                },
                body: new URLSearchParams(formData).toString()
            }).then(response => {
                    if (response.ok) {
                        response.json().then(json => {
                            window.updateStudents({
                                id: json.id ? json.id : -1,
                                name: formData.get('name') + " " + formData.get('surname'),
                                isDeleted: false,
                                isNew: true
                            });
                            window.justCloseCreationForm();
                        })
                    } else {
                        alert("error")
                    }
                }
            )
        }
    }

    render() {
        return (
            `<div class="modal-wrapper" id="#add-student-form-wrapper" style="z-index: 9000" onclick="closeCreationForm(event)">
                <form class="modal-form student-add-form"  method="POST" enctype="application/x-www-form-urlencoded" onsubmit="submitSaveStudent(event)">
                    <p class="form-title">Создать ученика</p>
                    <div class="student-add-form__content  form-grid">
                        <p>Фото</p><input type="file" />
                        <input type="hidden" name="avatar" value=""/>
                        <p>Имя*</p><input name="name" type="text"/>
                        <p>Фамилия*</p><input name="surname" type="text"/>
                        <p>Возраст</p><input name="age" type="number"/>
                        <p>Родитель</p><input name="parent" type="text"/>
                        <p>Контактный номер</p><input name="tel_number" type="text"/>
                        <p>Электронная почта</p><input name="email" type="email"/>
                        <p>Описание</p><textarea name="description"></textarea>
                    </div>
                    <div class="bottom-flex">
                        <div class="close-form-button" onclick="closeCreationForm(event)">Отмена</div>
                        <input type="submit" value="Сохранить"/>
                    </div>
                </form>
            </div>`
        );
    }
}

class StudentList extends Component {
    constructor(props) {
        super();
        this.state = {students: []}
    }

    render() {
        console.log("render List")
        console.log("std list", this.state.students)
        return `
        ${this.state.students.map(student => {
            if (student.isNew) {
                return `<input type="hidden" name="new_student" value="${student.id}"/>
                        <div class='lesson__content_child' id="lesson__content_child${student.id}" hidden'>
                            <div class='name'>${student.name}</div>
                                <div class='delete-student-button' data='${student.id}' onclick="deleteStudent(event)" >
                                    <img src='static/images/close.svg' data='${student.id}' alt='удалить'/>
                                </div>
                        </div>`
            }
            return student.isDeleted ? `<input type="hidden" name="delete_student" value="${student.id}"/>`
                : `<div class='lesson__content_child' id="lesson__content_child${student.id}" hidden'>
                        <div class='name'>${student.name}</div>
                            <div class='delete-student-button' data='${student.id}' onclick="deleteStudent(event)" >
                                <img src='static/images/close.svg' data='${student.id}' alt='удалить'/>
                            </div>
                   </div>`
        }).join("")}`
    }
}

class SearchForm extends Component {
    constructor() {
        super();
        this.state = {
            foundedStudents: [],
            searching: false,
            interval: false
        }

        window.searchByEnter = (event) => {
            if (event.key == "Enter") {
                window.search();
            }
        }

        window.search = () => {
            const student = document.querySelector("#search-student").value;
            fetch('/api/search_student?search=' + student).then(response => {
                if (response.ok) {
                    response.json().then(json => {
                        this.insert(json.students)
                    });
                }
            })
        }
    }

    insert(students) {
        if (!students) {
            document.querySelector("#founded-students").innerHTML = `<div class="founded-student">Ничего нет :(</div>`
        }
        document.querySelector("#founded-students").innerHTML = `${students.map(student => {
            return `<div class="founded-student" data="${student.id}">${student.name}</div>`
        }).join("")}`;
        const studentss = document.querySelectorAll(".founded-student");
        console.log("foundedddd", studentss);
        [...studentss].map(element => {
            console.log("founded-student")
            element.onclick = () => {
                window.updateStudents({
                    id: element.getAttribute("data"),
                    name: element.innerText,
                    isDeleted: false,
                    isNew: true,
                })
                window.closeSearchForm(true, true);
            }
        })
    }

    render() {
        console.log("fs", this.state.foundedStudents)
        console.log("render search")
        return `
            <div class="modal-wrapper" id="search-student-form-wrapper" style="z-index: 9000" onclick="closeSearchForm(event)">
                <div class="modal-form">
                    <p class="form-title">Найти ученика</p>
                    <div class="form-grid">
                        <p>Найти: </p><input type="text" id="search-student" oninput="search()" onkeydown="searchByEnter(event)"/>
                    </div> 
                    <div id="founded-students"></div>
                    <div class="bottom-flex">
                        <div class="close-form-button" onclick="closeSearchForm(event);">Отмена</div> 
                    </div>
                </div>
            </div>
        `
    }
}


class Form extends Component {
    constructor() {
        super();
        this.state = {
            isOpen: false,
            courses: [],
            cabinets: [],
            teachers: [],
            lessonData: {
                id: 0,
                weekday: 0,
                teacherId: 0,
                courseId: 0,
                cabinetId: 0,
                time: [0, 0, 0, 0],
            },
            students: [],
            searchOpened: false,
            creationOpened: false,
            isNew: false
        }

        this.count = 0;

        this.getData();
        this.creationForm = new CreationForm();
        this.searchForm = new SearchForm();
        this.studentList = new StudentList();

        window.closeForm = (event) => {
            if (["modal-wrapper", "close-form-button"].includes(event.target.className)) {
                this.setState({isOpen: false});
            }
        }

        window.deleteStudent = (event) => {
            window.updateStudents({
                id: event.target.getAttribute('data'),
                name: event.target.innerText,
                isDeleted: true,
                isNew: false
            })
        }


        window.saveLesson = (event) => {
            event.preventDefault();
            let url;
            if (this.state.isNew) {
                url = "/api/create_lesson";
            } else {
                url = "/api/update_lesson";
            }
            fetch(url, {
                method: 'POST',
                headers: {
                    'content-type': 'application/x-www-form-urlencoded',
                },
                body: new URLSearchParams(new FormData(event.target)).toString()
            }).then(response => {
                if (response.ok) {
                    window.location.reload();
                } else {
                    this.setState({isOpen: false});
                }
            })
        }

        window.openSearchForm = (event) => {
            this.setState({searchOpened: true});
        }

        window.justCloseCreationForm = () => {
            this.setState({creationOpened: false});
        }

        window.closeCreationForm = (event) => {
            if (["modal-wrapper", "close-form-button"].includes(event.target.className)) {
                this.setState({creationOpened: false});
            }
        }

        window.openCreationForm = (event) => {
            this.setState({creationOpened: true});
        }

        window.closeSearchForm = (event, just) => {
            if (just || ["modal-wrapper", "close-form-button"].includes(event.target.className)) {
                this.setState({searchOpened: false});
            }
        }

        window.setLessonStartHours = (event) => {
            this.state.lessonData.time[0] = event.target.value
        }

        window.setLessonStartMinutes = (event) => {
            this.state.lessonData.time[1] = event.target.value
        }

        window.setLessonEndHours = (event) => {
            this.state.lessonData.time[2] = event.target.value
        }

        window.setLessonEndMinutes = (event) => {
            this.state.lessonData.time[3] = event.target.value
        }

        window.updateStudents = (student) => {
            console.log("student", student);
            console.log("before", this.state.students);
            let found = false;
            for (let idx = 0; idx < this.state.students.length; idx++) {
                if (this.state.students[idx].id == student.id) {
                    this.state.students[idx] = student;
                    found = true;
                }
            }
            if (!found) {
                this.state.students.push(student);
            }
            console.log("after", this.state.students);
            this.setState({students: this.state.students});
        }
    }

    async getData() {
        const response = await fetch('/api/user_data');
        const json = await response.json();
        this.state.courses = json.courses;
        this.state.cabinets = json.cabinets;
        this.state.teachers = json.teachers;
    }

    render() {
        this.count += 1;
        this.studentList.setState({students: this.state.students});
        if (!this.state.courses || !this.state.cabinets || !this.state.teachers) {
            if (this.count % 2 === 0) {
                alert("Сначала заполните информацию о курсах, кабинетах и учителях. После обновите страницу");
            }
            return;
        }
        return this.state.isOpen ?
            `
            ${this.state.creationOpened ? this.creationForm.render() : ""}
            ${this.state.searchOpened ? this.searchForm.render() : ""}
            <div class="modal-wrapper" id="#lesson-edit-form-wrapper" onclick="closeForm(event)">
                <form class="modal-form" method="POST" enctype="application/x-www-form-urlencoded" onsubmit="saveLesson(event)">
                    ${this.state.isNew ? "" : `<input id="lesson-id" name="lesson_id" type="hidden" value="${this.state.lessonData.id}">`}
                        <div class="form-title">${this.state.isNew ? "Создать" : "Изменить"}&nbsp;урок</div>
                        <div class="form-grid">
                            <p>День недели</p>
                            <select name="weekday" id="lesson-edit-weekday">
                                <option value="0" ${this.state.lessonData.weekday === "Понедельник" ? 'selected="selected"' : ""} >Понедельник</option>
                                <option value="1" ${this.state.lessonData.weekday === "Вторник" ? 'selected="selected"' : ""} >Вторник</option>
                                <option value="2" ${this.state.lessonData.weekday === "Среда" ? 'selected="selected"' : ""} >Среда</option>
                                <option value="3" ${this.state.lessonData.weekday === "Четверг" ? 'selected="selected"' : ""}>Четверг</option>
                                <option value="4" ${this.state.lessonData.weekday === "Пятница" ? 'selected="selected"' : ""}>Пятница</option>
                                <option value="5" ${this.state.lessonData.weekday === "Суббота" ? 'selected="selected"' : ""}>Cуббота</option>
                                <option value="6" ${this.state.lessonData.weekday === "Воскресенье" ? 'selected="selected"' : ""}>Воскресенье</option>
                            </select>
                            ${this.state.isNew ?
                            `<p>Курс</p>
                            <select name="course" id="lesson-edit-title">
                                ${this.state.courses.map(course => {
                                    if (course.id == this.state.lessonData.courseId) {
                                        return `<option value="${course.id}" selected="selected">${course.title}</option>`
                                    } else {
                                        return `<option value="${course.id}">${course.title}</option>`
                                    }
                                }).join("")}` : ""}
                            </select>
                            <p>Кабинет</p>
                            <select name="cabinet" id="lesson-edit-cabinet">
                                ${this.state.cabinets.map(cabinet => {
                if (cabinet.id == this.state.lessonData.cabinetId) {
                    return `<option value="${cabinet.id}" selected="selected">${cabinet.title}</option>`
                } else {
                    return `<option value="${cabinet.id}">${cabinet.title}</option>`
                }
            }).join("")}
                            </select>
                            <p>Преподаватель</p>
                            <select name="teacher" id="lesson-edit-teacher">
                                ${this.state.teachers.map(teacher => {
                if (teacher.id == this.state.lessonData.teacherId) {
                    return `<option value="${teacher.id}" selected="selected">${teacher.name}</option>`
                } else {
                    return `<option value="${teacher.id}">${teacher.name}</option>`
                }
            }).join("")}
                            </select>
                            <p>Начало занятия</p>
                            <label>
                                <input type="number" maxlength="2" max="23" min="0" name="start-hours" id="start-hours-edit" value="${this.state.lessonData.time[0]}" oninput="setLessonStartHours(event)"/>
                                <span>:</span>
                                <input type="number" maxlength="2" max="59" min="0" name="start-minutes" id="start-minutes-edit" value="${this.state.lessonData.time[1]}" oninput="setLessonStartMinutes(event)"/>
                            </label>
                            <p>Конец занятия</p>
                            <label>
                                <input type="number" maxlength="2" max="23" min="0" name="end-hours" id="end-hours-edit" value="${this.state.lessonData.time[2]}" oninput="setLessonEndHours(event)"/>
                                <span>:</span>
                                <input type="number" maxlength="2" max="59" min="0" name="end-minutes" id="end-minutes-edit" value="${this.state.lessonData.time[3]}" oninput="setLessonEndMinutes(event)"/>
                            </label>
                        </div>
                        <div class="bottom-flex">
                            <div class="students-title">Студенты</div>
                        </div>
                        <div class="students">
                        ${this.studentList.render()}
                        </div>
                        <div class="bottom-control-wrapper">
                            <div class="add-student-button">
                            <div class="add-student-button__new" onclick="openCreationForm(event)">Создать</div>
                            <img class="add-student-button__plus" src="static/images/plus.svg" alt="добавить"/>
                            <div class="add-student-button__search" onclick="openSearchForm(event)">Найти</div>
                        </div>
                        <div class="bottom-flex">
                            <div class="close-form-button" onclick="closeForm()">Отмена</div>
                            <input type="submit" value="Сохранить"/>
                        </div>
                    </div>
                </formcla>
            </div>` : "";
    }
}

class DeleteLessonModal extends Component {
    constructor() {
        super();
        this.state = {
            isOpen: false,
            id: -1
        }

        window.closeDeleteModalForm = (event) => {
            if (["modal-wrapper", "close-form-button"].includes(event.target.className)) {
                this.setState({isOpen: false});
            }
        }

        window.deleteLesson = (event) => {
            event.preventDefault();
            fetch('/api/delete_lesson', {
                method: 'POST',
                headers: {
                    'content-type': 'application/x-www-form-urlencoded',
                },
                body: new URLSearchParams(new FormData(event.target)).toString()
            }).then(response => {
                if (response.ok) {
                    window.location.reload();
                } else {
                    alert('Не удалось удалить ;(');
                    this.setState({isOpen: false});
                }
            })
        }
    }

    render() {
        if (!this.state.isOpen) {
            return "";
        }
        return `
        <div class="modal-wrapper" onclick="closeDeleteModalForm(event)">
            <form class="modal-form" onsubmit="deleteLesson(event)">
                <div class="form-title">Удалить?</div>
                <input type="hidden" name="id" value="${this.state.id}"/>
                <div class="bottom-flex">
                    <div class="close-form-button" onclick="closeDeleteModalForm(event)">Отмена</div>
                    <input type="submit" value="Удалить"/>
                </div>
            </form> 
        </div>
        `
    }
}

const root = new Root(document.querySelector("#root"), new Form);
const deleteRootModal = new Root(document.querySelector("#root"), new DeleteLessonModal());

[...document.querySelectorAll(".schedule .card-wrapper")].map(lesson => {
    lesson.querySelector('.button-settings-lesson').onclick = () => {
        const [start, end] = lesson.querySelector('.lesson__footer').innerText.split(" - ");
        const [startH, startM] = start.split(":");
        const [endH, endM] = end.split(":");
        root.app.setState({
            isOpen: true,
            students: [...lesson.querySelectorAll('.lesson__content_child')].map(student => {
                return {
                    id: student.getAttribute('data'),
                    name: student.innerText,
                    isDeleted: false,
                    isNew: false
                }
            }),
            lessonData: {
                id: lesson.getAttribute('data'),
                weekday: lesson.getAttribute('weekday'),
                teacherId: lesson.getAttribute('teacher'),
                courseId: lesson.getAttribute('course'),
                cabinetId: lesson.getAttribute('cabinet'),
                time: [startH, startM, endH, endM],

            },
            isNew: false
        });
    }

    lesson.querySelector('.button-delete-lesson').onclick = () => {
        deleteRootModal.app.setState({
            isOpen: true,
            id: lesson.getAttribute('data'),
        })
    }
});

function iWeekToStr(week) {
    switch (week) {
        case 0:
            return 'Понедельник';
        case 1:
            return 'Вторник';
        case 2:
            return 'Среда';
        case 3:
            return 'Четверг';
        case 4:
            return 'Пятница';
        case 5:
            return 'Суббота';
        case 6:
            return 'Воскресенье';
    }
}

[...document.querySelectorAll('.add-lesson-button')].map((button, idx) => {
    console.log(iWeekToStr(idx), idx);
    button.onclick = () => {
        root.app.setState({
            isOpen: true,
            students: [],
            lessonData: {
                id: -1,
                weekday: iWeekToStr(idx),
                teacherId: -1,
                courseId: -1,
                cabinetId: -1,
                time: [0, 0, 0, 0],
            },
            isNew: true
        });
    }
})


class Window extends Component {
    constructor() {
        super();
        this.state = {
            now: "schedule"
        }
        this.scheduleButton = document.querySelector("#schedule-button");
        this.courseButton = document.querySelector("#course-button");
        this.teacherButton = document.querySelector("#teacher-button");
        this.cabinetButton = document.querySelector("#cabinet-button");

        this.scheduleButton.onclick = () => this.setState({now: "schedule"});
        this.courseButton.onclick = () => this.setState({now: "course"});
        this.teacherButton.onclick = () => this.setState({now: "teacher"});
        this.cabinetButton.onclick = () => this.setState({now: "cabinet"});

        this.coursesWin = document.querySelector(".window-courses");
        this.coursesList = document.querySelector('#window-courses-list');

        this.teachersWin = document.querySelector(".window-teachers");
        this.teachersList = document.querySelector('#window-teachers-list');

        this.cabinetsWin = document.querySelector(".window-cabinets");
        this.cabinetsList = document.querySelector('#window-cabinets-list');

        window.saveListElement = (event) => {
            event.preventDefault();
            fetch('/api/save_' + event.target.getAttribute('title'), {
                method: 'POST',
                headers: {
                    'content-type': 'application/x-www-form-urlencoded'
                },
                body: new URLSearchParams(new FormData(event.target)).toString()
            }).then(res => {
                if (!res.ok) {
                    alert("Неудача :(")
                } else {
                    alert("Успешно! :)")
                }
            })
        }

        window.addCourse = () => {
            this.coursesList.innerHTML += `
                    <form class="course-form" data="-1" onsubmit="saveListElement(event)" title="course">
                        <input type="text" value="" placeholder="Введите название" name="title"/>
                        <input type="number" value="" placeholder="Укажите цену" name="price"/>
                        <input type="hidden" value="-1" name="id"/>
                        <div class="course-form-buttons">
                            <input class="save-course-button" value type="submit"/>
                            <img class="delete-course-button" src="static/images/trash.svg"/>
                        </div>
                    </form>  
                `;
            this.initLists();
        }

        window.addTeacher = () => {
            this.teachersList.innerHTML += `
                    <form class="teacher-form" data="-1" onsubmit="saveListElement(event)" title="teacher">
                    <input type="text" value="" placeholder="Введите имя" name="name"/>
                    <input type="text" value="" placeholder="Введите фамилию" name="surname"/>
                    <input type="hidden" value="-1" name="id"/>
                    <div class="course-form-buttons">
                        <input class="save-course-button" value type="submit"/>
                        <img class="delete-course-button" src="static/images/trash.svg"/>
                    </div>
                    </form>  
                `;
            this.initLists()
        }

        window.addCabinet = () => {
            this.cabinetsList.innerHTML += `
                    <form class="cabinet-form" data="-1" onsubmit="saveListElement(event)" title="cabinet">
                    <input type="text" value="" placeholder="Введите аудиторию" name="name"/>
                    <input type="hidden" value="-1" name="id"/>
                    <div class="course-form-buttons">
                        <input class="save-course-button" value type="submit"/>
                        <img class="delete-course-button" src="static/images/trash.svg"/>
                    </div>
                    </form>  
                `;
            this.initLists();
        }
    }

    delEl(element) {
        fetch('/api/delete_' + element.getAttribute('title'), {
            method: 'POST',
            headers: {
                'content-type': 'application/x-www-form-urlencoded'
            },
            body: new URLSearchParams(new FormData(element)).toString()
        }).then(res => {
            // if (res.ok) {
            element.remove();
            // }
        })
    }

    initLists() {
        [...this.coursesList.querySelectorAll('.course-form'),
            ...this.teachersList.querySelectorAll('.teacher-form'),
            ...this.cabinetsList.querySelectorAll('.cabinet-form')].map(element => {
            console.log("1")
            element.querySelector('.delete-course-button').onclick = () => {
                this.delEl(element)
            }
        })
    }

    render() {
        this.scheduleButton.classList.remove('active');
        this.courseButton.classList.remove('active');
        this.teacherButton.classList.remove('active');
        this.cabinetButton.classList.remove('active');

        this.coursesWin.classList.replace('active-window', 'background-window');
        this.teachersWin.classList.replace('active-window', 'background-window');
        this.cabinetsWin.classList.replace('active-window', 'background-window');


        switch (this.state.now) {
            case "schedule":
                this.scheduleButton.classList.add('active');
                break;
            case "teacher":
                this.teacherButton.classList.add('active');
                this.teachersWin.classList.replace('background-window', 'active-window');
                break;
            case "cabinet":
                this.cabinetButton.classList.add('active');
                this.cabinetsWin.classList.replace('background-window', 'active-window');
                break;
            case "course":
                this.courseButton.classList.add('active');
                this.coursesWin.classList.replace('background-window', 'active-window');
                break;
        }
    }
}

const win = new Window();
win.render();
win.initLists();
