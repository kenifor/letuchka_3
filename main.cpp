#include "job.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <iostream>

#define THREADS_COUNT 3 // must be positive (from 1 to ...)


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Must be argument of command line: directory path" << std::endl;
        return 1;
    }

    // init sum
    double sum = 0.0f;

    path dir = path(argv[1], path::generic_format);

    vector<path> all_files;  // all files from directory

    // get files
    for (const auto& dir_entry : std::filesystem::directory_iterator(dir))
    {
        if (std::filesystem::file_type::regular == dir_entry.status().type())
        {
            all_files.push_back(dir_entry.path());
        }
    }

    vector<path> work_files; // vector size is N

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


    // create the list (vector) of threads using smart pointer
    std::vector<std::unique_ptr<std::thread>> threads;

    for (int i = 0; i < THREADS_COUNT; i++)
    {
        // create new thread and run it with function calculate and two parameters sum and work_files
        threads.push_back(std::make_unique<std::thread>(calculate, std::ref(sum), std::cref(work_files)));
    }

    for (int i = 0; i < THREADS_COUNT; i++)
    {
        // main thread must wait other threas
        threads[i]->join();
    }

    std::cout << "sum = " << sum << std::endl;

    std::ofstream output_file;

    dir += "\\out.dat";
    output_file.open(dir, std::ios_base::binary);

    if(output_file.is_open())
    {
        std::cout << "The output file was opened" << "\n";
    }
    else
    {
        std::cout << "The output file was not opened" << "\n";
        return 1;
    }

    // write some data to the output file
    output_file << "Sum: " << sum;


    // close file
    if (output_file.is_open())
        output_file.close();

    // write sum to the output file

    return 0;
}
