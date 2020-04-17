set(node_source
        node/node.cpp
        node/node_queue.cpp)

set(loader_source
        loader/loader.cpp)

set(parser_source
        parser/parser.cpp)

set(template_source
        template/template.cpp)

add_library(templates STATIC
        ${node_source}
        ${loader_source}
        ${parser_source}
        ${template_source})