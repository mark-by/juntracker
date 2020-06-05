import Component from "./Component.js";
class Menu {
    constructor(button, element) {
        this.element = element;
        this.hiddenPart = element.firstChild;
        this.button = button;
        this.state = {
            isOpen: false,
            event: null,
        }

        this.button.onclick = (event) => this.setState({isOpen: !this.state.isOpen, event: event})
        this.element.onclick = (event) => this.setState({isOpen: !this.state.isOpen, event: event})
        this.render();
    }

    setState(state) {
        this.state = {...this.state, ...state}
        this.render()
    }

    render() {
        console.log("header")
        if (this.state.event && (this.state.event.target === this.hiddenPart || this.state.event.target.className === "menu__option")) {
            return;
        }

        if (this.state.isOpen) {
            this.element.style.display = "block";
        } else {
            this.element.style.display = "none";
        }
    }
}

// document.querySelector('.header-menu').onclick = (event) => menu.setState({isOpen: !menu.state.isOpen, event: event})

let buttons = [...document.querySelectorAll('.menu')];
let elements = [...document.querySelectorAll('.hidden-menu')];
elements.map((element, idx) => {
    return new Menu(buttons[idx], element);
});

