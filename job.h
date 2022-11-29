#pragma once

#include <filesystem>
#include <vector>

using std::vector;
using std::filesystem::path;


void calculate(double& sum, const vector<path>& files);

//функция считывает данные в папке и возвращает список файлов которые удовлетворяют условиям задачи
vector<path> filterFiles(const path& dir);

// threadsCount, filesList --> calculating in separate threads --> sum (double)
double calculateInThreads(int treadsCount, const vector<path>& files);

// sum (double) --> write sum to output file --> result of data writing (bool)
bool writeSumToFile(double sum, path dir);

double readSumFromFile(const path& path_file);
