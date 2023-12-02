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

void SpMatrix::auto_resize(int new_num, bool type){
    // if type == True resize rows
    if(type){
        this->rows = new_num+1;
    }
    //else resize cols
    else{
        this->columns = new_num+1;
    }
}

void SpMatrix::insert(int data, int row, int col){
    if(row > this->rows){
        auto_resize(row, true);
    }
    if(col > this->columns){
        auto_resize(col, false);
    }
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
    }
    //if after recursive call
    else if(head->next == nullptr){
        Node* temp = new Node(data, row, col, head->next);
        head->next = temp;
        return;
    }
    else{
        insert(data, row, col, head->next);
        return;
    }
}

void SpMatrix::insert(int data, int row, int col, Node* node){
    if(!node){
        std::cout << data << " uh oh\n";
        return;
    }
    //checking for a next node
    if(node->next == nullptr){
        Node* temp = new Node(data, row, col);
        node->next = temp;
        return;
    }
    //checking if before next node by row
    else if(row < node->next->row){
        Node* temp = new Node(data, row, col, node->next);
        node->next = temp;
        return;
    }
    //checking if before next node if in same row
    else if(row == node->next->row){
        if(col < node->next->column){
            Node* temp = new Node(data, row, col, node->next);
            node->next = temp;
            return;
        }
        else if(col == node->next->column){
            Node* temp = new Node(data, row, col, node->next);
            push(node->next);
            node->next = temp;
            return;
        }
        else{
            insert(data, row, col, node->next);
        }
    }
    else{
        insert(data, row, col, node->next);
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

void SpMatrix::print(){
    std::cout << "Rows: " << rows << "\n" << "Columns: " << columns << "\n";
    Node* temp = head;
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(i == temp->row && j == temp->column){
                std::cout << temp->data << " ";
                if(temp->next != nullptr){
                    temp = temp->next;
                }
            }
            else{
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
}

void SpMatrix::to_csv(std::string fname){
    std::ofstream outf(fname);
    Node* temp = head;
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(i == temp->row && j == temp->column){
                outf << temp->data << ",";
                if(temp->next != nullptr){
                    temp = temp->next;
                }
            }
            else{
                outf << "0,";
            }
        }
        outf << "\n";
    }
    outf.close();
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