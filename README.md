# Trabajo Práctico Nº 2 | Programación de Videojuegos I

## 🎮 Actividad

Este trabajo práctico consiste en realizar un juego de **plataformas 2D**, aplicando en código los conceptos de pilas y colas, vistos en la cursada.

## 🕹️ Gameplay

[![Ver video del gameplay](https://img.youtube.com/vi/468tXj5txqs/0.jpg)](https://youtu.be/468tXj5txqs)


## 📝 Consigna

Controlar un personaje que debe escalar plataformas, evitar enemigos y llegar a la puerta de salida antes de que finalice un tiempo límite.

### Mecánicas principales:
- 6 plataformas por donde el jugador puede desplazarse
- El personaje puede saltar a través de las plataformas desde abajo hacia arriba.
- Solo es posible avanzar hacia arriba, no se puede volver a plataformas anteriores.
- El personaje comienza en el piso 0 y debe llegar al piso 6, donde se encuentra la puerta de salida.
- En cada piso hay enemigos que se desplazan lateralmente, pero solo uno se mueve a la vez.
- Si el jugador toca a un enemigo, cae al piso inicial (0).

## ⏱️ Condiciones de fin de juego

- **Victoria:** el jugador llega a la puerta dentro del tiempo.
- **Derrota:** se agota el tiempo (30 segundos) antes de llegar.

## 📦 Implementación de Pilas y Colas

### 🔄 Colas (3 pisos)

Los enemigos en tres pisos utilizan una **estructura de cola**:

1. El primer enemigo de la cola comienza a desplazarse.
2. Al llegar al final del piso, **sale de pantalla** y se vuelve a insertar **al final de la cola**.
3. Se repite el ciclo para el siguiente enemigo en espera.

👉 Esto simula una **entrada ordenada y continua** de enemigos.

### 🔁 Pilas (3 pisos restantes)

Los otros pisos implementan una **estructura de pilas** (Pila A y Pila B):

1. El enemigo en el **tope de la Pila A** se mueve por el piso.
2. Al finalizar el recorrido, se inserta en la **Pila B**.
3. Cuando todos los enemigos se encuentran en la Pila B, el proceso se **invierte**, devolviendo cada enemigo a la Pila A.

👉 Esto simula un **flujo cíclico y controlado** de enemigos en el piso.


### Controles:
- **A / D**: mover al personaje
- **Espacio / W**: saltar
- **Shift + A / Shift + D**: correr

Al finalizar, se muestran **Game Over** o **You Win**.

## ⚙️ Tecnologías usadas

- C++
- SFML
- Visual Studio

## 🖼️ Créditos y Licencia de Assets

Los recursos gráficos utilizados en este proyecto provienen de:

- **CHARACTER ANIMATION ASSET PACK**
- **CITY STREET TILESET PACK**

Estos paquetes fueron creados por **Mucho Pixels**, un estudio especializado en pixel art para videojuegos.
> El paquete **CHARACTER ANIMATION ASSET PACK** es completamente gratuito y se puede usar en proyectos comerciales, con las siguientes restricciones:

❌ No está permitido redistribuir directamente los archivos.
❌ No se pueden utilizar como parte de un logotipo o marca registrada.


🔗 Sitio oficial: [www.muchopixels.com]

---

## ▶️ Cómo ejecutar
1. Descargar la carpeta **"Instalador"**.
2. Dentro encontrarás todos los archivos necesarios y un archivo ejecutable:  
   **`TP2-ProgrVJ-I.exe`**
3. Ejecutá el `.exe` directamente para jugar.

> ⚠️ No borrar ni mover los archivos que acompañan al ejecutable. El juego depende de ellos para funcionar correctamente.

---

## 👨‍💻 Autor

**JulioCZ**  
1° Cuatrimestre – Año 2025  
Tecnicatura en Diseño y Programación de Videojuegos
