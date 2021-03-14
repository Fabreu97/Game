#include "Enemy.h"

ent::cha::ini::Enemy::Enemy(const bool pp, const float change_time, const string c):
    Character(pp,change_time,c),
    vidas(ENEMY_LIVES)
    {
        id = 0;
        acumulador_dist = 0.0f;
        dist_perc = 2.5f;
    }

ent::cha::ini::Enemy::~Enemy()
{

}

void ent::cha::ini::Enemy::Damage(long int attack_force)
{
    vidas -= attack_force;
    animacao_dano = true;
    imagem_atual.x = 0lu;
}

void ent::cha::ini::Enemy::setLifePoints(const unsigned long int life_points)
{
    vidas = life_points;
}

const long int ent::cha::ini::Enemy::getLifePoints() const
{
    return(vidas);
}

