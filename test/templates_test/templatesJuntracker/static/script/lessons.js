import Component from "./Component.js";

class Title extends Component {
    constructor(element) {
        super({
            content: element.innerText
        });
        this.element = element;
        this.render()
    }

    setTitle(title) {
        this.setState({content: title});
    }

    render() {
        this.element.innerText = this.state.content;
    }
}

class Option extends Component {
    constructor(element) {
        super({value: element.getAttribute("value"), content: element.innerText});
        this.element = element;
    }

    render() {
        this.element.setAttribute("value", this.state.value);
        this.element.innerText = this.state.content;
    }
}

class Input extends Component {
    constructor(element) {
        super({value: element.getAttribute("value")});
        this.element = element;
    }

    set(value) {
        this.setState({value: value});
    }

    render() {
        this.element.setAttribute("value", this.state.value);
    }
}

class Select extends Component {
    constructor(element) {
        super({selected: "-1"});
        this.element = element;
    }

    select(value) {
        let idx;
        [...this.element.options].map((option, index) => {
            if (option.value === value) {
                idx = index;
            }
        })
        this.setState({selected: idx.toString()});
    }

    deselect() {
        this.setState({selected: "-1"});
    }

    render() {
        this.element.selectedIndex = this.state.selected;
    }
}

class Student {
    constructor(name, id) {
        this.name = name;
        this.id = id;
    }

    str() {
        return `<div class='lesson__content_child' hidden><div class='name'>${this.name}</div>
                <div class='delete-student-button'><input type='hidden' name='student' value='${this.id}'/>
                <img src='static/images/close.svg' alt='удалить'/></div></div>`
    }
}

class StudentList extends Component {
    constructor(element, students) {
        super({students: students});
        this.element = element;
    }

    clear() {
        this.element.innerHTML = "";
    }

    addStudent(student) {
        const _student = new Student(student.name, student.id);
        this.element.innerHTML += _student.str();
    }

    render() {
        this.element.innerHTML = "";
        this.state.students.map(student => {
            const _student = new Student(student.name, student.id);
            this.element.innerHTML += _student.str();
        });
        [...this.element.children].map(element => {
            element.querySelector('.delete-student-button').onclick = () => {
                element.remove();
            }
        })
    }
}

class CreateStudentForm extends Component {
    constructor() {
        super();
    }
}

class LessonEditForm {
    constructor(closeHandler, students) {
        console.log(students);
        this.form = document.querySelector('.lesson-edit-form-wrapper');
        this.selectTitle = new Select(document.querySelector('#lesson-edit-title'));
        this.selectCabinet = new Select(document.querySelector('#lesson-edit-cabinet'));
        this.selectTeacher = new Select(document.querySelector('#lesson-edit-teacher'));
        this.startTimeHours = new Input(document.querySelector("#start-hours-edit"));
        this.startTimeMinutes = new Input(document.querySelector("#start-minutes-edit"));
        this.lessonId = new Input(this.form.querySelector("#lesson-id"));
        this.endTimeHours = new Input(document.querySelector("#end-hours-edit"));
        this.endTimeMinutes = new Input(document.querySelector("#end-minutes-edit"));
        this.studentList = new StudentList(document.querySelector(".students"), students);
        this.closeButton = this.form.querySelector('.close-form-button');
        this.createStudent = this.form.querySelector('.add-student-button__new');
        this.searchStudent = this.form.querySelector('.add-student-button__search');

        this.form.onsubmit = (event) => this.save(event);
        this.close = () => closeHandler();
    }

    save(event) {
        event.preventDefault();
        fetch('/api/update_lesson', {
            method: 'POST',
            headers: {
                'content-type' : 'application/x-www-form-urlencoded',
            },
            body: new URLSearchParams(new FormData(this.form.querySelector('form'))).toString()
        }).then(response => {
            if (response.ok) {
                this.close();
            } else {
                this.close()
            }
            window.location.reload();
        })
    }

}

class ScheduleLesson extends Component {
    constructor(element) {
        super({
            isOpen: false
        });
        this.element = element;
        this.course = new Title(element.querySelector('.lesson__header_course'))
        this.cabinet = new Title(element.querySelector('.lesson__header_cab'))
        this.teacher = new Title(element.querySelector('.lesson__header_tutor'))
        this.time = new Title(element.querySelector('.lesson__footer').firstChild)
        this.settingsButton = element.querySelector('.button-settings-lesson');

        this.id = this.element.getAttribute("data");
        this.form = new LessonEditForm(this.close.bind(this), this.getStudents());


        this.form.closeButton.onclick = () => this.close();

        this.settingsButton.onclick = () => this.open();
        this.form.form.onclick = (event) => {
            if (event.target.className === "lesson-edit-form-wrapper") {
                this.close();
            }
        }
        this.render();
    }

    parseTime() {
        const [start, end] = this.time.state.content.split(" - ");
        const [startH, startM] = start.split(":");
        const [endH, endM] = end.split(":");
        return {
            startHours: startH,
            startMinutes: startM,
            endHours: endH,
            endMinutes: endM
        };
    }

    initForm() {
        this.form.lessonId.set(this.id);
        this.form.selectTitle.select(this.course.element.getAttribute("data"));
        this.form.selectCabinet.select(this.cabinet.element.getAttribute("data"));
        this.form.selectTeacher.select(this.teacher.element.getAttribute("data"));
        const time = this.parseTime();
        this.form.startTimeHours.set(time.startHours);
        this.form.startTimeMinutes.set(time.startMinutes);
        this.form.endTimeHours.set(time.endHours);
        this.form.endTimeMinutes.set(time.endMinutes);
        this.form.studentList.render();
    }

    dropForm() {
        this.form.selectTitle.deselect();
        this.form.selectCabinet.deselect();
        this.form.selectTeacher.deselect();
        this.form.studentList.clear();
    }

    setCourse(course) {
        this.course.setTitle(course);
    }

    setCabinet(course) {
        this.cabinet.setTitle(course);
    }

    setTeacher(course) {
        this.teacher.setTitle(course);
    }

    setTime(time) {
        this.time.setTitle(time);
    }

    close() {
        this.dropForm();
        this.setState({isOpen: false});
    }

    open() {
        this.initForm();
        this.setState({isOpen: true});
    }

    getStudents() {
        let students = [];
        const studElements = [...this.element.querySelectorAll('.lesson__content_child')];
        studElements.map(element => {
            students.push({id: element.getAttribute("data"), name: element.innerText});
        })
        return students;
    }

    render() {
        if (this.state.isOpen) {
            this.form.form.style.display = "block";
        } else {
            this.form.form.style.display = "none";
        }
    }
}

let lessons = [...document.querySelectorAll(".schedule .card-wrapper")];
lessons.map(lesson => {
    return new ScheduleLesson(lesson);
});