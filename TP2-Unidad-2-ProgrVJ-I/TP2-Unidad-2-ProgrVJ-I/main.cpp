#include "Juego.h"

//Créditos y Licencia de Assets

// Los recursos gráficos utilizados en este proyecto provienen de los paquetes:
// - CHARACTER ANIMATION ASSET PACK
// - CITY STREET TILESET PACK 
// Ambos pertenecen a Mucho Pixels, un estudio de entretenimiento especializado en pixel art para videojuegos.
// Importante:
// - El paquete CHARACTER ANIMATION ASSET PACK es completamente gratuito y puede usarse incluso en proyectos comerciales.
// Sitio oficial para más información y recursos: https://www.muchopixels.com

int main() {
	srand(static_cast<unsigned>(time(0)));

	Juego juego;

	juego.jugar();

	return 0;
}