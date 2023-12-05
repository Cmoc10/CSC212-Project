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
    //reading in matrix one
    while(std::getline(ifs, line)){
        std::stringstream ss(line);
        ss >> data >> row >> col;
        matrix.insert(data, row, col);
    }
    //reading in matrix 2
    while(std::getline(ifs_2, line)){
        std::stringstream ss(line);
        ss >> data >> row >> col;
        matrix_2.insert(data, row, col);
    }
    //Printing first matrix then second
    matrix.print();
    std::cout << std::endl;
    matrix_2.print();
    //writing first matrix to csv file
    matrix.to_csv(ofname);
    std::cout << "\n";
    std::cin >> line;

    //addition of matrix then print matrix
    matrix = matrix.add(matrix_2);
    matrix.print();
    std::cout << "\n";
    std::cin >> line;

    std::ifstream multifs(mult_fname);
    std::ifstream multifs_2(mult_fname_2);

    //read in matrix 2 and 3 for multiplication
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
    //printing out matrix 3 & 4
    matrix_3.print();
    std::cout << "\n";
    matrix_4.print();
    std::cout << "\n";
    std::cin >> line;

    //multiplying matrix which prints
    mult_matrix = matrix_3.multiply(matrix_4);
    std::cin >> line;

    //showing remove function
    mult_matrix.remove(5);
    mult_matrix.print();
    
    return 0;
}