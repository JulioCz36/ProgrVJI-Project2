#include "Pila.h"
Pila::Pila() = default;;
Pila::~Pila() {
    while (tope) {
        Enemigo* borrar = tope;
        tope = tope->enemigoSiguiente;
        delete borrar;
    }
}

void Pila::agregar(Vector2f pos, char color, float escalaX) {
    Enemigo* nuevo = new Enemigo(pos, color);
    nuevo->s->setScale(escalaX, 1.f);
    nuevo->enemigoSiguiente = tope;
    tope = nuevo;
}
void Pila::eliminar(Vector2f& posOut, char& colorOut) {
    if (tope == nullptr) return;
    Enemigo* aux = tope;
    posOut = aux->verPos();
    colorOut = aux->color;
    tope = aux->enemigoSiguiente;
    delete aux;
}
int Pila::contar() {
    int cant = 0;
    Enemigo* actual = tope;
    while (actual) {
        cant++;
        actual = actual->enemigoSiguiente;
    }
    return cant;
}

void Pila::dibujar(RenderWindow& w) {
    Enemigo* actual = tope;
    while (actual) {
        actual->dibujar(w);
        actual = actual->enemigoSiguiente;
    }
}
Enemigo* Pila::verTope() const { return tope; }
bool Pila::estaVacia() { return tope == nullptr; }