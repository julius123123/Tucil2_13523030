#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP
#include "QuadNode.hpp"
#include "Error.hpp"

class QuadTree{
public:
    QuadNode* root;
    static int min_block;
    static double error_thres;
    static int rows;
    static int cols;
    QuadTree(int row0, int row1, int col0, int col1, uchar* image);
    ~QuadTree();
    void BuildTree(QuadNode* node);
};
#endif