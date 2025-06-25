#include "Partida.h"

Partida::Partida() {
	fondoTextura.loadFromFile("assets/mundo/mundo_fondo.png");
	fondo.setTexture(fondoTextura);
	colision.cargar("assets/sonidos/punch.wav");
	colision.queVolumen(50);

	//creo jugador
	jugador = new Personaje(Vector2f(400, 561), gravedad);

	//creo puerta
	puerta = new Puerta(Vector2f(400, 48));

	//creo las plataformar
	for (int i = 0;i < 6;i++) {
		float baseY = 588;
		float espacioEntre = 41;
		float alturaPlataforma = 43;

		float y = baseY - (i + 1) * (alturaPlataforma + espacioEntre);

		Plataforma* p = new Plataforma(Vector2f(400, y));
		plataformas[i] = p;
	}

	//creo las pilas
	for (int i = 0;i < 6;i++) {
		Pila *p = new Pila();
		pilas[i] = p;
	}
	//creo las colas
	for (int i = 0;i < 3;i++) {
		Cola* c = new Cola();
		colas[i] = c;
	}
	//agrego los enemigos a las pilas
	for (int i = 0; i < 6; i += 2) {
		if (i == 2) {
			pilas[i+1]->agregar(Vector2f(770, plataformas[i]->verPos().y), 'Y', -1);
			pilas[i+1]->agregar(Vector2f(730, plataformas[i]->verPos().y), 'B', -1);
			pilas[i+1]->agregar(Vector2f(690, plataformas[i]->verPos().y), 'G', -1);
			pilas[i+1]->agregar(Vector2f(650, plataformas[i]->verPos().y), 'R', -1);
		}
		else {
			pilas[i]->agregar(Vector2f(40, plataformas[i]->verPos().y), 'R', 1);
			pilas[i]->agregar(Vector2f(80, plataformas[i]->verPos().y), 'G', 1);
			pilas[i]->agregar(Vector2f(120, plataformas[i]->verPos().y), 'B', 1);
			pilas[i]->agregar(Vector2f(160, plataformas[i]->verPos().y), 'Y', 1);
		}
	}
	//agrego enemigos a las colas
	for (int i = 0; i < 3; i ++) {
		if (i == 0 || i == 2) {
			colas[i]->agregar(Vector2f(650, plataformas[1 + i * 2]->verPos().y), 'R', -1);
			colas[i]->agregar(Vector2f(690, plataformas[1 + i * 2]->verPos().y), 'G', -1);
			colas[i]->agregar(Vector2f(730, plataformas[1 + i * 2]->verPos().y), 'B', -1);
			colas[i]->agregar(Vector2f(770, plataformas[1 + i * 2]->verPos().y), 'Y', -1);
		}else {
			colas[i]->agregar(Vector2f(160, plataformas[1 + i * 2]->verPos().y), 'R', 1);
			colas[i]->agregar(Vector2f(120, plataformas[1 + i * 2]->verPos().y), 'G', 1);
			colas[i]->agregar(Vector2f(80, plataformas[1 + i * 2]->verPos().y), 'B', 1);
			colas[i]->agregar(Vector2f(40, plataformas[1 + i * 2]->verPos().y), 'Y', 1);
		}
	}
}
Partida::~Partida() {
	delete jugador;
	delete puerta;
	for (int i = 0;i < 6;i++) {
		delete pilas[i];
	}
	for (int i = 0;i < 3;i++) {
		delete colas[i];
	}
}

void Partida::actualizar(Juego& j){

	float deltaTime = reloj.verReinicio();

	hud.actualizar(deltaTime);
	hud.actualizarTexto();

	if (hud.seGano()) {
		puerta->abrioPuerta();
		delete jugador;
		jugador = nullptr;
	}
	puerta->actualizar(deltaTime);

	if (hud.seTermino()) {
		jugador->perdio();
	}

	if (jugador) jugador->actualizar(deltaTime);

	if (hud.seTermino() || hud.seGano()) return;

	actualizarPilas(deltaTime);
	actualizarColas(deltaTime);

	JugadorYPlataforma();
	JugadorYPuerta();
	JugadorYEnemigos();

}
void Partida::dibujar(RenderWindow& w){
	w.draw(fondo);

	puerta->dibujar(w);
	if(jugador) jugador->dibujar(w);

	// Dibuja la pila de enemigos
	for (int i = 0;i < 6;i++) {
		pilas[i]->dibujar(w);
	}
	for (int i = 0;i < 3;i++) {
		if (enTransicionPila[i])
			enTransicionPila[i]->dibujar(w);
	}

	for (int i = 0;i < 3;i++) {
		colas[i]->dibujar(w);
		if (enTransicionCola[i])
			enTransicionCola[i]->dibujar(w);
	}

	for (int i = 0;i < 5;i++) {
		plataformas[i]->dibujar(w);
	}
	hud.dibujar(w);

}
void Partida::procesoEventos(Juego& j, Event& event){
	if (jugador) jugador->manejarEventos(event);

	if (event.type == Event::KeyPressed && event.key.code == Keyboard::R && (hud.seTermino() || hud.seGano()) && hud.puedeReiniciar()) {
		j.reiniciar();
	}
}

void Partida::JugadorYPlataforma() {
	FloatRect rectJugador = jugador->verBounds();
	float velocidadY = jugador->verVelocidadY(); 

	jugador->queTerreno(false);
	for (int i = 0; i < 6; ++i) {

		// Verificamos colisión
		if (rectJugador.intersects(plataformas[i]->verBounds())) {
			if (i < 5) { 
				jugador->queTerreno(true);
			}

			float jugadorY = rectJugador.top + rectJugador.height;
			float plataformaY = plataformas[i]->verBounds().top +38;

			if (velocidadY > 0 && jugadorY <= plataformaY + 15.f){
				jugador->apoyarEn(plataformaY); 
				break; 
			}
		}

	}
}
void Partida::JugadorYPuerta() {
	FloatRect rectJugador = jugador->verBounds();
	FloatRect rectPuerta = puerta->verBounds();

	if (rectJugador.intersects(rectPuerta)) {
		hud.elGano();
	}
}
void Partida::JugadorYEnemigos() {
	FloatRect rectJugador = jugador->verBounds();

	if (jugador->esHerido() || jugador->enStunActivo()) { return; } // Evita repetir golpes

	for (int i = 0; i < 3; ++i) {
		if (enTransicionPila[i] && enTransicionPila[i]->verBounds().intersects(rectJugador)) {
			colision.play();
			jugador->recibirGolpe();
			return;
		}
		if (enTransicionCola[i] && enTransicionCola[i]->verBounds().intersects(rectJugador)) {
			colision.play();
			jugador->recibirGolpe();
			return;
		}
	}

	for (int i = 0; i < 6; ++i) {
		Enemigo* actual = pilas[i]->verTope();
		while (actual) {
			if (actual->verBounds().intersects(rectJugador)) {
				colision.play();
				jugador->recibirGolpe();
				return;
			}
			actual = actual->enemigoSiguiente;
		}
	}

	for (int i = 0; i < 3; ++i) {
		Enemigo* actual = colas[i]->verPrimero();
		while (actual) {
			if (actual->verBounds().intersects(rectJugador)) {
				colision.play();
				jugador->recibirGolpe();
				return;
			}
			actual = actual->enemigoSiguiente;
		}
	}
}


void Partida::actualizarPilas(float deltaTime) {
	char colorEnemigo;
	Vector2f posEnemigo;
	for (int i = 0; i < 3; i++) { 
		if (enTransicionActivo[i]) {
			enTransicionPila[i]->actualizar(deltaTime);
			if (enTransicionPila[i]->llegoDestino) {
				int origen = i * 2;
				int destino = i * 2 + 1;

				if (izquierdaADerecha[i]) {
					pilas[destino]->agregar(enTransicionPila[i]->verPos(), enTransicionPila[i]->color, -1);
				}
				else {
					pilas[origen]->agregar(enTransicionPila[i]->verPos(), enTransicionPila[i]->color, 1);
				}

				delete enTransicionPila[i];
				enTransicionPila[i] = nullptr;
				enTransicionActivo[i] = false;
			}
			continue;
		}

		int pilaOrigen = i * 2;
		int pilaDestino = i * 2 + 1;

		if (izquierdaADerecha[i] && pilas[pilaDestino]->contar() >= 4)
			izquierdaADerecha[i] = false;
		else if (!izquierdaADerecha[i] && pilas[pilaOrigen]->contar() >= 4)
			izquierdaADerecha[i] = true;

		if (izquierdaADerecha[i] && !pilas[pilaOrigen]->estaVacia()) {
			pilas[pilaOrigen]->eliminar(posEnemigo, colorEnemigo);
			enTransicionPila[i] = new Enemigo(posEnemigo, colorEnemigo);

			// Calculamos el destino en función de la cantidad en pila destino
			int cantidadDestino = pilas[pilaDestino]->contar();
			Vector2f basePosDerecha = Vector2f(770.f, plataformas[pilaDestino]->verPos().y);
			Vector2f destino = basePosDerecha + Vector2f(-40.f * cantidadDestino, 0.f);

			enTransicionPila[i]->destino = destino;
			enTransicionPila[i]->enMovimiento = true;
			enTransicionActivo[i] = true;
		}
		else if (!izquierdaADerecha[i] && !pilas[pilaDestino]->estaVacia()) {
			pilas[pilaDestino]->eliminar(posEnemigo, colorEnemigo);
			enTransicionPila[i] = new Enemigo(posEnemigo, colorEnemigo);

			int cantidadOrigen = pilas[pilaOrigen]->contar();
			Vector2f basePosIzquierda = Vector2f(30.f, plataformas[pilaOrigen]->verPos().y);
			Vector2f destino = basePosIzquierda + Vector2f(40.f * cantidadOrigen, 0.f);

			enTransicionPila[i]->destino = destino;
			enTransicionPila[i]->s->setScale(-1.f, 1.f);
			enTransicionPila[i]->enMovimiento = true;
			enTransicionActivo[i] = true;
		}
	}
}

void Partida::actualizarColas(float dt) {
	for (int i = 0; i < 3; ++i) {

		// Si no hay enemigo en transición, sacamos uno de la cola
		if (!enTransicionCola[i]) {
			colas[i]->eliminar(posEnemigoCola[i], colorEnemigoCola[i]);
			enTransicionCola[i] = new Enemigo(posEnemigoCola[i], colorEnemigoCola[i]);
			if(i == 0 || i == 2) {
				enTransicionCola[i]->s->setScale(-1.f, 1.f);
				enTransicionCola[i]->destino = Vector2f(-30.f, posEnemigoCola[i].y);
			}else {
				enTransicionCola[i]->destino = Vector2f(830.f, posEnemigoCola[i].y);
			}
			enTransicionCola[i]->enMovimiento = true;
		}

		// Si hay enemigo en transición, actualizarlo
		if (enTransicionCola[i]) {
			enTransicionCola[i]->actualizar(dt);

			// Cuando sale de pantalla, lo volvemos a agregar
			if (enTransicionCola[i]->verPos().x > 800.f || enTransicionCola[i]->verPos().x < -20.f) {
				float desplazamiento = (i == 0 || i == 2) ? -40.f : 40.f;
				colas[i]->moverVisualmente(desplazamiento);

				float nuevaX = (i == 0 || i == 2) ? 770.f : 40.f;
				float escala = (i == 0 || i == 2) ? -1.f : 1.f;

				colas[i]->agregar(Vector2f(nuevaX, posEnemigoCola[i].y), enTransicionCola[i]->verColor(), escala);

				delete enTransicionCola[i];
				enTransicionCola[i] = nullptr;
			}
		}
	}

}









