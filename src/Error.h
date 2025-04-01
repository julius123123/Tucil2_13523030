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

        static double sigma(vector<double> data);
        static double variance(vector<double> data);
        static double MAD(vector<double> data);
        static double MPD(vector<double> data);
        static double entropy(vector<double> data);


};
#endif