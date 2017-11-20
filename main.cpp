/*********************************************************************
 Project name: Laba3                                                  *
 Project type: Win32 Console Application                              *
 File name: main.cpp                                                  *
 Language: CPP, XCode 9, MSVS 2017 and above                          *
 Programmers: Bushmanov Maksim Sergeevich, Zaycev Evgeniy Pavlovich   *
 Created: 3/11/2017                                                   *
 Last revision: 19/11/2017                                            *
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
            
            int count = 0; // Сетчик для перемещения в массиве fileContent
            int k = 0;
            char foundedSizeArray[10]; // Найденый размер рабочего массива
            int foundedSize;
            
            while ((fileContent[count] >= '0' && fileContent[count] <= '9') || fileContent[count] == ' ') { // Пока числа выполняется цикл
                if (fileContent[count] >= '0' && fileContent[count] <= '9') {
                    foundedSizeArray[k] = fileContent[count]; // Присваиваем элемент из файла в массив разрядности
                    k++; // Следущий элемент в файле
                }
                count++;
            }
            foundedSize = GetNumber(foundedSizeArray, k);
            int Array[foundedSize]; // Рабочий массив
            int i = 0;
            for (int j = count; j < fileSize;j++){ // Цикл поиска чисел массива. j - номер элемента в массиве  count - место после размерности массива.
                
                if (fileContent[j] != ' ' && ((fileContent[j] >= '0' && fileContent[j] <= '9') || fileContent[j] == '-')) { // Если не пробел и число то
                    int znak = 1;
                    
                    while ((fileContent[j+1] == '-' || (fileContent[j+1] >= '0' && fileContent[j+1] <= '9')) && fileContent[j] == '-') {
                        znak *= -1;
                        j++;
                    }
                    
                    char numberSymbolsArray[10]; // Массив для вычисления числа более одного разряда
                    int countSymbol = 0; // Счетчик разрядности и индекса массива

                    while (fileContent[j] >= '0' && fileContent[j] <= '9') { // Пока числа выполняется цикл
                        numberSymbolsArray[countSymbol] = fileContent[j]; // Присваиваем элемент из файла в массив разрядности
                        countSymbol++;
                        j++; // Следущий элемент в файле
                    }
                    
                    if (fileContent[j-1] >= '0' && fileContent[j-1] <= '9' && fileContent[j] == '-') {
                        cout << "В вашем массиве есть неверный элемент типа x-y, где x и y целые числа.\nВведите правильный элемент: ";
                        cin >> Array[i];
                        i++;
                        while (fileContent[j] == '-') {
                            j++;
                        }
                    }
                    else if ((fileContent[j+1] != '-' && fileContent[j] != '-') || (fileContent[j-1] != '-' && fileContent[j] != '-')) { // Только если не будет минуса без числа
                        Array[i] = GetNumber(numberSymbolsArray, countSymbol); // Присваивание рабочему массиву число из массива разрядности
                        Array[i] *= znak;
                        i++;
                    }
                }
            }
            if (i < foundedSize) cout << "У вас не хватает элементов в массиве(Размерность: " << foundedSize << "). Добавьте их сейчас или измените размерность в файле Array.txt\nДобавляйте эелементы по одному." << endl;
            // Не хватает проверки вводимого элемента, элемент должен быть целым числом, возможен "-".
            while (i < foundedSize) {
                cout << "Элемент # " << i << ": ";
                char a;
                cin >> a;
                if (a >= '0' && a <= '9'){
                }
                else {
                    while (a <= 0 && a >= 9){
                    cout << "Нужно вводить целое число!\nЭлемент # " << i << ": ";
                    cin >> a;
                }
                }
                Array[i] = a;
                i++;
            }
            
            int result = 1; // Результат перемножения нечетных элементов в массиве
            int countNechet = 0;
            int znam = 0;
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
                cout << "Среднее арифметическое до минимального по модулю элемента невозможно вычислить."<< endl;
            }
            else {
                sred_arifm = sum/znam; // Вычисляем среднее арифметическое до минимального по модулю элементов
                cout << "Минимальный по модулю элемент массива: " << min << endl;
                cout << "Среднее арифметическое до минимального по модулю элемента: " << sred_arifm << endl;
            }
        }
    return 0;
}
