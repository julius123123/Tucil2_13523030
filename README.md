#  QuadTree Image Compression

Program ini merupakan cara mengompresi gambar menggunakan pendekatan Divide and Conquer dengan struktur data QuadTree. Gambar akan direpresentasikan sebagai blok-blok persegi dan hanya akan dipecah jika nilai error (varian warna) lebih tinggi dari ambang batas tertentu atau jumlah pixel dibawah batas minimum. Proses ini menghasilkan versi gambar dengan warna yang lebih seragam.

---

##  Requirements

Program ini dibuat menggunakan bahasa **C++** dan membutuhkan beberapa dependensi:

- C++17
- OpenCV4
- BoostFileSystem

##  Kompilasi Linux
```bash
g++ -o src/main src/main3.cpp src/Error.cpp src/QuadTree.cpp src/QuadNode.cpp  `pkg-config --cflags --libs opencv4` -lboost_system -lboost_filesystem`
```
##  Kompilasi Windows
```bash
g++ -std=c++17 -O2 -o QuadTreeWindows.exe ^
    src/main.cpp src/QuadTree.cpp src/QuadNode.cpp src/Error.cpp ^
    -I"path_to_vcpkg/installed/x64-mingw-dynamic/include" ^
    -L"path_to_vcpkg/installed/x64-mingw-dynamic/lib" ^
    -lopencv_core -lopencv_imgcodecs -lopencv_highgui ^
    -lboost_filesystem -lboost_system
```
##  Menjalankan Linux
Jalankan file main pada bin
#Cara Menjalankan
Jalankan kode hasil kompilasi. Program akan meminta input
1. Nama file gambar (path absolut)
2. Metode perhitungan error (1 - 4)
3. Threshold error
4. Jumlah minimum blok
5. Nama file output (path absolut)


Dibuat oleh Julius Arthur - 13523030
