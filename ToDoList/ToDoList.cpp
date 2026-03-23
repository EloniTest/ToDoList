#include <iostream>
#include <vector>
#include <string>
#include <fstream>      // для работы с файлами
#include <limits>       // для cin.ignore()
#include <ctime>

struct Task {
	std::string description;
	bool done = false;
	std::string date;
};

std::string getCurrentDate() {
	time_t now = time(nullptr);
	tm ltm;
	localtime_s(&ltm, &now);
	std::string date = std::to_string(ltm.tm_mday) + "." + std::to_string(1 + ltm.tm_mon) + "." + std::to_string(1900 + ltm.tm_year);
	return date;
}


void showMenu() {
	system("cls");
	std::cout << "\n=== ToDo List ===\n";
	std::cout << "1. Показать все задачи\n";
	std::cout << "2. Добавить задачу\n";
	std::cout << "3. Отметить задачу выполненной\n";
	std::cout << "4. Удалить задачу\n";
	std::cout << "0. Выход\n";
	std::cout << "Выберите действие: ";
}
void loadTasks(std::vector<Task>& tasks) {
	using namespace std;
	ifstream file("tasks.txt");
	if (!file.is_open()) return;

	string line;

	while (getline(file, line)) {
		if (line.empty()) continue;
		Task t;
		t.done = (line[0] == '1');
		// поиск 2 разделителя
		size_t first = line.find('|');
		size_t second = line.find('|', first + 1);
		t.description = line.substr(first + 1, second - first + 1);
		t.date = line.substr(second + 1);
		tasks.push_back(t);
	}
	file.close();
}
void showAllTask(const std::vector<Task>& tasks) {
	if (tasks.empty()) {
		std::cout << "Список пуст\n";
		return;
	}

	std::cout << "Ваши задачи:\n";

	for (size_t i = 0; i < tasks.size();i++)
	{
		std::cout << i + 1 << ". ";
		if (tasks[i].done) {
			std::cout << "[x]";
		}
		else {
			std::cout << "[ ]";
		}
		std::cout << "Задача: " << tasks[i].description << ". Время создания: " << tasks[i].date << std::endl;
	}



}
void saveTask(const std::vector<Task>& tasks) {
	std::ofstream file("tasks.txt");
	if (!file.is_open())
	{
		std::cout << "Ошибка: не удалось открыть файл для записи!\n";
	}

	for (auto& t : tasks) {
		file << (t.done ? "1" : "0") << "|" << t.description << t.date << std::endl;
	}
	file.close();
	std::cout << "Список задач сохранен\n";
}
int main()
{
	setlocale(LC_ALL, "RU");

	using namespace std;
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

