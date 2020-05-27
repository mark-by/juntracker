class Component {
    constructor(state) {
        this.state = state
    }

    render() {

    }

    setState(state) {
        this.state = {...this.state, ...state}
        this.render()
    }
}

export default Component;