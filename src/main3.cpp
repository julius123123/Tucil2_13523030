#include "QuadNode.hpp"
#include "QuadTree.hpp"
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <fstream>
#include <sys/stat.h>

long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

using namespace std;

int main(){
    string fn, on;
    int min, error_thres, error_cal;
    // Input file
    cout<<"File (absolut): ";
    cin>>fn;
    cout<<endl;
    //Error calc
    cout<<"Pilih perhitungan error (masukkan nomor): "<<endl;
    cout<<"1. Variance\n2. Mean absolute deviation\n3. Max Pixel Difference\n4. Entropy"<<endl;
    cin>>error_cal;
    cout<<endl;
    //Ambang batas
    cout<<"Error: ";
    cin>>error_thres;
    cout<<endl;
    //Minimal blok
    cout<<"Min_block: ";
    cin>>min;
    cout<<endl;
    cout<<"Output (absolut dan dengan ekstensi): ";
    cin>>on;
    cout<<endl;
    cv::Mat image;
    image = cv::imread(fn);
    uchar* p = image.ptr<uchar>(0);
    auto t1 = chrono::high_resolution_clock::now();
    QuadTree tree = QuadTree(0, image.rows, 0, image.cols, p, image.rows, image.cols, min, error_thres, error_cal);
    tree.BuildTree(tree.root);
    cv::Mat image2(image.rows, image.cols, CV_8UC3);
    memcpy(image2.data, tree.image, image.rows * image.cols * 3);
    // cv::Mat image2(image.rows, image.cols, true ? CV_8UC3 : CV_8UC1, tree.image);
    
    // cv::imshow("Ori", ori);
    // cv::imshow("Hasil", image2);

    cv::imwrite(on, image2);
    auto t2 = chrono::high_resolution_clock::now();
    auto ms_int = chrono::duration_cast<chrono::milliseconds>(t2 - t1);

    cout<<"Waktu eksekusi: "<<ms_int.count()<<" ms\n";

    double size1 = static_cast<double>(GetFileSize(fn));
    double size2 = static_cast<double>(GetFileSize(on));
    double compress_persen = 100 * (size2/size1);
    cout<<"Ukuran awal: "<<size1<<" bytes.\n";
    cout<<"Ukuran akhir: "<<size2<< " bytes.\n";
    cout<<"Persentase kompresi: "<<compress_persen<<"%\n";
    cout<<"Kedalaman pohon: "<<tree.depth<<"\n";
    cout<<"Banyak simpul: "<<tree.leaf<<"\n";
    
    cout<<on<<endl;
    
    return 0;
}