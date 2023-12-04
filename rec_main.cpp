#include "sp_matrix.h"
#include <vector>
#include <sstream>
#include <fstream>

//Make recomendation fucntion work for regular matracies.

std::string to_lower(std::string str){
    std::string newstr;
    for(char let: str){
        newstr.push_back(std::tolower(let));
    }
    return newstr;
}

int get_index(std::vector<std::string> labels, std::string to_find){
    for(int i=0; i<labels.size(); i++){
        if(to_lower(labels[i]) == to_lower(to_find)){
            return i;
        }
    }
    return -1;
}


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
    topThree results;
    topThree recomendations;
    std::string input;
    int index;
    int mistakeCounter = 0;
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
        std::cout << "The highest rated show is: " << titles[results.first] << " with a rating of " << std::fixed << std::setprecision(2) << results.highestscore << "\n";
        std::cout << "The lowest rated show is: " << titles[matrix.lowest()] << "\n";
        break;
    case 3:
        std::cout << "Which Show would you like to get reccomendations based off of?\n";
        std::cin >> input;
        index = get_index(titles, input);
        while(index == -1){
            mistakeCounter++;
            if(mistakeCounter == 3){
                std::cout<<"Please choose from this list: ";
                for(int i = 0; i<titles.size(); i++){
                    if(i == titles.size()-1){
                        std::cout<<titles[i];
                    } else {
                    std::cout<<titles[i]<<", ";
                    }
                }
                std::cout<<std::endl;
            } else{
                std::cout<<"Not a valid show or movie. Please type a different show."<<std::endl;
            }
            std::cin >> input;
            index = get_index(titles,input); 

        }
        recomendations = matrix.make_recs(index);
        std::cout << "People who liked " << titles[index] << " also liked " << titles[recomendations.first] 
        << ", " << titles[recomendations.second] << ", " << titles[recomendations.third]<<std::endl;
        break;
    default:
        break;
    }
    return 0;
}