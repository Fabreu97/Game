#ifndef INCLUDED_OBSTACLE03_H
#define INCLUDED_OBSTACLE03_H

#include "Obstacle.h"

namespace ent {
    namespace obs {
        class Obstacle03 : public Obstacle
        {
        private:

        public:

            Obstacle03(const Vector2D<float> position = Vector2D<float>(700.0f, 772.0f), const Vector2D<float> tamanho = Vector2D<float>(2000.0, 400.0f), const string c = "Texture/Plataforma_03.png");
            ~Obstacle03();

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

#endif // INCLUDED_OBSTACLE03_H
