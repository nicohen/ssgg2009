#ifndef SEGMENTO_H
#define SEGMENTO_H

#include "FiguraGeometrica.h"
#include "stdlib.h"

class Segmento : public FiguraGeometrica
{
    public:
        /** Constructor
         * @param desde Las coordeandas donde empieza el segmento
         * @param hasta Las coordenadas donde termina el segmento
         * @note El segmento se hace responsable de destruir las mismas cuando corresponda
         **/
        Segmento(Coordenadas* desde, Coordenadas* hasta);

        /** Default destructor */
        virtual ~Segmento();
        Coordenadas* getDesde() { return desde; }
        Coordenadas* getHasta() { return hasta; }

        /**
         * Devuelve la pendiente del segmento
         */
        float pendiente();

        /**
         * Devuelve la longitud del segmento
         */
        double longitud();

        /**
         * Dibuja el segmento
         */
        void dibujar();

        /**
         * Dibuja el segmento
         */
        void dibujarPunteado();

        /**
         * Rellena el segmento
         */
        void rellenar();

        /**
         * Devuelve true si la figura contiene al punto (x,y)
         */
        bool contiene(int x, int y);

    protected:
        // Variables miembro
        Coordenadas* desde;
        Coordenadas* hasta;

        // Dibuja el Segmento segun el algoritmo DDA
        void dibujarDDA();
        // Dibuja el segmento segun el algoritmo Bresenham
        void dibujarBresenham();

    private:

    	void dibujarDDAPunteado();
    	void dibujarBresenhamPunteado();

};

#endif // SEGMENTO_H
