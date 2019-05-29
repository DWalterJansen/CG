#ifndef TRANSFORMATION2D_H_INCLUDED
#define TRANSFORMATION2D_H_INCLUDED

#include "wMatrix.h"

class Transformation2D{
    private:
        //Matriz para as composição de transformação
        wMatrix mt_show;
        wMatrix mt_real;
        long initWidth;
        long initHeight;
        long newWidth;
        long newHeight;
        bool colorful;

    public:
        Transformation2D(){
            mt_show = mt_show.Eye();
            mt_real = mt_real.Eye();
        };
        wMatrix getMT_Show(){return mt_show;};
        wMatrix getMT_Real(){return mt_real;};
        //Geters
        long getNewWidth(){return newWidth;}
        long getNewHeight(){return newHeight;}
        bool getColorful(){return colorful;}
        //Setters
        void setInitWidth(long initWidth){this->initWidth = initWidth;}
        void setInitHeight(long initHeight){this->initHeight = initHeight;}
        void setColorful(bool colorful){this->colorful = colorful;}
        //translation
        wMatrix getTranslation(double tx, double ty);
        //rotation
        wMatrix getRotation(double theta);
        //scale
        wMatrix getScale(double sx, double sy);
        //shear
        wMatrix getSher(double shx, double shy);

        //composição
        void composition(const wMatrix &m);
        void compositionReal(const wMatrix &m);
        void reset();
        void resetMT_Real();
        ~Transformation2D(){};
};

#endif // TRANSFORMATION2D_H_INCLUDED
