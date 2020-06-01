import Component from "./Component.js";

//     parseTime() {
//         const [start, end] = this.time.state.content.split(" - ");
//         const [startH, startM] = start.split(":");
//         const [endH, endM] = end.split(":");
//         return {
//             startHours: startH,
//             startMinutes: startM,
//             endHours: endH,
//             endMinutes: endM
//         };
//     }

//         return `<div class='lesson__content_child' hidden data='${this.id}'>
//                     <div class='name'>${this.name}</div>
//                     <div class='delete-student-button'>
//                         <img src='static/images/close.svg' alt='удалить'/>
//                     </div>
//                 </div>`
//     }
// }
//
// class StudentList extends Component {
//     constructor(element, students) {
//         super({students: students});
//         this.element = element;
//     }
//
//     clear() {
//         this.element.innerHTML = "";
//     }

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

class Form extends Component {
    constructor() {
        super();
        this.state = {
            isOpen: false,
            lessonData: {
                id: 0,
                weekday: 0,
                teacherId: 0,
                courseId: 0,
                cabinetId: 0,
                time: "",
                students: []
            }
        }

        window.closeForm = (event) => {
            if (["modal-wrapper", "close-form-button"].includes(event.target.className)) {
                this.setState({isOpen: false});
            }
        }
        window.deleteStudent = (event) => {
            const id = event.target.getAttribute('data');
            document.querySelector('#lesson__content_child'+ id).outerHTML =
                `<input type="hidden" name="delete_student" value="${id}"/>`;
        }
    }

    render() {
        let courses = [];
        let cabinets = [];
        let teachers = [];
        fetch('/api/get_user_data').then(result => {
            if (result.ok) {
                result.json().then(json => {
                    courses = json.courses;
                    cabinets = json.cabintes;
                    teachers = json.teachers;
                    }
                )
            } else {
                console.log("Error: ", result.status);
            }
        })
        return this.state.isOpen ?
            `<div class="modal-wrapper" id="#lesson-edit-form-wrapper" onclick="closeForm(event)">
                <form class="modal-form" method="POST" enctype="application/x-www-form-urlencoded">
                    <input id="lesson-id" name="lesson_id" type="hidden" value="${this.state.lessonData.id}">
                        <div class="form-title"><span id="edit-action">Изменить</span>&nbsp;урок</div>
                        <div class="form-grid">
                            <p>День недели</p>
                            <select name="weekday" id="lesson-edit-weekday">
                                <option value="0">Понедельник</option>
                                <option value="1">Вторник</option>
                                <option value="2">Среда</option>
                                <option value="3">Четверг</option>
                                <option value="4">Пятница</option>
                                <option value="5">Cуббота</option>
                                <option value="6">Воскресенье</option>
                            </select>
                            <p>Курс</p>
                            <select name="course" id="lesson-edit-title">
                                ${courses.map(course => {
                return `<option value="${course.id}">${course.title}</option>`
            })}
                            </select>
                            <p>Кабинет</p>
                            <select name="cabinet" id="lesson-edit-cabinet">
                                ${cabinets.map(cabinet => {
                return `<option value="${cabinet.id}">${cabinet.title}</option>`
            })}
                            </select>
                            <p>Преподаватель</p>
                            <select name="teacher" id="lesson-edit-teacher">
                                ${teachers.map(teacher => {
                return `<option value="${teacher.id}">${teacher.name}</option>`
            })}
                            </select>
                            <p>Начало занятия</p>
                            <label>
                                <input type="number" maxlength="2" max="23" min="0" name="start-hours" id="start-hours-edit"/>
                                <span>:</span>
                                <input type="number" maxlength="2" max="59" min="0" name="start-minutes" id="start-minutes-edit"/>
                            </label>
                            <p>Конец занятия</p>
                            <label>
                                <input type="number" maxlength="2" max="23" min="0" name="end-hours" id="end-hours-edit"/>
                                <span>:</span>
                                <input type="number" maxlength="2" max="59" min="0" name="end-minutes" id="end-minutes-edit"/>
                            </label>
                        </div>
                        <div class="bottom-flex">
                            <div class="students-title">Студенты</div>
                        </div>
                        <div class="students">
                        ${this.state.lessonData.students.map(student => {
                            return `<div class='lesson__content_child' id="lesson__content_child${student.id}" hidden'>
                                        <div class='name'>${student.name}</div>
                                        <div class='delete-student-button' data='${student.id}' onclick="deleteStudent(event)" >
                                            <img src='static/images/close.svg' data='${student.id}' alt='удалить'/>
                                        </div>
                                    </div>`}).join("")}
                        </div>
                        <div class="bottom-control-wrapper">
                            <div class="add-student-button">
                            <div class="add-student-button__new">Создать</div>
                            <img class="add-student-button__plus" src="static/images/plus.svg" alt="добавить"/>
                            <div class="add-student-button__search">Найти</div>
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
        root.app.setState({
            isOpen: true,
            lessonData: {
                id: lesson.getAttribute('data'),
                weekday: lesson.getAttribute('weekday'),
                teacherId: lesson.getAttribute('teacher'),
                courseId: lesson.getAttribute('course'),
                cabinetId: lesson.getAttribute('cabinet'),
                time: lesson.querySelector('.lesson__footer').innerText,
                students: [...lesson.querySelectorAll('.lesson__content_child')].map(student => {
                    return {
                        id: student.getAttribute('data'),
                        name: student.innerText
                    }
                })
            }
        });
    }
});


// class Title extends Component {
//     constructor(element) {
//         super({
//             content: element.innerText
//         });
//         this.element = element;
//         this.render()
//     }
//
//     setTitle(title) {
//         this.setState({content: title});
//     }
//
//     render() {
//         this.element.innerText = this.state.content;
//     }
// }
//
// class Option extends Component {
//     constructor(element) {
//         super({value: element.getAttribute("value"), content: element.innerText});
//         this.element = element;
//     }
//
//     render() {
//         this.element.setAttribute("value", this.state.value);
//         this.element.innerText = this.state.content;
//     }
// }
//
// class Input extends Component {
//     constructor(element) {
//         super({value: element.getAttribute("value")});
//         this.element = element;
//     }
//
//     set(value) {
//         this.setState({value: value});
//     }
//
//     render() {
//         this.element.setAttribute("value", this.state.value);
//     }
// }
//
// class Select extends Component {
//     constructor(element) {
//         super({selected: "-1"});
//         this.element = element;
//     }
//
//     select(value) {
//         let idx;
//         [...this.element.options].map((option, index) => {
//             if (option.value === value) {
//                 idx = index;
//             }
//         })
//         this.setState({selected: idx.toString()});
//     }
//
//     deselect() {
//         this.setState({selected: "-1"});
//     }
//
//     render() {
//         this.element.selectedIndex = this.state.selected;
//     }
// }
//
// class Student {
//     constructor(name, id) {
//         this.name = name;
//         this.id = id;
//     }
//
//     str() {
//         return `<div class='lesson__content_child' hidden data='${this.id}'>
//                     <div class='name'>${this.name}</div>
//                     <div class='delete-student-button'>
//                         <img src='static/images/close.svg' alt='удалить'/>
//                     </div>
//                 </div>`
//     }
// }
//
// class StudentList extends Component {
//     constructor(element, students) {
//         super({students: students});
//         this.element = element;
//     }
//
//     clear() {
//         this.element.innerHTML = "";
//     }
//
//     addStudent(student) {
//         const _student = new Student(student.name, student.id);
//         this.element.innerHTML += _student.str();
//     }
//
//     render() {
//         this.element.innerHTML = "";
//         this.state.students.map(student => {
//             const _student = new Student(student.name, student.id);
//             this.element.innerHTML += _student.str();
//         });
//         [...this.element.children].map(element => {
//             element.querySelector('.delete-student-button').onclick = () => {
//                 const id = element.getAttribute('data');
//                 element.outerHTML =  `<input type='hidden' name='delete-student' value='${id}'/>`
//             }
//         })
//     }
// }
//
// class CreateStudentForm extends Component {
//     constructor() {
//         super();
//     }
// }
//
// class Modal extends Component{
//     constructor(closeHandler, element) {
//         super({isOpen: false});
//         this.modalWrapper = element;
//         this.modal = element.firstChild;
//         this.closeButton = element.querySelector('.close-button');
//         this.close = () => closeHandler();
//         this.modalWrapper.onclick = this.close();
//         this.modal.onclick = () => {};
//         this.closeButton.onclick = this.close;
//     }
//
//     close() {
//         this.setState({isOpen: false});
//     }
//
//     open() {
//         this.setState({isOpen: true});
//     }
//
//     render() {
//         if (this.state.isOpen) {
//             this.modalWrapper.style.display = "block";
//         } else {
//             this.modalWrapper.style.display = "none";
//         }
//     }
// }
//
// class LessonEditForm extends Modal {
//     constructor(closeHandler, element, students) {
//         super(closeHandler, element);
//         this.form = this.modal;
//         this.selectTitle = new Select(document.querySelector('#lesson-edit-title'));
//         this.selectCabinet = new Select(document.querySelector('#lesson-edit-cabinet'));
//         this.selectTeacher = new Select(document.querySelector('#lesson-edit-teacher'));
//         this.startTimeHours = new Input(document.querySelector("#start-hours-edit"));
//         this.startTimeMinutes = new Input(document.querySelector("#start-minutes-edit"));
//         this.lessonId = new Input(this.form.querySelector("#lesson-id"));
//         this.endTimeHours = new Input(document.querySelector("#end-hours-edit"));
//         this.endTimeMinutes = new Input(document.querySelector("#end-minutes-edit"));
//         this.studentList = new StudentList(document.querySelector(".students"), students);
//         this.createStudent = this.form.querySelector('.add-student-button__new');
//         this.searchStudent = this.form.querySelector('.add-student-button__search');
//
//         this.form.onsubmit = (event) => this.save(event);
//     }
//
//     save(event) {
//         event.preventDefault();
//         fetch('/api/update_lesson', {
//             method: 'POST',
//             headers: {
//                 'content-type': 'application/x-www-form-urlencoded',
//             },
//             body: new URLSearchParams(new FormData(this.form.querySelector('form'))).toString()
//         }).then(response => {
//             if (response.ok) {
//                 this.close();
//             } else {
//                 this.close()
//             }
//             window.location.reload();
//         })
//     }
//
// }
//
// class ScheduleLesson extends Component {
//     constructor(element) {
//         super({
//             isOpen: false
//         });
//         this.element = element;
//         this.course = new Title(element.querySelector('.lesson__header_course'))
//         this.cabinet = new Title(element.querySelector('.lesson__header_cab'))
//         this.teacher = new Title(element.querySelector('.lesson__header_tutor'))
//         this.time = new Title(element.querySelector('.lesson__footer').firstChild)
//         this.settingsButton = element.querySelector('.button-settings-lesson');
//
//         this.id = this.element.getAttribute("data");
//         this.form = new LessonEditForm(this.close.bind(this), this.getStudents());
//
//
//         this.form.closeButton.onclick = () => this.close();
//
//         this.settingsButton.onclick = () => this.open();
//         this.form.form.onclick = (event) => {
//             if (event.target.className === "lesson-edit-form-wrapper") {
//                 this.close();
//             }
//         }
//         this.render();
//     }
//
//     parseTime() {
//         const [start, end] = this.time.state.content.split(" - ");
//         const [startH, startM] = start.split(":");
//         const [endH, endM] = end.split(":");
//         return {
//             startHours: startH,
//             startMinutes: startM,
//             endHours: endH,
//             endMinutes: endM
//         };
//     }
//
//     initForm() {
//         this.form.lessonId.set(this.id);
//         this.form.selectTitle.select(this.course.element.getAttribute("data"));
//         this.form.selectCabinet.select(this.cabinet.element.getAttribute("data"));
//         this.form.selectTeacher.select(this.teacher.element.getAttribute("data"));
//         const time = this.parseTime();
//         this.form.startTimeHours.set(time.startHours);
//         this.form.startTimeMinutes.set(time.startMinutes);
//         this.form.endTimeHours.set(time.endHours);
//         this.form.endTimeMinutes.set(time.endMinutes);
//         this.form.studentList.render();
//     }
//
//     dropForm() {
//         this.form.selectTitle.deselect();
//         this.form.selectCabinet.deselect();
//         this.form.selectTeacher.deselect();
//         this.form.studentList.clear();
//     }
//
//     setCourse(course) {
//         this.course.setTitle(course);
//     }
//
//     setCabinet(course) {
//         this.cabinet.setTitle(course);
//     }
//
//     setTeacher(course) {
//         this.teacher.setTitle(course);
//     }
//
//     setTime(time) {
//         this.time.setTitle(time);
//     }
//
//     close() {
//         this.dropForm();
//         this.setState({isOpen: false});
//     }
//
//     open() {
//         this.initForm();
//         this.setState({isOpen: true});
//     }
//
//     getStudents() {
//         let students = [];
//         const studElements = [...this.element.querySelectorAll('.lesson__content_child')];
//         studElements.map(element => {
//             students.push({id: element.getAttribute("data"), name: element.innerText});
//         })
//         return students;
//     }
//
//     render() {
//         if (this.state.isOpen) {
//             this.form.form.style.display = "block";
//         } else {
//             this.form.form.style.display = "none";
//         }
//     }
// }
//