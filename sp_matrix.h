#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

struct topThree {
    int first;
    int second;
    int third;
    float highestscore;
    float lowestscore;
};

class Node{
    private:
        int data;
        Node* next;
        int row;
        int column;

        friend class SpMatrix;
    public:
        Node();
        // Overloading
        Node(int data, int row, int col);
        Node(int data, int row, int col, Node* next);
        ~Node();
};

class SpMatrix{
    private:
    int rows;
    int columns;
    Node* head;
    void insert(int data, int row, int col, Node* node);
    void push(Node* node);
    void remove(int data, Node* node);
    //resize function for rows/cols
    void auto_resize(int new_num, bool type);

    public:
    SpMatrix();
    SpMatrix(int row, int col);
    SpMatrix(int row, int col, Node* head);
    void insert(int data, int row, int col);
    void remove(int data);
    //Adds two sparse matracies together
    SpMatrix add(SpMatrix& matrix2);
    //passing by reference for speed
    //multiplies two sparse matracies
    SpMatrix multiply(SpMatrix& matrix2);
    //Outputs the top three highest Averges
    topThree highest();
    //Outputs the top three averages with respect to a specifc column
    topThree highest(int col);
    //outputs the lowest average
    topThree lowest();
    //Make recomendations for a show based off input from the user
    topThree make_recs(int col);
    void to_csv(std::string fname);
    void to_csv_matrix(std::string fname, std::vector<std::vector<int>> matrix);
    //prints out the sparse matrix
    void print();
};
