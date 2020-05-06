set(node_source
        node/node.cpp
        node/node_queue.cpp)

set(loader_source
        loader/loader.cpp)

set(parser_source
        parser/if_parser.cpp
        parser/block_parser.cpp
        parser/for_parser.cpp
        parser/text_parser.cpp
        parser/var_parser.cpp
        parser/parser.cpp)

set(template_source
        template/template.cpp)

add_library(templates STATIC
        ${node_source}
        ${loader_source}
        ${parser_source}
        ${template_source})