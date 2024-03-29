#include "Pantalla.h"
#include "../Interaccion/IU.h"

void Pantalla::actualizar(list<Dibujable*> escena3d, list<Dibujable*> editorSup, list<Dibujable*> editorInf){
    float* ojoCamara = this->camara.getOjo();
    float* sobreCamara = this->camara.getSobre();
    float* arribaCamara = this->camara.getArriba();

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	////////////////// Escena 3D
	Pantalla::getInstancia()->setAmbiente3D();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (ojoCamara[0], ojoCamara[1], ojoCamara[2], sobreCamara[0],
        sobreCamara[1], sobreCamara[2], arribaCamara[0], arribaCamara[1], arribaCamara[2]);
    glRotatef(this->rotacionY, -1, 1, 0); //rotacion en y
    glRotatef(this->rotacionX,  0, 0, 1); // rotacion en x

	if (Pantalla::getInstancia()->ejesVisibles())
		 glCallList(this->getDL_AXIS());

	if (Pantalla::getInstancia()->grillaVisible())
		 glCallList(this->getDL_GRID());

    glDisable(GL_LIGHTING);
    list<Dibujable*>::iterator it3d = escena3d.begin();
    while (it3d != escena3d.end()){
        ((Dibujable*)*it3d)->dibujar();
        it3d++;
    }
	glEnable(GL_LIGHTING);
    ////////////////// Fin


	////////////////// Panel 2D para la vista superior
	Pantalla::getInstancia()->setAmbiente2DSuperior();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0, 0, 0.5, 0, 0, 0, 0, 1, 0);
	glCallList(this->getDL_AXIS2D_TOP());

	IU::getInstancia()->getEditorSenderoPlantacion()->dibujar();

	glDisable(GL_LIGHTING);
	list<Dibujable*>::iterator it2dS = editorSup.begin();
    while (it2dS != editorSup.end()){
        ((Dibujable*)*it2dS)->dibujar();
        it2dS++;
    }
	glEnable(GL_LIGHTING);
	////////////////// Fin

	////////////////// Panel 2D para la vista del perfil de altura
	Pantalla::getInstancia()->setAmbiente2DInferior();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0, 0, 0.5, 0, 0, 0, 0, 1, 0);
	glCallList(this->getDL_AXIS2D_HEIGHT());

	IU::getInstancia()->getEditorHoja()->dibujar();

	glDisable(GL_LIGHTING);
	list<Dibujable*>::iterator it2dI = editorInf.begin();
    while (it2dI != editorInf.end()){
        ((Dibujable*)*it2dI)->dibujar();
        it2dI++;
    }
	glEnable(GL_LIGHTING);
	////////////////// Fin

	glutSwapBuffers();
	this->forzarRedibujo();
}

void Pantalla::forzarRedibujo(){
    glutPostRedisplay();
}

void Pantalla::redimensionar (int w, int h){
   	Pantalla::getInstancia()->setAncho(w);
   	Pantalla::getInstancia()->setAlto(h);
   	IU::getInstancia()->getEditorHoja()->redimensionar(w,h);
   	IU::getInstancia()->getEditorSenderoPlantacion()->redimensionar(w,h);
}

void Pantalla::dibujarEjes()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
		// X
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(15.0, 0.0, 0.0);
		// Y
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 15.0, 0.0);
		// Z
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 15.0);
	glEnd();
	glEnable(GL_LIGHTING);
}

// Recuadro superior derecho
void Pantalla::dibujarEjesVista2DSuperior()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
	glEnd();
	glEnable(GL_LIGHTING);
}

// Recuadro inf der
void Pantalla::dibujarEjesVista2DInferior()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 0.5, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
	glEnd();
	glEnable(GL_LIGHTING);
}

/** Grilla 3d
 */
void Pantalla::dibujarGrilla2D()
{
	int i;
	glDisable(GL_LIGHTING);
	glColor3f(0.35, 0.1, 0.1);
	glBegin(GL_LINES);
	for(i=-20; i<21; i++)
	{
		glVertex3f(i, -20.0, 0.0);
		glVertex3f(i,  20.0, 0.0);
		glVertex3f(-20.0, i, 0.0);
		glVertex3f( 20.0, i, 0.0);
	}
	glEnd();
	glEnable(GL_LIGHTING);
}
void Pantalla::setAmbiente3D()
{
	glViewport (0, 0, (GLsizei) this->window_size[0], (GLsizei) this->window_size[1]);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    // Primer parametro para modificar zoom camara
    gluPerspective(this->camara.getZoom(), (GLfloat) this->window_size[0]/(GLfloat) this->window_size[1], 0.10, 100.0);
    this->modo = BSPLINE;
}

void Pantalla::setAmbiente2DSuperior()
{
	Rectangulo* superior = IU::getInstancia()->getEditorSenderoPlantacion()->getMarco();
	Coordenadas* c = superior->getVerticeSO();
	glViewport (c->getX(), (this->getAlto() - c->getY()), (GLsizei) superior->getBase(), (GLsizei) superior->getAltura());
	delete c;
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	this->modo = BSPLINE;

}

void Pantalla::setAmbiente2DInferior()
{
	Rectangulo* inferior = IU::getInstancia()->getEditorHoja()->getMarco();
	Coordenadas* c = inferior->getVerticeSO();
	glViewport (c->getX(), (this->getAlto() - c->getY()), (GLsizei)inferior->getBase(), (GLsizei) inferior->getAltura());
    delete c;
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	this->modo = BEZIER;
}


void Pantalla::configurarEscenario(){
    this->dl_handle = glGenLists(3);
	glClearColor (0.02, 0.02, 0.04, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, this->luz.getColor());
    glLightfv(GL_LIGHT0, GL_AMBIENT, this->luz.getAmbiente());
    glLightfv(GL_LIGHT0, GL_POSITION, this->luz.getPosicion());
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

	// Generaci�n de las Display Lists
	glNewList(this->getDL_AXIS(), GL_COMPILE);
		this->dibujarEjes();
	glEndList();
	glNewList(this->getDL_GRID(), GL_COMPILE);
		this->dibujarGrilla2D();
	glEndList();
	glNewList(this->getDL_AXIS2D_TOP(), GL_COMPILE);
		this->dibujarEjesVista2DSuperior();
	glEndList();
	glNewList(this->getDL_AXIS2D_HEIGHT(), GL_COMPILE);
		this->dibujarEjesVista2DInferior();
	glEndList();
}

void Pantalla::aumentarZoom(){
    float zoom = this->camara.getZoom();
    if (zoom > 0)
        this->camara.setZoom(--zoom);
}

void Pantalla::disminuirZoom(){
    float zoom = this->camara.getZoom();
    if (zoom < MAX_ZOOM)
        this->camara.setZoom(++zoom);
}

void Pantalla::calcularRotacionCamara(int x, int y){
    static int ultimoX = 0;
    static int ultimoY = 0;

    int deltaX = x - ultimoX;
    int deltaY = y - ultimoY;

    if (deltaX > 0) this->rotacionX += 0.50;
    if (deltaX < 0) this->rotacionX += -0.50;
    if (deltaY > 0) this->rotacionY += 0.50;
    if (deltaY < 0) this->rotacionY += -0.50;

    ultimoX = x;
    ultimoY = y;
}
