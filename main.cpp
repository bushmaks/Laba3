/*********************************************************************
 Progect name: Laba3                                                  *
 Project type: Win32 Console Application                              *
 File name: main.cpp                                                  *
 Language: CPP, XCode 9, MSVS 2017 and above                          *
 Programmers: Bushmanov Maksim Sergeevich, Zaycev Evgeniy Pavlovich   *
 Created: 3/11/2017                                                   *
 Last revision: 9/11/2017                                             *
 *********************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

const char *FName = "Mass.txt"; // Название исходного файла

long long int GetSizeOfFile(const char* path){ // Функция для вычисления размера файла.
    ifstream in(path, ifstream::ate | ifstream::binary); // Открываем заданный файл и переставляем курсор в конец.
    return in.tellg(); // Выдает позицию курсора в файле в битах.
}


int GetNumber(const char* symbols, int length){ // Атрибуты: массив, длина массива и разрядность числа. Функция для определения номера: 1 разрядный, 2 разрядный и т.д.
    int res = 0; // Результат выполнения
    for (int i = 1; i <= length; i++){ // Цикл для вычисления разрядности. Например: Число - 150. Вычисление: 100 + 50 + 0.
        res += (symbols[i-1]-'0') * pow(10, length - i); // i = 1 потому что разрядность начинается с 1. "-'0'" - нужен для конвертации из char в int. (int) не работает.
    }
    return res;
}

int main(){
    long long int fileSize = GetSizeOfFile(FName); // Размер файла в байт
    char fileContent[fileSize]; // Массив для файла
       
       ifstream fin(FName, ifstream::binary); // Открываем файл в fin, в бинарном виде
       
        if (!fin.is_open()) { // Проверка на чтение файла
            cout << "Ошибка чтения файла." << endl;
        }
        else { // Если файл открыт
            for  (int i = 0; !fin.eof(); i++) { // Цикл для занесения файла в массив. До конца файла
                fileContent[i] = fin.get();
            }
            int count = 0; // Сетчик для перемещения в массиве fileContent
            int foundedArraySize; // Найденый размер массива
            do { // Ищем размер массива. Если не число, то ищем дальше поэлементно
                foundedArraySize = (int)fileContent[count];
                count++;
            }
            while (!((int)foundedArraySize > 47 && (int)foundedArraySize < 58));
            
            
            int Array[foundedArraySize]; // Рабочий массив
            for (int i = 0, j = count; j < fileSize;i++,j++){ // Цикл поиска чисел массива. j - номер элемента в массиве  count - место после размерности массива.
                if (fileContent[j] != ' ' && ((int)fileContent[j] > 47 && (int)fileContent[j] < 58)) { // Если не пробел и не число то
                    char numberSymbolsArray[10]; // Массив для вычисления числа более одного разряда
                    int countSymbol = 0; // Счетчик разрядности и индекса массива
                    while ((int)fileContent[j] > 47 && (int)fileContent[j] < 58) { // Пока числа выполняется цикл
                        numberSymbolsArray[countSymbol] = fileContent[j]; // Присваиваем элемент из файла в массив разрядности
                        countSymbol++;
                        j++; // Следущий элемент в файле
                    }
                    Array[i] = GetNumber(numberSymbolsArray, countSymbol); // Присваивание рабочему массиву число из массива разрядности
                    cout << Array[i] << " "; // Вывод массива из файла
                }
            }
            cout << endl;
        }
    return 0;
}
