#include "Character.h"

ent::cha::Character::Character(const bool pp, const float change_time, const string c):
    CollidingEntity(c),
    life(true),
    dano(false),
    change_animation(false),
    flag_change_face(false),
    velocidade(0.0f, 0.0f),
    cont_imagem(0,0),
    imagem_atual(0,0),
    face_certa(true),
    pode_pular(pp),
    lestatico(0),
    landando(0),
    lsalto(0),
    lataque(0),
    ldano(0),
    tempo_ciclo(change_time),
    galho(0.0f)
    {
        tempo_total = 0.0f;
    }

ent::cha::Character::~Character()
{

}

void ent::cha::Character::Dead(const bool l)
{
    life = l;
}

const bool ent::cha::Character::getLife() const
{
    return(life);
}

void ent::cha::Character::setDano(const bool d)
{
    dano = d;
}

const bool ent::cha::Character::getDano() const
{
    return(dano);
}

const bool ent::cha::Character::getFace() const
{
    return(face_certa);
}

void ent::cha::Character::setVelocidade(const Vector2D<float> v)
{
    velocidade = v;
}

void ent::cha::Character::setVelocidade(const float x, const float y)
{
    velocidade.x = x;
    velocidade.y = y;
}

const Vector2D<float> ent::cha::Character::getVelocidade() const
{
    return(velocidade);
}

void ent::cha::Character::incrementarVelocidade(const Vector2D<float>& vel)
{
    velocidade = velocidade + vel;
}

void ent::cha::Character::incrementarVelocidade(const float& x, const float& y)
{
    velocidade.x += x;
    velocidade.y += y;
}

void ent::cha::Character::setCurrentImage(const Vector2D<unsigned long int> v)
{
    imagem_atual = v;
}

void ent::cha::Character::setCurrentImage(const unsigned long int x, const unsigned long int y)
{
    imagem_atual.x = x;
    imagem_atual.y = y;
}

const Vector2D<unsigned long int> ent::cha::Character::getCurrentImage() const
{
    return(imagem_atual);
}

void ent::cha::Character::setContImage(const Vector2D<unsigned long int> v)
{
    cont_imagem = v;
}

void ent::cha::Character::setContImage(const unsigned long int x, const unsigned long int y)
{
    cont_imagem.x = x;
    cont_imagem.y = y;
}

void ent::cha::Character::PreencherLinhas(const unsigned long int estatico, const unsigned long int andando, const unsigned long int salto, const unsigned long int ataque, const unsigned long int dano)
{
    lestatico = estatico;
    landando = andando;
    lsalto = salto;
    lataque = ataque;
    ldano = dano;
}

void ent::cha::Character::setTempoCiclo(const float t)
{
    tempo_ciclo = t;
}

const float ent::cha::Character::getTempoCiclo() const
{
    return(tempo_ciclo);
}

void ent::cha::Character::Update()
{
    InitialUpdate();
    UpdateAnimacao();
    UpdateGerenciador();
}
