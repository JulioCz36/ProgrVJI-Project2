#pragma once
#include "Enemigo.h"
class Enemigo;

class Cola {
private:
    Enemigo* primero = nullptr; // Primer enemigo en la cola
    Enemigo* ultimo = nullptr;  // Último enemigo en la cola

public:
    Cola();
    ~Cola();

    // Agrega un enemigo al final de la cola
    void agregar(Vector2f pos, char color, float escalaX);

    // Elimina el primer enemigo de la cola (deja su info en los parámetros)
    void eliminar(Vector2f& posOut, char& colorOut);

    // Dibuja todos los enemigos de la cola
    void dibujar(RenderWindow& w);

    // Mueve visualmente todos los enemigos en X
    void moverVisualmente(float desplazamiento);

    // Devuelve true si la cola está vacía
    bool estaVacia() const;

    // Devuelve un puntero al primer enemigo de la cola
    Enemigo* verPrimero() const;
};


