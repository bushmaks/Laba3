/*********************************************************************
 Project name: Laba3                                                  *
 Project type: Win32 Console Application                              *
 File name: main.cpp                                                  *
 Language: CPP, XCode 9, MSVS 2017 and above                          *
 Programmers: Bushmanov Maksim Sergeevich, Zaycev Evgeniy Pavlovich   *
 Created: 3/11/2017                                                   *
 Last revision: 23/11/2017                                            *
 *********************************************************************/
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const char *FName = "Array.txt"; // Название исходного файла

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
    long long int fileSize = GetSizeOfFile(FName); // Размер файла в байтах
    char fileContent[fileSize]; // Массив для файла
    
       ifstream fin(FName, ifstream::binary); // Открываем файл в fin, в бинарном виде
       
        if (!fin.is_open()) { // Проверка на чтение файла
            cout << "Ошибка чтения файла. Добавьте файл Array.txt в каталог программы." << endl;
        }
        else { // Если файл открыт
            
            for  (int i = 0; !fin.eof(); i++) { // Цикл для занесения файла в массив. До конца файла
                fileContent[i] = fin.get();
            }
            fin.close(); // Закрываем файл
            int count = 0; // Сетчик для перемещения в массиве fileContent
            int countSizeArray = 0; // Счетчик разрядности размерности
            char foundedSizeArray[10]; // Массив для нахождения размерности рабочего массива
            int foundedSize; // Найденый размер рабочего массива
            while (!(fileContent[count] >= '0' && fileContent[count] <= '9')) count++; // Пока не число
            while (fileContent[count] >= '0' && fileContent[count] <= '9') { // Пока числа выполняется цикл
                    foundedSizeArray[countSizeArray] = fileContent[count]; // Присваиваем элемент из файла в массив разрядности размерности
                    countSizeArray++; // Разрядность размерности рабочего массива
                    count++; // Следущий элемент в файле
            }
            foundedSize = GetNumber(foundedSizeArray, countSizeArray); // Вычисляем размерность рабочего массива
            int Array[foundedSize]; // Рабочий массив
            int i = 0;
            for (; count < fileSize; count++){ // Цикл поиска чисел массива. count - номер элемента в массиве fileContent.
                
                if (fileContent[count] != ' ' && ((fileContent[count] >= '0' && fileContent[count] <= '9') || fileContent[count] == '-')) { // Если не пробел и число то
                    int znak = 1; // Знак элемента в массиве
                    
                    while ((fileContent[count+1] == '-' || (fileContent[count+1] >= '0' && fileContent[count+1] <= '9')) && fileContent[count] == '-') { // Если минус, смена знака
                        znak *= -1; // Смена знака элемента массива
                        count++;
                    }
                    
                    char numberSymbolsArray[10]; // Массив для вычисления числа более одного разряда
                    int countSymbol = 0; // Счетчик разрядности и индекса массива

                    while (fileContent[count] >= '0' && fileContent[count] <= '9') { // Пока числа выполняется цикл
                        numberSymbolsArray[countSymbol] = fileContent[count]; // Присваиваем элемент из файла в массив разрядности
                        countSymbol++;
                        count++; // Следущий элемент в файле
                    }
                    
                    if (fileContent[count-1] >= '0' && fileContent[count-1] <= '9' && fileContent[count] == '-') { // Проверка на случай число-
                        cout << "В вашем массиве есть неверный элемент типа x-y, где x и y целые числа.\nВведите правильный элемент: ";
                        cin >> Array[i];
                        i++;
                        while (fileContent[count] == '-') {
                            count++;
                        }
                    }
                    else if ((fileContent[count+1] != '-' && fileContent[count] != '-') || (fileContent[count-1] != '-' && fileContent[count] != '-')) { // Только если не будет минуса без числа
                        Array[i] = GetNumber(numberSymbolsArray, countSymbol); // Присваивание рабочему массиву число из массива разрядности
                        Array[i] *= znak; // Смена знака
                        i++;
                    }
                }
            }
            if (i < foundedSize) { // Если размерность больше, чем массив
                cout << "Размерность массива не совпадает с заданной размерностью(" << foundedSize << "). Добавьте элементы или измените размерность в файле Array.txt" << endl;
                return 1;
            }
            
            
            // Начало работы с рабочим массивом
            
            int result = 1; // Результат перемножения нечетных элементов в массиве
            int countNechet = 0;
            int znam = 0; // Знаменатель
            int iMin = 0; // Индекс минимального по модулю элемента в массиве
            int min = abs(Array[0]); // Минимальное значение по модулю в массиве
            double sum = 0;// Сумма элементов до минимального значения по модулю в массиве
            double sred_arifm;
            // Проверяем каждый элемент массива
            cout << "Заданный массив: ";
            for (int i=0; i < foundedSize; i++){
                cout << Array[i] << " "; // Вывод рабочего массива из файла
                // Находим нечетные элементы в массиве
                if ((Array[i]%2) != 0){
                    result *= Array[i];
                    countNechet++;
                }

                if (abs(Array[i]) < min){ // Находим минимальный по модулю элемент и его индекс
                    min = abs(Array[i]);
                    iMin = i;
                }
            }
            cout << endl;
            // Вычисление суммы элементов до минимального по модулю элемента
            for (int i=0; i <= iMin; i++){
                sum += Array[i];
                znam++;
            }
            if (countNechet > 1) {
                cout << "Перемноженные нечетные элементы в массиве: " << result << endl;
            }
            else {
                cout << "Перемножить нечетные элементы не удалось. (Либо их нет, либо элемент один.)" << endl;
                }
            if (iMin == 0) {
                cout << "Среднее арифметическое до минимального по модулю элемента невозможно вычислить." << endl;
            }
            else {
                sred_arifm = sum/znam; // Вычисляем среднее арифметическое до минимального по модулю элементов
                cout << "Минимальный по модулю элемент массива: " << min << endl;
                cout << "Среднее арифметическое до минимального по модулю элемента: " << sred_arifm << endl;
            }
        }
    return 0;
}
