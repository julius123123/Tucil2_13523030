#include "QuadTree.hpp"

int QuadTree::rows = 0;
int QuadTree::cols = 0;
int QuadTree::min_block = 0;
double QuadTree::error_thres = 0;
QuadTree::QuadTree(int row0, int row1, int col0, int col1, uchar* image){
    root = new QuadNode(row0, row1, col0, col1, image);
}

QuadTree::~QuadTree(){
    delete root;
}

void QuadTree::BuildTree(QuadNode* node){
    std::cout<<"BT"<<std::endl;
    double varB = Error::variance(node->image, cols, 0, node->row0, node->col0, node->row1, node->col1);
    double varG = Error::variance(node->image, cols, 1, node->row0, node->col0, node->row1, node->col1);
    double varR = Error::variance(node->image, cols, 2, node->row0, node->col0, node->row1, node->col1);

    double var = (varB + varG + varR)/3;
    int size = (node->row1 - node->row0) * QuadTree::cols + node->col1 - node->col0;
    bool valid = false;

    if (var > QuadTree::error_thres){
        if (size > QuadTree::min_block && size/4 >= QuadTree::min_block){
            valid = true;
            node->split();
            for (int i = 0; i < 4; i++){
                std::cout<<i<<" row: "<<node->child[i]->row0<<std::endl;
                BuildTree(node->child[i]);
            }
        }
    }

    if (!valid){
        double avgB = Error::average(node->image, QuadTree::cols, 0, node->row0, node->col0, node->row1, node->col1);
        double avgG = Error::average(node->image, QuadTree::cols, 1, node->row0, node->col0, node->row1, node->col1);
        double avgR = Error::average(node->image, QuadTree::cols, 2, node->row0, node->col0, node->row1, node->col1);
        int idx;
        
        for (int i = node->row0; i <= node->row1; i++){
            for (int j = node->col0; j <= node->col1; j++){
                idx = (i * QuadTree::cols + j) * 3;
                    node->image[idx+0] = avgB;
                    node->image[idx+1] = avgG;
                    node->image[idx+2] = avgR;
            }
        }
    }
}