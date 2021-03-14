#include "Entity.h"

///IMPLEMENTACOES DA CLASS ENTIDADE

GraphicManager* ent::Entity::control = NULL;

ent::Entity::Entity(const string c)
{
    id = 0;
    path = c;
}

ent::Entity::~Entity()
{

}

void ent::Entity::setID(const unsigned long int ID)
{
    id = ID;
}

const unsigned long int ent::Entity::getID() const
{
    return(id);
}

const string ent::Entity::getKey() const
{
    return(key);
}

const string ent::Entity::getTexture() const
{
    return(path);
}

void ent::Entity::setSizeTexture(const Vector2D<float> v)
{
    tam_tex = v;
}

void ent::Entity::setSizeTexture(const float x, const float y)
{
    tam_tex.x = x;
    tam_tex.y = y;
}

const Vector2D<float> ent::Entity::getSizeTexture() const
{
    return(tam_tex);
}

void ent::Entity::setPosition(const Vector2D<float> v)
{
    pos = v;
}

void ent::Entity::setPosition(const float x, const float y)
{
    pos.x = x;
    pos.y = y;
}

const Vector2D<float> ent::Entity::getPosition() const
{
    return(pos);
}

void ent::Entity::setGraphicManager(GraphicManager* pg)
{
    control = pg;
}

GraphicManager* ent::Entity::getGraphicManager()
{
    return(control);
}

const long int ent::Entity::getLifePoints() const
{
    return(0);
}

const Vector2D<float> ent::Entity::getVelocidade() const
{
    return(VF(0.0f, 0.0f));
}

const Vector2D<unsigned long int> ent::Entity::getCurrentImage() const
{
    return(VLU(0lu, 0lu));
}
