#pragma once
#include <SFML/Graphics.hpp>
#include "Objeto.h"
using namespace sf;

// representa la puerta de salida del nivel
class Puerta : public Objeto {
public:
	Puerta(Vector2f pos);

	// Cambia la apariencia para indicar que la puerta se abrió
	void abrioPuerta();
};



