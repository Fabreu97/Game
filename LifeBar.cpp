#include "LifeBar.h"

ent::cha::LifeBar::LifeBar(const unsigned long int life):
    ent::cha::Character(),
    vidas(life),
    invulnerable(true),
    damage(0lu),
    time_in(0.0f),
    tempo_invulnerabilidade(TEMPO_INVUNERABILIDADE)
{
    imagem_atual = Vector2D<unsigned long int>(0,0);
    tam_tex = Vector2D<float>(64.0f, 64.0f);
    tam = Vector2D<float>(64.0f, 64.0f);
    path = "Texture/CCC.png";
    key = "Life1";
}

ent::cha::LifeBar::~LifeBar()
{

}

void ent::cha::LifeBar::setTexture(const string t)
{
    path = t;
    control->setTextureLife01(path);
}

const long int ent::cha::LifeBar::getLifePoints() const
{
    return(vidas);
}

void ent::cha::LifeBar::Damage(const unsigned long int attack_force)
{
    if(!invulnerable)
    {
        damage = attack_force;
    }
}

const bool ent::cha::LifeBar::getInvulnerable() const
{
    return(invulnerable);
}

void ent::cha::LifeBar::InitialUpdate ()
{
    control->setSizeLife01(tam_tex);
    control->setPositionLife01();

    width_height.y = control->getTextureSizeLife01().y / cont_imagem.y;
    width_height.x = control->getTextureSizeLife01().x / cont_imagem.x;
    left_top.x = 0.0f;
    left_top.y = 0.0f;
}

void ent::cha::LifeBar::UpdatePosition()
{

}

void ent::cha::LifeBar::UpdateAnimacao()
{
    time_in += control->get_Delta_Time();
    if(damage > 0)
    {
        if(!invulnerable)
        {
            vidas--;
            damage--;
            imagem_atual.x++;

            time_in = 0.0f;
            invulnerable = true;
        }
    }
    if(imagem_atual.x != 0)
    {
        if(tempo_total > tempo_ciclo)
        {
            tempo_total -= tempo_ciclo;
            imagem_atual.x++;
        }
        tempo_total += control->get_Delta_Time();
    }
    if(imagem_atual.x == cont_imagem.x)
    {
        imagem_atual.x = 0;
        imagem_atual.y++;
        if(imagem_atual.y == cont_imagem.y)
        {
            imagem_atual.y--;
            imagem_atual.x = (cont_imagem.x - 1);
        }
    }

    left_top.x = width_height.x * imagem_atual.x;
    left_top.y = width_height.y * imagem_atual.y;
}

void ent::cha::LifeBar::UpdateGerenciador ()
{
    control->setIntRectLife01(width_height.x, width_height.y, left_top.x, left_top.y);
    control->setTextureRectLife01();
    control->setPositionLife01();
}
void ent::cha::LifeBar::Update ()
{
    if(time_in > tempo_ciclo * cont_imagem.x)
    {
        invulnerable = false;
    }

    UpdateAnimacao();
    UpdateGerenciador();

}
void ent::cha::LifeBar::Draw ()
{
    control->DrawLife01();
}

void ent::cha::LifeBar::DrawPause()
{
    control->setPositionLife01();
    control->DrawLife01();
}

void ent::cha::LifeBar::Move(const Vector2D<float> v)
{
    control->moveLife01(v);
}

void ent::cha::LifeBar::Move(const float x, const float y)
{
    control->moveLife01(x,y);
}
