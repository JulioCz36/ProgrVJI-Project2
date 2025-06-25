#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// representa una plataforma est�tica en la que el jugador puede apoyarse
class Plataforma {
	Texture textura;     // Textura visual de la plataforma
	Sprite background;   // Sprite para dibujar la plataforma

public:
	Plataforma(Vector2f pos);

	// Devuelve los l�mites del sprite
	FloatRect verBounds();

	// Dibuja la plataforma en la ventana
	void dibujar(RenderWindow& w);

	// Ajusta la hitbox del sprite con m�rgenes personalizados
	FloatRect ajustarHitbox(float top, float bottom, float left, float right);

	// Dibuja la hitbox
	void dibujarHitbox(RenderWindow& w);

	// Devuelve la posici�n de la plataforma
	Vector2f verPos();
};

