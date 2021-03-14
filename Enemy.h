#ifndef INCLUDED_ENEMY_H
#define INCLUDED_ENEMY_H

#include "Character.h"

namespace ent {
    namespace cha {
        namespace ini {
            class Enemy : public Character
            {
            protected:

                long int vidas;
                float dist_perc;
                float acumulador_dist;
                bool animacao_dano;

            public:

                Enemy(const bool pp = true, const float change_time = 0.4f, const string c = "");
                ~Enemy();

                virtual void Damage(long int attack_force);
                void setLifePoints(const unsigned long int);
                const long int getLifePoints() const;
            };
        }
    }
}

#endif // INCLUDED_ENEMY_H
