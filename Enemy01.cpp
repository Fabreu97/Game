#include "Enemy01.h"

ent::cha::ini::Enemy01::Enemy01(const bool pp, const float change_time, const string c):
    Enemy(pp,change_time,c)
    {
        id = IDINI01;
        key = "Enemy1";
        velocidade.x = VELINI01;
        PreencherLinhas(0lu, 1lu, 2lu, 7lu, 3lu);
        tam.x = TAMANHO_COLIDIVEL_INIMIGO01_X;
        tam.y = TAMANHO_COLIDIVEL_INIMIGO01_Y;
        tam_tex.x = TAMANHO_DA_TEXTURA_INIMIGO01_X;
        tam_tex.y = TAMANHO_DA_TEXTURA_INIMIGO01_Y;
        setContImage(3,9);
        setTempoCiclo(0.2f);
        vidas = ENEMY_LIVES;
        setTexture("Texture/n_linux.png");
    }

ent::cha::ini::Enemy01::~Enemy01()
{

}

void ent::cha::ini::Enemy01::Damage(long int attack_force)
{
    vidas -= attack_force;
    animacao_dano = true;
    imagem_atual.x = 0lu;
}

void ent::cha::ini::Enemy01::setTexture(const string t)
{
    path = t;
    control->setTexture(key, path);
}

void ent::cha::ini::Enemy01::Update()
{
    if(vidas <= 0l)
    {
        life = false;
    }
    control->setPosition(key, pos);
    UpdateMovement();
    UpdateAnimacao();
    UpdateGerenciador();
}

void ent::cha::ini::Enemy01::InitialUpdate()
{
    control->setSize(key, tam_tex);
    control->setPosition(key, pos);
    width_height.y = control->getTextureSize(key).y / cont_imagem.y;
}

void ent::cha::ini::Enemy01::UpdateMovement()
{
    Vector2D<float> recuo(0.0f, 0.0f);

    acumulador_dist += control->get_Delta_Time();
    if(!animacao_dano)
    {
        if(velocidade.x > 0.0f)
        {
            velocidade.x = VELINI01;
        }
        else
        {
            velocidade.x = -VELINI01;
        }
        if(acumulador_dist > dist_perc)
        {
            acumulador_dist -= dist_perc;
            velocidade.x = velocidade.x * (-1.0f);
        }

        //MÉTODOS DE ONCOLLISON
    }
    else
    {
        if(hcollision.y)
        {
            velocidade.x = -100.0f;
        }
        if(hcollision.x)
        {
            velocidade.x = +100.0f;
        }
    }

    if(vcollision.y)//direcao.y > 0.0f
    {
        velocidade.y = 0.0f;
    }
    else
    {
        velocidade.y += 981.0f * control->get_Delta_Time();
    }
    Move(control->get_Delta_Time() * velocidade);
    //MÉTODOS DE ONCOLLISON ^^
}

void ent::cha::ini::Enemy01::UpdateAnimacao()
{

    //QUAL ANIMAÃO SERA ANIMADA
    unsigned long int flag1 = imagem_atual.y;
    if(!animacao_dano)
    {
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
    }
    else
    {
        imagem_atual.y = ldano;
        if(velocidade.x < 0.0f)
        {
            face_certa = true;
        }
        else
        {
            face_certa = false;
        }
    }

    //VEREFICA SE TROCOU DE ANIMAÇÃO

    if(flag1 != imagem_atual.y)
    {
        change_animation = true;
    }
    else
    {
        change_animation = false;
    }

    if(change_animation)
    {
        imagem_atual.x = 0;
    }

    //PARTE DA TROCA DE ANIMAÇÃO PELO TEMPO DECORRIDO
    tempo_total += control->get_Delta_Time();

    if(tempo_total > tempo_ciclo)
    {
        tempo_total -= tempo_ciclo;
        imagem_atual.x = (imagem_atual.x + 1) % cont_imagem.x;
        if(!change_animation && imagem_atual.x == 0)
        {
            imagem_atual.y = landando;
            animacao_dano = false;
            dano = false;
        }
    }

    //AJEITANDO A TEXTURA PARA O GERENCIADOR GRÁFICO
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
    control->setIntRect(key, width_height.x, width_height.y, left_top.x, left_top.y);
    control->setTextureRect(key);
}

void ent::cha::ini::Enemy01::UpdateGerenciador() //TO DO
{
    control->setIntRect(key, width_height.x, width_height.y, left_top.x, left_top.y);
    control->setTextureRect(key);
    pos = control->getPosition(key);
}

void ent::cha::ini::Enemy01::UpdatePosition()
{
    pos = control->getPosition(key);
}

void ent::cha::ini::Enemy01::Draw()
{
    control->Draw(key);
}

void ent::cha::ini::Enemy01::DrawPause()
{
    control->setIntRect(key, width_height.x, width_height.y, left_top.x, left_top.y);
    control->setTextureRect(key);
    control->setPosition(key, pos);
    control->setSize(key, tam_tex);
    control->Draw(key);
}

void ent::cha::ini::Enemy01::Move(const Vector2D<float> v)
{
    control->Move(key, v);
}

void ent::cha::ini::Enemy01::Move(const float x, const float y)
{
    control->Move(key, x, y);
}
