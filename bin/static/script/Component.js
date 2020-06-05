class Component {
    constructor(props) {
        this.state;
        this.props = props;
        this.root;
    }

    init(root) {
       this.root = root;
    }

    render() {}

    setState(state) {
        this.state = {...this.state, ...state}
        if (this.root) {
            this.root.render();
        }
        this.render()
    }
}

export default Component;