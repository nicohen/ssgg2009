#include "Domo.h"

Domo::Domo(const float lado, const float altura) {
	this->lado = lado;
	this->altura = altura;
}

Domo::~Domo() {}

void Domo::dibujar() {
	Coordenadas c;
	glColor4f(135.0f/256.0f, 206.0f/256.0f, 255.0f/256.0f, 0.0f);
	glPushMatrix();
		glPushMatrix();
			glBegin(GL_QUADS);
				c=Matematica::obtenerNormalizado(Coordenadas(UNITARIO,UNITARIO,-UNITARIO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(1)
				glVertex3f(NULO,NULO,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(-UNITARIO,UNITARIO,-UNITARIO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(2)
				glVertex3f(lado,NULO,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(-UNITARIO,-UNITARIO,-UNITARIO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(3)
				glVertex3f(lado,lado,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(UNITARIO,-UNITARIO,-UNITARIO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(4)
				glVertex3f(NULO,lado,NULO);
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glRotated(90,NULO,UNITARIO,NULO);
			glBegin(GL_QUADS);
				c=Matematica::obtenerNormalizado(Coordenadas(UNITARIO,UNITARIO,-UNITARIO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(1)
				glVertex3f(NULO,NULO,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(UNITARIO,UNITARIO,NULO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(5)
				glVertex3f(lado,NULO,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(UNITARIO,-UNITARIO,NULO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(6)
				glVertex3f(lado,lado,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(UNITARIO,-UNITARIO,-UNITARIO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(4)
				glVertex3f(NULO,lado,NULO);
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glRotated(90,NULO,UNITARIO,NULO);
			glTranslated(NULO,NULO,this->lado);
			glBegin(GL_QUADS);
				c=Matematica::obtenerNormalizado(Coordenadas(-UNITARIO,UNITARIO,-UNITARIO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(2)
				glVertex3f(NULO,NULO,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(-UNITARIO,UNITARIO,NULO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(7)
				glVertex3f(lado,NULO,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(-UNITARIO,-UNITARIO,NULO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(8)
				glVertex3f(lado,lado,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(-UNITARIO,-UNITARIO,-UNITARIO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(3)
				glVertex3f(NULO,lado,NULO);
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glRotated(90,UNITARIO,NULO,NULO);
			glTranslated(NULO,-this->lado,NULO);
			glBegin(GL_QUADS);
				c=Matematica::obtenerNormalizado(Coordenadas(UNITARIO,UNITARIO,NULO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(5)
				glVertex3f(NULO,NULO,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(-UNITARIO,UNITARIO,NULO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(7)
				glVertex3f(lado,NULO,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(-UNITARIO,UNITARIO,-UNITARIO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(2)
				glVertex3f(lado,lado,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(UNITARIO,UNITARIO,-UNITARIO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(1)
				glVertex3f(NULO,lado,NULO);
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glRotated(90,UNITARIO,NULO,NULO);
			glTranslated(NULO,-this->lado,-this->lado);
			glBegin(GL_QUADS);
				c=Matematica::obtenerNormalizado(Coordenadas(UNITARIO,-UNITARIO,NULO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(6)
				glVertex3f(NULO,NULO,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(-UNITARIO,-UNITARIO,NULO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(8)
				glVertex3f(lado,NULO,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(-UNITARIO,-UNITARIO,-UNITARIO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(3)
				glVertex3f(lado,lado,NULO);
				c=Matematica::obtenerNormalizado(Coordenadas(UNITARIO,-UNITARIO,-UNITARIO));
				glNormal3f(c.getX(),c.getY(),c.getZ()); //(4)
				glVertex3f(NULO,lado,NULO);
			glEnd();
		glPopMatrix();
	glPopMatrix();
}
