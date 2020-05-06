#include <parser/re_tags.h>

namespace parser {
    std::string getName(const std::string &text) {
        std::sregex_iterator currentMatch(text.begin(), text.end(), tag::nameWithDots);
        currentMatch++;
        return currentMatch->str();
    }

    int tagType(const std::string &tag) {
        switch (tag[1]) {
            case '{':
                return variable_t;
            case '#':
                return comment_t;
            case '%':
                return BlockType(tag);
            default:
                return undefined_t;
        }
    }

    int BlockType(const std::string &text) {
        std::smatch match;
        std::regex_search(text, match, tag::name);
        std::string matchStr = match.str();
        if (matchStr == "block") {
            return block_t;
        } else if (matchStr == "if") {
            return if_t;
        } else if (matchStr == "for") {
            return for_t;
        } else if (matchStr == "include") {
            return include_t;
        } else if (matchStr == "extends") {
            return extends_t;
        } else if (matchStr == "endfor") {
            return endfor_t;
        } else if (matchStr == "endif") {
            return endif_t;
        } else if (matchStr == "endblock") {
            return endblock_t;
        } else {
            return undefined_t;
        }
    }


}

