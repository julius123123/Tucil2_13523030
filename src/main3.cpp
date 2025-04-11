#define STB_IMAGE_IMPLEMENTATION
#define GIF_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "QuadNode.hpp"
#include "QuadTree.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "stb_image.h"
#include "lib/gif.h"
using namespace std;

namespace fs = std::filesystem;

long GetFileSize(std::string filename)
{
    return static_cast<long>(fs::file_size(filename));

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


void make_gif(QuadTree& tree, const std::string& gif_output) {
    GifWriter writer;

    GifBegin(&writer, gif_output.c_str(), tree.cols, tree.rows, 100, 8, false);
    for (int i = 0; i < tree.depth; ++i) {
        unsigned char* raw_rgb = new unsigned char[tree.cols * tree.rows * 3];
        tree.CreateGif(i, raw_rgb, tree.root);

        GifWriteFrame(&writer, raw_rgb, tree.cols, tree.rows,100, 8, false);

        delete[] raw_rgb;

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
    
    // Load gambar
    int width, height, channels;
    unsigned char* p = stbi_load(fn.c_str(), &width, &height, &channels, 3);

    if (!p) {
        std::cerr << "Gagal memuat gambar: " << fn << std::endl;
        return 1;
    }

    
    auto t1 = chrono::high_resolution_clock::now();//waktu

    // Buat quadtree dari awal
    QuadTree tree = QuadTree(0, height, 0, width, p, height, width, min, error_thres, error_cal);
    tree.BuildTree(tree.root);

    // Simpan gambar
    stbi_write_jpg(on.c_str(), width, height, 3, tree.image, width * 3);
   
    //Simpan gambar tiap kedalaman;
    make_gif(tree, gif_output);
    
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