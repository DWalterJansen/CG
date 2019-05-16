///////////////////////////////////////////////////////////////////
//  Trabalho prático de Computação Gráfica.
//  Programadores: Iarah Almeida Gonçalvez; David Walter Jansen
///////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

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
    std::cout << "\t File name to open (.ppm): " << std::endl;
    std::string file_name;
    std::cin >> file_name;
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

    std::cout << "\n For each transformation, enter the letter code... " << std::endl;
    char code;
    for(int i = 0; i < number; ++i){
        std::cout << "\n\t + Code for " << i+1 << "th tranformation: ";
        std::cin >> code;
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
                std::cout << "Invalid Choice. Enter a, b, c or d" << std::endl;
                break;
        }
    }
}

void option3(){
    clear_screen();
    std::cout << "\t Geometric Transformations\n\n" << std::endl;
    std::cout << " 3 - Type of sampling" << std::endl;
    std::cout << "\t a - Pontual" << std::endl;
    std::cout << "\t b - Bilinear" << std::endl;

    std::cout << "\n Enter the letter code for the type of sampling> " << std::endl;
    char code;
    std::cin >> code;

    switch (code){
            case 'a':
                std::cout << "\t\t You choose Punctual";
                break;

            case 'b':
                std::cout << "\t\t You choose Bilinear";
                break;

            default:
                std::cout << "Invalid Choice. Enter a or b" << std::endl;
                break;
        }

}

void option4(){
    std::cout << "\t Geometric Transformations\n\n" << std::endl;
    std::cout << " 4 - Save result image" << std::endl;
    std::cout << "\t File name to save (.ppm): " << std::endl;
    std::string file_name;
    std::cin >> file_name;
}

int main()
{
    while(true){
        std::cout << "\t Geometric Transformations\n\n" << std::endl;
        std::cout << " 1 - Read image" << std::endl;
        std::cout << " 2 - Make transformations" << std::endl;
        std::cout << " 3 - Type of sampling" << std::endl;
        std::cout << " 4 - Save result image" << std::endl;

        std::cout << "\nSelect an option by number: ";
        unsigned int option;
        std::cin >> option;

        switch (option){
            case 1:
                std::cout << "You choose 1";
                option1();
                break;

            case 2:
                std::cout << "You choose 2";
                option2();
                break;

            case 3:
                std::cout << "You choose 3";
                break;

            case 4:
                std::cout << "You choose 4";
                break;

            default:
                std::cout << "Invalid Choice. Enter a no between 1 and 5" << std::endl;
                break;
        }
        break;
    }
    return 0;
}
