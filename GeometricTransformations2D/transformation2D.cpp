/*****************************************************************************/
/* Arquivo: transformation2D.h
 * Descri��o: Defini��o de um TAD para transforma��es lineares em 2D
 * Data cria��o: 16/05/2019
 * �ltima modifica��o: 17/05/2019
 * Programador: David Walter Jansen, Iarah Gon�alves de Almeida
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
    //utiliza a matriz base, e multiplica � esquerda a matriz de transforma��o
    wMatrix internal = mt_show;
    wMatrix external = m;
    mt_show = external * internal;
}

void Transformation2D::compositionReal(const wMatrix &m){
    // points like: (x, y, 1)
    wVector p1(0, 0, 1);
    wVector p2(0, initHeight, 1);
    wVector p3(initWidth, 0, 1);
    wVector p4(initWidth, initHeight, 1);

    double minX, maxX, minY, maxY;
    wMatrix aux = m;

    // Aplica a transforma��o sobre os 4 pontos das quinas da imagem
    p1 = aux * p1;
    p2 = aux * p2;
    p3 = aux * p3;
    p4 = aux * p4;

    // Calcula as posi��es minimas e m�ximas das coordenadas
    maxX = std::max(std::max(p1[0], p2[0]), std::max(p3[0], p4[0]));
    maxY = std::max(std::max(p1[1], p2[1]), std::max(p3[1], p4[1]));
    minX = std::min(std::min(p1[0], p2[0]), std::min(p3[0], p4[0]));
    minY = std::min(std::min(p1[1], p2[1]), std::min(p3[1], p4[1]));

    // Calcula o novo tamanho da imagem
    newHeight = std::ceil(abs(maxY-minY));
    newWidth = std::ceil(abs(maxX-minX));

    // Matriz de transla��o para corre��o do posicionamento.
    wMatrix t;
    t.Eye();
    t[0][2] = -minX;
    t[1][2] = -minY;

    //Atualiza matriz real
    mt_real = aux;
    mt_real = t * mt_real;
}

void Transformation2D::resetMT_Real(){
    mt_real = mt_real.Eye();
}

void Transformation2D::reset(){
    mt_show = mt_show.Eye();
    mt_real = mt_real.Eye();
    initWidth = 0;
    initHeight = 0;
    newWidth = 0;
    newHeight = 0;
    colorful = false;
}
