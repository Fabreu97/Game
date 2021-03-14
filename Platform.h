#ifndef INCLUDED_PLATFORM_H
#define INCLUDED_PLATFORM_H

#include "Obstacle.h"

namespace ent {
    namespace obs {
        class Platform : public Obstacle
        {
        public:
            Platform(const Vector2D<float> position = Vector2D<float>(1000.0f, 300.0f), const Vector2D<float> tamanho = Vector2D<float>(2000.0, 400.0f), const string c = "Texture/MeioChaoGrande.png");
            ~Platform();

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

#endif // INCLUDED_PLATFORM_H
