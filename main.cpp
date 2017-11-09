#include <iostream>
//#include <fstream>
using namespace std;


int main() {
   /* char Mass[255];
    ifstream file("test.txt");
    if (!file.is_open()) {
        cout << "Ошибка! Файл не найден!" << endl;
    }
    else {
        file >> Mass;
        cout << Mass << endl;
    */
    int Mass[] = {2,3,4,6,-8,7,1,-9,6};
    int Size = (sizeof(Mass)/sizeof(int));
    int result = 1;
    int iMin = -1;
    int min = Mass[0];
    double sum = 0;
    
    // Проверяем каждый элемент массива
    for (int i=0;i < Size;i++){
    // Находим нечетные элементы в массиве и перемножаем их
        if ((Mass[i]%2) != 0){
            result *= Mass[i];
        }
    // Находим минимальный по модулю элемент
        if (abs(Mass[i]) < min){
            min = abs(Mass[i]);
            iMin = i;
        }
    }
    // Вычисление суммы элементов до минимального по модулю элемента
    for (int i=0;i < iMin;i++){
        sum += Mass[i];
    }

    cout << "Перемноженные нечетные элементы в массиве: " << result << endl;
    cout << "Минимальный по модулю элемент массива: " << min << endl;
    cout << "Среднее арифметическое до минимального по модулю элемента: " << sum/iMin << endl;
    
    return 0;
}
