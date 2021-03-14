#include "Player.h"

ent::cha::jog::Player::Player(const float height_jumper, const float aceleracao, const bool pp, const float change_time, const string c):
    Character(pp, change_time, c),
    speed(aceleracao),
    altura_salto(height_jumper),
    animacao_disparo(false)
{
    tempo_entre_disparo = 0.4f;
    time_projetil = 0.0f;
    cont_projetil = 5lu;
}

ent::cha::jog::Player::~Player()
{

}

const bool ent::cha::jog::Player::getInvulnerable() const
{
    return(vida.getInvulnerable());
}

void ent::cha::jog::Player::setTempoCicloLife(const float a)
{
    vida.setTempoCiclo(a);
}

void ent::cha::jog::Player::setTextureLife(const string t)
{
    path = t;
    vida.setTexture(t);
}

void ent::cha::jog::Player::setSizeLife(const Vector2D<float> s)
{
    vida.setSizeTexture(s);
    vida.setSize(s);
}

void ent::cha::jog::Player::setSizeLife(const float x, const float y)
{
    vida.setSizeTexture(x,y);
}

void ent::cha::jog::Player::setContImageLife(const Vector2D<unsigned long int> v)
{
    vida.setContImage(v);
}

void ent::cha::jog::Player::setContImageLife(const unsigned long int x, const unsigned long int y)
{
    vida.setContImage(x,y);
}

void ent::cha::jog::Player::setCurrentImageLife(const Vector2D<unsigned long int> v)
{
    vida.setCurrentImage(v);
}

void ent::cha::jog::Player::setCurrentImageLife(const unsigned long int x, const unsigned long int y)
{
    vida.setCurrentImage(x,y);
}

void ent::cha::jog::Player::Damage(const unsigned long int attack_force)
{
    vida.Damage(attack_force);
}

void ent::cha::jog::Player::setSpeed(const float aceleracao)
{
    speed = aceleracao;
}

const float ent::cha::jog::Player::getSpeed() const
{
    return(speed);
}

void ent::cha::jog::Player::setAlturaSalto(const float& a)
{
    altura_salto = a;
}

const float ent::cha::jog::Player::getAlturaSalto() const
{
    return(altura_salto);
}

ent::cha::Projectile* ent::cha::jog::Player::getProjetil(const unsigned long int indice) const
{
    return(FilaProjetil[indice]);
}

const unsigned long int ent::cha::jog::Player::getSizeListaProjetil() const
{
    return(FilaProjetil.getSize());
}
