#include "Enemy02.h"

ent::cha::ini::Enemy02::Enemy02(const bool pp, const float change_time, const string c):
    Enemy(pp,change_time,c)
    {
        id = IDINI02;
        key = "Enemy2";
    }

ent::cha::ini::Enemy02::~Enemy02()
{

}

void ent::cha::ini::Enemy02::Damage(long int attack_force)
{
    vidas -= attack_force;
    animacao_dano = true;
    imagem_atual.x = 0lu;

}

void ent::cha::ini::Enemy02::setTexture(const string t)
{
    path = t;
    control->setTexture(key, path);
}

void ent::cha::ini::Enemy02::Update()
{

}

void ent::cha::ini::Enemy02::InitialUpdate()
{

}

void ent::cha::ini::Enemy02::UpdateAnimacao()
{

}

void ent::cha::ini::Enemy02::UpdateGerenciador()
{

}

void ent::cha::ini::Enemy02::UpdatePosition()
{
    pos = control->getPosition(key);
}

void ent::cha::ini::Enemy02::Draw()
{
    control->Draw(key);
    cout << endl;
    cout << "Position: " << "(" << pos.x << " , " << pos.y << ")" << endl;
    cout << "Size: " << "(" << tam.x << " , " << tam.y << ")" << endl;
    cout << "SizeTextura: " << "(" << tam_tex.x << " , " << tam_tex.y << ")" << endl;
    cout << "WidthHeight: " << "(" << width_height.x << " , " << width_height.y << ")" << endl;
    cout << "LeftTop: " << "(" << left_top.x << " , " << left_top.y << ")" << endl;
    cout << endl;
}

void ent::cha::ini::Enemy02::DrawPause()
{
    control->setIntRect(key, width_height.x, width_height.y, left_top.x, left_top.y);
    control->setTextureRect(key);
    control->setPosition(key, pos);
    control->setSize(key, tam_tex);
    control->Draw(key);
}

void ent::cha::ini::Enemy02::Move(const Vector2D<float> v)
{
    control->Move(key, v);
}

void ent::cha::ini::Enemy02::Move(const float x, const float y)
{
    control->Move(key, x, y);
}
