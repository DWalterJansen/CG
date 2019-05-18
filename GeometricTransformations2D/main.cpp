///////////////////////////////////////////////////////////////////
//  Trabalho prático de Computação Gráfica.
//  Programadores: Iarah Almeida Gonçalvez; David Walter Jansen
///////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include "colormod.h"

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
                    std::cout << "\tInvalid Choice. Enter a, b, c or d" << std::endl;
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
}
