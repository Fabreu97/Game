#ifndef INCLUDED_OBSTACLE_H
#define INCLUDED_OBSTACLE_H

#include "CollidingEntity.h"

namespace ent {
    namespace obs {
        class Obstacle : public CollidingEntity
        {
        protected:

            Vector2D<float> velocidade;
            float push_jogador;

        public:
            Obstacle(const Vector2D<float> position = Vector2D<float>(700.0f, 772.0f), const Vector2D<float> tamanho = Vector2D<float>(2000.0, 400.0f), const string c = "Texture/MeioChaoGrande.png");
            virtual ~Obstacle();

            void setVelocidade(const Vector2D<float> v);
            void setVelocidade(const float x, const float y);
            const Vector2D<float> getVelocidade() const;

            void setPush(const float p);
            const float getPush() const;

            virtual void setTempoCiclo(const float t);
            virtual const float getTempoCiclo() const;

            virtual void setCurrentImage(const Vector2D<unsigned long int> v);
            virtual void setCurrentImage(const unsigned long int x, const unsigned long int y);
            virtual const Vector2D<unsigned long int> getCurrentImage() const;

            virtual void setContImage(const Vector2D<unsigned long int> v);
            virtual void setContImage(const unsigned long int x, const unsigned long int y);
            virtual const Vector2D<unsigned long int> getContImage() const;
        };
    }
}

#endif // INCLUDED_OBSTACLE_H
