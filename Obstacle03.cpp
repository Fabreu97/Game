#include "Obstacle03.h"

ent::obs::Obstacle03::Obstacle03(const Vector2D<float> position, const Vector2D<float> tamanho, const string c):
    Obstacle(position, tamanho, c)
{
    id = IDOBS03;
    key = "Obstacle3";
}

ent::obs::Obstacle03::~Obstacle03()
{

}

void ent::obs::Obstacle03::setTexture(const string t)
{
    path = t;
    control->setTexture(key, t);
}

void ent::obs::Obstacle03::UpdatePosition()
{
    pos = control->getPosition(key);
}

void ent::obs::Obstacle03::InitialUpdate()
{

}

void ent::obs::Obstacle03::UpdateGerenciador()
{

}

void ent::obs::Obstacle03::Update()
{

}

void ent::obs::Obstacle03::Draw()
{
    control->Draw(key);
}

void ent::obs::Obstacle03::DrawPause()
{
    control->setPosition(key, pos);
    control->setSize(key, tam_tex);
    control->Draw(key);
}

void ent::obs::Obstacle03::Move(const Vector2D<float> v)
{
    control->Move(key, v);
}

void ent::obs::Obstacle03::Move(const float x, const float y)
{
    control->Move(key, x, y);
}
