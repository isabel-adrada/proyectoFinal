#ifndef RAY_H
#define RAY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Jugador.h"
#include "Personaje.h"
#include "Escenario.h"
#include "Collider.h"

// Clase forward declaration para evitar inclusión circular
class HormigaInfectada;

// Clase Ray (no hereda de HormigaNormal)
class Ray : public Personaje, public Jugador {
private:
    // Miembros propios
    sf::RectangleShape hitbox;  // Hitbox para colisiones
    Collider* collider;         // Collider para el sistema AABB

    std::vector<sf::Texture> texturasDerecha;
    std::vector<sf::Texture> texturasIzquierda;
    std::vector<sf::Texture> texturasFrontal;
    std::vector<sf::Texture> texturasAtaque;

    int frameActual = 0;
    bool moviendoDerecha = false;
    bool moviendoIzquierda = false;
    bool enMovimiento = false;
    bool mirandoDerecha = true;
    bool atacando = false;

    sf::Clock relojAnimacion;
    sf::Clock relojAtaque;

    // Variables para el salto
    float velocidadY = 0.0f;
    float gravedad = 0.3f;
    bool enAire = false;
    float alturaSuelo = 750.0f;

    // Rango de ataque
    float rangoAtaque = 50.0f;

    int luz;

public:
    Ray(std::string nombreJugador);
    virtual ~Ray();
    sf::Sprite sprite;

    // Métodos de movimiento
    void caminarAdelante();
    void caminarAtras();
    void detener();
    void saltar();

    // Métodos de ataque específicos de Ray
    int golpearConBaston();
    bool atacarEnemigo(HormigaInfectada* enemigo);  // Atacar específicamente a hormiga infectada
    int golpearConLuz();
    int superGolpeDeLuz();

    // Getters y setters
    void setLuz(int luz);
    int getLuz();
    sf::Vector2f getPosicion() const { return sprite.getPosition(); }
    bool estaEnAire() const { return enAire; }
    bool estaMirandoDerecha() const { return mirandoDerecha; }
    bool estaAtacando() const { return atacando; }
    float getAlturaSuelo() const { return alturaSuelo; }
    sf::FloatRect getBounds() const { return hitbox.getGlobalBounds(); }
    Collider* getCollider() const { return collider; }

    void setPosicion(float x, float y);

    // Métodos para actualizar y dibujar
    void actualizar(Escenario* escenario = nullptr);
    void dibujar(sf::RenderWindow& ventana);

private:
    // Métodos auxiliares privados para cargar texturas
    void cargarTexturas();
    void actualizarHitbox();
};

#endif