#include "QuadTree.hpp"

QuadTree::QuadTree(int row0, int row1, int col0, int col1, uchar* image, int rows, int cols, int min, double error, int e){
    root = new QuadNode(row0, row1, col0, col1, 0);
    this->image = new uchar[rows * cols * 3];
    memcpy(this->image, image, rows * cols * 3);
    this->rows = rows;
    this->cols = cols;
    this->min_block = min;
    this->error_thres = error;
    this->error_calc = e;
    this->ori = new uchar[rows * cols *3];
    memcpy(this->ori, image, rows*cols * 3);
}

QuadTree::~QuadTree(){
    delete[] image;
    delete[] ori;
}

void QuadTree::BuildTree(QuadNode* node){
    if (node->depth > depth){
        depth = node->depth;
    }
    double varB, varG, varR;
    if (error_calc == 1){
        varB= Error::variance(image, cols, 0, node->row0, node->col0, node->row1, node->col1);
        varG = Error::variance(image, cols, 1, node->row0, node->col0, node->row1, node->col1);
        varR = Error::variance(image, cols, 2, node->row0, node->col0, node->row1, node->col1);
    }
    
    else if (error_calc == 2){
        varB = Error::MAD(image, cols, 0, node->row0, node->col0, node->row1, node->col1);
        varG = Error::MAD(image, cols, 1, node->row0, node->col0, node->row1, node->col1);
        varR = Error::MAD(image, cols, 2, node->row0, node->col0, node->row1, node->col1);
    }
    
    else if (error_calc == 3){
        varB = Error::MPD(image, cols, 0, node->row0, node->col0, node->row1, node->col1);
        varG = Error::MPD(image, cols, 1, node->row0, node->col0, node->row1, node->col1);
        varR = Error::MPD(image, cols, 2, node->row0, node->col0, node->row1, node->col1);
    }
    
    else if (error_calc == 4){
        varB = Error::entropy(image, cols, 0, node->row0, node->col0, node->row1, node->col1);
        varG = Error::entropy(image, cols, 1, node->row0, node->col0, node->row1, node->col1);
        varR = Error::entropy(image, cols, 2, node->row0, node->col0, node->row1, node->col1);
    }
    
    double var = (varB + varG + varR)/3;
    int size = (node->row1 - node->row0) * (node->col1 - node->col0);
    bool valid = false;

    if (var > error_thres){
        if (size > min_block && size/4 >= min_block){
            valid = true;
            node->split();
            leaf += 4;
            for (int i = 0; i < 4; i++){
                BuildTree(node->child[i]);
            }
        }
    }

    if (!valid){
        double avgB = Error::average(image, cols, 0, node->row0, node->col0, node->row1, node->col1);
        double avgG = Error::average(image, cols, 1, node->row0, node->col0, node->row1, node->col1);
        double avgR = Error::average(image, cols, 2, node->row0, node->col0, node->row1, node->col1);
        int idx;
        
        for (int i = node->row0; i <= node->row1; i++){
            for (int j = node->col0; j <= node->col1; j++){
                idx = (i * cols + j) * 3;
                    image[idx+0] = avgB;
                    image[idx+1] = avgG;
                    image[idx+2] = avgR;
            }
        }
    }
}



void QuadTree::CreateGif(int depth_target, uchar* gif, QuadNode* node){
    bool isLeaf = true;
    if (node->depth < depth_target){
        if (node->child[0] != nullptr){
            isLeaf = false;
            CreateGif(depth_target, gif, node->child[0]);
            CreateGif(depth_target, gif, node->child[1]);
            CreateGif(depth_target, gif, node->child[2]);
            CreateGif(depth_target, gif, node->child[3]);
        }
    }

    if (isLeaf){
        double avgB = Error::average(ori, cols, 0, node->row0, node->col0, node->row1, node->col1);
        double avgG = Error::average(ori, cols, 1, node->row0, node->col0, node->row1, node->col1);
        double avgR = Error::average(ori, cols, 2, node->row0, node->col0, node->row1, node->col1);
        int idx;
        
        for (int i = node->row0; i < node->row1; i++){
            for (int j = node->col0; j <= node->col1; j++){
                idx = (i * cols + j) * 3;
                gif[idx+0] = avgB;
                gif[idx+1] = avgG;
                gif[idx+2] = avgR;
            }
        }
    }       
}
