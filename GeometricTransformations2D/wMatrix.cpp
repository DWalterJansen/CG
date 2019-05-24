/*****************************************************************************/
/* Arquivo: WMatrix.h
 * Descrição: Definição de um TAD para manipulação de matrizes 3x3...
 * Data criação: 16/05/2004
 * Última modificação: 16/05/2004
 * Programador: Wagner Ferreira de Barros
 *****************************************************************************/

#include "wMatrix.h"

double wVector::Size() const
{
	double soma = 0;
	for (int i=0; i<3; i++)
		soma += elem[i]*elem[i];
	return sqrt(soma);
}

void wVector::Print() const
{
     printf( "[" );

     for (int i = 0; i < 3; i++)
     {
         if (i != 2)
         {
             printf("%f, ", elem[i]);
         }
         else
         {
             printf( "%f]", elem[i] );
         }
     }
}

const wVector& wVector::operator=(wVector v )
{
    for (int i=0; i<3; i++ )
        elem[i] = v.elem[i];
    return *this;
}

wVector wVector::operator+(const double value)
{
	wVector result = (*this);
    for (int i=0; i<3; i++)
        result.elem[i] += value;
    return result;
}

wVector wVector::operator+(wVector v)
{
	wVector result = (*this);

	for (int i=0; i<3; i++)
        result.elem[i] += v.elem[i];
    return result;
}

wVector wVector::operator-(const double value)
{
	wVector result = (*this);

    for (int i=0; i<3; i++)
        result.elem[i] -= value;
    return result;
}

wVector wVector::operator-(wVector v)
{
	wVector result = (*this);

    for (int i=0; i<3; i++)
        result.elem[i] -= v.elem[i];
    return result;
}

// produto escalar
wVector wVector::operator*(const double value)
{
	wVector result = (*this);

    for (int i=0; i<3; i++ )
        result.elem[i] *= value;
    return result;
}

double wVector::operator*(wVector v)
{
    double sum = 0;
    for (int i=0; i<3; i++)
        sum += elem[i] * v.elem[i];
    return sum;
}

wVector wVector::operator/(const double value)
{
	wVector result = (*this);

    for (int i=0; i<3; i++ )
        result.elem[i] /= value;
    return result;
}

wVector wVector::Cross(wVector u)
{
    wVector aux;

    aux.elem[0] = (elem[1] * u.elem[2]) - (elem[2] * u.elem[1]);
    aux.elem[1] = (elem[2] * u.elem[0]) - (elem[0] * u.elem[2]);
    aux.elem[2] = (elem[0] * u.elem[1]) - (elem[1] * u.elem[0]);

    return aux;
}
/*-----------------------------------------------------------------*/
void wMatrix::Print() const
{
    for (int i=0; i<3; i++)
    {
        elem[i].Print();
        printf("\n");
    }
}

void wMatrix::Print(std::string symbol) const
{
    for (int i=0; i<3; i++)
    {
        std::cout << symbol;
        elem[i].Print();
        printf("\n");
    }
}

wMatrix::wMatrix( double m[3][3])
{
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            this->Set( m[i][j], i, j);
}


void wMatrix::Set( double m[3][3] )
{
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            this->Set( m[i][j], i, j);
}

const wMatrix& wMatrix::Eye()
{
    for (int i=0; i<3; i++ )
        for (int j=0; j<3; j++ )
            i == j ? Set( 1, i, j ) : Set( 0, i, j);
    return *this;
}

wMatrix wMatrix::Transp()
{
    wMatrix aux;
    for (int i=0; i<3; i++ )
        for (int j=0; j<3; j++)
            aux.Set( elem[i][j], j, i);
    return aux;
}

const wMatrix& wMatrix::operator=( wMatrix m)
{
    for (int i=0; i<3; i++)
            Set( m[i], i);
    return *this;
}

wMatrix wMatrix::operator+( wMatrix m)
{
    wMatrix result = (*this);
    for (int i=0; i<3; i++)
         result.Set( result.elem[i] + m[i], i);
    return  (result);
}
wMatrix wMatrix::operator+( wVector v )
{
    wMatrix result = (*this);
    for (int i=0; i<3; i++)
        result.Set( result.elem[i] + v[i], i);
    return (result);
}

wMatrix wMatrix::operator+( const double& value)
{
    wMatrix result = (*this);
    for (int i=0; i<3; i++)
        result.Set( result.elem[i] + value, i);
    return (result);
}

wMatrix wMatrix::operator-( wMatrix m)
{
    wMatrix result;
    for (int i=0; i<3; i++)
         result.Set( (*this)[i] - m[i], i);
    return  (result);
}
wMatrix wMatrix::operator-( wVector v )
{
    wMatrix result;
    for (int i=0; i<3; i++)
        result.Set((*this)[i] - v[i], i);
    return (result);
}

wMatrix wMatrix::operator-( const double& value)
{
    wMatrix result;
    for (int i=0; i<3; i++)
        result.Set( (*this)[i] - value, i );
    return (result);
}

wMatrix wMatrix::operator/( const double& value)
{
    wMatrix result;
    assert( value != 0 );
    for (int i=0; i<3; i++)
        result.Set((*this)[i] / value, i);
    return (result);
}

wVector wMatrix::operator*( wVector v )
{
    wVector result;
    for (int i=0; i<3; i++)
        result.Set( (*this).elem[i] * v, i );
    return result;
}

wMatrix wMatrix::operator*( const double& value)
{
    wMatrix result;
    for (int i=0; i<3; i++)
        result.Set( (*this)[i] * value, i );
    return (result);
}


wMatrix wMatrix::operator*( wMatrix M)
{
    wVector vet_aux;
    wMatrix aux, result;
    aux = M.Transp();
    for (int i=0; i<3; i++)
        for ( int j=0; j<3; j++ )
            result.Set( (*this)[i] * aux[j], i, j );
    return (result);
}

// cálculo do determinante de uma w_matriz 3x3
double wMatrix::Det( ) const
{
    double det = 0;

    det = elem[0][0] * elem[1][1] * elem[2][2] +
          elem[0][1] * elem[1][2] * elem[2][0] +
          elem[0][2] * elem[1][0] * elem[2][1] -
        ( elem[0][2] * elem[1][1] * elem[2][0] +
          elem[0][1] * elem[1][0] * elem[2][2] +
          elem[0][0] * elem[2][1] * elem[1][2]);

    return det;
}

/* inversão de uma w_matrix de dimensão 3 na forma: */
wMatrix wMatrix::Inv() const
{
    double ret[3][3], det;
    det = Det();

    if ( det <= 10e-8 )
    {
        printf("Erro ao inverter Matriz... < A matriz deve ser não singular >");
        exit(0);
    }

    ret[0][0] =  elem[1][1]*elem[2][2] - elem[1][2]*elem[2][1];
    ret[0][1] = -elem[0][1]*elem[2][2] + elem[0][2]*elem[2][1];
    ret[0][2] =  elem[0][1]*elem[1][2] - elem[0][2]*elem[1][1];

    ret[1][0] = -elem[1][0]*elem[2][2] + elem[1][2]*elem[2][0];
    ret[1][1] =  elem[0][0]*elem[2][2] - elem[0][2]*elem[2][0];
    ret[1][2] = -elem[0][0]*elem[1][2] + elem[0][2]*elem[1][0];

    ret[2][0] =  elem[1][0]*elem[2][1] - elem[1][1]*elem[2][0];
    ret[2][1] = -elem[0][0]*elem[2][1] + elem[0][1]*elem[2][0];
    ret[2][2] =  elem[0][0]*elem[1][1] - elem[1][0]*elem[0][1];

    wMatrix result( ret );

    return (result / det);
}
