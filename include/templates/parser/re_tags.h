#ifndef _RE_TAGS_H
#define _RE_TAGS_H

#include <regex>

#define BLOCK_TAG_START "\\{(\\%)"
#define BLOCK_TAG_END "\\%\\}"
#define VAR_TAG_START "\\{(\\{)"
#define VAR_TAG_END "\\}\\}"
#define COMMENT_TAG_START "\\{(#)"
#define COMMENT_TAG_END "#\\}"

namespace parser {
    enum TagType {
        block_t, endblock_t, endfor_t, endif_t, for_t, if_t, else_t, include_t,
        extends_t, variable_t, comment_t, undefined_t
    };

    namespace tag {
        inline std::regex any(BLOCK_TAG_START R"(\s*(\w+)\s*([\w.]*)\s*([\w.]*)\s*([\w.]*)\s*)" BLOCK_TAG_END "|"
                              VAR_TAG_START R"((\s*)([\w.]+)(\s*))" VAR_TAG_END "|"
                              COMMENT_TAG_START ".*?" COMMENT_TAG_END);
        /*regex any:
         * () - group; Группу можно взять по ее порядковому номеру: $1 - группа номер 1. Нумерация с 1.
         *{% for i in array %} - $1 = %; $2 = for; $3 = i; $4 = in; $5 = array;
         * {% endfor %} - $1 = %; $2 = endfor;
         * {{   var }} - $6 = {; $7 = '   '; $8 = var; $9 = ' ';
         * {# comment #} - $10 = #;
         */
        inline std::regex variable(VAR_TAG_START ".*?" VAR_TAG_END);

        inline std::regex comment(COMMENT_TAG_START ".*?" COMMENT_TAG_END);

        inline std::regex anyBlock(BLOCK_TAG_START R"(\s*(\w+)\s*([\w.]*)\s*([\w.]*)\s*([\w.]*)\s*)" BLOCK_TAG_END);

        inline std::regex startBlock(BLOCK_TAG_START R"(\s*(block)\s*([\w.]+)\s*)" BLOCK_TAG_END);

        inline std::regex includeTag(BLOCK_TAG_START R"(\s*include\s+([\w.]+)\s*)" BLOCK_TAG_END); // $2 - file

        inline std::regex endBlock(BLOCK_TAG_START R"(\s*endblock\s*?)" BLOCK_TAG_END);

        inline std::regex startFor(BLOCK_TAG_START R"(\s*for\s+(\w+)\s+in\s+([\w.]+)\s*?)" BLOCK_TAG_END); // $1 - % $2 - name $3 - iterVar

        inline std::regex startForOrEndFor(BLOCK_TAG_START R"(\s*for\s+(\w+)\s+in\s+([\w.]+)\s*?)" BLOCK_TAG_END "|"
                                           BLOCK_TAG_START R"(\s*endfor\s*?)" BLOCK_TAG_END); // $1 - % $2 - name $3 - iterVar $4 - %

        inline std::regex endFor(BLOCK_TAG_START R"(\s*endfor\s*?)" BLOCK_TAG_END);

        inline std::regex beforeHtmlTagSpaces(R"(\s+(?=<.*?>)|\s+(?=</.*?>))");

        inline std::regex afterHtmlTagSpaces(R"((<.*?>|</.*?>)(\s+))"); // $1 - htmlTag $2 - spaces

        inline std::regex extends(BLOCK_TAG_START R"(\s*extends\s+([\w./]+)\s*?)" BLOCK_TAG_END); /// $1 - filename
    }
}

#endif //_RE_TAGS_H
