#include "Plataforma.h"

Plataforma::Plataforma(Vector2f pos) {
	textura.loadFromFile("assets/mundo/plataforma.png");
	background.setTexture(textura);
	background.setOrigin(textura.getSize().x / 2, textura.getSize().y / 2);
	background.setPosition(pos);
}

FloatRect Plataforma::verBounds()
{
    return ajustarHitbox(35, 0, 0, 0);
}

void Plataforma::dibujar(RenderWindow& w) {
	w.draw(background);
	//ddibujarHitbox(w);
}

FloatRect Plataforma::ajustarHitbox(float top, float bottom, float left, float right) {
	FloatRect hitbox = background.getGlobalBounds();
	hitbox.top += top;
	hitbox.left += left;
	hitbox.width -= (left + right);
	hitbox.height -= (top + bottom);
	return hitbox;
}

void Plataforma::dibujarHitbox(RenderWindow& w) {
	FloatRect bounds = verBounds();
	RectangleShape hitboxVisual;
	hitboxVisual.setPosition(bounds.left, bounds.top);
	hitboxVisual.setSize(Vector2f(bounds.width, bounds.height));
	hitboxVisual.setFillColor(Color::Transparent);
	hitboxVisual.setOutlineColor(Color::Green);
	hitboxVisual.setOutlineThickness(1.f);
	w.draw(hitboxVisual);
}

Vector2f Plataforma::verPos() {
	return background.getPosition();
}
