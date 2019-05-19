#ifndef TRANSFORMATION2D_H_INCLUDED
#define TRANSFORMATION2D_H_INCLUDED

#include "wMatrix.h"

class Transformation2D{
    private:
        //Matriz para as composição de transformação
        wMatrix mt;
        double correctionX;
        double correctionY;
        int newWidth;
        int newHeight;

    public:
        Transformation2D(){
            mt = mt.Eye();
        };
        wMatrix getMT(){return mt;};
        //translation
        double getcorrectionX(){return correctionX;}
        double getcorrectionY(){return correctionY;}
        wMatrix getTranslation(double tx, double ty);
        //rotation
        wMatrix getRotation(double theta);
        //scale
        wMatrix getScale(double sx, double sy);
        //shear
        wMatrix getSher(double shx, double shy);

        //composição
        void composition(const wMatrix &m);
        void mapDimension(int width, int height);
        void reset();
        ~Transformation2D(){};
};

#endif // TRANSFORMATION2D_H_INCLUDED
