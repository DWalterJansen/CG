/*****************************************************************************
 * Arquivo: WMatrix.h
 * Descrição: Definição de um TAD para manipulação de matrizes 3x3 e vetores 1x3
 * Data criação: 16/05/2004
 * Última modificação: 16/05/2004
 * Programador: Wagner Ferreira de Barros
 *****************************************************************************/

#ifndef WMATRIX_H_
#define WMATRIX_H_

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

class wVector
{
    private:
        double elem[3];

    public:
        wVector(){elem[0] = 0; elem[1]=0; elem[2]=0;}
        wVector( const wVector& v) {  for (int i=0; i<3;i++) elem[i] = v.elem[i]; }
		wVector( double value[3] ) { Set( value ); }
		wVector( double x, double y, double z){ Set( x, y, z);}

        void Set( double value, int i ){elem[i] = value;}
		void Set( double value[3] ) { elem[0] = value[0]; elem[1]=value[1]; elem[2]=value[2]; }
		void Set(double x, double y, double z ){elem[0]=x; elem[1]=y; elem[2] = z;}

        double &operator[](const int i) { return this->elem[i];}
        double operator[](const int i) const { return this->elem[i];}
		double Size() const;

        wVector operator+(const double);
        wVector operator+(wVector);

        wVector operator-(const double value);
        wVector operator-(wVector v);

        wVector operator*(const double);   // produto escalar
        double operator*(wVector);  // produto interno
        wVector Cross( wVector );

        wVector operator/(const double);

        const wVector& operator=(wVector );

        void Print() const;
};

class wMatrix:public wVector
{
    private:
        wVector elem[3]; // cada vetor representa uma linha da matriz
        double Det() const;
    public:
        // construtor que aloca e seta os valores da matriz
        // por default é gerada uma matriz 3x3 com todos os elementos iguais a 0
        wMatrix( ){ }
        wMatrix( const wMatrix& m ) { for (int i=0; i<3; i++) elem[i] = m.elem[i];}
        wMatrix( double[3][3] );

        const wMatrix& Eye();     // gera uma matriz identidade
        wMatrix Inv() const;     // matriz inversa...
        wMatrix Transp();  // matriz transposta...

        void Set(double value, int row, int col){ elem[row].Set( value, col );}
        void Set(wVector v, int i ) { elem[i] = v; }
		void Set( double m[3][3] );

        wVector &operator[](const int i){ return elem[i]; }
        wVector operator[](const int i) const { return elem[i]; }

        //wVector operator[](const int i) const { return elem[i]; }

        const wMatrix& operator=( wMatrix );

        wMatrix operator+( wMatrix );
        wMatrix operator+( wVector );
        wMatrix operator+( const double& );

        wMatrix operator-( wMatrix );
        wMatrix operator-( wVector );
        wMatrix operator-( const double& );

        wMatrix operator*( wMatrix );
        wVector operator*( wVector );
        wMatrix operator*( const double&);

        wMatrix operator/( const double& );

        void Print() const;
        void Print(std::string symbol) const;
};

#endif
