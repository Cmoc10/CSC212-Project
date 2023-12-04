#include "sp_matrix.h"
#include <vector>
#include <sstream>
#include <fstream>

int main(int argc, char** argv){
    std::string ifname = argv[1];
    std::string fname_2 = argv[2];
    std::string mult_fname = argv[3];
    std::string mult_fname_2 = argv[4];

    SpMatrix matrix;
    SpMatrix matrix_2;
    SpMatrix matrix_3;
    SpMatrix matrix_4;
    SpMatrix mult_matrix;

    std::ifstream ifs(ifname);
    std::ifstream ifs_2(fname_2);
    std::string ofname = ifname.substr(0, ifname.rfind('.')) + "_matrix.csv";

    std::string line;


    int data;
    int row;
    int col;

    while(std::getline(ifs, line)){
        std::stringstream ss(line);
        ss >> data >> row >> col;
        matrix.insert(data, row, col);
    }

    while(std::getline(ifs_2, line)){
        std::stringstream ss(line);
        ss >> data >> row >> col;
        matrix_2.insert(data, row, col);
    }

    matrix.print();
    std::cout << std::endl;
    matrix_2.print();
    matrix.to_csv(ofname);
    std::cout << "\n";
    std::cin >> line;
    matrix = matrix.add(matrix_2);
    matrix.print();
    std::cout << "\n";
    std::cin >> line;

    std::ifstream multifs(mult_fname);
    std::ifstream multifs_2(mult_fname_2);

    while(std::getline(multifs, line)){
        std::stringstream ss(line);
        ss >> data >> row >> col;
        matrix_3.insert(data, row, col);
    }

    while(std::getline(multifs_2, line)){
        std::stringstream ss(line);
        ss >> data >> row >> col;
        matrix_4.insert(data, row, col);
    }

    matrix_3.print();
    std::cout << "\n";
    matrix_4.print();
    std::cout << "\n";
    std::cin >> line;
    mult_matrix = matrix_3.multiply(matrix_4);
    std::cin >> line;
    mult_matrix.remove(5);
    mult_matrix.print();
    return 0;
}