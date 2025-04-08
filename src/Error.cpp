#include "Error.hpp"
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

double Error::average(uchar* data, int i_col, int channel, int row0, int col0, int row1, int col1){
    long double res = 0;
    int idx;
    double value;
    double x;
    int n = 0;
    for (int i = row0; i <= row1; i++){
        for (int j = col0; j <= col1; j++){
            n++;
            idx = (i * i_col + j) * 3;
            value = static_cast<double>(data[idx + channel]); 
            res += value;
            // cout<<res<<endl;
        }
    }
    // cout<<"x: "<<x;
    // cout<<"res "<<res<<endl;
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
    for(int i = 0; i < n * 3; i+=3){
        double val = static_cast<double>(data[i + channel]);
        res += pow((val - avg), 2);
    }

    return res / n;
}

double Error::variance(uchar* data, int i_col, int channel, int row0, int col0, int row1, int col1){
    double res = 0;
    double val;
    double avg = average(data, i_col, channel, row0, col0, row1, col1);
    int idx = 0;
    int n  = 0;
    for (int i = row0; i <= row1; i++){
        for (int j = col0; j <= col1; j++){
            n++;
            idx = (i * i_col + j) * 3;
            val = static_cast<double>(data[idx + channel]);
            res += pow((val - avg), 2);
        }
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

double Error::MAD(uchar* data, int n, int channel){
    double avg = average(data, n, channel);
    double res = 0;

    for (int i = 0; i < n*3; i+=3){
        double val = static_cast<double>(data[i + channel]);
        res += fabs((val - avg));
    }

    return res / n;
}

double Error::MAD(uchar* data, int i_col, int channel, int row0, int col0, int row1, int col1){
    double avg = average(data, i_col, channel, row0, col0, row1, col1);
    double res = 0;
    int n = 0;
    int idx;
    for (int i = row0; i <= row1; i++){
        for (int j = col0; j <= col1; j++){
            n++;
            idx = (i * i_col + j) * 3;
            double val = static_cast<double>(data[idx + channel]);
            res += fabs((val - avg));
        }
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

double Error::MPD(uchar* data, int i_col, int channel, int row0, int col0, int row1, int col1){
    double max = data[0];
    double min = data[0];
    int n =0;
    int idx;

    for (int i = row0; i <= row1; i++){
        for (int j = col0; j <= col1; j++){
            n++;
            idx = (i * i_col + j) * 3;
            double val = static_cast<double>(data[idx + channel]);
            if (val> max){
                max =val;
            }

            if (val < min){
                min = val;
            }
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


double Error::entropy(uchar* data, int n, int channel){
    std::vector<double> table(255, 0);
    double prob;
    double res;

    for (int i = 0; i < n*3; i+=3){
        double val = static_cast<double>(data[i + channel]);
        table[val] += 1;
    }

    for (int i = 0; i < n*3; i+=3){
        double val = static_cast<double>(data[i + channel]);
        prob = table[val] / n;
        res += prob * log2(prob);
    }

    return ((-1) * res);
}

double Error::entropy(uchar* data, int i_col, int channel, int row0, int col0, int row1, int col1){
    std::vector<double> table(256, 0);
    double prob;
    double res = 0;
    int idx;
    int n = 0;
    
    for (int i = row0; i <= row1; i++){
        for (int j = col0; j <= col1; j++){
            n++;
            idx = (i * i_col + j) * 3;
            int val = static_cast<int>(data[idx + channel]);
            table[val] += 1;
        }
    }
    
    for (int i = row0; i <= row1; i++){
        for (int j = col0; j <= col1; j++){
            idx = (i * i_col + j) * 3;
            int val = static_cast<int>(data[idx + channel]);
            prob = table[val] / n;
            res += prob * log2(prob);
        }
    }
    
    return ((-1) * res);
}