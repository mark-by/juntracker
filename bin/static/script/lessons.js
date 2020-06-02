import Component from "./Component.js";

class Root {
    constructor(element, app) {
        this.element = element;
        this.app = app;
        this.app.init(this);
    }

    render() {
        this.element.innerHTML = this.app.render();
    }
}

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
                        if (json.students) {
                            this.insert(json.students)
                        }
                    });
                }
            })
        }
    }

    insert(students) {
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
            creationOpened: false
        }

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
            fetch('/api/update_lesson', {
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
        console.log(json)
        this.state.courses = json.courses;
        this.state.cabinets = json.cabinets;
        this.state.teachers = json.teachers
    }

    render() {
        this.studentList.setState({students: this.state.students});

        return this.state.isOpen ?
            `
            ${this.state.creationOpened ? this.creationForm.render() : ""}
            ${this.state.searchOpened ? this.searchForm.render() : ""}
            <div class="modal-wrapper" id="#lesson-edit-form-wrapper" onclick="closeForm(event)">
                <form class="modal-form" method="POST" enctype="application/x-www-form-urlencoded" onsubmit="saveLesson(event)">
                    <input id="lesson-id" name="lesson_id" type="hidden" value="${this.state.lessonData.id}">
                        <div class="form-title"><span id="edit-action">Изменить</span>&nbsp;урок</div>
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
                            <p>Курс</p>
                            <select name="course" id="lesson-edit-title">
                                ${this.state.courses.map(course => {
                if (course.id == this.state.lessonData.courseId) {
                    return `<option value="${course.id}" selected="selected">${course.title}</option>`
                } else {
                    return `<option value="${course.id}">${course.title}</option>`
                }
            }).join("")}
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
                                <input type="number" maxlength="2" max="23" min="0" name="start-hours" id="start-hours-edit" value="${this.state.lessonData.time[0]}"/>
                                <span>:</span>
                                <input type="number" maxlength="2" max="59" min="0" name="start-minutes" id="start-minutes-edit" value="${this.state.lessonData.time[1]}"/>
                            </label>
                            <p>Конец занятия</p>
                            <label>
                                <input type="number" maxlength="2" max="23" min="0" name="end-hours" id="end-hours-edit" value="${this.state.lessonData.time[2]}"/>
                                <span>:</span>
                                <input type="number" maxlength="2" max="59" min="0" name="end-minutes" id="end-minutes-edit" value="${this.state.lessonData.time[3]}"/>
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

const root = new Root(document.querySelector("#root"), new Form);

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

            }
        });
    }
});
