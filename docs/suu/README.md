# Suu
Suu is a compiled programming language, aimed at capturing fucntionality of modern languages in Kyrgyz.

## Alphabet
The keywords of the language can contain 36 lowercase letters of Kyrgyz alphabet only, which are the following:
```
а б в г д е ё ж з и й к л м н ң о ө п р с т у ү ф х ц ч ш щ ъ ы ь э ю я   
```

## Syntax
There is a list of reserved words, or keywords of the language, the members of which cannot be used as ordinary identifiers:
```
буул, чын, калп, эгер, же эгер, болбосо, сан, таксан, чейин,
тамсаб, ар бир, ичиндеги, кайтар, жана, же, класс.
```

## Examples
1. Code:
```
сан а = 3
сан б = 1

б < a чейин:
  чыгар("{б}")
  б = б + 1
```
Output:
```
1
2
3
```
2. Code:
```
тамсаб[] палоо = ["эт", "күрүч", "сабиз", "пияз"]
caн и = 1

ар бир палоо ичиндеги п:
    чыгар("азык#{и}: {п}")
    и = и + 1
```
Output:
```
азык#1: эт
азык#2: күрүч
азык#3: сабиз
азык#4: пияз
```
3. Code:
```
сан кош(сан а, сан б):
    сан в = а + б
    кайтар в

чыгар(кош(20, 20))
```
Output:
```
40
```

