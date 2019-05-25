///////////////////////////////////////////////////////////////////
//  Trabalho prático de Computação Gráfica.
//  Programadores: Iarah Almeida Gonçalvez; David Walter Jansen
///////////////////////////////////////////////////////////////////
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "transformation2D.h"
#include "colormod.h"
#include "image.h"

Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier def(Color::FG_DEFAULT);

void clear_screen(){
    #ifdef _WIN32
        std::system("cls");
    #else
        // Assume POSIX
        std::system ("clear");
    #endif
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool is_float(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    int accumulator = 0;
    while (it != s.end()){
        if( *it == '.' && accumulator == 0)
            accumulator++;
        else{
            if(!std::isdigit(*it) || accumulator == 2)
                break;
        }
        ++it;
    }
    return !s.empty() && it == s.end();
}

char linear_interpolation(char src1, char src2, int beginX, int x, int endX){
    int aux1 = (int) src1;
    int aux2 = (int) src2;

    if((endX - beginX) == 0){
        return src1;
    }
    return (char) ((endX-x)/(endX-beginX))*aux1 + ((x-beginX)/(endX-beginX))*aux2;
}

void option1(std::string &nameImage, Imagem &Img, Transformation2D &t2d){
    clear_screen();
    std::cout << "\tGeometric Transformations\n\n" << std::endl;
    std::cout << " 1 - Read image" << std::endl;
    std::cout << "\t File name to open (.ppm): ";
    std::cin >> nameImage;
    nameImage = nameImage + ".ppm";
    std::cin.sync();
    t2d.reset();
    Le_Imagem(&Img, nameImage.c_str());

    std::string imgType (Img.tipo);

    if(imgType.compare(0, 2,"P3") == 0 || imgType.compare(0, 2,"P6") == 0){
        t2d.setColorful(true);
    }
    else{
        t2d.setColorful(false);
    }

    t2d.setNewHeight(Img.vertical);
    t2d.setNewWidth(Img.horizontal);
}

void option2(Transformation2D &t2d){
    clear_screen();
    std::cout << "\tGeometric Transformations\n\n" << std::endl;
    std::cout << " 2 - Make transformations" << std::endl;
    std::cout << "\t a - Translation" << std::endl;
    std::cout << "\t b - Rotation" << std::endl;
    std::cout << "\t c - Scale" << std::endl;
    std::cout << "\t d - Shear" << std::endl;

    int number;
    std::string s;
    do{
        std::cout << "\n Give a number of transformations: ";
        std::cin >> s;
        std::cin.sync();
    }while(!is_number(s));
    number = std::stoi(s);


    std::cout << "\n For each transformation, enter the letter code... " << std::endl;
    char code;
    for(int i = 0; i < number; ++i){
        do{
            std::cout << blue <<"\n+ Code for " << i+1 << "th tranformation: " << def;
            std::cin >> code;
            std::cin.sync();
            switch (code){
                case 'a':
                    std::cout << "\t\t You've chosen Translation" << std::endl;
                    double tx;
                    double ty;
                    std::cout << "\t\t Translation in x: ";
                    std::cin >> tx;
                    std::cin.sync();
                    std::cout << "\t\t Translation in y: ";
                    std::cin >> ty;
                    std::cin.sync();
                    t2d.composition(t2d.getTranslation(tx, ty));
                    t2d.compositionReal(t2d.getTranslation(tx, ty), 't');
                    std::cout << blue;
                    t2d.getMT_Show().Print("\t\t");
                    std::cout << def;
                    break;

                case 'b':
                    std::cout << "\t You've chosen Rotation" << std::endl;
                    double theta;
                    do{
                        std::cout << "\t Enter the angle value (0.0 - 360.0): ";
                        std::cin >> theta;
                        std::cin.sync();
                    }while(!(0 <= theta && theta <= 360.0));
                    t2d.composition(t2d.getRotation(theta));
                    t2d.compositionReal(t2d.getRotation(theta), 'r');
                    std::cout << blue;
                    t2d.getMT_Show().Print("\t\t");
                    std::cout << def;
                    break;

                case 'c':
                    std::cout << "\t You've chosen Scale" << std::endl;
                    double sx;
                    double sy;
                    std::cout << "\t Scale in x: ";
                    std::cin >> sx;
                    std::cin.sync();
                    std::cout << "\t Scale in y: ";
                    std::cin >> sy;
                    std::cin.sync();
                    t2d.composition(t2d.getScale(sx, sy));
                    t2d.compositionReal(t2d.getScale(sx, sy), 's');
                    std::cout << blue;
                    t2d.getMT_Show().Print("\t\t");
                    std::cout << def;
                    break;

                case 'd':
                    std::cout << "\t You've chosen Shear" << std::endl;
                    double shx;
                    double shy;
                    std::cout << "\t Sher in x: ";
                    std::cin >> shx;
                    std::cin.sync();
                    std::cout << "\t Sher in y: ";
                    std::cin >> shy;
                    std::cin.sync();
                    t2d.composition(t2d.getSher(shx, shy));
                    t2d.compositionReal(t2d.getSher(shx, shy), 'c');
                    std::cout << blue;
                    t2d.getMT_Show().Print("\t\t");
                    std::cout << def;
                    break;

                default:
                    std::cout << red << "\tInvalid Choice. Enter a, b, c or d" << def <<std::endl;
                    break;
            }
        }while(!('a' <= code && code <= 'd'));
    }
    std::cout << "\n Press any key to return to the home menu...";
    std::cin.get();
    std::cin.sync();
}

void option3(std::string &typeSimpling){
    clear_screen();
    std::cout << "\t Geometric Transformations\n\n" << std::endl;
    std::cout << " 3 - Sampling Type" << std::endl;
    std::cout << "\t a - Ponctual" << std::endl;
    std::cout << "\t b - Bilinear" << std::endl;

    char code;
    do{
        std::cout << "\n Enter the letter code for the sampling type: ";
        std::cin >> code;
        std::cin.sync();

        switch (code){
            case 'a':
                std::cout << "\t\t You've chosen Punctual";
                typeSimpling = "Ponctual";
                break;

            case 'b':
                std::cout << "\t\t You've chosen Bilinear";
                typeSimpling = "Bilinear";
                break;

            default:
                std::cout << red << "Invalid Choice. Enter a or b" << def << std::endl;
                break;
        }
    }while(!('a' <= code && code <= 'b'));
    std::cout << "\n Press any key to return to the home menu...";
    std::cin.get();
    std::cin.sync();
}

void option4(Imagem &Img, Imagem &Img_dest, Transformation2D &t2d, std::string &typeSimpling){
    clear_screen();
    std::cout << "\t Geometric Transformations\n\n" << std::endl;
    std::cout << " 4 - Perform transformation and save new image" << std::endl;
    std::cout << "\t File name to save (.ppm): ";
    std::string file_name;
    std::cin >> file_name;
    file_name = file_name + ".ppm";
    std::cin.sync();

    // Aloca espaço para a matriz resultado
    Img_dest.pixel = alocapixels(t2d.getNewWidth()*3, t2d.getNewHeight());
    strcpy(Img_dest.tipo,Img.tipo);
    Img_dest.horizontal = t2d.getNewWidth();
    Img_dest.vertical = t2d.getNewHeight();

    // imagem não foi lida!!!
    if ( Img.pixel == NULL )
        exit(0);

    wMatrix T;
    T = t2d.getMT_Real();
    T = T.Inv();
    if( typeSimpling.compare("Ponctual") == 0){
        std::cout << "Ponctual";
        std::cin.get();
        int i, j;
        for(i=0; i< Img_dest.horizontal; i++){
            for( j=0; j< Img_dest.vertical; j++ ){
                wVector P, Q;
                P[0] = i;
                P[1] = j;
                P[2] = 1;
                Q = T*P;
                int x;
                int y;

                x = int(Q[0]+0.5)*3;
                y = int(Q[1]+0.5);
                if (-1 < x && x < Img.horizontal*3 && -1 < y && y < Img.vertical){
                    Img_dest.pixel[i*3][j] = Img.pixel[int(Q[0]+0.5)*3][int(Q[1]+0.5)];  //banda red
                }
                x = int(Q[0]+0.5)*3+1;
                if (-1 < x && x < Img.horizontal*3 && -1 < y && y < Img.vertical){
                    Img_dest.pixel[i*3+1][j] = Img.pixel[int(Q[0]+0.5)*3+1][int(Q[1]+0.5)];  //banda green
                }
                x = int(Q[0]+0.5)*3+2;
                if (-1 < x && x < Img.horizontal*3 && -1 < y && y < Img.vertical){
                    Img_dest.pixel[i*3+2][j] = Img.pixel[int(Q[0]+0.5)*3+2][int(Q[1]+0.5)];  //banda blue
                }
            }
        }
    }
    else if (typeSimpling.compare("Bilinear") == 0){
        std::cout << "Bilinear";
        std::cin.get();
        int i, j;
        char a, b;
        bool existA;
        bool existB;
        for(i=0; i< Img_dest.horizontal; i++){
            for( j=0; j< Img_dest.vertical; j++ ){
                wVector P, Q;
                P[0] = i;
                P[1] = j;
                P[2] = 1;
                Q = T*P;
                int x1, x2, y1, y2; //coords

                int c; // colors RGB
                for(c=0; c < 3; c++){
                    existA = false;
                    existB = false;
                    x1 = (int) floor(Q[0])*3 + c;
                    x2 = (int) ceil(Q[0])*3 + c;
                    y1 = (int) floor(Q[1]);
                    y2 = (int) ceil(Q[1]);

                    if(-1 < x1 && x1 < Img.horizontal*3 && -1 < y2 && y2 < Img.vertical){
                        if(-1 < x2 && x2 < Img.horizontal*3 && -1 < y2 && y2 < Img.vertical){
                            a = linear_interpolation(Img.pixel[x1][y2], Img.pixel[x2][y2], floor(Q[0]), Q[0], ceil(Q[0]));
                        }
                        else{
                            a = Img.pixel[x1][y2];
                        }
                        existA = true;
                    }
                    else{
                        if(-1 < x2 && x2 < Img.horizontal*3 && -1 < y2 && y2 < Img.vertical){
                            a = Img.pixel[x2][y2];
                            existA = true;
                        }
                    }

                    if(-1 < x1 && x1 < Img.horizontal*3 && -1 < y1 && y1 < Img.vertical){
                        if(-1 < x2 && x2 < Img.horizontal*3 && -1 < y1 && y1 < Img.vertical){
                            b = linear_interpolation(Img.pixel[x1][y1], Img.pixel[x2][y1], floor(Q[0]), Q[0], ceil(Q[0]));
                        }
                        else{
                            b = Img.pixel[x1][y1];
                        }
                        existB = true;
                    }
                    else{
                        if(-1 < x2 && x2 < Img.horizontal*3 && -1 < y1 && y1 < Img.vertical){
                            b = Img.pixel[x2][y1];
                            existB = true;
                        }
                    }

                    if(existA && existB){
                        Img_dest.pixel[i*3 + c][j] = linear_interpolation(a, b, floor(Q[1]), Q[1], ceil(Q[1]));
                    }
                    else if(existA){
                        Img_dest.pixel[i*3 + c][j] = a;
                    }
                    else if(existB){
                        Img_dest.pixel[i*3 + c][j] = b;
                    }
                }
            }
        }
    }
    Escreve_Imagem(Img_dest, file_name.c_str());
    std::cout << "\n Press any key to return to the home menu...";
    std::cin.get();
    std::cin.sync();
}

int main()
{
    Imagem Img, Img_dest;
    std::string nameImage;
    std::string typeSimpling;
    Transformation2D t2d;
    bool readImage = false;
    while(true){
        clear_screen();
        std::cout << "\t Geometric Transformations\n\n" << std::endl;
        std::cout << " 1 - Read image (Reset transformation matrix)";
        if(!nameImage.empty()){std::cout << "\n\tCurrent image: " << blue << nameImage << def;}
        std:: cout << std::endl;
        std::cout << " 2 - Make transformations" << std::endl;
        std::cout <<"\tCurrent transformation matrix:" << std::endl << blue;
        t2d.getMT_Show().Print("\t");
        std::cout << def;
        std::cout << " 3 - Sampling Type";
        if(!typeSimpling.empty()){std::cout << "\n\tCurrent simpling: " << blue << typeSimpling << def;}
        std:: cout << std::endl;
        std::cout << " 4 - Perform transformation and save new image" << std::endl;
        std::cout << " 5 - Exit" << std::endl;

        char option;
        do{
            std::cout << "\n Select an option by number: ";
            std::cin >> option;
            // Sincroniza buffer
            std::cin.sync();

            switch (option){
                case '1':
                    std::cout << "You've chosen 1";
                    option1(nameImage, Img, t2d);
                    readImage = true;
                    break;

                case '2':
                    if(!readImage){
                        std::cout << green << " Please, read an image first!" << def;
                        std::cin.get();
                        std::cin.sync();
                    }
                    else{
                        std::cout << "You've chosen 2";
                        option2(t2d);
                    }
                    break;

                case '3':
                    std::cout << "You've chosen 3";
                    option3(typeSimpling);
                    break;

                case '4':
                    if(!readImage){
                        std::cout << green << " Please, read an image first!" << def;
                        std::cin.get();
                        std::cin.sync();
                    }
                    else if(typeSimpling.empty()){
                        std::cout << green << " Please, select a simpling type!" << def;
                        std::cin.get();
                        std::cin.sync();
                    }
                    else{
                        std::cout << "You've chosen 4";
                        option4(Img, Img_dest, t2d, typeSimpling);
                    }
                    break;

                case '5':
                    return 0;
                    break;

                default:
                    std::cout << red << "Invalid Choice. Enter a number between 1 and 5" << def << std::endl;
                    break;
            }
        }while(!('0' < option && option < '6'));
    }

    return 0;
}
