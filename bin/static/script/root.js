export default class Root {
    constructor(element, app) {
        this.element = element;
        this.app = app;
        this.app.init(this);
    }

    render() {
        this.element.innerHTML = this.app.render();
    }
}