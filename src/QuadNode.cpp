#include "QuadNode.hpp"

QuadNode::QuadNode(int row0, int row1, int col0, int col1, uchar* image){
    this->row0 = row0;
    this->row1 = row1;
    this->col0 = col0;
    this->col1 = col1;
    this->image = image;
    for (int i = 0; i < 4; i++){
        child[i] = nullptr;
    }
}

QuadNode::QuadNode(QuadNode& other){
    this->row0 = other.row0;
    this->row1 = other.row1;
    this->col0 = other.col0;
    this->col1 = other.col1;
    this->image = other.image;
}

void QuadNode::operator=(QuadNode& other){
    this->row0 = other.row0;
    this->row1 = other.row1;
    this->col0 = other.col0;
    this->col1 = other.col1;
    this->image = other.image;
}

void QuadNode::split(){
    std::cout<<"split"<<std::endl;
    int row_mid = row0 +  (row1 - row0)/2;
    int col_mid = col0 + (col1-col0) / 2;
    
    child[0] = new QuadNode(row0, row_mid, col0, col_mid, image);
    child[1] = new QuadNode(row0, row_mid, col_mid, col1, image);
    child[2] = new QuadNode(row_mid, row1, col0, col_mid, image);
    child[3] = new QuadNode(row_mid, row1, col_mid, col1, image);
}

QuadNode::~QuadNode(){
    for (int i =0; i < 4; i++){
        delete child[i];
        child[i] = nullptr;
    }
}