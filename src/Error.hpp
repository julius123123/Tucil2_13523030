#ifndef ERROR_H
#define ERROR_H
#include <iostream>
#include <vector>
// #include <opencv2/opencv.hpp>
using namespace std;

class Error{
    public:
        Error();
        Error(Error&);
        ~Error();

        static double average(vector<double> data);
        static double average(unsigned char* data, int n, int channel);
        static double average(unsigned char* data, int i_col, int channel, int row0, int col0, int row1, int col1);

        static double sigma(vector<double> data);
        static double variance(vector<double> data);
        static double variance(unsigned char* data, int n, int channel);
        static double variance(unsigned char* data, int i_col, int channel, int row0, int col0, int row1, int col1);

        static double MAD(vector<double> data);
        static double MAD(unsigned char* data, int n, int channel);
        static double MAD(unsigned char* data, int i_col, int channel, int row0, int col0, int row1, int col1);
        static double MPD(vector<double> data);
        static double MPD(unsigned char* data, int i_col, int channel, int row0, int col0, int row1, int col1);
        static double entropy(vector<double> data);
        static double entropy(unsigned char* data, int n, int channel);
        static double entropy(unsigned char* data, int i_col, int channel, int row0, int col0, int row1, int col1);


};
#endif