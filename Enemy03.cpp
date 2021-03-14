#include "Enemy03.h"

ent::cha::ini::Enemy03::Enemy03(const bool pp, const float change_time, const string c):
    Enemy(pp,change_time,c)
    {
        id = IDINI03;
        key = "Enemy3";
    }

ent::cha::ini::Enemy03::~Enemy03()
{

}

void ent::cha::ini::Enemy03::Damage(long int attack_force)
{
    vidas -= attack_force;
    animacao_dano = true;
    imagem_atual.x = 0lu;

}

void ent::cha::ini::Enemy03::setTexture(const string t)
{
    path = t;
    control->setTexture(key, path);
}

void ent::cha::ini::Enemy03::Update()
{

}

void ent::cha::ini::Enemy03::InitialUpdate()
{
    control->setSize(key, tam_tex);
    control->setPosition(key, pos);
}

void ent::cha::ini::Enemy03::UpdateAnimacao()
{

}

void ent::cha::ini::Enemy03::UpdateGerenciador()
{

}

void ent::cha::ini::Enemy03::UpdatePosition()
{
    pos = control->getPosition(key);
}

void ent::cha::ini::Enemy03::Draw()
{
    control->Draw(key);
}

void ent::cha::ini::Enemy03::DrawPause()
{
    control->setIntRect(key, width_height.x, width_height.y, left_top.x, left_top.y);
    control->setTextureRect(key);
    control->setPosition(key, pos);
    control->setSize(key, tam_tex);
    control->Draw(key);
}

void ent::cha::ini::Enemy03::Move(const Vector2D<float> v)
{
    control->Move(key, v);
}

void ent::cha::ini::Enemy03::Move(const float x, const float y)
{
    control->Move(key, x, y);
}
