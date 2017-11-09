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
using namespace std;


int main() {
    int Mass[] = {2,2,3,3,5,1}; // Заданный массив
    int Size = (sizeof(Mass)/sizeof(int)); // Размер массива
    int result = 1; // Результат перемножения нечетных элементов в массиве
    int iMin = 0; // Индекс минимального по модулю элемента в массиве
    int min = Mass[0]; // Минимальное значение по модулю в массиве
    double sum = 0;// Сумма элементов до минимального значения по модулю в массиве
    double sred_arifm;
    // Проверяем каждый элемент массива
    for (int i=0;i < Size;i++){
    // Находим нечетные элементы в массиве
        if ((Mass[i]%2) != 0){
            result *= Mass[i]; // Перемножаем их
        }
    // Находим минимальный по модулю элемент и его индекс
        if (abs(Mass[i]) < min){
            min = abs(Mass[i]);
            iMin = i;
        }
    }
    // Вычисление суммы элементов до минимального по модулю элемента
    for (int i=0;i < iMin;i++){
        sum += Mass[i];
    }
    
    sred_arifm = sum/iMin; // Вычисляем среднее арифметическое до минимального по модулю элементов
    
    cout << "Перемноженные нечетные элементы в массиве: " << result << endl;
    cout << "Минимальный по модулю элемент массива: " << min << endl;
    cout << "Среднее арифметическое до минимального по модулю элемента: " << sred_arifm << endl;
    
    return 0;
}
