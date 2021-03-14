#ifndef INCLUDED_OBSTACLE02_H
#define INCLUDED_OBSTACLE02_H

#include "Obstacle.h"

namespace ent {
    namespace obs {
        class Obstacle02 : public Obstacle
        {
        public:

            Obstacle02(const Vector2D<float> position = Vector2D<float>(700.0f, 772.0f), const Vector2D<float> tamanho = Vector2D<float>(2000.0, 400.0f), const string c = "Texture/Plataforma_03.png");
            ~Obstacle02();

            void setTexture(const string t);

            void UpdatePosition();
            void InitialUpdate ();//............TO DO
            void UpdateGerenciador();//.........TO DO
            void Update();//....................TO DO
            void Draw();//......................TO DO
            void DrawPause();

            void Move(const Vector2D<float> v);
            void Move(const float x, const float y);
        };
    }
}

#endif // INCLUDED_OBSTACLE02_H
