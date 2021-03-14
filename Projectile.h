#ifndef INCLUDED_PROJECTILE_H
#define INCLUDED_PROJECTILE_H

#include "Character.h"

namespace ent {
    namespace cha {
        class Projectile: public Character
        {
        private:

            long int damage;
            float tempo_vida;
            float tempo_entre_disparo;
            float timev;
            float speed;

        public:

            Projectile(const long int dano = PROJECTILE_DAMAGE, const bool fc = true, const float lifetime = TEMPO_VIDA_PROJETIL_JOGADOR, const float time_between_shots = 0.2f);
            ~Projectile();

            const long int attackForce() const; //getDano();

            void setTexture(const string t);

            void InitialUpdate ();
            void UpdatePosition();
            void UpdateAnimacao();
            void UpdateGerenciador ();
            void Update ();
            void Draw ();
            void DrawPause();

            void Move(const Vector2D<float> v);
            void Move(const float x, const float y);

            const bool operator == (const ent::cha::Projectile& p) const;
            const bool operator != (const ent::cha::Projectile& p) const;
            void operator=(const ent::cha::Projectile& p);
        };
    }
}

#endif // INCLUDED_PROJECTILE_H
