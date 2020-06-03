export default class Message {
    constructor() {
        document.querySelector("message").outerHTML = `
        <div class="message">
            <div class="message-content">
            </div>
        </div>
        `
        this.element = document.querySelector(".message");
        this.message = document.querySelector(".message-content");
    }

    show(message, success) {
        this.message.innerText = message;
        this.element.style.display = "flex";
        this.element.style.transform = "translate(0, -10%)";
        if (success === "success") {
            this.element.classList.add("success");
        } else if (success === "fail") {
            this.element.classList.add("fail");
        }
        setTimeout(() => this.close(), 2000);
    }

    close() {
        this.element.style.transform = "";
        setTimeout(() => {
            this.element.style.display = "none";
            this.element.classList.remove("success");
            this.element.classList.remove("fail")
        }, 500);


    }

}