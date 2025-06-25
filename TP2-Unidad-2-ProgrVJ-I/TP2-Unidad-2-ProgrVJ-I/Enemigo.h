#pragma once
#include "Pila.h"
#include "Partida.h"
#include "Afichmation.h"
#include <SFML/Graphics.hpp>
using namespace sf;


class Enemigo {
    // Declaraci�n de clases amigas para acceder a miembros privados
    friend class Partida;
    friend class Pila;
    friend class Cola;

    Texture* t;      // Textura del enemigo
    Sprite* s;       // Sprite que representa visualmente al enemigo
    char color;      // Color del enemigo ('R', 'G', 'B', 'Y')

    float velocidad = 400.f;  // Velocidad de movimiento al desplazarse

    bool enMovimiento = false;   // Si est� en transici�n
    bool llegoDestino = false;   // Si alcanz� su destino 
    Vector2f destino;            // Coordenada final de su movimiento

    Afichmation polvo;           // Efecto de polvo

public:
    Enemigo(Vector2f pos, char color);

    // Actualiza la posici�n del enemigo si est� en movimiento
    void actualizar(float dt);

    // Dibuja el sprite del enemigo en la ventana
    void dibujar(RenderWindow& w);

    // Dibuja la hitbox (para debug)
    void dibujarHitbox(sf::RenderWindow& w);

    // Devuelve la hitbox del enemigo
    FloatRect verBounds();

    // Devuelve la posici�n actual del sprite
    Vector2f verPos();

    // Devuelve el color del enemigo
    char verColor() { return color; }

    // Puntero al siguiente enemigo en la estructura 
    Enemigo* enemigoSiguiente;
};


