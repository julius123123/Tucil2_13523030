#include "Error.h"
#include <math.h>

double Error::average(vector<double> data){
    int n = data.size();
    double res = 0;

    for (int i = 0; i < n; i++){
        res += data[i];
    }
    
    return res/n;
}


double Error::average(uchar* data, int n, int channel){
    double res = 0;

    for (int i = 0; i < n * 3; i+=3){
        double value = static_cast<double>(data[i + channel]); 
        res += value;
    }
    return (res/n);
}


double Error::sigma(vector<double> data){
    int n = data.size();
    double res = 0;

    for (int i = 0; i < n; i++){
        res += data[i];
    }

    return res;
}

double Error::variance(vector<double> data){
    int n = data.size();
    double res = 0;

    double avg = average(data);
    for(int i = 0; i < n; i++){
        res += pow((data[i] - avg), 2);
    }

    return res / n;
}


double Error::variance(uchar* data, int n, int channel){
    double res = 0;

    double avg = average(data, n, channel);
    for(int i = 0; i < n * 3; i++){
        double val = static_cast<double>(data[i + channel]);
        res += pow((val - avg), 2);
    }

    return res / n;
}


double Error::MAD(vector<double> data){
    int n = data.size();
    double avg = average(data);
    double res = 0;

    for (int i = 0; i < n; i++){
        res += fabs((data[i] - avg));
    }

    return res / n;
}

double Error::MPD(vector<double> data){
    double max = data[0];
    double min = data[0];

    for (int i = 0; i < data.size(); i++){
        if (data[i] > max){
            max = data[i];
        }

        if (data[i] < min){
            min = data[i];
        }
    }

    return (max - min);
}

double Error::entropy(vector<double> data){
    std::vector<double> table(255, 0);
    double prob;
    double res;

    int n = data.size();
    for (int i = 0; i < n; i++){
        table[data[i]] += 1;
    }

    for (int i = 0; i < n; i++){
        prob = table[data[i]] / n;
        res += prob * log2(prob);
    }

    return ((-1) * res);
}