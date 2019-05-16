#ifndef WIMAGE_H
#define WIMAGE_H

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class RGB{
public:
    /// atributos
    unsigned char R, G, B;

    /// construtor default
    RGB():R(0), G(0), B(0){}
    RGB(unsigned int r, unsigned int g, unsigned int b):R(r), G(g), B(b){}
};

class wImage{
    private:
        vector<RGB> pixels;
        unsigned int width, height;
    public:
        wImage();
        /// retorna uma referencia para o pixel da posição (linha l e coluna c)
        RGB& get(unsigned int l, unsigned int c);
        unsigned getWidth() const;
        unsigned getHeight() const;
        void zeros(int w, int h);
        void whites(int w, int h);
        void read(const string&);
        void write(const string&) const;
};

#endif // WIMAGE_H
