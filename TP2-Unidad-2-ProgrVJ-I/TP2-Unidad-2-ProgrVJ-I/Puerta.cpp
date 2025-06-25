#include "Puerta.h"
Puerta::Puerta(Vector2f pos) : Objeto("assets/mundo/puerta_sheet.png", pos, { 63, 96 }){

    backGround.Add("idle", { 0,1,2,3,4,5,6,7,8,9,10,11}, 15, true);
    backGround.Add("open", { 12 }, 1, true);
    backGround.Play("idle");

}
void Puerta::abrioPuerta() {
    backGround.Play("open");
}


