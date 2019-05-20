///////////////////////////////////////////////////////////////////
//  Trabalho pr�tico de Computa��o Gr�fica.
//  Programadores: Iarah Almeida Gon�alvez; David Walter Jansen
///////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include "transformation2D.h"
#include "colormod.h"
#include "image.h"

Color::Modifier red(Color::FG_RED);
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

void option1(std::string &nameImage){
    clear_screen();
    std::cout << "\tGeometric Transformations\n\n" << std::endl;
    std::cout << " 1 - Read image" << std::endl;
    std::cout << "\t File name to open (.ppm): ";
    std::cin >> nameImage;
    nameImage = nameImage + ".ppm";
    std::cin.sync();
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
                    std::cout << "\t\t You choose Translation" << std::endl;
                    double tx;
                    double ty;
                    std::cout << "\t\t Translation in x: ";
                    std::cin >> tx;
                    std::cin.sync();
                    std::cout << "\t\t Translation in y: ";
                    std::cin >> ty;
                    std::cin.sync();
                    std::cout << blue;
                    t2d.composition(t2d.getTranslation(tx, ty));
                    t2d.getMT().Print("\t\t");
                    std::cout << def;
                    break;

                case 'b':
                    std::cout << "\t You choose Rotation" << std::endl;
                    double theta;
                    do{
                        std::cout << "\t Enter the value of the angle (0.0 - 360.0): ";
                        std::cin >> theta;
                        std::cin.sync();
                    }while(!(0 <= theta && theta <= 360.0));
                    t2d.composition(t2d.getRotation(theta));
                    std::cout << blue;
                    t2d.getMT().Print("\t\t");
                    std::cout << def;
                    break;

                case 'c':
                    std::cout << "\t You choose Scale" << std::endl;
                    double sx;
                    double sy;
                    std::cout << "\t Scale in x: ";
                    std::cin >> sx;
                    std::cin.sync();
                    std::cout << "\t Scale in y: ";
                    std::cin >> sy;
                    std::cin.sync();
                    std::cout << blue;
                    t2d.composition(t2d.getScale(sx, sy));
                    t2d.getMT().Print("\t\t");
                    std::cout << def;
                    break;

                case 'd':
                    std::cout << "\t You choose Shear" << std::endl;
                    double shx;
                    double shy;
                    std::cout << "\t Sher in x: ";
                    std::cin >> shx;
                    std::cin.sync();
                    std::cout << "\t Sher in y: ";
                    std::cin >> shy;
                    std::cin.sync();
                    std::cout << blue;
                    t2d.composition(t2d.getSher(shx, shy));
                    t2d.getMT().Print("\t\t");
                    std::cout << def;
                    break;

                default:
                    std::cout << red << "\tInvalid Choice. Enter a, b, c or d" << def <<std::endl;
                    break;
            }
        }while(!('a' <= code && code <= 'd'));
        std::cout << "\n Press any key to return to the home menu...";
        std::cin.get();
        std::cin.sync();
    }
}

void option3(std::string &typeSimpling){
    clear_screen();
    std::cout << "\t Geometric Transformations\n\n" << std::endl;
    std::cout << " 3 - Type of sampling" << std::endl;
    std::cout << "\t a - Pontual" << std::endl;
    std::cout << "\t b - Bilinear" << std::endl;

    char code;
    do{
        std::cout << "\n Enter the letter code for the type of sampling: ";
        std::cin >> code;
        std::cin.sync();

        switch (code){
            case 'a':
                std::cout << "\t\t You choose Punctual";
                typeSimpling = "Punctual";
                break;

            case 'b':
                std::cout << "\t\t You choose Bilinear";
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

void option4(Imagem &Img, Imagem &Img_dest, Transformation2D &t2d, std::string &nameImage){
    clear_screen();
    std::cout << "\t Geometric Transformations\n\n" << std::endl;
    std::cout << " 4 - Perform transformation and save new image" << std::endl;
    std::cout << "\t File name to save (.ppm): ";
    std::string file_name;
    std::cin >> file_name;
    file_name = file_name + ".ppm";
    std::cin.sync();

    ///Parte Semelhante ao que Wagner Fez
    Le_Imagem(&Img, nameImage.c_str());
    strcpy(Img_dest.tipo,Img.tipo);

    ///Calcula novo tamanho
    t2d.mapDimension(Img.horizontal, Img.vertical);
    Img_dest.horizontal = t2d.getNewWidth();
    Img_dest.vertical = t2d.getNewHeight();
    Img_dest.pixel = alocapixels(3*t2d.getNewWidth(), t2d.getNewHeight());

    ///Rela��o entre sistemas de matriz e euclidiano;
    ///Ida
    wMatrix m2e = t2d.getScale(-1, 1);
    m2e = t2d.getTranslation(-Img.vertical, 0) * m2e;

    ///Volta
    wMatrix e2m = t2d.getTranslation(Img.vertical, 0);
    e2m = t2d.getScale(-1, 1) * e2m;


    // imagem n�o foi lida!!!
    if ( Img.pixel == NULL )
        exit(0);

    wMatrix S;
    S = e2m * S * m2e;
    S = t2d.getMT().Inv();
    Escreve_Imagem(Img_dest, file_name.c_str());
}

int main()
{
    Imagem Img, Img_dest;
    std::string nameImage;
    std::string typeSimpling;
    Transformation2D t2d;
    while(true){
        clear_screen();
        std::cout << "\t Geometric Transformations\n\n" << std::endl;
        std::cout << " 1 - Read image";
        if(!nameImage.empty()){std::cout << "\n\tCurrent image: " << blue << nameImage << def;}
        std:: cout << std::endl;
        std::cout << " 2 - Make transformations" << std::endl;
        std::cout <<"\tCurrent transformation matrix:" << std::endl << blue;
        t2d.getMT().Print("\t");
        std::cout << def;
        std::cout << " 3 - Type of sampling";
        if(!typeSimpling.empty()){std::cout << "\n\tCurrent simpling: " << blue << typeSimpling << def;}
        std:: cout << std::endl;
        std::cout << " 4 - Perform transformation and save new image" << std::endl;
        std::cout << " 5 - Exit" << std::endl;

        char option;
        do{
            std::cout << "\n Select an option by number: ";
            std::cin >> option;
            // Discards the input buffer
            std::cin.sync();

            switch (option){
                case '1':
                    std::cout << "You choose 1";
                    option1(nameImage);
                    break;

                case '2':
                    std::cout << "You choose 2";
                    option2(t2d);
                    break;

                case '3':
                    std::cout << "You choose 3";
                    option3(typeSimpling);
                    break;

                case '4':
                    std::cout << "You choose 4";
                    option4(Img, Img_dest, t2d, nameImage);
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
