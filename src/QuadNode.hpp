#ifndef QUAD_NODE_HPP
#define QUAD_NODE_HPP
#include <opencv2/opencv.hpp>

class QuadNode{
public:
    int row0;
    int row1;
    int col0;
    int col1;
    uchar* image;
    QuadNode* child[4];

    QuadNode(int row0, int row1, int col0, int col1, uchar* image);
    QuadNode(QuadNode&);
    ~QuadNode();
    void operator=(QuadNode&);
    void split();

};

#endif