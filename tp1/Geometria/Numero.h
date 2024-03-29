#ifndef NUMERO_H_
#define NUMERO_H_

#include "FiguraGeometrica.h"
#include "Coordenadas.h"
#include "Segmento.h"
#include <string.h>
#include <iostream.h>

class Numero : public FiguraGeometrica {

private:
	Coordenadas* coordenadas;
	float numero;
	int size;
	Color* color;

public:
	Numero(Coordenadas* coordenadas, float numero);
	Numero(Coordenadas* coordenadas, int numero);

	void setSize(int size);
	void setColor(Color* color);
	void dibujar();
	void dibujarPunteado();
    void rellenar();
    bool contiene(int x, int y);


	virtual ~Numero();
private:
    // Parsea un float como string
    std::string convertirReal(float value);
};

#endif /* NUMERO_H_ */
