#define GIF_STATIC
#include "QuadNode.hpp"
#include "QuadTree.hpp"
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <sys/stat.h>
#include "lib/gif.h"
using namespace std;

namespace fs = boost::filesystem;

long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

bool  isFileValid(string& name){
    ifstream f(name.c_str());
    return f.good();
}

bool isExtension(string name){
    string ext;
    ext = name.substr(name.find_last_of(".") + 1);
    return (ext == "jpg" || ext == "jpeg" || ext == "png");
}

string getFileInput(){
    string name;
    cin>>name;
    while (!isFileValid(name) || !isExtension(name)){
        std::cout<<"\nFile tidak valid\n";
        std::cout<<"File: ";
        cin>>name;
    }
    return name;
}

string getFileOutput(){
    string name;
    cin>>name;
    while (!isExtension(name)){
        std::cout<<"\nEkstensi tidak valid\n";
        std::cout<<"File:";
        cin>>name;
    }
    return name;
}

double validasi_error(){
    double input;
    cin>>input;

    while (input < 0){
        std::cout<<"Threshold harus lebih dari 0\n";
        std::cout<<"Thershold: ";
        cin>>input;
    }
    return input;
}

int validasi_min(){
    int input;
    cin>>input;

    while (input < 0){
        std::cout<<"Jumlah minimum block harus lebih dari 0\n";
        std::cout<<"Min block: ";
        cin>>input;
    }
    return input;
}

int validasi_method(){
    int method;
    cin>>method;

    while (method < 0 || method > 4){
        std::cout<<"Pilih method 1 - 4\n";
        std::cout<<"Method: ";
        cin>>method;
    }
    return method;
}


void make_gif(QuadTree& tree, const std::string& gif_output, int width, int height) {
    GifWriter writer;
    if (!GifBegin(&writer, gif_output.c_str(), width, height, 10)) {
        std::cerr << "Gagal membuat GIF: " << gif_output << std::endl;
        return;
    }

    for (int i = 0; i <= tree.depth; ++i) {
        // Buat buffer mentah dari QuadTree
        uchar* raw_bgr = new uchar[tree.rows * tree.cols * 3];
        tree.CreateGif(i, raw_bgr, tree.root);

        // Buat cv::Mat dari buffer (jangan lupa clone agar tidak ubah data asli)
        cv::Mat bgr_img(tree.rows, tree.cols, CV_8UC3, raw_bgr);
        cv::Mat rgb_img;
        cv::cvtColor(bgr_img, rgb_img, cv::COLOR_BGR2RGB);

        // Pastikan buffer datanya continuous dan pointer aman
        if (!rgb_img.isContinuous()) {
            rgb_img = rgb_img.clone();
        }
        cv::Mat test_img(height, width, CV_8UC3, bgr_img.data);
        cv::imwrite("check_frame_" + std::to_string(i) + ".png", test_img);

        // Simpan frame ke GIF
        GifWriteFrame(&writer, rgb_img.data, width, height, (i == tree.depth) ? 100 : 10);

        delete[] raw_bgr;
    }

    GifEnd(&writer);
}


int main(){
    double size1; 
    double size2;
    string fn, on, gif_output;
    int min, error_cal;
    double error_thres;

    //Directory
    fs::path cwd_full(fs::current_path());
    fs::path gif_path = cwd_full / "bin" / "gif";
    
    //Clear gif_path
    fs::remove_all(gif_path);
    fs::create_directories(gif_path);

    
    // Input file
    cout<<"File (absolut): ";
    fn = getFileInput();
    cout<<endl;

    //Error calc
    cout<<"Pilih perhitungan error (masukkan nomor): "<<endl;
    cout<<"1. Variance\n2. Mean absolute deviation\n3. Max Pixel Difference\n4. Entropy"<<endl;
    error_cal = validasi_method();
    cout<<endl;

    //Ambang batas
    cout<<"Error: ";
    error_thres = validasi_error();
    cout<<endl;

    //Minimal blok
    cout<<"Min_block: ";
    min = validasi_min();
    cout<<endl;

    // Output file
    cout<<"Output gambar (absolut dan dengan ekstensi): ";
    on = getFileOutput();
    cout<<endl;

    // Output gif
    cout<<"Output gif (absolut): ";
    cin>>gif_output;
    cout<<endl;
    
    // Buat gambar
    cv::Mat image;
    image = cv::imread(fn);
    // Pointer rgb
    uchar* p = image.ptr<uchar>(0);
    auto t1 = chrono::high_resolution_clock::now();//waktu

    // Buat quadtree dari awal
    QuadTree tree = QuadTree(0, image.rows, 0, image.cols, p, image.rows, image.cols, min, error_thres, error_cal);
    tree.BuildTree(tree.root);

    //Simpan hasil kompresi
    cv::Mat image2(image.rows, image.cols, CV_8UC3);
    memcpy(image2.data, tree.image, image.rows * image.cols * 3);
    cv::imwrite(on, image2);
    //Simpan gambar tiap kedalaman;
    // make_gif(tree, gif_path);
    
    // make_gif(tree, gif_output, image2.cols, image2.rows);

    // Hitung persentase kompresi
    size1 = static_cast<double>(GetFileSize(fn));
    size2 = static_cast<double>(GetFileSize(on));
    double compress_persen = 100 * (1 - (size2/size1));
    
    // Hitung durasi
    auto t2 = chrono::high_resolution_clock::now();
    auto ms_int = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
    
    // Output
    cout<<"Waktu eksekusi: "<<ms_int.count()<<" ms\n";
    cout<<"Ukuran awal: "<<size1<<" bytes.\n";
    cout<<"Ukuran akhir: "<<size2<< " bytes.\n";
    cout<<"Persentase kompresi: "<<compress_persen<<"%\n";
    cout<<"Kedalaman pohon: "<<tree.depth<<"\n";
    cout<<"Banyak simpul: "<<tree.leaf<<"\n";
   
    return 0;
}