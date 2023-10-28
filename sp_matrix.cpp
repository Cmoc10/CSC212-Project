#include "sp_matrix.h"

SpMatrix::SpMatrix(){
    this->columns = 0;
    this->rows = 0;
    this->head = nullptr;
}

SpMatrix::SpMatrix(int row, int col){
    this->columns = col;
    this->rows = row;
    this->head = nullptr;
}

SpMatrix::SpMatrix(int row, int col, Node* head){
    this->columns = col;
    this->rows = row;
    this->head = head;
}

void SpMatrix::insert(int data, int row, int col){
    //check if there is a head
    if(head == nullptr){
        Node* temp = new Node(data, row, col);
        head = temp;
        return;
    }
    //check if new node is before head
    else if(row < head->row){
        Node* temp = new Node(data, row, col, head);
        head = temp;
        return;
    }
    //check if node is in heads row
    else if(row == head->row){
        //check if new node is before head
        if(col < head->column){
            Node* temp = new Node(data, row, col, head);
            head = temp;
            return;
        }
        //check if new node is replacing hed
        else if(col == head->column){
            Node* temp = new Node(data, row, col, head);
            head = temp;
            return;
        }
        //check if head has a next
        else if(head->next == nullptr){
            Node* temp = new Node(data, row, col);
            head->next = temp;
            return;
        }
        //check if new node is in earlier row
        else if(row < head->next->row){
            Node* temp = new Node(data, row, col, head->next);
            head->next = temp;
            return;
        }
        //checks if in the same row as next
        else if(row == head->next->row){
            //if before reassign next
            if(col < head->next->column){
                Node* temp = new Node(data, row, col, head->next);
                head->next = temp;
                return;
            }
            //if the same push next back 1 spot
            else if(col == head->next->column){
                Node* temp = new Node(data, row, col, head->next);
                push(head->next);
                head->next = temp;
                return;
            }
            //if after recursive call
            else{
                insert(data, row, col, head->next);
                return;
            }
        }
        //if after recursive call
        else{
            insert(data, row, col, head->next);
            return;
        }
    }
}

void SpMatrix::insert(int data, int row, int col, Node* node){
    //check if new node is before node
    if(row < node->row){
        Node* temp = new Node(data, row, col, node);
        node = temp;
        return;
    }
    //check if node is in nodes row
    else if(row == node->row){
        //check if new node is before node
        if(col < node->column){
            Node* temp = new Node(data, row, col, node);
            node = temp;
            return;
        }
        //check if new node is replacing hed
        else if(col == node->column){
            Node* temp = new Node(data, row, col, node);
            node = temp;
            return;
        }
        //check if node has a next
        else if(node->next == nullptr){
            Node* temp = new Node(data, row, col);
            node->next = temp;
            return;
        }
        //check if new node is in earlier row
        else if(row < node->next->row){
            Node* temp = new Node(data, row, col, node->next);
            node->next = temp;
            return;
        }
        //checks if in the same row as next
        else if(row == node->next->row){
            //if before reassign next
            if(col < node->next->column){
                Node* temp = new Node(data, row, col, node->next);
                node->next = temp;
                return;
            }
            //if the same push next back 1 spot
            else if(col == node->next->column){
                Node* temp = new Node(data, row, col, node->next);
                push(node->next);
                node->next = temp;
                return;
            }
            //if after recursive call
            else{
                insert(data, row, col, node->next);
                return;
            }
        }
        //if after recursive call
        else{
            insert(data, row, col, node->next);
            return;
        }
    }
}
//function to push a value back if another value is trying to take the same place
void SpMatrix::push(Node* node){
    //check if at the end of a row
    if(node->column == columns){
        node->column = 0;
        node->row++;
        //check if pushing something else
        if(node->next->column == 0 && node->next->row == node->row + 1){
            push(node->next);
        }
        return;
    }
    //check if pushing something else
    else if(node->next->column != node->column + 1){
        node->column++;
        return;
    }
    else{
        node->column++;
        push(node->next);
        return;
    }
}

// Default constructor
Node::Node(){
    this->data = 0;
    this->next = nullptr;
    this->row = -1;
    this->column = -1;
}

Node::Node(int data, int row, int col){
    this->data = data;
    this->next = nullptr;
    this->row = row;
    this->column = col;
}


Node::Node(int data, int row, int col, Node* next){
    this->data = data;
    this->next = next;
    this->row = row;
    this->column = col;
}

Node::~Node(){
    if(this->next != nullptr){
        delete this->next;
    }
}