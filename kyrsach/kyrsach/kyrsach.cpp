#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>  
#include <random> 
#include <limits> 

using namespace std;


void permute(string str, int l, int r, vector<string>& result) {
    if (l == r) {
        result.push_back(str);
    }
    else {
        for (int i = l; i <= r; ++i) {
            swap(str[l], str[i]);
            permute(str, l + 1, r, result);
            swap(str[l], str[i]);
        }
    }
}

void generateRandomString(string& str, int length) {
    const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, chars.length() - 1);

    for (int i = 0; i < length; ++i) {
        str += chars[distrib(gen)];
    }
}

int main() {
    locale::global(locale(""));

    string inputString;
    int choice;

    do {
        cout << "Выберите способ ввода строки:\n";
        cout << "1. Ввести строку вручную\n";
        cout << "2. Сгенерировать случайную строку\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Некорректный ввод. Попробуйте снова.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) break;

        if (choice == 1) {
            cout << "Введите строку: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, inputString);
        }
        else if (choice == 2) {
            int length;
            cout << "Введите длину случайной строки: ";
            cin >> length;
            if (cin.fail() || length <= 0) {
                cout << "Некорректная длина строки. Попробуйте снова.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            inputString = "";
            generateRandomString(inputString, length);
            cout << "Сгенерированная строка: " << inputString << endl;
        }
        else {
            cout << "Некорректный выбор. Попробуйте снова.\n";
        }

        if (!inputString.empty()) {
            vector<string> permutations;
            permute(inputString, 0, inputString.length() - 1, permutations);
            sort(permutations.begin(), permutations.end(), greater<string>());

            cout << "Перестановки в антилексикографическом порядке (меньше введенной):\n";
            bool printed = false;
            for (const string& p : permutations) {
                if (p < inputString) {
                    cout << p << endl;
                    printed = true;
                }
            }
            if (!printed) {
                cout << "Перестановок меньше введенной строки нет\n";
            }


            char saveChoice;
            cout << "Сохранить результаты в файл? (y/n): ";
            cin >> saveChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (tolower(saveChoice) == 'y') {
                string filename;
                cout << "Введите имя файла: ";
                getline(cin, filename);

                ofstream outfile(filename);
                if (outfile.is_open()) {
                    for (const string& p : permutations) {
                        if (p < inputString) {
                            outfile << p << endl;
                        }
                    }
                    outfile.close();
                    cout << "Результаты сохранены в файл " << filename << endl;
                }
                else {
                    cerr << "Ошибка при открытии файла!" << endl;
                }
            }
        }
    } while (choice != 0);

    return 0;
}