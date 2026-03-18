#include <iostream>
#include <vector>
#include <string>
#include <fstream>      // для работы с файлами
#include <limits>       // для cin.ignore()


struct Task {
	std::string description;
	bool done = false;
};

void showMenu() {
	std::cout << "\n=== ToDo List ===\n";
	std::cout << "1. Показать все задачи\n";
	std::cout << "2. Добавить задачу\n";
	std::cout << "3. Отметить задачу выполненной\n";
	std::cout << "4. Удалить задачу\n";
	std::cout << "5. Сохранить и выйти\n";
	std::cout << "6. Загрузить список\n";
	std::cout << "0. Выход без сохранения\n";
	std::cout << "Выберите действие: ";
}
void loadTasks(std::vector<Task>& tasks) {
	using namespace std;
	ifstream file("task.txt");
	if (!file.is_open()) return;

	string line;

	while (getline(file, line))
		if (line.empty()) continue;

	Task t;
	t.done = (line[0] == '1');
	t.description = line.substr(2);
	tasks.push_back(t);
}
void showAllTask(const std::vector<Task>& tasks) {
	if (tasks.empty()) {
		std::cout << "Список пуст\n";
		return;
	}

	std::cout << "Ваши задачи:\n";

	for (size_t i = 0; i < tasks.size();i++)
	{
		if (tasks[i].done) {
			std::cout << "[x]";
		}
		else {
			std::cout << "[ ]";
		}
		std::cout << "Задача: " << tasks[i].description << std::endl;
	}



}
void saveTask(const std::vector<Task>& tasks) {
	std::ofstream file("tasks.txt");
	if (!file.is_open())
	{
		std::cout << "Ошибка сохранения!\n";
	}

	for (auto& t : tasks) {
		file << (t.done ? "1" : "0") << "|" << t.description << std::endl;
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
	float t;
	float testCommit;

	while (true) {
		showMenu();
		int choice;
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка буфера

		if (choice == 0) {
			cout << "Завершение программы";
			break;
		}

		else if (choice == 1) {
			showAllTask(tasks);
		}
		else if (choice == 2) {
			cout << "Введите задачу: ";
			string desc;
			getline(cin, desc);
			if (!desc.empty())
			{
				tasks.push_back({ desc,false });
			}
		}
		else if (choice == 3) {
			int index;
			cout << "===Список задач===\n";
			showAllTask(tasks);
			cout << "Введите номер задачи: ";
			cin >> index;
			if (index < 0 || index >= tasks.size())
			{
				cout << "Ошибка, ты вышел за диапозон!";
				continue;
			}
			tasks[index].done = true;
			cout << "Список обновлен!";
		}
		else if (choice == 4) {
			int index;
			cout << "Введите индекс для удаления: ";
			cin >> index;
			if (index < 0 || index >= tasks.size()) {
				cout << "Ошибка, ты вышел за диапозон!";
				continue;
			}
			else {
				tasks.erase(tasks.begin() + index);
			}
		}
		else if (choice == 6) {
			cout << "Загрузка списка";
			loadTasks(tasks);
			cout << "Загрузка завершена";
		}
		else if (choice == 5) {
			saveTask(tasks);
			break;
		}
	}

}

