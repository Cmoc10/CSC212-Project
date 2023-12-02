#include "sp_matrix.h"
#include <vector>
#include <sstream>
#include <fstream>

int main(int argc, char** argv){
    std::string ifname = argv[1];
    int mode = std::stoi(argv[2]);
    std::string file2 = argv[3];

    SpMatrix matrix;
    SpMatrix matrix2;

    std::ifstream ifs(ifname);
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

    //Get the second matrix for addition/multiplication
    std::ifstream ifs2(file2);
    std::string line2;
    while(std::getline(ifs2, line2)){
        std::stringstream ss2(line2);
        ss2 >> data >> row >> col;
        matrix2.insert(data, row, col);
    }

    switch (mode){
    case 1:
        matrix.print();
        break;
    case 2:
        matrix.to_csv(ofname);
        break;
    case 3:
        matrix = matrix.add(matrix2);
        matrix.print();
    default:
        break;
    }
    return 0;
}