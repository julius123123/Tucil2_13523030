#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP
#include "QuadNode.hpp"
#include "Error.hpp"

class QuadTree{
public:
    QuadNode* root;
    int min_block;
    double error_thres;
    int rows;
    int cols;
    uchar* image;
    int error_calc;
    int depth = 0;
    int leaf = 0;
    QuadTree(int row0, int row1, int col0, int col1, uchar* image,int rows,int cols, int min_block, double error, int error_calc);
    ~QuadTree();
    void BuildTree(QuadNode* node);
};
#endif