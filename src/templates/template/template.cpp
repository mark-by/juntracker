#include <template/template.h>

void templates::Template::render(templates::Context &context) {
    makeQueue();
    nodeQueue.render();
    _result = nodeQueue.result();
}

void templates::Template::_render(templates::Context &context) {

}


std::tuple<std::string::const_iterator, std::unique_ptr<templates::Node>> templates::Template::parse(std::string::const_iterator start, int type) {
    std::string::const_iterator endBlock;
    switch(type) {
        case parser::for_t:
            endBlock = forParser.set(start, buffer.end());
            return std::make_tuple(endBlock, forParser.parse());
        case parser::if_t:
            endBlock = ifParser.set(start, buffer.end());
            return std::make_tuple(endBlock, ifParser.parse());
        case parser::variable_t:
            endBlock = varParser.set(start, buffer.end());
            return std::make_tuple(endBlock, varParser.parse());
        default:
            return std::make_tuple(start, nullptr);
    }
}

void templates::Template::makeQueue() {
    std::sregex_iterator currMatch(buffer.begin(), buffer.end(), parser::tag::any);
    std::sregex_iterator end;
    std::string::const_iterator textStart = buffer.cbegin();
    std::string::const_iterator textEnd;
    while (currMatch != end) {
        if (currMatch->suffix().first <= textStart) {
            currMatch++;
            continue;
        }
        auto [endBlock, node] = parse(currMatch->prefix().second, parser::tagType(currMatch->str()));
        textParser.set(textStart, currMatch->prefix().second);
        nodeQueue.push(textParser.parse());
        nodeQueue.push(std::move(node));

        textStart = endBlock;
    }
    textParser.set(textStart, buffer.end());
    nodeQueue.push(textParser.parse());
}

templates::Template::Template(const std::string &filename) {
    loader.load(filename);
    buffer = loader.result();
}

std::string templates::Template::result() {
    return _result;
}

