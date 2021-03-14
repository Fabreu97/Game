#ifndef INCLUDED_PLAYER02_H
#define INCLUDED_PLAYER02_H

#include "Player.h"

namespace ent {
    namespace cha {
        namespace jog {
            class Player02 : public Player
            {
            public:

                Player02(const float height_jumper = HEIGHTJUMPER, const float aceleracao = 200.0f, const bool pp = true, const float change_time = 0.15f, const string c = "Texture/tux_from_linux.png");
                ~Player02();

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
                void OnCollision();

                void Move(const Vector2D<float> v);
                void Move(const float x, const float y);
            };
        }
    }
}

#endif // INLCUDED_PLAYER02_H
