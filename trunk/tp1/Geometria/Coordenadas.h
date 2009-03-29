#ifndef COORDENADAS_H
#define COORDENADAS_H

#include "GL/glut.h"
#include "GL/glx.h"
#include <math.h>

/**
 * Clase que representa Coordenadas cartesianas sobre un plano de 2 Dimensiones
 */

class Coordenadas
{
    public:
        Coordenadas();
        Coordenadas(unsigned int x, unsigned int y);
        virtual ~Coordenadas();
        unsigned int getX() { return x; }
        void setX(unsigned int val) { x = val; }
        unsigned int getY() { return y; }
        void setY(unsigned int val) { y = val; }

        /**
         * Devuelve una copia de las coordenadas
         */
        virtual Coordenadas* copia(){ return new Coordenadas(this->x,this->y);}

        /**
         * Devuelve TRUE si this tiene mayor o igual valor en x que el parametro c.
         * FALSE en caso contrario
         */
        bool mayorX(Coordenadas* c);

        /**
         * Devuelve la distancia hasta las coordenadas pasadas por parametro
         */
        virtual double distancia (Coordenadas* hasta);



    protected:
    private:
        unsigned int x;
        unsigned int y;
};

#endif // COORDENADAS_H
