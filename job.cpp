#include "job.h"

#include <thread>
#include <fstream>
#include <iostream>
#include <mutex>

std::mutex mtx;

vector<path> filterFiles(const path& dir){
    //path dir = path(argv[1], path::generic_format);

    vector<path> all_files;  // all files from directory

    // get files
    for (const auto& dir_entry : std::filesystem::directory_iterator(dir))
    {
        if (std::filesystem::file_type::regular == dir_entry.status().type())
        {
            all_files.push_back(dir_entry.path());
        }
    }

    vector<path> work_files;

    for (const auto& file: all_files)
    {
        std::string filename = file.filename().string();// получаю имя файла

        if (filename.substr(0, 3) == "in_")
        {
            auto iter = filename.find('.');

            std::string N = filename.substr(3, iter - 3); // получаю N
            bool N_is_natural = true;
            for (char digit : N)
            {
                if (!isdigit(digit))
                {
                    N_is_natural = false;
                }
            }

            if (N_is_natural)
            {
                // create a valid files list (in_N)
                work_files.push_back(file);
            }
        }
    }

    return work_files;
}

bool writeSumToFile(double sum, path dir)
{
    std::ofstream output_file;

    dir += "\\out.dat";
    output_file.open(dir, std::ios_base::binary);

    if (!output_file.is_open())
        return false;

    // write some data to the output file
    output_file << sum;

    // close file
    if (output_file.is_open())
        output_file.close();

    return true;
}

double readSumFromFile(const path& path_file)
{
    std::ifstream file(path_file, std::ios_base::binary);

    double sum;
    file >> sum;

    if (file.is_open())
        file.close();

    return sum;
}

double calculateInThreads(int treadsCount, const vector<path>& work_files)
{
    double sum = 0.0f;

    // create the list (vector) of threads using smart pointer
    std::vector<std::unique_ptr<std::thread>> threads;

    for (int i = 0; i < treadsCount; i++)
    {
        // create new thread and run it with function calculate and two parameters sum and work_files
        threads.push_back(std::make_unique<std::thread>(calculate, std::ref(sum), std::cref(work_files)));
    }

    for (int i = 0; i < treadsCount; i++)
    {
        // main thread must wait other threas
        threads[i]->join();
    }

    return sum;
}

void calculate(double& sum, const vector<path>& files)
{
    // PLAN
    // open file from files vector
    // read data
    // calculate
    // write result of calculating to 'sum' variable

    // execute it N times, N - count of files

    while (true)
    {
        mtx.lock();

        static int filesCounter = 0;

        if (filesCounter == files.size())
        {
            mtx.unlock();
            return;
        }

        ++filesCounter;

        mtx.unlock();

        // input file stream
        std::ifstream f(files[filesCounter-1], std::ios_base::in);

        // opening check
        if (!f.is_open())
        {
            std::cout << "File was not opened!" << std::endl;
            return;
        }

        // file was opened successfully then read data
        size_t command;
        double val1, val2;
        f >> command >> val1 >> val2;

        mtx.lock();
        switch (command)
        {
        case 1: // сложнеие
            sum += val1 + val2;
            break;
        case 2: // умножение
            sum += val1 * val2;
            break;
        case 3: // сумма квадратов
            sum += val1 * val1 + val2 * val2;
            break;
        default: break;
        }
        mtx.unlock();

        if (f.is_open())
            f.close();
    }
}
