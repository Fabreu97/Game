#ifndef INCLUDED_COLLIDING_ENTITY_H
#define INCLUDED_COLLIDING_ENTITY_H

#include "Entity.h"

namespace ent{
    class CollidingEntity: public Entity
        {
        protected:

            bool colidiu;
            VB hcollision;
            VB vcollision;
            Vector2D<float> tam;

        public:

            CollidingEntity(const string c = "");
            virtual ~CollidingEntity();

            void setColisao(const bool c);
            const bool getColisao() const;

            void restartCollisions();
            void setHorizontalCollision(const VB v);
            void setHorizontalCollision(const bool x, const bool y);
            const VB getHorizontalCollision() const;
            void setVerticalCollision(const VB v);
            void setVerticalCollision(const bool x, const bool y);
            const VB getVerticalCollision() const;

            void setSize(const Vector2D<float> v);
            void setSize(const float x, const float y);
            Vector2D<float> getSize() const;
            const Vector2D<float> getHalfSize() const;
            virtual void UpdatePosition() = 0;
            virtual void Move(const Vector2D<float> v) = 0;
            virtual void Move(const float x, const float y) = 0;
        };
}

#endif // INCLUDED_COLLIDING_ENTITY_H
