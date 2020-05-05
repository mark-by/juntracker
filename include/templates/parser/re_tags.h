#ifndef _RE_TAGS_H
#define _RE_TAGS_H

#include <regex>

#define BLOCK_TAG_START "\\{\\%"
#define BLOCK_TAG_END "\\%\\}"
#define VAR_TAG_START "\\{\\{"
#define VAR_TAG_END "\\}\\}"
#define COMMENT_TAG_START "\\{#"
#define COMMENT_TAG_END "#\\}"

namespace parser {
    namespace tag {
        std::regex any("(" BLOCK_TAG_START ".*?" BLOCK_TAG_END "|"
                       VAR_TAG_START ".*?" VAR_TAG_END "|"
                       COMMENT_TAG_START ".*?" COMMENT_TAG_END ")");

        std::regex anyBlock("(" BLOCK_TAG_START ".*?" BLOCK_TAG_END ")");

        std::regex startBlock("(" BLOCK_TAG_START "\\s*block\\s+\\w+\\s*?" BLOCK_TAG_END ")");

        std::regex endBlock("(" BLOCK_TAG_START "\\s*endblock\\s*?" BLOCK_TAG_END ")");

        std::regex extends("(" BLOCK_TAG_START "\\s*extends\\s+\\w+\\s*?" BLOCK_TAG_END ")");

        std::regex nameWithDots("[\\w.]+");
        std::regex name("\\w+");
    }

    std::string getName(const std::string &text) {
        std::sregex_iterator currentMatch(text.begin(), text.end(), tag::nameWithDots);
        currentMatch++;
        return currentMatch->str();
    }

    std::string getBlockType(const std::string &text) {
        std::smatch match;
        std::regex_search(text, match, tag::name);
        return match.str();
    }

    template <class iterator>
    auto getEndOfBlock(const std::sregex_iterator &startBlock, const iterator &endText) {
        return std::sregex_iterator(startBlock->suffix().first, endText, tag::endBlock)->suffix().first;
    }
}

#endif //_RE_TAGS_H
