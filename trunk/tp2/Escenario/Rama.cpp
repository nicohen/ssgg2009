#include "Rama.h"
#include "../Geometria/Rectangulo.h" // PAra probar

Rama::Rama(Curva* modeladoHoja, float orientacion, float angulo)
{
    this->color.setRojo(0.6f);
    this->color.setVerde(0.25f);
    this->qobj = gluNewQuadric(); // crea un objeto cuadrático
    this->orientacion = orientacion;
    this->angulo = angulo;
    this->hoja1 = new Hoja(modeladoHoja,this->calcularOrientacionHoja());
    this->hoja2 = new Hoja(modeladoHoja,this->calcularOrientacionHoja());
    this->hoja3 = new Hoja(modeladoHoja,this->calcularOrientacionHoja());
}

Rama::~Rama()
{
    gluDeleteQuadric(qobj);
    delete hoja1;
    delete hoja2;
    delete hoja3;
}

void Rama::dibujar(){
    // Cilindro unitario
    glDisable(GL_LIGHTING);
    glColor3f(this->color.getRojo(), this->color.getVerde(), this->color.getAzul());
    glPushMatrix();
        glRotatef(this->orientacion,0,0,1);
        glRotatef(this->angulo,0,1,0);
        glScalef(0.125,0.125,1.5);
        gluQuadricDrawStyle(this->qobj, GLU_FILL); //estilo relleno
        gluCylinder(qobj, 1, 1, 1, 100, 100);

    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0.3,1.4);
        glRotatef(this->hoja1->getOrientacion(),1,1,0);
        glScalef(0.125,0.125,1);
        this->hoja1->dibujar();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.3,0,1.2);
        glRotatef(this->hoja1->getOrientacion(),1,1,0);
        glScalef(0.125,0.125,1);
        this->hoja2->dibujar();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,0.3,1.0);
        glRotatef(this->hoja1->getOrientacion(),1,1,0);
        glScalef(0.125,0.125,1);
        this->hoja3->dibujar();
    glPopMatrix();
    glEnable(GL_LIGHTING);

}

float Rama::calcularOrientacionHoja(){
    float orientacion = rand() % 181;
    if (orientacion > 45)
        orientacion = 45 - orientacion;
    return orientacion;
}
