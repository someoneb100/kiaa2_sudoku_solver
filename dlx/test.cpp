#include "dlx.hpp"

#include <iostream>
#include <numeric>
#include <algorithm>
#include <cassert>
#include <functional>
namespace {
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const std::vector<T>& c){
        out << '{';
        if(!c.empty()){
            std::copy(
                c.cbegin(), c.cend()-1,
                std::ostream_iterator<T>(out, ", ")
            );
            out << c.back();
        }
        return out << '}';
    }

    void assert_solution(matrix_t results, matrix_t expected){
        assert((results.size() == expected.size()));
        auto all_results = std::inner_product(
            expected.cbegin(), expected.cend(),
            results.begin(),
            true,
            std::logical_and<bool>(),
            [](auto& a, auto& b){
                if (a.size() != b.size()){
                    std::cout << "Bad size: a.size = " + std::to_string(a.size()) + ", b.size = " + std::to_string(a.size()) << std::endl;
                    return false;
                }
                std::sort(b.begin(), b.end());
                if(!std::equal(a.begin(), a.end(), b.begin())){
                    std::cout << "Results are not the same:" << std::endl;
                    std::cout << "\tA = " << a << std::endl;
                    std::cout << "\tB = " << b << std::endl;
                    return false;
                }
                return true;
            }
        );
        assert((all_results));
    }
}

int main(){
    std::vector<std::vector<bool>> ProbMat(7, std::vector<bool>(7, false));
    ProbMat[0][0] = true; ProbMat[0][3] = true; ProbMat[0][6] = true;
    ProbMat[1][0] = true; ProbMat[1][3] = true;
    ProbMat[2][3] = true; ProbMat[2][4] = true; ProbMat[2][6] = true;
	ProbMat[3][2] = true; ProbMat[3][4] = true; ProbMat[3][5] = true;
    ProbMat[4][1] = true; ProbMat[4][2] = true; ProbMat[4][5] = true; ProbMat[4][6] = true;
    ProbMat[5][1] = true; ProbMat[5][6] = true;
    ProbMat[6][0] = true; ProbMat[6][3] = true;

    matrix_t expected1 = {{1, 3, 5}, {3, 5, 6}};
    matrix_t expected2 = expected1;
    matrix_t expected3 = {{1, 3, 5}};

    DLX solver1(ProbMat);
    auto result1 = solver1.search();
    assert_solution(result1, expected1);

    DLX solver2(ProbMat);
    solver2.add(3);
    auto result2 = solver2.search();
    assert_solution(result2, expected2);

    DLX solver3(ProbMat);
    solver3.add(1);
    auto result3 = solver3.search();
    assert_solution(result3, expected3);
}