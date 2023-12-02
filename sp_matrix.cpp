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
        //std::cout << columns << std::endl;
    }
}

void SpMatrix::insert(int data, int row, int col){
    if(row > (this->rows)-1){
        auto_resize(row, true);
    }
    if(col > (this->columns-1)){
        auto_resize(col, false);
    }
    //check if there is a head
    //std::cout << columns << std::endl;
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

void SpMatrix::remove(int data){
    Node* temp = this->head;
    Node* prev = nullptr;

    //Run until the data is found or hits the end of the matrix (data not found)
    while(temp->data != data && temp != nullptr){
        prev = temp;
        temp = temp->next;
    }

    //If data is found
    if(temp != nullptr){
        //If it's the first data being removed, reassign head node
        if(temp == this->head){
            this->head = temp->next;
        }
        else{
            prev->next = temp->next;
        }

        //Remove the data
        temp->next = nullptr;
        delete temp;
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

SpMatrix SpMatrix::add(SpMatrix& matrix2){
    SpMatrix result(rows, columns);

    //traverse through matrixes
    //starting position 
    Node* temp1 = this->head;
    Node* temp2 = matrix2.head;
    //Same position
    while(temp1 != nullptr && temp2 != nullptr){
        //Check the row first
        //Same row
        if(temp1->row == temp2->row){
            //check the columns
            if(temp1->column < temp2->column){
                result.insert(temp1->data, temp1->row, temp1->column);
                temp1 = temp1->next;
                if(temp1 == nullptr){
                    break;
                }
            }
            else if(temp2->column < temp1->column){
                result.insert(temp2->data, temp2->row, temp2->column);
                temp2 = temp2->next;
                if(temp2 == nullptr){
                    break;
                }
            }
            //Same column, add them together
            else if(temp1->column == temp2->column){
                int sum;
                sum = temp1->data + temp2->data;
                result.insert(sum, temp1->row, temp1->column);

                temp1 = temp1->next;
                temp2 = temp2->next;
                if(temp1 == nullptr || temp2 == nullptr){
                    break;
                }
            }
        }
        //Check for smaller row
        else if(temp1->row < temp2->row){
            result.insert(temp1->data, temp1->row, temp1->column);
            temp1 = temp1->next;
        }
        else if(temp2->row < temp1->row){
            result.insert(temp2->data, temp2->row, temp2->column);
            temp2 = temp2->next;
        }

    }
    while(temp1 != nullptr && temp2 == nullptr){
        result.insert(temp1->data, temp1->row, temp1->column);
        temp1 = temp1->next;
    }
    while(temp2 != nullptr && temp1 == nullptr){
        result.insert(temp2->data, temp2->row, temp2->column);
        temp2 = temp2->next;
    }

    return result;
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