#include "Reader.h"
#include "HashTable.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <limits>
using namespace std;

static void printMenu() {
    cout << "\n================ Хеш-таблица (цепное хеширование) ================\n";
    cout << "1) Добавить читателя\n";
    cout << "2) Удалить читателя по номеру\n";
    cout << "3) Найти читателя по номеру\n";
    cout << "4) Вывести таблицу\n";
    cout << "5) Автозаполнение 5–7 записями (рандом)\n";
    cout << "0) Выход\n";
    cout << "-------------------------------------------------------------------\n";
    cout << "Выберите пункт меню: ";
}

static int promptInt(const string &msg) {
    cout << msg;
    int x{};
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Некорректный ввод. Повторите: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}

static string promptLine(const string &msg) {
    cout << msg;
    string s;
    getline(cin, s);
    return s;
}

int main() {
    HashTable table(10);

    while (true) {
        printMenu();
        int choice{};
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите номер пункта меню.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) {
            cout << "Выход. Спасибо!\n";
            break;
        }

        switch (choice) {
            case 1: {
                int ticket = promptInt("Введите номер читательского билета (5 цифр): ");
                string fio = promptLine("Введите ФИО: ");
                string addr = promptLine("Введите адрес: ");

                Reader r(ticket, fio, addr);
                if (table.insert(r)) {
                    cout << "Добавлено: [" << ticket << "] " << fio << ", " << addr << "\n";
                } else {
                    cout << "Запись с таким номером уже существует.\n";
                }
                break;
            }
            case 2: {
                int ticket = promptInt("Введите номер для удаления: ");
                if (table.remove(ticket)) {
                    cout << "Удалено: [" << ticket << "]\n";
                } else {
                    cout << "Элемент с номером " << ticket << " не найден.\n";
                }
                break;
            }
            case 3: {
                int ticket = promptInt("Введите номер для поиска: ");
                Reader found;
                if (table.find(ticket, found)) {
                    cout << "Найдено: [" << found.getTicketNumber() << "] "
                            << found.getFio() << ", " << found.getAddress() << "\n";
                } else {
                    cout << "Не найдено.\n";
                }
                break;
            }
            case 4: {
                cout << "Содержимое таблицы:\n";
                table.display();
                break;
            }
            case 5: {
                table.fillDemo();
                cout << "Готово. Таблица пополнена.\n";
                break;
            }
            default:
                cout << "Нет такого пункта меню. Повторите выбор.\n";
                break;
        }
    }

    return 0;
}
