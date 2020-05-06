# SqlWrapper

Обёртка над библиотекой работы с базой данных.
=======
# HTMLTemplate

Для работы необходима библиотека boost (https://dl.bintray.com/boostorg/release/1.72.0/source/). Она должна лежать в дирректории include/boost. То есть в include/boost/boost все хедеры.

## Context example (out)
```json
{
    "name": "Mark Bykhovets",
    "obj": {
        "value1": "1",
        "value2": "2"
    },
    "array": [
        "1",
        "5",
        "3",
        "4",
        "6"
    ],
    "vector_array": [
        "65",
        "4",
        "3",
        "45",
        "6",
        "65"
    ],
    "person": [
        {
            "name": "Josh",
            "second_name": "Brown",
            "age": "20"
        },
        {
            "name": "Homer",
            "second_name": "Simpson",
            "age": "31"
        },
        {
            "name": "Ragnar",
            "second_name": "Lodbrok",
            "age": "25"
        }
    ]
}
OUT
2
1 5 3 4 6 
{
    "name": "Josh",
    "second_name": "Brown",
    "age": "20"
}
{
    "name": "Homer",
    "second_name": "Simpson",
    "age": "31"
}
{
    "name": "Ragnar",
    "second_name": "Lodbrok",
    "age": "25"
}
```