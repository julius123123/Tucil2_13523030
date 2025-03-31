#ifndef ERROR_H
#define ERROR_H
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;

class Error{
    protected:
        double* data;
    public:
        Error();
        Error(Error&);
        ~Error();

        double average(vector<double> data);
        double sigma(vector<double> data);
        double variance(vector<double> data);
        double MAD(vector<double> data);
        double MPD(vector<double> data);
        double entropy(vector<double> data);


};
#endif