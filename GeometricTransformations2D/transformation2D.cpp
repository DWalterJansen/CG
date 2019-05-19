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

//Calculate new dimension of transformed image
void Transformation2D::mapDimension(int width, int height){
    // points like: (x, y, 1)
    wVector leftUp(0, height-1, 1);
    wVector rightUp(width-1, height-1, 1);
    wVector leftDw(0, 0, 1);
    wVector rightDw(width, 0, 1);

    // new points
    wVector TleftUp = mt * leftUp;
    wVector TrightUp = mt * rightUp;
    wVector TleftDw = mt * leftDw;
    wVector TrightDw = mt *rightDw;

    double minX, maxX, minY, maxY;
    minX = std::min(std::min(TleftUp[0], TrightUp[0]), std::min(TleftDw[0], TrightDw[0]));
    maxX = std::max(std::max(TleftUp[0], TrightUp[0]), std::max(TleftDw[0], TrightDw[0]));
    minY = std::min(std::min(TleftUp[1], TrightUp[1]), std::min(TleftDw[1], TrightDw[1]));
    maxY = std::max(std::max(TleftUp[1], TrightUp[1]), std::max(TleftDw[1], TrightDw[1]));

    // Retirar depois esse comentátio
    // Lógica usada: Estabelecendo a diferença máxima entre o X e Y, é possível saber o
    //  tamanho da nova imagem.
    newWidth = abs(maxX - minX) + 1;
    newHeight = abs(maxY - minY) + 1;

    // Retirar depois esse comentátio
    //Com base na transformação da imagem, é possível fazer uma comparação entre
    // o ponto de inicio da imagem base e da imagem transformada.
    //Isso permite gerar fatores de translação para que a nova imagem aparece completamente.
    correctionX = 0 - minX;
    correctionY = height-1 - maxY;
}

void Transformation2D::reset(){
    mt = mt.Eye();
    correctionX = 0;
    correctionY = 0;
}
