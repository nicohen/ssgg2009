#ifndef COORDENADAS_H
#define COORDENADAS_H

#include "../Visualizacion/Dibujable.h"
#include <math.h>

/**
 * Clase que representa Coordenadas cartesianas
 */

class Coordenadas : public Dibujable
{
    public:
        Coordenadas();
        Coordenadas(int x, int y);
        Coordenadas(int x, int y, int z);
        Coordenadas(float x, float y);
        Coordenadas(float x, float y, float z);
        Coordenadas(double x, double y);// trunca a float
        Coordenadas(double x, double y, double z);// trunca a float
        Coordenadas(const Coordenadas& coordenadas); //construtor de copia
        virtual ~Coordenadas();

        void setX(int val) { x = val; }
        void setY(int val) { y = val; }
        void setZ(int val) { z = val; }

        float getX() { return x; }
        void setX(float val) { x = val; }
        float getY() { return y; }
        void setY(float val) { y = val; }
        float getZ() { return z; }
        void setZ(float val) { z = val; }
        void setX(double val) { x = val; } //trunca
        void setY(double val) { y = val; } //trunca
        void setZ(double val) { z = val; } //trunca


        /**
         * Dibuja la coordenada como una circunferencia rellena de radio 5
         */
        void dibujar();

        /**
         * Devuelve una copia de las coordenadas
         */
        virtual Coordenadas* copia(){ return new Coordenadas(this->x,this->y);}

        /**
         * Devuelve TRUE si this tiene mayor o igual valor en x que el parametro c.
         * FALSE en caso contrario
         */
        bool tieneMayorX(Coordenadas* c);

        /**
         * True si tienen mismos atributos, false en caso contrario
         */
        bool esIgual(Coordenadas c);

        /**
         * Devuelve las Coordenadas de mayor valor en X
         */
        Coordenadas* mayorX(Coordenadas* c);

        /**
         * Devuelve las Coordenadas de menor valor en X
         */
        Coordenadas* menorX(Coordenadas* c);

        /**
         * Devuelve las Coordenadas de mayor valor en Y
         */
        Coordenadas* mayorY(Coordenadas* c);

        /**
         * Devuelve las Coordenadas de menor valor en Y
         */
        Coordenadas* menorY(Coordenadas* c);

        /**
         * Devuelve la distancia hasta las coordenadas pasadas por parametro
         */
        virtual double distancia (Coordenadas hasta);
        /**
         * Devuelve el angulo de separacion entre 2 puntos ctomados como vectores (en radianes)
         */
        double angulo (Coordenadas hasta);

        /** @brief Operador de suma y resta e igualdad **/
        Coordenadas operator+(const Coordenadas& punto);
        Coordenadas operator-(const Coordenadas& punto);
        Coordenadas& operator=(const Coordenadas& punto);
        /** Sobrecarga del operador = **/
        bool operator == (Coordenadas coordenadas);

    protected:
    private:
        float x;
        float y;
        float z;
};

#endif // COORDENADAS_H
