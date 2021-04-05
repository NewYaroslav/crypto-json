# crypto-json
C ++ library for JSON encryption with COMMENTS

## Описание

**Проект находится в разработке**

Данная библиотека позволяет хранить данные JSON с комментариями в зашифрованных файлах.
Библиотека написана на *C++11*.

## JSON с комментариями

Для очистики строковых данных, содержащих JSON данные с комментариями, используется функция *std::string strip_json_comments(const std::string &json_string)*.
Реализацию функции *strip_json_comments* можно найти в файле *include\crypto-json\strip-json-comments.hpp*.
Функция *strip_json_comments* переписана с JS на С++. За основу был взяд код проекта [strip-json-comments](https://github.com/sindresorhus/strip-json-comments).

Пример JSON с комментариями (взят от [сюда](https://github.com/spmbt/jsonComm))

```
//first line

	{"aaa": "qwerty",// 
	"bbb": 1234 //comment (not pure JSON syntax)
	,"ccc": true # alternative comment style
	,"dd\"d":/*multiline\\" comm\\ent*/ /*comm2\\*/null,
	"ee//e": "example of any symbols in key including inactive comments",
	"multiline1"/*: 1, //- example of multiline comments
	"multiline2": 2,
	"multiline3":= 1234,*/:[36.8,false/*,34*/,
		"/**/",[1,2,3,4,[//56789
		5,6,[[/*0*/7,{"x":/*xx*/"x"}],8]],{}]  ],
	"mayBeAnyStructure":{"a":1/**/,"b":2},
"lineEnd\\\\":"end"
}//after json

/*2nd after*/  
```