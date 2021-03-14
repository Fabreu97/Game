#ifndef INCLUDED_LIFE_BAR_H
#define INCLUDED_LIFE_BAR_H

#include "Character.h"

namespace ent{
    namespace cha{
        class LifeBar: public Character {
        private:

            long int vidas;
            bool invulnerable;
            long int damage;
            float time_in;
            float tempo_invulnerabilidade;

        public:

            LifeBar (const unsigned long int life = QTD_VIDAS_JOG);
            ~LifeBar ();

            void setTexture(const string t = "Texture/CCC.png");
            const long int getLifePoints() const;
            void Damage(const unsigned long int attack_force);
            const bool getInvulnerable() const;

            void InitialUpdate ();
            void UpdatePosition(); //VOID
            void UpdateAnimacao();
            void UpdateGerenciador ();
            void Update ();
            void Draw ();
            void DrawPause ();

            void Move(const Vector2D<float> v);
            void Move(const float x, const float y);
        };
    }
}

#endif // INCLUDED_LIFE_BAR_H
