#include "solver.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <exception>
#include <iterator>
#include <algorithm>
#include <execution>
#include <numeric>
#include <cmath>

namespace {
    std::vector<std::string> get_dataset(std::filesystem::path dataset_file_path)
    {
        dataset_file_path.replace_filename("dataset.txt");
        std::ifstream dataset_file(dataset_file_path);
        if(!dataset_file){
            throw std::runtime_error("File 'dataset.txt' does not exist. Please run CMake to download it!");
        }
        std::vector<std::string> lines;
        std::string line;
        while(std::getline(dataset_file, line))
            lines.emplace_back(line);
        return lines;
    }

    Board initialize_board(const std::string& line){
        Board b;
        for(size_t i = 0; i != Board::size; ++i){
            for(size_t j = 0; j != Board::size; ++j){
                char c = line[i*Board::size + j];
                Value v = (c == '.') ? Value::EMPTY : static_cast<Value>(c - '0');
                if(v != Value::EMPTY) b[i][j] = v;
            }
        }
        return b;
    }

    int time_it(SudokuSolver& solver){
        auto t1 = std::chrono::high_resolution_clock::now();
        solver.solution(false);
        auto t2 = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
    }

} // namespace

int main(int, char** argv){
    auto lines = get_dataset(argv[0]);
    std::vector<int> timer(lines.size());

    #pragma omp parallel for
    for(size_t i = 0; i < lines.size(); ++i){
        Board b = initialize_board(lines[i]);

        SudokuSolver solver(b);
        auto time = time_it(solver);

        #pragma omp critical
        {
            std::cout << "* Solved test " << i << " in " << time << "ms!" << std::endl;
            timer[i] = time;
        }
    }

    std::cout << "==============================================" << std::endl;
    auto minTime = *std::min_element(timer.begin(), timer.end());
    auto maxTime = *std::max_element(timer.begin(), timer.end());
    auto meanTime = static_cast<double>(std::accumulate(timer.begin(), timer.end(), 0)) / timer.size();

    double variance = 0.0;
    for (int time : timer) {
        variance += std::pow(time - meanTime, 2);
    }
    variance /= timer.size();

    double stddevTime = std::sqrt(variance);

    std::cout << "Minimum time: " << minTime/1000.0 << 's' << std::endl;
    std::cout << "Maximum time: " << maxTime/1000.0 << 's' << std::endl;
    std::cout << "Mean time: " << meanTime/1000.0 << 's' << std::endl;
    std::cout << "Standard deviation: " << stddevTime/1000.0 << 's' << std::endl;

    return 0;
}
