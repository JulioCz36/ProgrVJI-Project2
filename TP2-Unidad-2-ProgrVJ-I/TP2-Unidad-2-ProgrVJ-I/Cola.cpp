#include "Cola.h"

Cola::Cola() {}

Cola::~Cola() {
    while (primero) {
        Enemigo* temp = primero;
        primero = primero->enemigoSiguiente;
        delete temp;
    }
}

void Cola::agregar(Vector2f pos, char color, float escalaX) {
    Enemigo* nuevo = new Enemigo(pos, color);
    nuevo->s->setScale(escalaX, 1.f);
    nuevo->enemigoSiguiente = nullptr;

    if (primero == nullptr) {
        primero = nuevo;
    }
    else {
        ultimo->enemigoSiguiente = nuevo;
    }
    ultimo = nuevo;
}

void Cola::eliminar(Vector2f& posOut, char& colorOut) {
    if (!primero) return;

    Enemigo* temp = primero;
    posOut = temp->verPos();
    colorOut = temp->color;

    if (primero == ultimo) {
        primero = nullptr;
        ultimo = nullptr;
    }
    else {
        primero = primero->enemigoSiguiente;
    }

    delete temp;
}

void Cola::dibujar(RenderWindow& w) {
    Enemigo* actual = primero;
    while (actual) {
        actual->dibujar(w);
        actual = actual->enemigoSiguiente;
    }
}

void Cola::moverVisualmente(float desplazamiento) {
    Enemigo* actual = primero;
    while (actual) {
        Vector2f nuevaPos = actual->s->getPosition();
        nuevaPos.x += desplazamiento;
        actual->s->setPosition(nuevaPos);
        actual = actual->enemigoSiguiente;
    }
}

bool Cola::estaVacia() const {
    return primero == nullptr;
}

Enemigo* Cola::verPrimero() const {
    return primero;
}
