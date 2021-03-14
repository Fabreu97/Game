#include "Player02.h"

ent::cha::jog::Player02::Player02(const float height_jumper, const float aceleracao, const bool pp, const float change_time, const string c):
    Player(height_jumper, aceleracao,pp,change_time,c)
    {
        id = IDJOG02;
        key = "Player02";
        this->setSizeTexture(TAMANHO_DA_TEXTURA_JOGADOR_X, TAMANHO_DA_TEXTURA_JOGADOR_Y);
        this->setPosition(700.f, 800.0f);
        this->setContImage(3,9);
        this->PreencherLinhas(0,1);
        this->setSpeed(SPEED_JOGADOR);
        this->setTempoCiclo(0.2);
        this->setTexture("Texture/tux_from_linux.png");
        this->InitialUpdate();
    }
ent::cha::jog::Player02::~Player02()
{

}


void ent::cha::jog::Player02::setTexture(const string t)
{
    path = t;
    control->setTexture(key, t);
}

void ent::cha::jog::Player02::InitialUpdate()
{
    control->setSize(key, tam_tex);
    control->setPosition(key, pos);

}

void ent::cha::jog::Player02::UpdatePosition()
{
    pos = control->getPosition(key);
}

void ent::cha::jog::Player02::Update()
{
    this->UpdateMovement();
    this->UpdateAnimacao();
    this->UpdateGerenciador();
}

void ent::cha::jog::Player02::UpdateMovement()
{
    velocidade.x *= 0.0f;

    if(control->isPA())
    {
        velocidade.x -= speed;
    }
    if(control->isPD())
    {
        velocidade.x += speed;
    }
    if(control->isP_Space() && pode_pular)
    {
        pode_pular = false;
        velocidade.y = -sqrt(2 * 981.0f * altura_salto);
    }
}

void ent::cha::jog::Player02::UpdateAnimacao()
{
    if(vcollision.y == 1lu && velocidade.y > 0.0f)
    {
        velocidade.y = 0.0f;
        pode_pular = true;
    }
    else
    {
        velocidade.y += 981.0f * control->get_Delta_Time();
    }


    if(velocidade.x != 0.0f)
    {
        imagem_atual.y = landando;
        if(velocidade.x > 0.0f)
        {
            face_certa = true;
        }
        else
        {
            face_certa = false;
        }
    }
    else
    {
        imagem_atual.y = lestatico;
    }

    tempo_total += control->get_Delta_Time();

    if(tempo_total > tempo_ciclo)
    {
        tempo_total -= tempo_ciclo;
        imagem_atual.x = (imagem_atual.x + 1) % cont_imagem.x;
    }
    width_height.y = control->getTextureSize(key).y / cont_imagem.y;
    width_height.x = control->getTextureSize(key).x / cont_imagem.x;

    left_top.y = width_height.y * imagem_atual.y;

    if(face_certa)
    {
        left_top.x = width_height.x * imagem_atual.x;
    }
    else
    {
        width_height.x = -abs(width_height.x);
        left_top.x = (imagem_atual.x + 1) * abs(width_height.x);
    }

    Move(velocidade * control->get_Delta_Time());
}

void ent::cha::jog::Player02::UpdateGerenciador()
{
    control->setIntRect(key, width_height.x, width_height.y, left_top.x, left_top.y);
    control->setTextureRect(key);
    control->Move(key, velocidade * control->get_Delta_Time());
    pos = control->getPosition(key);
}

void ent::cha::jog::Player02::Draw()
{
    control->Draw(key);
}

void ent::cha::jog::Player02::DrawPause()
{
    control->Draw(key);
}

void ent::cha::jog::Player02::Move(const Vector2D<float> v)
{
    control->Move(key, v);
}

void ent::cha::jog::Player02::Move(const float x, const float y)
{
    control->Move(key, x, y);
}

void ent::cha::jog::Player02::OnCollision()
{
    if(hcollision.x == 1lu)
    {
        pode_pular = true;
        velocidade.x = 0.0f;
    }
    else if(hcollision.y == 1lu)
    {
        pode_pular = true;
        velocidade.x = 0.0f;
    }
    if(vcollision.x == 1lu)
    {
        velocidade.y = 0.0f;
    }
    else if(vcollision.y == 1lu)
    {
        pode_pular = true;
        velocidade.y = 0.0f;
    }
}
