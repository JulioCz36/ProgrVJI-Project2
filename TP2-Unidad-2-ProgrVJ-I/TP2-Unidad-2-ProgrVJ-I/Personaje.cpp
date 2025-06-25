#include "Personaje.h"
Personaje::Personaje(Vector2f pos, float gravedadMundo)
    : Objeto("assets/personaje/personaje_sheet.png", pos, { 64, 64 }, 2.5f),
    polvo("assets/personaje/polvo.png", true, 50, 50), gravedad(gravedadMundo) {

    backGround.Add("idle", { 0, 1, 2, 3, 4,5,6,7 }, 8, true);
    backGround.Add("walk", { 8, 9, 10, 11, 12,13,14,15 }, 8, true);
    backGround.Add("run", { 16, 17, 18, 19, 20,21,22,23 }, 8, true);
    backGround.Add("jump", { 24,25 }, 8, true);
    backGround.Add("fall", { 26,27 }, 8, true);
    backGround.Add("land", { 28,29 }, 8, true);
    backGround.Add("herido", { 30 }, 1, false);
    backGround.Add("stun", { 31 }, 1, false);

    polvo.Add("pathogen", { 0,1,2,3,4,5 }, 6, true);
    polvo.setScale(1.5, 1.5);



    running.cargar("assets/sonidos/running.wav");
    running.quePitch(0.6f);
    walk.cargar("assets/sonidos/running.wav");
    walk.quePitch(0.52f);

    runningMetal.cargar("assets/sonidos/running-metal.wav");
    runningMetal.quePitch(0.9f);
    runningMetal.queVolumen(15);
    walkMetal.cargar("assets/sonidos/running-metal.wav");
    walkMetal.quePitch(0.8f);
    walkMetal.queVolumen(15);

    jump.cargar("assets/sonidos/jump.wav");
    land.cargar("assets/sonidos/land.wav");
}

void Personaje::actualizar(float deltaTime) {
    Objeto::actualizar(deltaTime);
    if (perdioPartida) {
        return;
    }
    polvo.Update();

    if (estaHerido) {
        tiempoHerido += deltaTime;
        if (tiempoHerido >= 0.2f) {
            estaHerido = false;
            enStun = true;
            tiempoStun = 0.f;
            backGround.Play("stun");
            quePos(Vector2f(400, 561));
        }
        return;
    }

    if (enStun) {
        tiempoStun += deltaTime;
        if (tiempoStun >= 0.2f) {
            enStun = false;
        }
        return; 
    }
    mover(deltaTime);
    verificarLimitesPantalla();
    aplicarGravedad(deltaTime);

    if (estaQuieto() && !enElAire) {
        backGround.Play("idle");
    }

}
void Personaje::manejarEventos(Event& e) {
    if (perdioPartida) {
        return;
    }
    if (e.type == Event::KeyPressed && (e.key.code == saltar1 || e.key.code == saltar2) && !enElAire) {
        polvo.setPosition(backGround.getPosition().x, backGround.getPosition().y + verBounds().height / 2.f);
        polvo.Play("pathogen");
        mostrarPolvoSalto = true;

        velocidadY = -velocidadSalto;
        enElAire = true;
    }
}
void Personaje::dibujar(RenderWindow& w) {
    w.draw(backGround);
    if (mostrarPolvoSalto) {
        w.draw(polvo);
    }
    //dibujarHitbox(w);
}


void Personaje::mover(float deltaTime) {
    float desplazamiento = velocidad * deltaTime;
    bool corriendo = false;
    bool caminando = false;

    if (Keyboard::isKeyPressed(der)) {
        backGround.FlipX(false);
        backGround.move(desplazamiento, 0);
        if (!enElAire) {
            backGround.Play("walk");
            caminando = true;
        }
    }
    if (Keyboard::isKeyPressed(izq)) {
        backGround.FlipX(true);
        backGround.move(-desplazamiento, 0);
        if (!enElAire) {
            backGround.Play("walk");
            caminando = true;
        }
    }
    if (Keyboard::isKeyPressed(der) && Keyboard::isKeyPressed(correr)) {
        backGround.FlipX(false);
        backGround.move(desplazamiento * 1.5f, 0);
        if (!enElAire) {
            backGround.Play("run");
            corriendo = true;
        }
    }
    if (Keyboard::isKeyPressed(izq) && Keyboard::isKeyPressed(correr)) {
        backGround.FlipX(true);
        backGround.move(-desplazamiento * 1.5f, 0);
        if (!enElAire) {
            backGround.Play("run");
            corriendo = true;
        }
    }

    // Control del sonido de correr
    if (corriendo) {
        if (sobreMetal) {
            if (!runningMetal.estaReproduciendo()) runningMetal.play();
        }
        else {
            if (!running.estaReproduciendo()) running.play();
        }
    }
    else {
        running.stop();
        runningMetal.stop();
    }

    // Control del sonido de caminar
    if (caminando && !corriendo) {
        if (sobreMetal) {
            if (!walkMetal.estaReproduciendo())  walkMetal.play();
        }
        else {
            if (!walk.estaReproduciendo()) walk.play();
        }
    }
    else {
        walk.stop();
        walkMetal.stop();
    }
}
void Personaje::aplicarGravedad(float deltaTime) {
    if (enElAire) {
        velocidadY += gravedad * deltaTime;
        backGround.move(0, velocidadY * deltaTime);
    }
}
void Personaje::recibirGolpe() {
    estaHerido = true;
    tiempoHerido = 0.f;
    backGround.Play("herido");
    velocidadY = 0; 
    mostrarPolvoSalto = false;
    enElAire = false;
    saltoIniciado = false;
    caidaIniciada = false;
}

void Personaje::apoyarEn(float y) {
    backGround.setPosition(backGround.getPosition().x, y - verBounds().height);
    velocidadY = 0;
    enElAire = false;
}

void Personaje::animacion(float deltaTime) {
    if (enElAire) {
        if (velocidadY < 0 && !saltoIniciado) {
            backGround.Play("jump");
            saltoIniciado = true;
            caidaIniciada = false;

            jump.play();
        }
        else if (velocidadY > 0 && !caidaIniciada) {
            backGround.Play("fall");
            caidaIniciada = true;
        }
    }
    else {
        // Si acaba de aterrizar
        if (saltoIniciado || caidaIniciada) {
            saltoIniciado = false;
            caidaIniciada = false;
            backGround.Play("land");
            mostrarPolvoSalto = false;
            land.play();
        }
    }
}

bool Personaje::estaQuieto() {
    return !(Keyboard::isKeyPressed(der) ||Keyboard::isKeyPressed(izq));
}
void Personaje::verificarLimitesPantalla() {
    FloatRect bounds = backGround.getGlobalBounds();
    Vector2f pos = backGround.getPosition();

    float margenIzquierdo = 55.f;
    float margenDerecho = 55.f;

    float izquierdaReal = pos.x - bounds.width / 2 + margenIzquierdo;
    float derechaReal = pos.x + bounds.width / 2 - margenDerecho;

    if (izquierdaReal  < 0) {
        backGround.setPosition(bounds.width / 2 - margenIzquierdo, pos.y);
    }
    if (derechaReal > 800) {
        backGround.setPosition(800 - bounds.width / 2 + margenDerecho, pos.y);
    }
}

FloatRect Personaje::verBounds() { 
    if (enElAire) {
        return ajustarHitbox(backGround.getGlobalBounds(), 33, 50, 70, 70);
    }
    else {
        return ajustarHitbox(backGround.getGlobalBounds(), 50, 40, 70, 70);
    }
}

void Personaje::queTerreno(bool esMetal) {
    sobreMetal = esMetal;
}

void Personaje::perdio() {
    backGround.Play("herido");
    quePos(Vector2f(400, 561));
    perdioPartida = true;
}

bool Personaje::esHerido()  { return estaHerido; }
bool Personaje::enStunActivo() { return enStun; }




