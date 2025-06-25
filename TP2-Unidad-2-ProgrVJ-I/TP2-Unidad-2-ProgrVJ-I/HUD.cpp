#include "HUD.h"

HUD::HUD() {
	teclas_texture.loadFromFile("assets/controles/teclas.png");
	controles.setTexture(teclas_texture);
	controles.setPosition(600, 10);

	// Configurar texto principal
	texto.inicializar(20);
	texto.quePosicion(100, 30);

	// Configurar texto de reinicio
	reinicio.inicializar(18);
	reinicio.quePosicion(680, 300);
	reinicio.queColor(Color::White);
	reinicio.queTexto("R to restart");

	// Configurar texto de reinicio
	reloj.cargar("assets/sonidos/tic-tac.wav");
	reloj.quePitch(0.28f);
	reloj.queVolumen(80);

	win.cargar("assets/sonidos/win.wav");
	win.queVolumen(60);
	over.cargar("assets/sonidos/game-over.wav");
	over.queVolumen(60);

	restart.cargar("assets/sonidos/button-R.wav");
	restart.queVolumen(40);
}

void HUD::actualizar(float deltaTime) {
	// Si el juego está en curso sonido reloj
	if (!reloj.estaReproduciendo() && !terminado && !gano) {
		reloj.play();
	}

	// Si se terminó el juego o el jugador ganó
	if (terminado || gano) {
		reloj.stop(); // Detener el sonido de reloj

		// Reproducir sonido condicion
		if (!sonidoCondicion) {
			if (terminado) over.play();
			if (gano) win.play();
			sonidoCondicion = true;
		}
		
		// Esperar 2 segundos antes de comenzar el parpadeo del mensaje de reinicio
		tiempoDesdeFin += deltaTime;
		if (tiempoDesdeFin >= 2.f) {
			reiniciar = true;
			tiempoParpadeo += deltaTime;

			// Alternar visibilidad del mensaje de reinicio cada 0.5 segundos
			if (tiempoParpadeo >= 0.5f) {
				mostrarReinicioAnterior = mostrarReinicio;
				mostrarReinicio = !mostrarReinicio;
				tiempoParpadeo = 0.f;

				// Reproducir sonido solo al aparecer el mensaje
				if (!mostrarReinicioAnterior && mostrarReinicio) {
					restart.play();
				}
			}
		}

		return;
	}

	// Reducir el tiempo restante mientras el juego está en curso
	tiempoRestante -= deltaTime;

	// Verificar si se acabó el tiempo
	if (tiempoRestante <= 0.f) {
		tiempoRestante = 0.f;
		terminado = true;
	}
}
void HUD::dibujar(RenderWindow& w) {
	if (!terminado && !gano) {
		w.draw(controles);
	}

	if (terminado || gano) {
		fondoNegro.setSize(Vector2f(w.getSize()));
		fondoNegro.setFillColor(Color(0,0,0,200));
		w.draw(fondoNegro);
	}

	texto.dibujar(w);

	if ((terminado || gano) && mostrarReinicio) {
		reinicio.dibujar(w);
	}
}

void HUD::actualizarTexto() {
	if (gano) {
		texto.queColor(Color(0, 173, 17));
		texto.quePosicion(400, 200);
		texto.queSize(60);
		texto.queTexto("¡ You win !");
	}
	else if (terminado) {
		texto.queColor(Color(170, 0, 20));
		texto.quePosicion(400, 200);
		texto.queSize(60);
		texto.queTexto("Game Over");
	}
	else {
		texto.queColor(Color(254, 198, 47));
		texto.queTexto("Time: " + to_string((int)tiempoRestante));
	}
}

void HUD::elGano() {
	gano = true;
}

bool HUD::seTermino(){
	return terminado;
}
bool HUD::seGano() {
	return gano;
}

bool HUD::puedeReiniciar() {
	return reiniciar;
}
