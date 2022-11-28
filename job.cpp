#include "job.h"

#include <fstream>
#include <iostream>
#include <mutex>

std::mutex mtx;

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
