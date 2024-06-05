#include <iostream>
#include <string>
#include <windows.h>
#include <locale.h>

using namespace std;

typedef bool (*CharCheckFunction)(const char*, const char*);

int main() {
    setlocale(LC_ALL, "RUS");

    cout << "Введите строку для поиска символов: ";
    string inputStr;
    getline(cin, inputStr);

    if (inputStr.empty()) {
        cerr << "Ошибка: Вы не ввели строку для поиска символов." << endl;
        return 1;
    }

    cout << "Введите символы для поиска: ";
    string searchChars;
    getline(cin, searchChars);

    if (searchChars.empty()) {
        cerr << "Ошибка: Вы не ввели символы для поиска." << endl;
        return 1;
    }

    HMODULE hDLL = LoadLibraryW(L"DinamicLib.dll");
    if (hDLL == NULL) {
        cerr << "Не удалось загрузить DLL." << endl;
        return 1;
    }

    CharCheckFunction checkCharsInString = (CharCheckFunction)GetProcAddress(hDLL, "serchstr");
    if (checkCharsInString == NULL) {
        cerr << "Не удалось получить адрес функции." << endl;
        FreeLibrary(hDLL);
        return 1;
    }

    bool result = checkCharsInString(inputStr.c_str(), searchChars.c_str());

    if (result) {
        cout << "Все символы найдены! :)" << endl;
    }
    else {
        cout << "Не все символы найдены! :(" << endl;
    }

    FreeLibrary(hDLL);

    return 0;
}
