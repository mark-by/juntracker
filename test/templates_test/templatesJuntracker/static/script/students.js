import Component from "./Component.js";
import Root from "./root.js";

class SearchList extends Component {
    constructor(initList) {
        super();
        this.state = {
            students: initList,
        }
        this.initList = initList;
    }

    render() {
        return `${
            this.state.students.map(student => {
                return `
                
                `
            })
        }`
    }
}

const root = new Root(document.querySelector(".students-form"), new SearchList([...document.querySelector(".students-form").children]));