import Component from "./Component.js";

class Menu extends Component {
    render() {
        if (this.state.event && (this.state.event.target.className === "header-menu-hidden-part" || this.state.event.target.className === "menu__option")) {
            return;
        }

        if (this.state.isOpen) {
            this.state.element.style.display = "block";
        } else {
            this.state.element.style.display = "none";
        }
    }
}


const menu = new Menu({
    element: document.querySelector('.header-menu-hidden-part-wrapper'),
    isOpen: false,
    event: null,
})
document.querySelector('.header-menu').onclick = (event) => menu.setState({isOpen: !menu.state.isOpen, event: event})
menu.state.element.onclick = (event) => menu.setState({isOpen: !menu.state.isOpen, event: event})

menu.render()
