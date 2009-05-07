#ifndef PANTALLA_H
#define PANTALLA_H

#include <stdlib.h>
#include <GL/glut.h>
#include "../Geometria/Rectangulo.h"
#include "../Geometria/Coordenadas.h"
#include "../Geometria/Curva.h"
#include <list.h>

class Pantalla
{
    public:
        /**
         * Devuelve la instancia unica segun el patron de diseño Singleton
         */
        static Pantalla* getInstancia(){
            static Pantalla* pantalla = NULL;
            if (!pantalla)
                pantalla = new Pantalla();
            return pantalla;
        }
        /**
         *  Desabilita el motor limpiando los recursos que este estaba utilizando.
         *   El mismo queda inutilizable
         */
        inline static void limpiar(){
            delete (Pantalla::getInstancia());
        }

        //getters
        bool ejesVisibles() {return this->view_axis;}
        bool grillaVisible() {return this->view_grid;}
        float getAncho() {return this->window_size[0];}
        float getAlto() {return this->window_size[1];}

        // Esto queda??
        float getRotacionEsfera() { return this->rotate_sphere;}
        void setRotacionEsfera(float rot) { this->rotate_sphere = rot; }
        //

        //setters
        void setEjesVisibles(bool b) { this->view_axis = b;}
        void setGrillaVisible(bool b) { this->view_grid = b;}
        void setAncho(const float ancho) { this->window_size[0] = ancho;}
        void setAlto(const float alto) { this->window_size[1] = alto;}

        /** Despliegue de datos en pantalla **/
        static void display();

        void dibujarEjes();

        // Recuadro superior derecho
        void dibujarEjesVista2DSuperior();

        // Recuadro inf der
        void dibujarEjesVista2DInferior();

        /** Dibuja una grilla en el plano z=0 **/
        void dibujarGrilla2D();

        /** Configura la matriz opengl en modo 3d (esto lo vamos a sacar de aca..) **/
        void setAmbiente3D();

        /** TODO: Describir esta funcionalidad **/
        void setAmbiente2DSuperior();

        /** TODO: Describir esta funcionalidad **/
        void setAmbiente2DInferior();

        void setPuntoControlSPlines(Coordenadas coordenada);

        list<Coordenadas> getPuntosControlSPlines() {return this->puntosControlBSplines;}

        void setPuntoControlBezier(Coordenadas coordenada);

        void dibujarFiguraBSplines();

    protected:
    private:
        GLfloat window_size[2];
        bool view_grid;
        bool view_axis;
        Rectangulo superior;
        Rectangulo inferior;
        Rectangulo central;
        /** Estas 2 variables float posiblemente se muevan a una clase Camara*/
        // Color de la esfera en movimiento dentro de la escena
        float color_esfera[4];
        // Variable asociada al movimiento de rotaci�n de la esfera alrededor del eje Z
        float rotate_sphere;

        list<Coordenadas> puntosControlBSplines;
        list<Coordenadas> puntosControlBezier;

        // configura con los valores iniciales los rectangulos visibles en la pantalla
        void configurarEscenario();

        // constructor
        Pantalla()
        {
            this->view_grid = true;
            this->view_axis = true;
            this->window_size[0]=1024;
            this->window_size[1]=768;
            this->configurarEscenario();
            // esto queda??
            this->color_esfera[0] = 0.5f;
            this->color_esfera[1] = 0.5f;
            this->color_esfera[2] = 0.2f;
            this->color_esfera[3] = 1.0f;
            this->rotate_sphere = 0;
        }
        // destructor
        inline ~Pantalla()
        {
            //dtor
        }
};

#endif // PANTALLA_H
