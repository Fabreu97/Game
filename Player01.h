#ifndef INCLUDED_PLAYER01_H
#define INCLUDED_PLAYER01_H

#include "Player.h"

namespace ent {
    namespace cha {
        namespace jog {
            class Player01: public Player
            {
            private:

                unsigned long int col_estatico;
                unsigned long int col_andando;
                unsigned long int col_ataque;

            public:

                Player01(const float height_jumper = HEIGHTJUMPER, const float aceleracao = 30.0f, const bool pp = true, const float change_time = 0.15f, const string c = "Texture/tux_from_linux.png");
                ~Player01();

                void setTexture(const string t);

                //Update
                void Update(); //Posso Ocultar
                void InitialUpdate();
                void UpdatePosition();
                void UpdateMovement();
                void UpdateAnimacao();
                void UpdateGerenciador();

                void Draw();
                void DrawPause();
                void OnCollision(); //..............REVIEW

                void Move(const Vector2D<float> v);
                void Move(const float x, const float y);

                void DispararProjetil();
                void DrawProjetil();
                void DrawProjetilPause();
                const long int getLifePoints() const;
            };
        }
    }
}

#endif // INCLUDED_PLAYER01_H
