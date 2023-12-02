#include "sp_matrix.h"
#include <vector>
#include <sstream>
#include <fstream>

int main(int argc, char** argv){
    std::string ifname = argv[1];
    int mode = std::stoi(argv[2]);

    SpMatrix matrix;

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
    switch (mode){
    case 1:
        matrix.print();
        break;
    case 2:
        matrix.to_csv(ofname);
        break;
    default:
        break;
    }
    return 0;
}