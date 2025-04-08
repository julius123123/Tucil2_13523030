#ifndef ERROR_H
#define ERROR_H
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;

class Error{
    public:
        Error();
        Error(Error&);
        ~Error();

        static double average(vector<double> data);
        static double average(uchar* data, int n, int channel);
        static double average(uchar* data, int i_col, int channel, int row0, int col0, int row1, int col1);

        static double sigma(vector<double> data);
        static double variance(vector<double> data);
        static double variance(uchar* data, int n, int channel);
        static double variance(uchar* data, int i_col, int channel, int row0, int col0, int row1, int col1);

        static double MAD(vector<double> data);
        static double MAD(uchar* data, int n, int channel);
        static double MAD(uchar* data, int i_col, int channel, int row0, int col0, int row1, int col1);
        static double MPD(vector<double> data);
        static double MPD(uchar* data, int i_col, int channel, int row0, int col0, int row1, int col1);
        static double entropy(vector<double> data);
        static double entropy(uchar* data, int n, int channel);
        static double entropy(uchar* data, int i_col, int channel, int row0, int col0, int row1, int col1);


};
#endif