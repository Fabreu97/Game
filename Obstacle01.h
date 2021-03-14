#ifndef INCLUDED_OBSTACLE01_H
#define INCLUDED_OBSTACLE01_H

#include "Obstacle.h"

namespace ent {
    namespace obs {
        class Obstacle01 : public Obstacle
        {
        public:

            Obstacle01(const Vector2D<float> position = Vector2D<float>(1000.0f, 300.0f), const Vector2D<float> tamanho = Vector2D<float>(64.0, 64.0f), const string c = "Texture/bau.png");
            ~Obstacle01();

            void setTexture(const string t);

            void UpdatePosition();
            void InitialUpdate ();//...........TO DO
            void UpdateGerenciador();//........TO DO
            void Update();//...................TO DO
            void Draw();//.....................TO DO
            void DrawPause();

            void Move(const Vector2D<float> v);
            void Move(const float x, const float y);
        };
    }
}

#endif // INCLUDED_OBSTACLE01_H
