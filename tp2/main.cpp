#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

// Variables que controlan la ubicaci�n de la c�mara en la Escena 3D
float eye[3] = {15.0, 15.0, 5.0};
float at[3]  = { 0.0,  0.0, 0.0};
float up[3]  = { 0.0,  0.0, 1.0};

// Variables asociadas a �nica fuente de luz de la escena
float light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float light_position[3] = {10.0f, 10.0f, 8.0f};
float light_ambient[4] = {0.05f, 0.05f, 0.05f, 1.0f};

// Color de la esfera en movimiento dentro de la escena
float color_esfera[4] = {0.5f, 0.5f, 0.2f, 1.0f};

// Variable asociada al movimiento de rotaci�n de la esfera alrededor del eje Z
float rotate_sphere = 0;

// Variables de control
bool view_grid = true;
bool view_axis = true;


// Handle para el control de las Display Lists
GLuint dl_handle;
#define DL_AXIS (dl_handle+0)
#define DL_GRID (dl_handle+1)
#define DL_AXIS2D_TOP (dl_handle+2)
#define DL_AXIS2D_HEIGHT (dl_handle+3)

// Tama�o de la ventana
GLfloat window_size[2];
#define W_WIDTH window_size[0]
#define W_HEIGHT window_size[1]

#define TOP_VIEW_POSX	((int)((float)W_WIDTH*0.70f))
#define TOP_VIEW_W		((int)((float)W_WIDTH*0.30f))
#define TOP_VIEW_POSY	((int)((float)W_HEIGHT*0.70f))
#define TOP_VIEW_H		((int)((float)W_HEIGHT*0.30f))

#define HEIGHT_VIEW_POSX	((int)((float)W_WIDTH*0.70f))
#define HEIGHT_VIEW_W		((int)((float)W_WIDTH*0.30f))
#define HEIGHT_VIEW_POSY	((int)((float)W_HEIGHT*0.40f))
#define HEIGHT_VIEW_H		((int)((float)W_HEIGHT*0.30f))


void OnIdle (void)
{
	rotate_sphere += 0.1;
	if(rotate_sphere > 360.0) rotate_sphere = 0.0;
    glutPostRedisplay();
}

// Ejes cartesianos 3d
void DrawAxis()
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
void DrawAxis2DTopView()
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
void DrawAxis2DHeightView()
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
void DrawXYGrid()
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
void Set3DEnv()
{
	glViewport (0, 0, (GLsizei) W_WIDTH, (GLsizei) W_HEIGHT);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    // Primer parametro para modificar zoom camara
    gluPerspective(60.0, (GLfloat) W_WIDTH/(GLfloat) W_HEIGHT, 0.10, 100.0);
}

void SetPanelTopEnv()
{
	glViewport (TOP_VIEW_POSX, TOP_VIEW_POSY, (GLsizei) TOP_VIEW_W, (GLsizei) TOP_VIEW_H);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
	gluOrtho2D(-0.10, 1.05, -0.10, 1.05);
}

void SetPanelHeightEnv()
{
	glViewport (HEIGHT_VIEW_POSX, HEIGHT_VIEW_POSY, (GLsizei) HEIGHT_VIEW_W, (GLsizei) HEIGHT_VIEW_H);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
	gluOrtho2D(-0.10, 1.05, -0.10, 1.05);
}

void init(void)
{
	dl_handle = glGenLists(3);

	glClearColor (0.02, 0.02, 0.04, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

	// Generaci�n de las Display Lists
	glNewList(DL_AXIS, GL_COMPILE);
		DrawAxis();
	glEndList();
	glNewList(DL_GRID, GL_COMPILE);
		DrawXYGrid();
	glEndList();
	glNewList(DL_AXIS2D_TOP, GL_COMPILE);
		DrawAxis2DTopView();
	glEndList();
	glNewList(DL_AXIS2D_HEIGHT, GL_COMPILE);
		DrawAxis2DHeightView();
	glEndList();
}



void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	///////////////////////////////////////////////////
	// Escena 3D
	Set3DEnv();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);

	if (view_axis)
		 glCallList(DL_AXIS);

	if (view_grid)
		 glCallList(DL_GRID);
	//
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	// Panel 2D para la vista superior
	SetPanelTopEnv();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0, 0, 0.5, 0, 0, 0, 0, 1, 0);
	glCallList(DL_AXIS2D_TOP);
	//
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	// Panel 2D para la vista del perfil de altura
	SetPanelHeightEnv();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0, 0, 0.5, 0, 0, 0, 0, 1, 0);
	glCallList(DL_AXIS2D_HEIGHT);
	//
	///////////////////////////////////////////////////

	glutSwapBuffers();
}

void reshape (int w, int h)
{
   	W_WIDTH  = w;
	W_HEIGHT = h;
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 0x1b:
         exit (0);
         break;
	  case 'g':
		  view_grid = !view_grid;
		  glutPostRedisplay();
		  break;

	  case 'a':
		  view_axis = !view_axis;
		  glutPostRedisplay();
		  break;
     default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (1024, 768);
   glutInitWindowPosition (0, 0);

   glutCreateWindow (argv[0]);
   glutFullScreen();
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(OnIdle);
   glutMainLoop();
   return 0;
}
