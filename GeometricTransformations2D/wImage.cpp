#include "wImage.h"
#include <cstdlib>
wImage::wImage()
{
    width = 0;
    height = 0;
}

void wImage::read(const string& arq)
{
    //string type, width_str, height_str, max_num_str;
    string type, ncols_str, nlins_str, max_num_str;
    string R_str, G_str, B_str;

    ifstream file(arq.c_str());
    if (!file)
    {
        cout<<"Cannot open file: "<<arq<<endl;
        return;
    }

    /// lendo o arquivo de imagem ppm
    /// tipo de imagem
    file>>type;
    if ( type != "P3" ){
        cout<<"ERROR: The Input file is not a ASCII PPM (P3)!!!";
        file.close();
        return;
    }

    pixels.clear();

    file>>ncols_str>>nlins_str>>max_num_str;
    width = atoi(ncols_str.c_str());
    height = atoi( nlins_str.c_str());

    RGB aux;
    for(unsigned int i=0; i<width*height; i++)
    {
        file>>R_str>>G_str>>B_str;
        aux.R = atoi(R_str.c_str());
        aux.G = atoi(G_str.c_str());
        aux.B = atoi(B_str.c_str());
        pixels.push_back(aux);
    }

    file.close();
}


void wImage::write(const string& arq) const
{
    char tmp[100];
    ofstream file(arq.c_str(), std::ofstream::out);
    if (!file)
    {
        cout<<"Cannot write file: "<<arq<<endl;
        return;
    }

    file<<"P3\n"
        <<width<<" "<<height<<endl
        <<255<<endl;
    RGB aux;
    for(unsigned int i=0;i<width*height; i++)
    {
        aux = pixels[i];
        sprintf(tmp, "%03d %03d %03d", aux.R, aux.G, aux.B);
        if ((i+1)%width!=0)
            file<<tmp<<"\t\t";
        else
            file<<tmp<<"\n";
    }

    file.close();

}
/// retorna o pixel RGB da posição (linha, coluna)
RGB& wImage::get(unsigned int linha, unsigned int coluna)
{
    return pixels[width*linha+coluna];
}


unsigned int wImage::getWidth() const{
    return width;
}

unsigned int wImage::getHeight() const{
    return height;
}

/// imagem de valores maximos = brancos
void wImage::whites(int w, int h)
{
    width = w;
    height = h;
    RGB aux(255, 255, 255);
    pixels.clear();
    for( unsigned int i=0; i<width*height; i++)
        pixels.push_back(aux);
}

/// imagem de valores minimos = pretos
void wImage::zeros(int w, int h)
{
    width = w;
    height = h;
    RGB aux;
    pixels.clear();
    for( unsigned int i=0; i<width*height; i++)
        pixels.push_back(aux);
}
