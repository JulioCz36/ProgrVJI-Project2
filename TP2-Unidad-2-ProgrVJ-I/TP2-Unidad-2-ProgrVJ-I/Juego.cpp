#include "Juego.h"
#include "Partida.h"

Juego::Juego() : w(VideoMode(800, 641), "Trabajo Práctico Nº 2", Style::Titlebar | Style::Close) {
	w.setFramerateLimit(60);
	actual = new Partida();
}
Juego::~Juego() {
	delete actual;
}
void Juego::jugar() {
	while (w.isOpen()) {
		procesoEventos();
		w.clear();

		actualizar();

		dibujar();

		w.display();

		if (prox) {
			delete actual;
			actual = prox;
			prox = nullptr;
		}
	}
}

void Juego::actualizar() {
	actual->actualizar(*this);
}

void Juego::dibujar() {
	actual->dibujar(w);
}

void Juego::procesoEventos() {
	Event e;
	while (w.pollEvent(e)) {
		if (e.type == Event::Closed) {
			w.close();
		}
		else {
			actual->procesoEventos(*this, e);
		}
	}
}
void Juego::cambiarScena(Escena* scena_nueva) {
	prox = scena_nueva;
}

void Juego::reiniciar() {
	cambiarScena(new Partida());
}





