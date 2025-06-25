#include "Enemigo.h"

Enemigo::Enemigo(Vector2f pos, char c) : 
    polvo("assets/enemigos/polvo.png",true,50,50),color(c) {
	t = new Texture();
    switch (c) {
    case 'R': // rojo
        t->loadFromFile("assets/enemigos/barril_rojo.png");
        break;
    case 'G': // verde
        t->loadFromFile("assets/enemigos/barril_verde.png");
        break;
    case 'B': // azul
        t->loadFromFile("assets/enemigos/barril_azul.png");
        break;
    case 'Y': // amarillo
        t->loadFromFile("assets/enemigos/barril_amarillo.png");
        break;
    default:
        t->loadFromFile("assets/enemigos/barril_rojo.png"); 
        break;
    }
	s = new Sprite(*t);
    s->setOrigin(t->getSize().x / 2, t->getSize().y / 2);
	s->setPosition(pos);
    enemigoSiguiente = nullptr;

    polvo.Add("walking", {0,1,2,3,4,5},15,true);
    polvo.setScale(1.5, 1.5);
}

void Enemigo::actualizar(float dt) {
    if (enMovimiento && !llegoDestino) {
        polvo.Update();
        polvo.Play("walking");

        Vector2f pos = s->getPosition();
        float dx = destino.x - pos.x;

        // Dirección unitaria: -1 (izquierda), 1 (derecha)
        float direccion = (dx > 0) ? 1.f : -1.f;

        // Flip del polvo si va hacia la izquierda
        polvo.FlipX(direccion < 0);

        // Posicionar el polvo detrás del sprite, según dirección
        float offsetX = (direccion > 0)
            ? -polvo.getGlobalBounds().width + 50   
            : s->getGlobalBounds().width - 10;

        polvo.setPosition(s->getPosition().x + offsetX, s->getPosition().y + 3);

        s->move(direccion * velocidad * dt, 0.f);

        float rotacion = direccion * velocidad * dt * 5.f; 
        s->rotate(rotacion);

        // Comprobación para no pasarse
        if ((direccion > 0 && s->getPosition().x >= destino.x) ||
            (direccion < 0 && s->getPosition().x <= destino.x)) {
            s->setPosition(destino.x, pos.y);
            llegoDestino = true;
            enMovimiento = false;
        }
    }
}

void Enemigo::dibujar(RenderWindow& w){
    w.draw(*s);
    w.draw(polvo);
    //dibujarHitbox(w);
}
void Enemigo::dibujarHitbox(sf::RenderWindow& w) {
    FloatRect bounds = s->getGlobalBounds();

    RectangleShape rect;
    rect.setPosition(bounds.left, bounds.top);
    rect.setSize(Vector2f(bounds.width, bounds.height));
    rect.setFillColor(Color::Transparent);
    rect.setOutlineColor(Color::Red);
    rect.setOutlineThickness(1.f);

    w.draw(rect);
}


FloatRect Enemigo::verBounds()
{
	return s->getGlobalBounds();
}

Vector2f Enemigo::verPos() {
    return s->getPosition();
}
