#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP
#include "QuadNode.hpp"
#include "Error.hpp"
#include "string.h"
#include <cstdint>


class QuadTree{
public:
    QuadNode* root;
    int min_block;
    double error_thres;
    int rows;
    int cols;
    unsigned char* image;
    unsigned char* ori;
    int error_calc;
    int depth = 0;
    int leaf = 0;
    QuadTree(int row0, int row1, int col0, int col1, unsigned char* image,int rows,int cols, int min_block, double error, int error_calc);
    ~QuadTree();
    void BuildTree(QuadNode* node);
    void CreateGif(int depth, unsigned char* gif, QuadNode* node);
};
#endif