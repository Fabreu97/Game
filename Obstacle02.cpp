#include "Obstacle02.h"

ent::obs::Obstacle02::Obstacle02(const Vector2D<float> position, const Vector2D<float> tamanho, const string c):
    Obstacle(position, tamanho, c)
{
    id = IDOBS02;
    key = "Obstacle2";
}

ent::obs::Obstacle02::~Obstacle02()
{

}

void ent::obs::Obstacle02::setTexture(const string t)
{
    path = t;
    control->setTexture(key, path);
}

void ent::obs::Obstacle02::UpdatePosition()
{
    pos = control->getPosition(key);
}

void ent::obs::Obstacle02::InitialUpdate()
{

}

void ent::obs::Obstacle02::UpdateGerenciador()
{

}

void ent::obs::Obstacle02::Update()
{

}

void ent::obs::Obstacle02::Draw()
{
    control->Draw(key);
}

void ent::obs::Obstacle02::DrawPause()
{
    control->setPosition(key, pos);
    control->setSize(key, tam_tex);
    control->Draw(key);
}

void ent::obs::Obstacle02::Move(const Vector2D<float> v)
{
    control->Move(key, v);
}

void ent::obs::Obstacle02::Move(const float x, const float y)
{
    control->Move(key, x, y);
}
