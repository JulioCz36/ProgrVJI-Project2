#pragma once
#include <SFML/Graphics.hpp>
#include "Texto.h"
#include "Audio.h"

using namespace sf;
using namespace std;

// Clase HUD: Maneja la interfaz gráfica 
class HUD{
	//Controles de guias
	Texture teclas_texture;
	Sprite controles;

	// Fondo negro semitransparente al finalizar
	RectangleShape fondoNegro;

	// texto muestra tiempo o estado, reinicio indica cómo reiniciar el juego
	Texto texto, reinicio;

	// Sonidos tic-tac,reinicio parpadeando,victoria, derrota
	Audio reloj,restart, win, over;

	// Tiempo restante de la partida
	float tiempoRestante = 31.f; 
	// Indica si se acabó el tiempo
	bool terminado = false;
	// Indica si el jugador ganó
	bool gano = false;

	// controlar el parpadeo
	float tiempoParpadeo = 0.f;
	// alternar visibilidad
	bool mostrarReinicio = false;

	bool reiniciar = false;
	// Guarda el valor anterior de mostrarReinicio
	bool mostrarReinicioAnterior = true;

	// tiempo desde que terminó la partida
	float tiempoDesdeFin = 0.f;
	// Controla que los sonidos de fin
	bool sonidoCondicion = false;

public:
	HUD();
	// Actualiza el HUD cada frame
	void actualizar(float deltaTime);
	// Dibuja los textos del HUD en la ventana
	void dibujar(RenderWindow& w);
	// Cambia el contenido del texto
	void actualizarTexto();
	// Marca que ganó la partida
	void elGano();
	// Devuelve si el tiempo se terminó
	bool seTermino();
	// Devuelve si se gano el juego
	bool seGano();
	// Devuelve true si el jugador puede reiniciar el juego
	bool puedeReiniciar();
};

