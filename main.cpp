#include "job.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#define THREADS_COUNT 3 // must be positive (from 1 to ...)


int main(int argc, char** argv)
{
    // количество аргументов должно быть 2 (1й - путь до программы, 2й - путь до папки с файлами)
    if (argc != 2)
    {
        std::cout << "Must be argument of command line: directory path" << std::endl;
        return 1;
    }

    // files dir --> read files and get data --> files list
    vector<path> work_files = filterFiles(argv[1]);// vector size is N

    // threadsCount --> calculating in separate threads --> sum (double)
    double sum = calculateInThreads(THREADS_COUNT, work_files);

    // print sum on the screen
    std::cout << "sum = " << sum << std::endl;

    // sum (double) --> write sum in output file --> result of data writing (bool)

    if (writeSumToFile(sum, argv[1]))
    {
        std::cout << "The output file was opened and sum was wrote." << "\n";
        return 0;
    }
    else
    {
        std::cout << "The output file was not opened." << "\n";
        return 1;
    }
}
