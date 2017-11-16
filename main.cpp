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

long long int GetSizeOfFile(const char* path){
    ifstream in(path, ifstream::ate | ifstream::binary);
    return in.tellg();
}


int GetNumber(const char* symbols, int length){
    int res = 0;
    cout << "Function sym: " << symbols[0] << " Len: " << length << endl;
    for (int i = 1; i <= length; i++){
         res += (symbols[i-1]-'0') * pow(10, length - i);
    }
    cout << "Res: " << res << endl;
    return res;
}

int main(){
    long long int fileSize = GetSizeOfFile(FName);
    char fileContent[fileSize];
   try {
       
       ifstream fin(FName, ifstream::binary);
       
        if(!fin.is_open()){
            throw "Ошибка чтения файла.";
        }
        else {
            for  (int i = 0; !fin.eof(); i++) {
                fileContent[i] = fin.get();
                //cout << i << ": " << (fileContent[i]) << endl;
            }
            int count = 0;
            int foundedArraySize;
            do {
                foundedArraySize = (int)fileContent[count];
                count++;
            }
            while (!((int)foundedArraySize > 47 && (int)foundedArraySize < 58));
            
            
            int Array[foundedArraySize];
            for (int i = 0, j = count; j < fileSize;){
                if (fileContent[j] != ' ' && ((int)fileContent[j] > 47 && (int)fileContent[j] < 58)) {
                    char numberSymbolsArray[10];
                    int countSymbol = 0;
                    while ((int)fileContent[j] > 47 && (int)fileContent[j] < 58) {
                        cout << " FileContent: " << fileContent[j] << endl;
                        numberSymbolsArray[countSymbol] = fileContent[j];
                        countSymbol++;
                        j++;
                    }
                    Array[i] = GetNumber(numberSymbolsArray, countSymbol);
                }
                i++;
                j++;
            }
        }
    }
    catch(exception e) {
        cout << e.what() << endl;
    }
    return 0;
}
