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

using namespace std;

const char *FName = "Mass.txt"; // Название исходного файла

long long int GetSizeOfFile(const char* path){
    ifstream in(path, ifstream::ate | ifstream::binary);
    return in.tellg();
}


int main(){
    char fileContent[GetSizeOfFile(FName)];
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
            char arraySize;
            do {
                arraySize = fileContent[count];
                count++;
            }
            while (!((int)arraySize > 47 && (int)arraySize < 58));
        }
    }
    catch(exception e) {
        cout << e.what() << endl;
    }
    return 0;
}
