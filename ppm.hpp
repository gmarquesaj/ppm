#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
 
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;
using std::to_string;
using std::vector;
class ppm
{
public:
    vector<unsigned char> pxl;
    int w, h, cores;
    char code[3];
    ppm(int w, int h);
    ppm(string caminho);
    ~ppm();
    void salvar(string caminho);
    void print();
    void teste();
    void get(unsigned char & r,unsigned char & g,unsigned char & b,int x,int y);
    void set(unsigned char r,unsigned char g,unsigned char b,int x,int y);

};
