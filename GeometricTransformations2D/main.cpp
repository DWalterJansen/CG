///////////////////////////////////////////////////////////////////
//  Trabalho prático de Computação Gráfica.
//  Programadores: Iarah Almeida Gonçalvez; David Walter Jansen
///////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include "transformation2D.h"
#include "colormod.h"
/*
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

void option1(){
    clear_screen();
    std::cout << "\tGeometric Transformations\n\n" << std::endl;
    std::cout << " 1 - Read image" << std::endl;
    std::cout << "\t File name to open (.ppm): ";
    std::string file_name;
    std::cin >> file_name;
    std::cin.sync();
}

void option2(){
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
                    std::cout << "\t\t You choose Translation";
                    break;

                case 'b':
                    std::cout << "\t\t You choose Rotation";
                    break;

                case 'c':
                    std::cout << "\t\t You choose Scale";
                    break;

                case 'd':
                    std::cout << "\t\t You choose Shear";
                    break;

                default:
                    std::cout << red << "\tInvalid Choice. Enter a, b, c or d" << def <<std::endl;
                    break;
            }
        }while(!('a' <= code && code <= 'd'));
    }
}

void option3(){
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
                break;

            case 'b':
                std::cout << "\t\t You choose Bilinear";
                break;

            default:
                std::cout << red <<"Invalid Choice. Enter a or b" << def << std::endl;
                break;
        }
    }while(!('a' <= code && code <= 'b'));
}

void option4(){
    clear_screen();
    std::cout << "\t Geometric Transformations\n\n" << std::endl;
    std::cout << " 4 - Save result image" << std::endl;
    std::cout << "\t File name to save (.ppm): " << std::endl;
    std::string file_name;
    std::cin >> file_name;
    std::cin.sync();
}

int main()
{
    clear_screen();
    while(true){
        std::cout << "\t Geometric Transformations\n\n" << std::endl;
        std::cout << " 1 - Read image" << std::endl;
        std::cout << " 2 - Make transformations" << std::endl;
        std::cout << " 3 - Type of sampling" << std::endl;
        std::cout << " 4 - Save result image" << std::endl;
        std::cout << " 5 - Exit" << std::endl;

        char option;
        do{
            std::cout << "\nSelect an option by number: ";
            std::cin >> option;
            // Discards the input buffer
            std::cin.sync();

            switch (option){
                case '1':
                    std::cout << "You choose 1";
                    option1();
                    break;

                case '2':
                    std::cout << "You choose 2";
                    option2();
                    break;

                case '3':
                    std::cout << "You choose 3";
                    option3();
                    break;

                case '4':
                    std::cout << "You choose 4";
                    option4();
                    break;

                case '5':
                    return 0;
                    break;

                default:
                    std::cout << red <<"Invalid Choice. Enter a number between 1 and 5" << def << std::endl;
                    break;
            }
        }while(!('0' < option && option < '6'));

        char answer;
        do{
            std::cout << " Perform new operation (y /n)?";
            std::cin >> answer;
            std::cin.sync();
        }while(answer != 'N' && answer != 'n' && answer != 'Y' && answer != 'y');

        if (answer == 'N' or answer == 'n'){
            break;
        }
    }

    return 0;
}*/


///teste das funções de leitura e escrita de imagens no formato PPM
/*
#include <stdio.h>
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
    S[0][0]=sx;
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
}
*/

///Teste Composição
/*int main(){
    Transformation2D t2d;
    t2d.composition(t2d.getScale(2,2));
    t2d.composition(t2d.getSher(3,3));
    t2d.getMT().Print();
    return 0;
}
*/
