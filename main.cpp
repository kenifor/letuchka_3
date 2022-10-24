#include <filesystem>
#include <fstream>
#include <vector>
#include <execution>
#include <mutex>

using namespace std;

using std::filesystem::path;

int main(int argc, char** argv)
{
    if (argc != 2) {
        return 0;
    }

    path p = path(argv[1], path::generic_format);

    double sum = 0.;
    vector<path> files;
    for (const auto& dir_entry : filesystem::directory_iterator(p)) {
        if (filesystem::file_type::regular == dir_entry.status().type()) {
            files.push_back(dir_entry.path());
        }
    }

    mutex m;
    std::for_each(std::execution::par, files.begin(), files.end(), [&sum, &m](path p) {
        string filename = p.filename().string();// получаю имя файла
        if (filename.substr(0, 3) == "in_"sv) {
            auto iter = filename.find('.');
            string N = filename.substr(3, iter - 3); // получаю N
            bool N_is_natural = true;
            for (char digit : N) {
                if (!isdigit(digit)) {
                    N_is_natural = false;
                }
            }
            if (N_is_natural) {
                ifstream f(p);
                size_t command;
                double val1, val2;
                f >> command >> val1 >> val2;
                lock_guard lg(m);
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
                }
            }
        }
        });

    ofstream of(p / path("out.dat"s));
    of << sum;
}
