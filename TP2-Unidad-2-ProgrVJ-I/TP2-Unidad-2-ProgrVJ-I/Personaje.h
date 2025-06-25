#pragma once
#include "Afichmation.h"
#include <SFML/Graphics.hpp>
#include "Audio.h"
#include "Objeto.h"
using namespace sf;

class Personaje : public Objeto {
    // Sonidow de salto,aterrizaje,l correr,al caminar
    Audio jump, land, running, runningMetal, walk, walkMetal;
    Afichmation polvo; // Efecto visual al saltar

    float velocidad = 90.f;          // Velocidad de movimiento horizontal
    float velocidadSalto = 330.f;    // Velocidad inicial al saltar
    float gravedad;                  // Valor de gravedad del mundo (inyectado)
    float velocidadY = 0.f;          // Velocidad vertical


    bool sobreMetal = false;         // Indica si está sobre una superficie metálica
    bool mostrarPolvoSalto = false;  // Indica si debe mostrar el efecto de polvo
    bool perdioPartida = false;      // Indica si el jugador perdió


    bool enElAire = false;       // Si el personaje está  en el aire
    bool saltoIniciado = false; // Detectar comienzo del salto
    bool caidaIniciada = false; // Detectar comienzo de una caída

    bool estaHerido = false;         // Estado de herido por colisión
    bool enStun = false;             // Estado de aturdimiento
    float tiempoHerido = 0.f;        // Tiempo desde que fue herido
    float tiempoStun = 0.f;          // Tiempo desde que está en estado de stun

    Keyboard::Key izq = Keyboard::A;         // Tecla para ir a la izquierda
    Keyboard::Key der = Keyboard::D;         // Tecla para ir a la derecha
    Keyboard::Key correr = Keyboard::LShift; // Tecla para correr
    Keyboard::Key saltar1 = Keyboard::Space; // Tecla principal para saltar
    Keyboard::Key saltar2 = Keyboard::W;     // Tecla alternativa para saltar

public:
    Personaje(Vector2f pos, float gravedadMundo);

    void actualizar(float deltaTime) override;          // Lógica de movimiento y física
    void manejarEventos(Event& e);             // Procesamiento de eventos del jugador
    void dibujar(RenderWindow& w)override;


    void animacion(float deltaTime) override;  // Cambia la animación según movimiento
    void mover(float deltaTime);               // Aplica movimiento horizontal
    void aplicarGravedad(float deltaTime);     // Aplica la gravedad al jugador

    void recibirGolpe();                        // cuando el personaje recibe daño
    void apoyarEn(float y);                     // Ajusta la posición al "apoyarse" en una plataforma

    bool estaQuieto();                         // Indica si el personaje está quieto
    void verificarLimitesPantalla();           // Evita que salga de la pantalla
    FloatRect verBounds() override;            // Devuelve los límites del sprite

    void queTerreno(bool esMetal);          // Define si el personaje en una plataforma

    void perdio();                          // cuando el jugador pierde la partida

    // Indican si está herido o aturdido
    bool esHerido();
    bool enStunActivo();


    float verVelocidadY() const { return velocidadY; } // Getter de velocidad vertical
    void queVelocidadY(float v) { velocidadY = v; }    // Setter de velocidad vertical

};


