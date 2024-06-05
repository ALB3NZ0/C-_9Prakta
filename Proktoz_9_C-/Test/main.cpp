#include <iostream>
#include <string>
#include <windows.h>
#include <locale.h>

using namespace std;

typedef bool (*CharCheckFunction)(const char*, const char*);

int main() {
    setlocale(LC_ALL, "RUS");

    cout << "������� ������ ��� ������ ��������: ";
    string inputStr;
    getline(cin, inputStr);

    if (inputStr.empty()) {
        cerr << "������: �� �� ����� ������ ��� ������ ��������." << endl;
        return 1;
    }

    cout << "������� ������� ��� ������: ";
    string searchChars;
    getline(cin, searchChars);

    if (searchChars.empty()) {
        cerr << "������: �� �� ����� ������� ��� ������." << endl;
        return 1;
    }

    HMODULE hDLL = LoadLibraryW(L"DinamicLib.dll");
    if (hDLL == NULL) {
        cerr << "�� ������� ��������� DLL." << endl;
        return 1;
    }

    CharCheckFunction checkCharsInString = (CharCheckFunction)GetProcAddress(hDLL, "serchstr");
    if (checkCharsInString == NULL) {
        cerr << "�� ������� �������� ����� �������." << endl;
        FreeLibrary(hDLL);
        return 1;
    }

    bool result = checkCharsInString(inputStr.c_str(), searchChars.c_str());

    if (result) {
        cout << "��� ������� �������! :)" << endl;
    }
    else {
        cout << "�� ��� ������� �������! :(" << endl;
    }

    FreeLibrary(hDLL);

    return 0;
}
