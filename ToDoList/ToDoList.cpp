#include <iostream>
#include <vector>
#include <string>
#include <fstream>      // для работы с файлами
#include <limits>       // для cin.ignore()
#include <ctime>
#include <windows.h>
#include "Task.h"
#include "TaskManager.h"



using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	
	setlocale(LC_ALL, "RU");

	vector<Task> tasks;
	loadTasks(tasks);

	while (true) {
		showMenu();

		int choice;
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка буфера


		if (choice == 1) {
			showAllTask(tasks);
			system("pause");
		}
		else if (choice == 2) {
			cout << "Введите задачу: ";
			string desc;
			getline(cin, desc);
			if (!desc.empty()) {
				tasks.push_back({ desc, false, getCurrentDate()});
				cout << "Задача добавлена (" << getCurrentDate() << ")\n";
			}
			system("pause");
		}
		else if (choice == 3) {
			int index;
			cout << "===Список задач===\n";
			showAllTask(tasks);
			cout << "Введите номер задачи: ";
			cin >> index;
			index--;
			if (index < 0 || index >= tasks.size())
			{
				cout << "Ошибка, ты вышел за диапозон!";
				continue;
			}
			tasks[index].done = true;
			cout << "Список обновлен!";
			system("pause");
		}
		else if (choice == 4) {
			int index;
			cout << "Введите индекс для удаления: ";
			cin >> index;
			index--;
			if (index < 0 || index >= tasks.size()) {
				cout << "Ошибка, ты вышел за диапозон!";
				continue;
			}
			else {
				tasks.erase(tasks.begin() + index);
			}
			system("pause");
		}
		else if (choice == 0) {
			saveTask(tasks);
			break;
		}
	}

}

