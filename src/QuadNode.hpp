#ifndef QUAD_NODE_HPP
#define QUAD_NODE_HPP
#include <opencv2/opencv.hpp>

class QuadNode{
public:
    int row0;
    int row1;
    int col0;
    int col1;
    int depth;
    QuadNode* child[4];

    QuadNode(int row0, int row1, int col0, int col1, int depth);
    QuadNode(QuadNode&);
    ~QuadNode();
    void operator=(QuadNode&);
    void split();

};

#endif