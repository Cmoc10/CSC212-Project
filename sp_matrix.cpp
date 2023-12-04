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
                outf << ",";
            }
        }
        outf << "\n";
    }
    outf.close();
}

void SpMatrix::to_csv_matrix(std::string fname, std::vector<std::vector<int>> matrix){
    std::ofstream outf(fname);
    for(int i=0; i<matrix.size(); i++){
        for(int j=0; j<matrix[i].size(); j++){
            outf << matrix[i][j] << ",";
        }
        outf << "\n";
    }
    outf.close();
}

SpMatrix SpMatrix::multiply(SpMatrix& matrix2){
    SpMatrix result; 
    Node* matrix2temp = matrix2.head;
    if(columns != matrix2.rows){
        std::cout<<"Can not multiply; unequal columns and rows\n";
        return result;
    }

    SpMatrix newMatrix2;

    while(matrix2temp != nullptr){
        newMatrix2.insert(matrix2temp->data, matrix2temp->column, matrix2temp->row);
        matrix2temp = matrix2temp->next;
    }


    std::cout << "Rows: " << newMatrix2.rows << "\n" << "Columns: " << newMatrix2.columns << "\n";
    Node* temps = newMatrix2.head;
    for(int i=0; i<newMatrix2.rows; i++){
        for(int j=0; j<newMatrix2.columns; j++){
            if(i == temps->row && j == temps->column){
                std::cout << temps->data << " ";
                if(temps->next != nullptr){
                    temps = temps->next;
                }
            }
            else{
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }



    Node* temp = head;
    Node* temp2 = newMatrix2.head;
    Node* temptemp;
    int matrix1Num;
    int matrix2Num;
    int data2 = 0;
    int counter = 1;
    for(int matrix2row = 0; matrix2row < newMatrix2.rows; matrix2row++){
        temp = head;
        for(int i = 0; i < rows; i++){ //goes through each row of matrix one
            temp2 = newMatrix2.head;
            //std::cout<<temp2->data<<std::endl;
            for(int j = 0; j < columns; j++){ // During each row will then go thorugh each column so it can multiple
                if(i == temp->row && j == temp->column){
                    matrix1Num = temp->data;
                    if(temp->next != nullptr){
                        temp = temp->next;
                    }
                }
                else{
                    matrix1Num = 0;
                }
                if(matrix2row == temp2->row && j == temp2->column){
                    matrix2Num = temp2->data;
                    if(temp2->next != nullptr){
                        temp2 = temp2->next;
                    }
                }
                else{
                    matrix2Num = 0;
                }
                std::cout<< "data2 = " << data2 << " + "<< matrix1Num<< "*"<<matrix2Num<< " which = "<< matrix1Num*matrix2Num<<std::endl;
                data2 += (matrix1Num*matrix2Num);
                std::cout<<"new data 2:"<< data2<<std::endl;
                
            }
            if(counter != matrix2row){
                temptemp = temp2;
            }
            result.insert(data2, i, matrix2row);
            data2 = 0;
        }
        newMatrix2.head = temp2;
    }

    std::cout << "Result\nRows: " << result.rows << "\n" << "Columns: " << result.columns << "\n";
    temps = result.head;
    for(int i=0; i<result.rows; i++){
        for(int j=0; j<result.columns; j++){
            if(i == temps->row && j == temps->column){
                std::cout << temps->data << " ";
                if(temps->next != nullptr){
                    temps = temps->next;
                }
            }
            else{
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }

    return result;
}

topThree SpMatrix::highest(){
    topThree result;
    SpMatrix tempMatrix;
    Node* temp = head;
    while(temp != nullptr){ //flipping
        tempMatrix.insert(temp->data, temp->column, temp->row);
        temp = temp->next;
    }

    double average;
    std::vector<double> averages;
    temp = tempMatrix.head;
    int counter = 0;
    for(int i = 0; i < tempMatrix.rows; i++){
        average = 0;
        counter = 0;
        for(int j = 0; j < tempMatrix.columns; j++){
            if(i == temp->row && j == temp->column){
                average += temp->data;
                counter++;
                if(temp->next != nullptr){
                    temp = temp->next;
                }
            }
        }
        average =  average / counter;
        averages.push_back(average);
    }
    auto highestAverage = std::max_element(averages.begin(), averages.end());
    int index = std::distance(averages.begin(), highestAverage);
    result.first = index;
    result.highestscore = averages[index];
    //std::cout<<index<<std::endl;
    averages[index] = 0;

    highestAverage = std::max_element(averages.begin(), averages.end());
    index = std::distance(averages.begin(), highestAverage);
    result.second = index;
    averages[index] = 0;

    highestAverage = std::max_element(averages.begin(), averages.end());
    index = std::distance(averages.begin(), highestAverage);
    result.third = index;
    averages[index] = 0;

    return result;
}

topThree SpMatrix::highest(int col){
    topThree result;
    SpMatrix tempMatrix;
    Node* temp = head;
    while(temp != nullptr){ //flipping
        tempMatrix.insert(temp->data, temp->column, temp->row);
        temp = temp->next;
    }

    double average;
    std::vector<double> averages;
    temp = tempMatrix.head;
    int counter = 0;
    for(int i = 0; i < tempMatrix.rows; i++){
        average = 0;
        counter = 0;
        for(int j = 0; j < tempMatrix.columns; j++){
            if(i == temp->row && j == temp->column){
                average += temp->data;
                counter++;
                if(temp->next != nullptr){
                    temp = temp->next;
                }
            }
        }
        average =  average / counter;
        averages.push_back(average);
    }
    for(int i = 0; i<averages.size(); i++){
        //std::cout<<averages[i]<<", ";
    }
    //std::cout<<std::endl;
    averages[col] = 0;
    auto highestAverage = std::max_element(averages.begin(), averages.end());
    int index = std::distance(averages.begin(), highestAverage);
    result.first = index;
    //std::cout<<index<<std::endl;
    averages[index] = 0;

    highestAverage = std::max_element(averages.begin(), averages.end());
    index = std::distance(averages.begin(), highestAverage);
    result.second = index;
    //std::cout<<index<<std::endl;
    averages[index] = 0;

    highestAverage = std::max_element(averages.begin(), averages.end());
    index = std::distance(averages.begin(), highestAverage);
    result.third = index;
    //std::cout<<index<<std::endl;
    averages[index] = 0;

    return result;
}

int SpMatrix::lowest(){
    SpMatrix tempMatrix;
    Node* temp = head;
    while(temp != nullptr){ //flipping
        tempMatrix.insert(temp->data, temp->column, temp->row);
        temp = temp->next;
    }

    double average;
    std::vector<double> averages;
    temp = tempMatrix.head;
    int counter = 0;
    for(int i = 0; i < tempMatrix.rows; i++){
        average = 0;
        counter = 0;
        for(int j = 0; j < tempMatrix.columns; j++){
            if(i == temp->row && j == temp->column){
                average += temp->data;
                counter++;
                if(temp->next != nullptr){
                    temp = temp->next;
                }
            }
        }
        average =  average / counter;
        averages.push_back(average);
    }
    
    auto highestAverage = std::min_element(averages.begin(), averages.end());
    int index = std::distance(averages.begin(), highestAverage);
    return index;
}


topThree SpMatrix::make_recs(int col){
    topThree result;
    SpMatrix tempMatrix;
    Node* temp = head;
    while(temp != nullptr){ //flipping
        tempMatrix.insert(temp->data, temp->column, temp->row);
        temp = temp->next;
    }
    SpMatrix goodRating;
    temp = tempMatrix.head;
    //tempMatrix.print();
    for(int k = 0; k<tempMatrix.rows; k++){
        for(int j = 0; j < tempMatrix.columns; j++){
            if(k == temp->row && j == temp->column){
                //std::cout<<"helpppppppppp   ";
                if(temp->data >= 3 && k==col){
                    
                    Node* temps = tempMatrix.head;
                    for(int i = 0; i<tempMatrix.rows; i++){
                        for(int l = 0; l < tempMatrix.columns; l++){
                            if(i == temps->row && l == temps->column){ //Inserting the whole column where >= 3
                                if(j == l){
                                    goodRating.insert(temps->data, i, j);
                                }
                                if(temps->next != nullptr){
                                    temps = temps->next;
                                }
                            }
                        }
                    }


                }
                if(temp->next != nullptr){
                    temp = temp->next;
                }
                
            }
            
        }
    }

    //goodRating.print();

    temp = goodRating.head;

    SpMatrix newGoodRating;
    while(temp != nullptr){ //flipping
        newGoodRating.insert(temp->data, temp->column, temp->row);
        temp = temp->next;
    }

    //newGoodRating.print();
    result = newGoodRating.highest(col);
    return result;

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