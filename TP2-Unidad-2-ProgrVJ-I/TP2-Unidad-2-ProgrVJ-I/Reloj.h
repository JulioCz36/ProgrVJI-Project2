#pragma once
#include <SFML/System.hpp>
using namespace sf;

// Clase auxiliar que permite llevar el control del tiempo transcurrido
// con la capacidad de pausar y reanudar 
class Reloj {
private:
    Clock reloj;               // Reloj interno de SFML
    float tiempoPausado = 0.f; // Tiempo total acumulado en pausa
    bool enPausa = false;      // Indica si actualmente está pausado
    Time tiempoInicioPausa;    // Momento exacto en que se pausó

public:

    void pausar() {
        // Registra el tiempo en que se pausó si no estaba ya en pausa
        if (!enPausa) {
            enPausa = true;
            tiempoInicioPausa = reloj.getElapsedTime();
        }
    }

    void reanudar() {
        // Calcula cuánto duró la pausa y lo acumula
        if (enPausa) {
            Time ahora = reloj.getElapsedTime();
            tiempoPausado += (ahora - tiempoInicioPausa).asSeconds();
            enPausa = false;
        }
    }


    float verTiempoTranscurrido() const {
        // Devuelve el tiempo real transcurrido, excluyendo pausas
        if (enPausa) {
            return (tiempoInicioPausa.asSeconds() - tiempoPausado);
        }
        else {
            return (reloj.getElapsedTime().asSeconds() - tiempoPausado);
        }
    }

    void reiniciar() {
        // Reinicia completamente el reloj y elimina las pausas anteriores
        reloj.restart();
        tiempoPausado = 0.f;
        enPausa = false;
    }

    float verReinicio() {
        // Retorna el tiempo actual transcurrido y reinicia el reloj
        float tiempo = verTiempoTranscurrido();
        reloj.restart();
        return tiempo;
    }
};