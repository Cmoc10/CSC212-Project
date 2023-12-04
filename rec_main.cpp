#include "sp_matrix.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>




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

int get_show(std::string input, std::vector<std::string> titles){
    int mistakeCounter = 0;
    int index = get_index(titles, input);
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
        return index;
}


int main(int argc, char** argv){
    std::string ifname = argv[2];
    int mode = std::stoi(argv[1]);

    SpMatrix matrix;
    std::vector<std::vector<int>> matrix_2;
    std::vector<int> temp_vec = {};

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
    if(mode != 5){
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
    }
    else{
        while(std::getline(ifs, line)){
            std::stringstream ss(line);
            if(!first){
                matrix_2.push_back(temp_vec);
            }
            while(std::getline(ss, entry, ' ')){
                std::stringstream ss2(entry);
                if(!first){
                    ss2 >> data;
                    matrix_2[row].push_back(data);
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
    }
    ifs.close();
    std::string type = "dense";
    if(mode == 4){
        type = "sparse";
    }
    topThree results;
    topThree results2;
    topThree recomendations;
    std::string input;
    int index;
    std::string outfname_matrix = "output_dense.csv";
    std::string outfname = "output_sparse.csv";
    auto start = std::chrono::high_resolution_clock::now();
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
        results2 = matrix.lowest();
        std::cout << "The highest rated show is: " << titles[results.first] << " with a rating of " << std::fixed << std::setprecision(2) << results.highestscore << "\n";
        std::cout << "The lowest rated show is: " << titles[results2.first] << " with a rating of " << std::fixed << std::setprecision(2) << results2.lowestscore << "\n";
        break;
    case 3:
        std::cout << "Which Show would you like to get reccomendations based off of?\n\t-And please use an underscore (_) as a space.";
        std::cin >> input;
        index = get_show(input, titles);
        recomendations = matrix.make_recs(index);
        std::cout << "People who liked " << titles[index] << " also liked " << titles[recomendations.first] 
        << ", " << titles[recomendations.second] << ", " << titles[recomendations.third]<<std::endl;
        break;
    case 4:
        matrix.to_csv(outfname);
        break;
    case 5:
        matrix.to_csv_matrix(outfname_matrix, matrix_2);
        break;
    default:
        break;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    if(mode > 3){
        std::cout << "milliseconds to complete type " << type << ": " << duration.count() << std::endl;
    }
    return 0;
}