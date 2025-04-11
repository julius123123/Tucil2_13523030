#  QuadTree Image Compression

Program ini merupakan cara mengompresi gambar menggunakan pendekatan Divide and Conquer dengan struktur data QuadTree. Gambar akan direpresentasikan sebagai blok-blok persegi dan hanya akan dipecah jika nilai error (varian warna) lebih tinggi dari ambang batas tertentu atau jumlah pixel dibawah batas minimum. Proses ini menghasilkan versi gambar dengan warna yang lebih seragam.

--

##  Requirements

Program ini dibuat menggunakan bahasa **C++** dan membutuhkan beberapa dependensi:

- C++17

##  Kompilasi Linux
```bash
 g++ -o main main3.cpp Error.cpp QuadTree.cpp QuadNode.cpp
```
##  Kompilasi Windows
```bash
g++ -o main_windows main3.cpp QuadNode.cpp QuadTree.cpp Error.cpp
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
