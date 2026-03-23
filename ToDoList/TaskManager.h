#pragma once
#include "Task.h"
#include <vector>
#include <string>

void showMenu();
std::string getCurrentDate();

void loadTasks(std::vector<Task>& tasks);
void showAllTask(const std::vector<Task>& tasks);
void saveTask(const std::vector<Task>& tasks);