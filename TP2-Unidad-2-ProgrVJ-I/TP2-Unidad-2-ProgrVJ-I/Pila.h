#pragma once
#include "Enemigo.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Enemigo;

class Pila {
private:
    Enemigo* tope = nullptr; // Puntero al enemigo en el tope de la pila
    float espacio = 40.f;    // Espaciado horizontal entre enemigos

public:
    Pila();
    ~Pila();

    // Agrega un enemigo al tope de la pila
    void agregar(Vector2f pos, char color, float escalaX);

    // Elimina el tope de la pila 
    void eliminar(Vector2f& posOut, char& colorOut);

    // Devuelve la cantidad de enemigos en la pila
    int contar();

    // Dibuja todos los enemigos de la pila
    void dibujar(RenderWindow& w);

    // Devuelve un puntero al enemigo del tope
    Enemigo* verTope() const;

    // Devuelve true si la pila está vacía
    bool estaVacia();
};


