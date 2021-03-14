#include "Obstacle.h"

ent::obs::Obstacle::Obstacle( const Vector2D<float> position, const Vector2D<float> tamanho, const string c):
    CollidingEntity(c),
    push_jogador(PUSH_PLATAFORMA)
    {
        id = IDPLATF;
        tam_tex = tamanho;
        tam = tamanho;
        pos = position;
    }
ent::obs::Obstacle::~Obstacle()
{

}

void ent::obs::Obstacle::setVelocidade(const Vector2D<float> v)
{
    velocidade = v;
}

void ent::obs::Obstacle::setVelocidade(const float x, const float y)
{
    velocidade.x = x;
    velocidade.y = y;
}

const Vector2D<float> ent::obs::Obstacle::getVelocidade() const
{
    return(velocidade);
}

void ent::obs::Obstacle::setPush(const float p)
{
    push_jogador = p;
}

const float ent::obs::Obstacle::getPush() const
{
    return(push_jogador);
}

void ent::obs::Obstacle::setTempoCiclo(const float t)
{

}
const float ent::obs::Obstacle::getTempoCiclo() const
{
    return(0.0);
}

void ent::obs::Obstacle::setCurrentImage(const Vector2D<unsigned long int> v)
{

}
void ent::obs::Obstacle::setCurrentImage(const unsigned long int x, const unsigned long int y)
{

}
const Vector2D<unsigned long int> ent::obs::Obstacle::getCurrentImage() const
{
    return(Vector2D<unsigned long int>(0lu,0lu));
}

void ent::obs::Obstacle::setContImage(const Vector2D<unsigned long int> v)
{

}
void ent::obs::Obstacle::setContImage(const unsigned long int x, const unsigned long int y)
{

}
const Vector2D<unsigned long int> ent::obs::Obstacle::getContImage() const
{
    return(Vector2D<unsigned long int>(0lu,0lu));
}
