#include "Platform.h"

ent::obs::Platform::Platform(const Vector2D<float> position, const Vector2D<float> tamanho, const string c):
    Obstacle(position, tamanho, c)
{
    id = IDPLATF;
    key = "Platform";
    setTexture("Texture/MeioChaoGrande.png");
}
ent::obs::Platform::~Platform()
{

}

void ent::obs::Platform::setTexture(const string t)
{
    path = t;
    control->setTexture(key, path);
}

void ent::obs::Platform::UpdatePosition()
{
    pos = control->getPosition(key);
}
void ent::obs::Platform::InitialUpdate ()
{
    control->setSize(key, tam);
    control->setPosition(key, pos);
}
void ent::obs::Platform::UpdateGerenciador()
{
    control->setSize(key, tam);
    control->setPosition(key, pos);
}
void ent::obs::Platform::Update()
{
    control->setSize(key, tam);
    control->setPosition(key, pos);
}
void ent::obs::Platform::Draw()
{
    control->Draw(key);
}

void ent::obs::Platform::DrawPause()
{
    control->setPosition(key, pos);
    control->setSize(key, tam_tex);
    control->Draw(key);
}

void ent::obs::Platform::Move(const Vector2D<float> v)
{
    control->Move(key, v);
}

void ent::obs::Platform::Move(const float x, const float y)
{
    //control->movePlataforma(x,y);
    control->Move(key, x, y);
}

