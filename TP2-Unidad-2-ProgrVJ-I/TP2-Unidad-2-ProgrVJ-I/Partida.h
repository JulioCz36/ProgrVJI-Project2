#pragma once
#include <SFML/Graphics.hpp>

#include "Pila.h"
#include "Personaje.h"
#include "HUD.h"
#include "Reloj.h"
#include "Escenas.h"
#include "Puerta.h"
#include "Plataforma.h"
#include "Enemigo.h"
#include "Cola.h"

using namespace sf;
using namespace std;

class Cola;
class Pila;
class Enemigo;
class Escena;

class Partida : public Escena {
	Texture fondoTextura;	// Textura de fondo
	Sprite fondo;             // Sprite que representa el fondo visual
	
	Reloj reloj;			// Cronómetro para manejar el tiempo de partida
	Audio colision;     // Sonido de colisión entre el jugador y bloques

	HUD hud;	 // Interfaz de usuario

	Personaje* jugador = nullptr; // Puntero al jugador
	float gravedad = 787.5f;	//	gravedad aplicada al jugador

	Puerta* puerta = nullptr; // Puerta de salida

	Plataforma *plataformas[6];  // Arreglo de plataformas

	// Arreglo de pilas de enemigos
	Pila *pilas[6];

	// Enemigos que están en transición de una pila a otra
	Enemigo* enTransicionPila[3] = { nullptr, nullptr, nullptr };
	bool enTransicionActivo[3] = { false, false, false };
	bool izquierdaADerecha[3] = { true, true, true };

	// Arreglo de colas de enemigos
	Cola* colas[3];

	// Enemigos que están saliendo o entrando en las colas
	Enemigo* enTransicionCola[3] = { nullptr, nullptr, nullptr };
	Vector2f posEnemigoCola[3];// Posición del enemigo eliminado de la cola
	char colorEnemigoCola[3];      // Color del enemigo eliminado de la cola


public:
	Partida();
	~Partida();

	// actualización de la escena.
	void actualizar(Juego& j) override;
	// Dibuja elementos visibles en pantalla.
	void dibujar(RenderWindow& w) override;

	// Procesa la entrada del jugador y eventos del sistema.
	void procesoEventos(Juego& j, Event& event) override;

	// Maneja la colisión entre el jugador y las plataformas
	void JugadorYPlataforma();

	// Detecta si el jugador llegó a la puerta
	void JugadorYPuerta();

	// Verifica colisiones entre el jugador y los enemigos (colas y pilas)
	void JugadorYEnemigos();

	//Estructura Pila
	void actualizarPilas(float deltaTime);

	//Estructura Cola
	void actualizarColas(float dt);
};

