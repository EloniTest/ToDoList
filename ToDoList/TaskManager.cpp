#include "Task.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>      // для работы с файлами
#include <limits>       // для cin.ignore()
#include <ctime>
#include "TaskManager.h"


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
