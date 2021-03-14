#ifndef INCLUDED_ENEMY01_H
#define INCLUDED_ENEMY01_H

#include "Enemy.h"

namespace ent {
    namespace cha {
        namespace ini{
            class Enemy01 : public Enemy
            {
            public:

                Enemy01(const bool pp = true, const float change_time = 0.4f, const string c = "");
                ~Enemy01();
                void Damage(long int attack_force);
                void setTexture(const string t);

                //Update
                void Update();//.................. TO DO
                void InitialUpdate();//............TO DO
                void UpdateMovement();//...........TO DO
                void UpdateAnimacao();//...........TO DO
                void UpdateGerenciador();//........TO DO
                void UpdatePosition();

                void Draw();
                void DrawPause();

                void Move(const Vector2D<float> v);
                void Move(const float x, const float y);
            };
        }
    }
}

#endif // INCLUDED_ENEMY01_H
