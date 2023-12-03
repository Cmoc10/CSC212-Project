#include "sp_matrix.h"
#include <vector>
#include <sstream>
#include <fstream>


int main(int argc, char** argv){
    std::string ifname = argv[2];
    int mode = std::stoi(argv[1]);

    SpMatrix matrix;
    SpMatrix matrix2;

    std::ifstream ifs(ifname);
    std::string ofname = ifname.substr(0, ifname.rfind('.')) + "_matrix.csv";

    std::string line;
    std::string entry;
    std::vector<std::string> titles;
    std::string str_temp;

    int data;
    int row = 0;
    int col = 0;
    bool first = true;

    while(std::getline(ifs, line)){
        std::stringstream ss(line);
        while(std::getline(ss, entry, ' ')){
            std::stringstream ss2(entry);
            if(!first){
                ss2 >> data;
                if(data != 0){
                    matrix.insert(data, row, col);
                }
                col++;
            }
            else{
                ss2 >> str_temp;
                titles.push_back(str_temp);
            }
        }
        if(first){
            first = false;
        }
        else{
            row++;
            col = 0;
        }
    }
    ifs.close();
    if(argc > 2){
            std::string fname2 = argv[3];
    first = true;
    std::ifstream ifs2(fname2);
    while(std::getline(ifs2, line)){
        std::stringstream ss(line);
        while(std::getline(ss, entry, ' ')){
            std::stringstream ss2(entry);
            if(!first){
                ss2 >> data;
                matrix.insert(data, row, col);
                col++;
                }
                else{
                    
                }
            }
            if(first){
                first = false;
            }
            else{
                row++;
                col = 0;
            }
        }
    ifs2.close();
    }
    topThree results;
    topThree recomendations;
    switch (mode){
    case 1:
        for(std::string title: titles){
            std::cout << title << " ";
        }
        std::cout << "\n";
        matrix.print();
        break;
    case 2:
        results = matrix.highest();
        std::cout << "The highest rated show is: " << titles[results.first] << "\n";
        std::cout << "The lowest rated show is: " << titles[matrix.lowest()] << "\n";
        recomendations = matrix.make_recs(1);
        std::cout << "Based on you liking the show " << titles[1] << " other people who liked " << titles [1] << " also liked "
            << titles[recomendations.first] << ", " << titles[recomendations.second] << ", " << titles[recomendations.third]<<std::endl;
        break;
    case 3:

    default:
        break;
    }
    return 0;
}