///////////////////////////////////////////////////////////////////
//  Trabalho prático de Computação Gráfica.
//  Programadores: Iarah Almeida Gonçalvez; David Walter Jansen
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

    std::cout << "\n Give a number of transformations: ";
    int number;
    std::cin >> number;
    std::cin.sync();

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
}

void option4(Imagem &Img, Imagem &Img_dest, Transformation2D &t2d){
    clear_screen();
    std::cout << "\t Geometric Transformations\n\n" << std::endl;
    std::cout << " 4 - Perform transformation and save new image" << std::endl;
    std::cout << "\t File name to save (.ppm): ";
    std::string file_name;
    std::cin >> file_name;
    file_name = file_name + ".ppm";
    std::cin.sync();

    /*
        ESCREVER FUNÇÃO DE SALVAR
    */
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
                    option4(Img, Img_dest, t2d);
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


///teste das funções de leitura e escrita de imagens no formato PPM
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "wMatrix.h"


int main(int argc, char *argv[])
{
    Imagem Img, Img_dest;
    Le_Imagem(&Img, "car_raw.ppm" );
    float sx = 0.7, sy = 0.7;

    int altura = (int)(sx*Img.vertical),
        largura = (int)(sy*Img.horizontal);
    strcpy(Img_dest.tipo,Img.tipo);
    Img_dest.horizontal = largura;
    Img_dest.vertical = altura;
    Img_dest.pixel = alocapixels(largura*3, altura);

    // imagem não foi lida!!!
    if ( Img.pixel == NULL )
        exit(0);



    wMatrix S;
    S.Eye();
    S[0][0] = sx;
    S[1][1] = sy;
    S = S.Inv();

    int i, j;
    for(i=0; i< Img_dest.horizontal; i++) // é usado 3*horizontal porque a imagem é colorida
        for( j=0; j<Img_dest.vertical; j++ )
        {
            wVector P, Q;
            P[0] = i;
            P[1] = j;
            P[2] = 1;
            Q = S*P;
            Img_dest.pixel[i*3][j] = Img.pixel[int(Q[0]+0.5)*3][int(Q[1]+0.5)];  //banda red
            Img_dest.pixel[i*3+1][j] = Img.pixel[int(Q[0]+0.5)*3+1][int(Q[1]+0.5)];  //banda green
            Img_dest.pixel[i*3+2][j] = Img.pixel[int(Q[0]+0.5)*3+2][int(Q[1]+0.5)];  //banda blue
        }
    Escreve_Imagem(Img_dest, "car_reduzido.ppm" );
    system("PAUSE");
    return 0;
}*/


///Teste Composição
/*int main(){
    Transformation2D t2d;
    t2d.composition(t2d.getScale(2,2));
    t2d.composition(t2d.getSher(3,3));
    t2d.getMT().Print();
    return 0;
}
*/
