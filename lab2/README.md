# Лабораторна робота № 2 ІО-46 Попович Мілана
## Тема: Розроблення Makefile та CMake 

---
## Завдання
Створіть `Makefile` (не забудьте про секцію `clean`) та `CMakeLists.txt`,
щоб створити свій проект. Результатом має бути: одна бібліотека (static
або shared) та виконуваний файл.
Створіть із файлу `CMakeLists.txt` сценарій збірки для системи збирання
`Ninja`.

---
## Виконання завдання

Історія термінала:
```sh
    1  cd Downloads
    2  git clone https://github.com/SergiiPiatakov/calculator.git
    3  cd calculator
    4  touch main.cpp
    5  vim main.cpp
    6  mkdir src
    7  mv calculator.h calculator.cpp main.cpp src
    8  cd src
    9  ls
   10  cd ..
   11  touch Makefile
   12  vim Makefile
   13  make
   14  ./calc
   15  make clean
   16  touch CMakeLists.txt
   17  vim CMakeLists.txt
   18  mkdir build_ninja
   19  cd build_ninja
   20  cmake -G Ninja ..
   21  ninja
   22  cd ~ 
   23  date
   24  history > history.txt
```

Код файлу main.cpp
<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/61f62fb37f938e34947e52e3c7daf43d23eaecd3/lab2/img/Screenshot%20From%202026-10-05%2018-59-06.png" width="800">

Код файлу Makefile
<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/61f62fb37f938e34947e52e3c7daf43d23eaecd3/lab2/img/Screenshot%20From%202026-10-05%2018-59-37.png" width="800">

Код файлу CMakeLists.txt
<img src="https://github.com/MilanaPopovych/AK-2_Labwork/blob/61f62fb37f938e34947e52e3c7daf43d23eaecd3/lab2/img/Screenshot%20From%202026-10-05%2018-59-51.png" width="800">

---

## Висновки
Під час виконання лабораторної роботи було 
