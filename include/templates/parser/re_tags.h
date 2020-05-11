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
    enum TagType {block_t, endblock_t, endfor_t, endif_t, for_t, if_t, else_t, include_t,
            extends_t, variable_t, comment_t, undefined_t};

    namespace tag {
        inline std::regex any("(" BLOCK_TAG_START ".*?" BLOCK_TAG_END "|"
                       VAR_TAG_START ".*?" VAR_TAG_END "|"
                       COMMENT_TAG_START ".*?" COMMENT_TAG_END ")");

        inline std::regex variable("(" VAR_TAG_START ".*?" VAR_TAG_END ")");

        inline std::regex comment("(" COMMENT_TAG_START ".*?" COMMENT_TAG_END ")");

        inline std::regex anyBlock("(" BLOCK_TAG_START ".*?" BLOCK_TAG_END ")");

        inline std::regex startBlock("(" BLOCK_TAG_START "\\s*block\\s+\\w+\\s*?" BLOCK_TAG_END ")");

        inline std::regex endBlock("(" BLOCK_TAG_START "\\s*endblock\\s*?" BLOCK_TAG_END ")");

        inline std::regex startFor("(" BLOCK_TAG_START "\\s*for\\s+\\w+\\s+in\\s+[\\w.]+\\s*?" BLOCK_TAG_END ")");

        inline std::regex endFor("(" BLOCK_TAG_START "\\s*endfor\\s*?" BLOCK_TAG_END ")");

        inline std::regex BeforeVarSpaces(R"(\s*(?=\w))");

        inline std::regex AfterVarSpaces(R"(\s*(?=\}\}))");

        inline std::regex startIf("(" BLOCK_TAG_START "\\s*if\\s+[\\w.]+\\s*?" BLOCK_TAG_END ")");

        inline std::regex endIf("(" BLOCK_TAG_START "\\s*endif\\s*?" BLOCK_TAG_END ")");

        inline std::regex elseTag("(" BLOCK_TAG_START "\\s*else\\s*?" BLOCK_TAG_END ")");

        inline std::regex endIfOrElse("(" BLOCK_TAG_START "\\s*endif\\s*?" BLOCK_TAG_END "|"
                                      BLOCK_TAG_START "\\s*else\\s*?" BLOCK_TAG_END ")");

        inline std::regex extends("(" BLOCK_TAG_START "\\s*extends\\s+[\\w.]+\\s*?" BLOCK_TAG_END ")");

        inline std::regex nameWithDots("[\\w.]+");

        inline std::regex name("\\w+");
    }
}

#endif //_RE_TAGS_H
