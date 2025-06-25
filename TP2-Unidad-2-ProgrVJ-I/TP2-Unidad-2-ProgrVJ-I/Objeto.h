#pragma once
#include "Afichmation.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Objeto {
protected:
    Afichmation backGround; // Sprite animado del objeto

public:
    Objeto(const string& rutaSprite, Vector2f pos, Vector2i frameSize, float escala = 1.f)
        : backGround(rutaSprite, true, frameSize.x, frameSize.y) {
        backGround.setPosition(pos);
        backGround.setScale(escala, escala);
    }
    // Actualiza el estado del objeto
    virtual void actualizar(float deltaTime) {
        animacion(deltaTime);
        backGround.Update();
    }
    // Método puro que debe implementarse en clases derivadas
    virtual void animacion(float deltaTime) {};

    // Dibuja el objeto en la ventana.
    virtual void dibujar(RenderWindow& w){
        w.draw(backGround);
        // Para mostrar la hitbox con fines de depuración
        //dibujarHitbox(w);
    }
    // Cambia la posición del objeto.
    virtual void quePos(Vector2f pos) {
        backGround.setPosition(pos);
    }
    // Devuelve la posición actual del objeto.
    Vector2f verPos() const {
        return backGround.getPosition();
    }

    // Devuelve los límites globales del sprite
    virtual FloatRect verBounds() {
        return backGround.getGlobalBounds();
    }

    // Permite ajustar manualmente la hitbox del objeto
    FloatRect ajustarHitbox(FloatRect original, float top, float bottom, float left, float right) {
        original.top += top;
        original.left += left;
        original.width -= (left + right);
        original.height -= (top + bottom);
        return original;
    }
    // Dibuja visualmente la hitbox del objeto
    void dibujarHitbox(RenderWindow& w) {
        FloatRect bounds = verBounds();
        RectangleShape hitboxVisual;
        hitboxVisual.setPosition(bounds.left, bounds.top);
        hitboxVisual.setSize(Vector2f(bounds.width, bounds.height));
        hitboxVisual.setFillColor(Color::Transparent);
        hitboxVisual.setOutlineColor(Color::Red);
        hitboxVisual.setOutlineThickness(1.f);
        w.draw(hitboxVisual);
    }
};
