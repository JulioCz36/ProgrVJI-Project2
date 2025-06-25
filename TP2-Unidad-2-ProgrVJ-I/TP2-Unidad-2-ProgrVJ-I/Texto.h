#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// Clase auxiliar para manejar texto en pantalla.

class Texto {
private:
    Text texto;       // Objeto de texto de SFML
    Font fuente;      // Fuente usada para mostrar el texto

public:
    Texto() = default;

    void inicializar(int size) {
        // Carga la fuente y configura el texto con tamaño y color inicial
        fuente.loadFromFile("assets/font/Pixeled.ttf");
        texto.setFont(fuente);
        texto.setCharacterSize(size);
        texto.setFillColor(Color(26, 25, 50)); // Azul oscuro
    }

    void queSize(int size) {
        // Cambia el tamaño del texto
        texto.setCharacterSize(size);
    }

    void queTexto(const string& str) {
        // Establece el contenido del texto y lo centra respecto a su posición
        texto.setString(str);
        FloatRect bounds = texto.getGlobalBounds();
        texto.setOrigin(bounds.width / 2, bounds.height / 2);
    }

    void quePosicion(float x, float y) {
        // Define la posición del texto en la ventana
        texto.setPosition(x, y);
    }

    void queColor(Color color) {
        // Cambia el color del texto
        texto.setFillColor(color);
    }

    Vector2f verPosicion() const {
        return texto.getPosition();
    }

    Text& verTexto() {
        // Acceso directo al objeto Text
        return texto;
    }

    string verString() const {
        // Devuelve el texto actual como string estándar
        return texto.getString().toAnsiString();
    }

    void dibujar(RenderWindow& window) {
        // Dibuja el texto en la ventana
        window.draw(texto);
    }
};