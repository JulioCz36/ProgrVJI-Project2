#pragma once
#include <SFML/Graphics.hpp>
#include "Juego.h"
#include <SFML/Window/Event.hpp>
using namespace sf;
class Juego;

// Clase abstracta base que representa una "escena" del juego.
class Escena {
public:
	Escena() {};
	// Método virtual para procesar eventos como teclado o mouse.
	virtual void procesoEventos(Juego& j, Event& event) {}

	// Se encarga de actualizar la lógica de la escena.
	virtual void actualizar(Juego& j) = 0;

	// Se encarga de dibujar todos los elementos gráficos de la escena.
	virtual void dibujar(RenderWindow& w) = 0;
};
