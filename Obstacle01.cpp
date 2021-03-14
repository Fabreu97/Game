#include "Obstacle01.h"

ent::obs::Obstacle01::Obstacle01(const Vector2D<float> position, const Vector2D<float> tamanho, const string c):
    Obstacle(position, tamanho, c)
{
    id = IDOBS01;
    push_jogador = PUSH_BAU;
    this->setSizeTexture(BAU_SIZE_X,BAU_SIZE_Y);
    this->setSize(BAU_SIZE_X,BAU_SIZE_Y);
    key = "Obstacle1";
    setTexture(c);
}

ent::obs::Obstacle01::~Obstacle01()
{

}

void ent::obs::Obstacle01::setTexture(const string t)
{
    path = t;
    control->setTexture(key, path);
}

void ent::obs::Obstacle01::UpdatePosition()
{
    pos = control->getPosition(key);
}

void ent::obs::Obstacle01::InitialUpdate()
{
    control->setSize(key, tam_tex);
    control->setPosition(key, pos);
}

void ent::obs::Obstacle01::UpdateGerenciador()
{
    InitialUpdate();
}

void ent::obs::Obstacle01::Update()
{
    velocidade.y += 981.0f * control->get_Delta_Time();
    UpdateGerenciador();
    if(vcollision.y == 1lu)
    {
        velocidade.y = 0.0f;
    }
    Move(velocidade * control->get_Delta_Time());
    UpdatePosition();

}

void ent::obs::Obstacle01::Draw()
{
    control->Draw(key);
}

void ent::obs::Obstacle01::DrawPause()
{
    control->setPosition(key, pos);
    control->setSize(key, tam_tex);
    control->Draw(key);
}

void ent::obs::Obstacle01::Move(const Vector2D<float> v)
{
    control->Move(key, v);
}

void ent::obs::Obstacle01::Move(const float x, const float y)
{
    control->Move(key, x, y);
}
