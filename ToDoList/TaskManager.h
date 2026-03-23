#pragma once
#include "Task.h"
#include <vector>
#include <string>

void showMenu();
std::string GetCurrentDate();

void loadTasks(std::vector<Task>& tasks);
void showAllTask(const std::vector<Task>& tasks);
void saveTask(const std::vector<Task>& tasks);