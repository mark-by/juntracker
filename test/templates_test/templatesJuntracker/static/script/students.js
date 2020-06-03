import Component from "./Component.js";
import Root from "./root.js";

class SearchList extends Component {
    constructor(initList) {
        super();
        this.state = {
            students: initList,
            isInit: true
        }
        this.initList = initList;
    }

    render() {
        if (this.state.isInit) {
            return this.initList;
        }
        if (!this.state.students) { return `<div class="student-search-wrapper"> Ничего нет :( </div>` }

            return `${
            this.state.students.map(student => {
                return `
                <div class="student-search-wrapper">
                    <input type="checkbox" name="id" value="${student.id}">
                    <img src="${student.avatar ? student.avatar : 'static/images/avatar.svg'}"/>
                    <div class="student-name">${student.name}</div>
                    <div class="student-age">${student.age} лет</div>
                    <div class="student-groups">
                        ${student.courses ? student.courses.map(course => {
                    return `<div class="course"> ${course} </div>`
                }).join("") : ""}
                    </div>
                    <img class="student-delete-button" src="static/images/close.svg"/>
                </div>
                `
            }).join("")
        }`
    }
}

const initState = document.querySelector(".students-form").innerHTML
console.log(initState)
const root = new Root(document.querySelector(".students-form"), new SearchList(initState));
document.querySelector("#search-input").oninput = (event) => {
    if (event.target.value.length === 0) {
        root.app.setState({isInit: true})
        return;
    }
    fetch('/api/verbose_search_student?search=' + event.target.value).then(response => {
        if (response.ok) {
            response.json().then(json => {
                root.app.setState({students: json.students, isInit: false});
            })
        } else {
            root.app.setState({isInit: ture});
            // root.app.setState({
            //     students: [
            //         {id: 1, avatar: null, name: "Вася Петров", age: 20, courses: ["Python", "Robot"]},
            //         {id: 1, avatar: null, name: "Вася Петров", age: 20, courses: ["Python", "Robot"]},
            //         {id: 1, avatar: null, name: "Вася Петров", age: 20, courses: ["Python", "Robot"]},
            //         {id: 1, avatar: null, name: "Вася Петров", age: 20, courses: ["Python", "Robot"]},
            //     ],
            //     isInit: false
            // });
        }
    })
}