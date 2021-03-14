#include "Projectile.h"

ent::cha::Projectile::Projectile(const long int dano, const bool fc, const float lifetime, const float time_between_shots):
    Character(true, 0.01f, "Texture/fire.png"),
    damage(dano),
    tempo_vida(lifetime),
    tempo_entre_disparo(time_between_shots)
{
    face_certa = fc;
    timev = 0.0f;
    key = "Projectile";
}

ent::cha::Projectile::~Projectile() {}

const long int ent::cha::Projectile::attackForce() const
{
    return(damage);
}

void ent::cha::Projectile::setTexture(const string t)
{
    path = t;
    control->setTexture(key, path);
}

void ent::cha::Projectile::InitialUpdate ()
{
    control->setSize(key, tam_tex);
    control->setPosition(key, pos);

    width_height.x = control->getTextureSize(key).x / cont_imagem.x;
    width_height.y = control->getTextureSize(key).y / cont_imagem.y;

    left_top.x = 0.0f;
    left_top.y = 0.0f;
}

void ent::cha::Projectile::UpdatePosition()
{
    pos = control->getPosition(key);
}

void ent::cha::Projectile::UpdateAnimacao()
{
    timev += control->get_Delta_Time();
    if(tempo_vida < timev)
    {
        colidiu = true;
    }
    if(colidiu)
    {
        tempo_total += control->get_Delta_Time();

        if(tempo_total > tempo_ciclo)
        {
            imagem_atual.x++;
            tempo_total -= tempo_ciclo;
        }

        if(imagem_atual.x == cont_imagem.x)
        {
            life = false;
        }
    }

    if(velocidade.x > 0.0f)
    {
        left_top.x = imagem_atual.x * abs(width_height.x);
    }
    else
    {
        left_top.x = (imagem_atual.x + 1) * abs(width_height.x);
        width_height.x = -abs(width_height.x);
    }

    control->setIntRect(key, width_height.x, width_height.y, left_top.x, left_top.y);
    control->setTextureRect(key);
}

void ent::cha::Projectile::UpdateGerenciador ()
{
    control->setPosition(key, pos);
}

void ent::cha::Projectile::Update ()
{
    UpdateAnimacao();
    UpdateGerenciador();
    if(!colidiu)
    {
        Move(velocidade * control->get_Delta_Time());
        pos = control->getPosition(key);
    }
}

void ent::cha::Projectile::Draw ()
{
    if(life)
    {
        control->Draw(key);
    }
}

void ent::cha::Projectile::DrawPause()
{
    control->setIntRect(key, width_height.x, width_height.y, left_top.x, left_top.y);
    control->setTextureRect(key);
    control->setPosition(key, pos);
    control->Draw(key);
}

void ent::cha::Projectile::Move(const Vector2D<float> v)
{
    control->Move(key, v);
}

void ent::cha::Projectile::Move(const float x, const float y)
{
    control->Move(key, x, y);
}

const bool ent::cha::Projectile::operator ==(const ent::cha::Projectile& p) const
{
    if(pos.x == p.getPosition().x)
    {
        if(pos.y == p.getPosition().y)
        {
            return(true);
        }
    }
    return (false);
}

const bool ent::cha::Projectile::operator != (const ent::cha::Projectile& p) const
{
    if(*this == p)
    {
        return(false);
    }
    return(true);
}

inline void ent::cha::Projectile::operator=(const ent::cha::Projectile& p)
{
    this->pos = p.getPosition();
    this->tam_tex = p.getSizeTexture();
    this->path = p.getTexture();
}
