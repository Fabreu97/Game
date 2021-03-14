#include "CollidingEntity.h"

ent::CollidingEntity::CollidingEntity(const string c):
    Entity(c),
    colidiu(false),
    hcollision(false, false),
    vcollision(false, false),
    tam(tam_tex)
{
}

ent::CollidingEntity::~CollidingEntity()
{

}

void ent::CollidingEntity::setColisao(const bool c)
{
    colidiu = c;
}

const bool ent::CollidingEntity::getColisao() const
{
    return(colidiu);
}

void ent::CollidingEntity::restartCollisions()
{
    VB aux(false, false);
    hcollision = aux;
    vcollision = aux;
}

void ent::CollidingEntity::setHorizontalCollision(const VB v)
{
    if(!hcollision.x)
    {
        hcollision.x = v.x;
    }
    if(!hcollision.y)
    {
        hcollision.y = v.y;
    }
}

void ent::CollidingEntity::setHorizontalCollision(const bool x, const bool y)
{
    if(!hcollision.x)
    {
        hcollision.x = x;
    }
    if(!hcollision.y)
    {
        hcollision.y = y;
    }
}

const VB ent::CollidingEntity::getHorizontalCollision() const
{
    return(hcollision);
}

void ent::CollidingEntity::setVerticalCollision(const VB v)
{
    if(!vcollision.x)
    {
        vcollision.x = v.x;
    }
    if(!vcollision.y)
    {
        vcollision.y = v.y;
    }
}

void ent::CollidingEntity::setVerticalCollision(const bool x, const bool y)
{
    if(!vcollision.x)
    {
        vcollision.x = x;
    }
    if(!vcollision.y)
    {
        vcollision.y = y;
    }
}

const VB ent::CollidingEntity::getVerticalCollision() const
{
    return(vcollision);
}

void ent::CollidingEntity::setSize(const Vector2D<float> v)
{
    tam = v;
}

void ent::CollidingEntity::setSize(const float x, const float y)
{
    tam.x = x;
    tam.y = y;
}

Vector2D<float> ent::CollidingEntity::getSize() const
{
    return(tam);
}

const Vector2D<float> ent::CollidingEntity::getHalfSize() const
{
    return(tam * 0.5f);
}
