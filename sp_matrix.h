#include <iostream>
#include <iomanip>

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
    public:
    SpMatrix();
    SpMatrix(int row, int col);
    SpMatrix(int row, int col, Node* head);
    void insert(int data, int row, int col);
    void print();
};