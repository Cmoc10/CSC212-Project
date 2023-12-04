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
    SpMatrix add(SpMatrix& matrix2);
    //passing by reference for speed
    SpMatrix multiply(SpMatrix& matrix2);
    topThree highest();
    topThree highest(int col);
    int lowest();
    topThree make_recs(int col);
    void to_csv(std::string fname);
    void to_csv_matrix(std::string fname, std::vector<std::vector<int>> matrix);
    void print();
};