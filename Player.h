#ifndef INCLUDED_PLAYER_H
#define INCLUDED_PLAYER_H

#include "LifeBar.h"
#include "Projectile.h"
#include "QueueProjectile.h"

namespace ent {
    namespace cha {
        namespace jog {
            class Player: public Character {
            protected:

                LifeBar vida;
                List<Projectile> FilaProjetil;
                float tempo_entre_disparo;
                float time_projetil;
                unsigned long int cont_projetil;

                float speed; // aceleracao
                float altura_salto;
                bool animacao_disparo; //APENAS QUEM PODERÁ SOLTA UM PROJETIL

            public:

                Player(const float height_jumper = 1000.0f, const float aceleracao = 200.0f, const bool pp = false, const float change_time = 0.15f, const string c = "Texture/tux_from_linux.png");
                ~Player();

                //MÉTODOS DA CLASSE BARRA_DE_VIDA:
                const bool getInvulnerable() const;
                void setTempoCicloLife(const float a);
                void setTextureLife(const string t = "Texture/CCC.png");
                void setSizeLife(Vector2D<float> s);
                void setSizeLife(const float x, const float y);
                void setContImageLife(const Vector2D<unsigned long int> v);
                void setContImageLife(const unsigned long int x, const unsigned long int y);
                void setCurrentImageLife(const Vector2D<unsigned long int> v);
                void setCurrentImageLife(const unsigned long int x, const unsigned long int y);
                void Damage(const unsigned long int attack_force);

                void setSpeed(const float aceleracao);
                const float getSpeed() const;

                void setAlturaSalto(const float& a);
                const float getAlturaSalto() const;

                //MÉTODOS DA LISTA PROJETIL
                ent::cha::Projectile* getProjetil(const unsigned long int indice) const;
                const unsigned long int getSizeListaProjetil() const;

            };
        }
    }
}

#endif // INCLUDED_PLAYER_H
