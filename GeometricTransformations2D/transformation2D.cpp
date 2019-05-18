/*****************************************************************************/
/* Arquivo: transformation2D.h
 * Descrição: Definição de um TAD para transformações lineares em 2D
 * Data criação: 16/05/2019
 * Última modificação: 17/05/2019
 * Programador: David Walter Jansen, Iarah Gonçalves de Almeida
 *****************************************************************************/
#include "transformation2D.h"
#include <iostream>
#include <cmath>

#define PI 3.14159265
double cosseno(double theta){
    return std::cos(theta * PI / 180.0 );
}

double seno(double theta){
    return std::sin(theta * PI / 180.0 );
}

//translation
wMatrix Transformation2D::getTranslation(double tx, double ty){
    double t[3][3] = {{1, 0, tx},{0, 1, ty}, {0, 0, 1}};
    return wMatrix(t);
}

//rotation
wMatrix Transformation2D::getRotation(double theta){
    double r[3][3] = {{cosseno(theta), -seno(theta), 0},{seno(theta), cosseno(theta), 0}, {0, 0, 1}};
    return wMatrix(r);
}

//scale
wMatrix Transformation2D::getScale(double sx, double sy){
    double s[3][3] = {{sx, 0, 0},{0, sy, 0}, {0, 0, 1}};
    return wMatrix(s);
}

//shear
wMatrix Transformation2D::getSher(double shx, double shy){
    double sh[3][3] = {{1, shx, 0},{shy, 1, 0}, {0, 0, 1}};
    return wMatrix(sh);
}

void Transformation2D::composition(const wMatrix &m){
    //utiliza a matriz base, e multiplica à esquerda a matriz de transformação
    wMatrix internal = mt;
    wMatrix external = m;
    mt = external * internal;
}
