import Component from "./Component.js";

class HeaderWindow extends Component {
    constructor(istate) {
        super(istate);
        const today = new Date().toJSON().slice(0, 10);
        const state = {
            date: today.slice(8, 10) + '.' + today.slice(5, 7) + '.' + today.slice(2, 4),
            day: this.getDay(),
            time: this.currentTime(),
            dayElement: document.querySelector('#current-week-day'),
            timeElement: document.querySelector('#current-time'),
            dateElement: document.querySelector('#current-date'),
        }
        this.state = {...state, ...istate};
    }

    currentTime() {
        const now = new Date();
        const hours = now.getHours();
        const minutes = now.getMinutes();
        return hours + ':' + (minutes < 10 ? "0" + minutes : minutes);
    }

    updateTime() {
        this.setState({time: this.currentTime()});
    }

    getDay() {
        const day = new Date().getDay();
        switch (day) {
            case 0:
                return 'Воскресенье';
            case 1:
                return 'Понедельник';
            case 2:
                return 'Вторник';
            case 3:
                return 'Среда';
            case 4:
                return 'Четверг';
            case 5:
                return 'Пятница';
            case 6:
                return 'Суббота';
        }
    }

    render() {
        this.state.dayElement.innerText = this.state.day;
        this.state.timeElement.innerText = this.state.time;
        this.state.dateElement.innerText = this.state.date;
    }
}

class Lesson extends Component {
   constructor(element) {
       super();
       this.state = {
           element: element,
           startTime: null,
       }
       this.children = [...element.querySelectorAll('.lesson__content_child')]
       this.initCheckBoxesForChildren();
   }

   initCheckBoxesForChildren() {
      this.children.map(element => {
          this.initCheckBoxesForChild(element);
      })
   }

   initCheckBoxesForChild(child) {
       let input = child.querySelector('input')
       let child_id = child.querySelector('.name').getAttribute('data');
       input.getAttribute('checked') ?
           input.setAttribute('value','1_' + child_id) :
           input.setAttribute('value','0_' + child_id);
       input.onclick = (event) => {
           if (input.getAttribute('checked')) {
               input.removeAttribute('checked');
               input.setAttribute('value','0_' + child_id)
           } else {
               input.setAttribute('checked', '1')
               input.setAttribute('value', '1_' + child_id)
           }
       }
   }

    nowToInt() {
        const date = new Date();
        return date.getHours()*100 + date.getMinutes()
    }

    isCurrent() {
        let now = this.nowToInt();
        let startTime = this.getStartTime();
        return (startTime[0] * 100 + startTime[1]) <= now;
    }


    isEnded() {
        let now = this.nowToInt();
        let endTime = this.getEndTime()
        return now >= endTime[0]*100 + endTime[1];
    }


    //[12, 30] - array of integers
    getStartTime() {
        return this.state.element.querySelector('.start-time').innerText.split(':').map((element) => {
            return parseInt(element);
        })
    }

    //[12, 30] - array of integers
    getEndTime() {
        return this.state.element.querySelector('.end-time').innerText.split(':').map((element) => {
            return parseInt(element);
        })
    }

    render() {
       this.state.startTime = this.getStartTime()
    }

}

class CurrentLesson extends Lesson {
    constructor(element) {
        super(element);
        this.state = {
            element : element,
            progressBar: element.querySelector('.progress-bar>span'),
            startTime: null,
            endTime: null,
        }
    }

    getProgress() {
        if (!this.state.startTime || !this.state.endTime) {
            this.state.startTime = this.getStartTime();
            this.state.endTime = this.getEndTime();
        }
        const startTime = this.state.startTime;
        const endTime = this.state.endTime;
        const diff = (endTime[0] - startTime[0]) * 60 + (endTime[1] - startTime[1]);
        const now = new Date();
        return ((now.getHours() * 60 + now.getMinutes() - startTime[0] * 60 - startTime[1]) / diff) * 100;
    }

    save() {
        console.log("saved");
    }

    render() {
        this.state.progressBar.style.width = this.getProgress() + "%";
    }
}

class List extends Component {
    constructor(list, LessonClass) {
        super();
        this.LessonClass = LessonClass;
        this.state = {
            list : list,
            objects : [...list.children].map(element => {return new LessonClass(element)})
        }
    }

    render() {
        for (let i = 0; i < this.state.objects.length; i++) {
            this.state.objects[i].render()
        }
    }
}

class CurrentList extends List {
    add(element) {
        let submitButton = "<span title=\"Сохранить\"><input type=\"submit\" value=\"\" class=\"save-button\"></span>\n"
        let currentLessonClassName = "current-lesson"

        element.querySelector('form').innerHTML += submitButton;
        element.classList.add(currentLessonClassName);
        this.state.list.innerHTML += element.outerHTML;
        this.updateObj()
    }

    updateObj() {
        delete this.state.objects;
        this.state.objects = [...this.state.list.children].map(element => {
            return new this.LessonClass(element);
        });
    }

    update() {
        for (let i = 0; i < this.state.objects.length; i++) {
            if (this.state.objects[i].isEnded()) {
                this.state.objects[i].save();
                this.state.objects[i].state.element.remove();
                let removed = this.state.objects.splice(i,1);
                delete removed[0];
            }
        }
    }
}

class NextList extends List {
    constructor(list, currentList, Lesson) {
        super(list, Lesson);
        this.currentList = currentList;
    }

    update() {
        for (let i = 0; i < this.state.objects.length; i++) {
            if (this.state.objects[i].isCurrent()) {
                this.currentList.add(this.state.objects[i].state.element);
                this.state.objects[i].state.element.remove();
                let removed = this.state.objects.splice(i,1);
                delete removed[0];
            }
        }
    }
}

const header = new HeaderWindow();

const currentList = new CurrentList(document.querySelector('#current-wrapper'), CurrentLesson)
const nextList = new NextList(document.querySelector('#next-wrapper'), currentList, Lesson)

header.render();
header.updateTime();

nextList.update();
currentList.update();
currentList.render();

setInterval(() => {
    header.updateTime();
    currentList.render();
    currentList.update();
    nextList.update();
}, 1000);

// setInterval(() => {
// }, 10000)
