#include "Player01.h"

ent::cha::jog::Player01::Player01(const float height_jumper, const float aceleracao, const bool pp, const float change_time, const string c):
    Player(height_jumper, aceleracao,pp,change_time,c),
    col_estatico(3lu),
    col_andando(9lu),
    col_ataque(5lu)
    {
        key = "Player01";
        id = IDJOG01;
        this->setSize(TAMANHO_COLIDIVEL_JOGADOR01_X, TAMANHO_COLIDIVEL_JOGADOR01_Y);
        this->setSizeTexture(TAMANHO_DA_TEXTURA_JOGADOR01_X, TAMANHO_DA_TEXTURA_JOGADOR01_Y);
        this->setPosition(400.f, 800.0f);
        this->setContImage(9lu,3lu);
        this->PreencherLinhas(0lu,1lu, 0lu, 2lu);
        this->setSpeed(SPEED_JOGADOR01);
        this->setTempoCiclo(CHANGE_TIME_ANIMATION_PLAYER01);
        this->setTexture("Texture/Marco.png");

        this->setTextureLife("Texture/CCC.png");
        this->setSizeLife(96.0f, 32.0f);
        this->setContImageLife(6lu,6lu);
        this->setCurrentImageLife(0lu,0lu);
        this->setTempoCicloLife(0.15f);

        this->InitialUpdate();
        galho = (7.0f/51.0f) * tam_tex.x;
        tam.x = tam_tex.x * (29.0f/51.0f);
    }
ent::cha::jog::Player01::~Player01()
{
    while(FilaProjetil.getSize() != 0lu)
    {
        ent::cha::Projectile* aux = FilaProjetil[0];
        delete(aux);
        aux = NULL;
        FilaProjetil.deleteData(0lu);
    }
}

void ent::cha::jog::Player01::setTexture(const string t)
{
    path = t;
    control->setTexture(key, path);
}

void ent::cha::jog::Player01::InitialUpdate()
{
    control->setSize(key, tam_tex);
    control->setPosition(key, pos);
    vida.InitialUpdate();
    control->setTexture("Projectile", "Texture/fire.png");
}

void ent::cha::jog::Player01::UpdatePosition()
{
    pos = control->getPosition(key);
}

void ent::cha::jog::Player01::Update()
{
    UpdateMovement();
    UpdateAnimacao();
    UpdateGerenciador();
    vida.Update();
    dano = false;
    DispararProjetil();
}

void ent::cha::jog::Player01::UpdateMovement()
{
    velocidade.x /= 5;

    if(control->isP_Left() && !animacao_disparo)
    {
        velocidade.x -= speed;
    }
    if(control->isP_Right() && !animacao_disparo)
    {
        velocidade.x += speed;
    }
    if(control->isPEnter() && pode_pular)
    {
        pode_pular = false;
        velocidade.y = -sqrt(2 * 981.0f * altura_salto);
    }
    if(vcollision.y)
    {
        velocidade.y = 0.0f;
        pode_pular = true;
    }
    else
    {
        velocidade.y += 981.0f * control->get_Delta_Time();
    }
}

void ent::cha::jog::Player01::UpdateAnimacao()
{
    //TESTES LÓGICOS PARA MUDANÇA DE ANIMAÇÃO DO JOAGDOR 01
    bool flag1 = face_certa;
    const unsigned long int flag_type_animation = imagem_atual.y;

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

    //TESTE PARA AJEITAR QUANDO TROCA A LINHA DE ANIMAÇÃO OU A FACE DO JOGADOR01

    if(face_certa != flag1)
    {
        flag_change_face = true;
    }

    tempo_total += control->get_Delta_Time();

    //ANIMAÇÃO QUANDO NÃO ESTA DISPARANDO O PROJETIL

    if(!animacao_disparo)
    {
        if(tempo_total > tempo_ciclo)
        {
            tempo_total -= tempo_ciclo;
            switch(imagem_atual.y)
            {
            case 1lu:
                {
                    imagem_atual.x = (imagem_atual.x + 1) % col_andando;
                    break;
                }
            case 0lu:
                {
                    imagem_atual.x = (imagem_atual.x + 1) % col_estatico;
                    break;
                }
            default:
                {
                    break;
                }
            }
        }
        if(flag_type_animation != imagem_atual.y)
        {
            imagem_atual.x = 0lu;
        }
    }

    //ANIMACAO DE DISPARO DE PROJETIL
    if(animacao_disparo)
    {
        imagem_atual.y = lataque;
        if(time_projetil == 0.0f)
        {
            imagem_atual.x = 0lu;
            change_animation = true;
        }
        float t = (tempo_entre_disparo / col_ataque) * (imagem_atual.x + 1);
        if(time_projetil > t)
        {
            imagem_atual.x = (imagem_atual.x + 1) % col_ataque;
            change_animation = false;
        }
        if(imagem_atual.x == 0lu && !change_animation)
        {
            animacao_disparo = false;
        }
    }

    time_projetil += control->get_Delta_Time();

    //AJEITANDO CONFIGURAÇÕES DA ANIMAÇÃO COMO ENTRADA PARA O GERENCIADOR GRÁFICO
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

void ent::cha::jog::Player01::UpdateGerenciador()
{
    control->setIntRect(key, width_height.x, width_height.y, left_top.x, left_top.y);
    control->setTextureRect(key);
    control->Move(key, velocidade * control->get_Delta_Time());
    pos = control->getPosition(key);
    if(flag_change_face)
    {
        flag_change_face = false;
        if(face_certa)
        {
            pos.x += (2 * galho);
        }
        else
        {
            pos.x -= (2 * galho);
        }
        control->setPosition(key, pos);
    }
}

void ent::cha::jog::Player01::Draw()
{
    DrawProjetil();
    control->Draw(key);
    vida.Draw();
}

void ent::cha::jog::Player01::DrawPause()
{
    DrawProjetilPause();
    control->Draw(key);
    vida.DrawPause();
}

void ent::cha::jog::Player01::OnCollision()
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

void ent::cha::jog::Player01::Move(const Vector2D<float> v)
{
    control->Move(key, v);
}

void ent::cha::jog::Player01::Move(const float x, const float y)
{
    control->Move(key, x, y);
}

void ent::cha::jog::Player01::DispararProjetil()
{
    if(control->isP_ALT())
    {
        if( (FilaProjetil.getSize() < cont_projetil) && (tempo_entre_disparo < time_projetil) && !animacao_disparo)
        {
            animacao_disparo = true;
            ent::cha::Projectile* aux = new ent::cha::Projectile(1l);
            aux->setSizeTexture(20.0f, 20.0f);
            aux->setSize(20.0f, 20.0f);
            if(face_certa)
            {
                aux->setPosition(pos.x + ( tam_tex.x * (14.5f/51.0f) ), pos.y - ( tam_tex.y * (7.5f/ 51.0f) ) );
                aux->setVelocidade(VELOCIDADE_PROJETIL , 0.0f);
                //Move(-20.0f, 0.0f);
            }
            else
            {
                aux->setPosition(pos.x - ( tam_tex.x * (14.5f/51.0f) ), pos.y - ( tam_tex.y * (7.5f/ 51.0f) ) );
                aux->setVelocidade(-VELOCIDADE_PROJETIL , 0.0f);
                //Move(+20.0f, 0.0f);
            }
            aux->setContImage(7,1);
            aux->setTempoCiclo(TEMPO_CICLO_PROJETIL);
            aux->InitialUpdate();
            FilaProjetil.insertList(aux);
            time_projetil = 0.0f;
        }
    }
}

void ent::cha::jog::Player01::DrawProjetil()
{
    List<ent::cha::Projectile>::Iterator it;
    for(it = FilaProjetil.Begin(); it != FilaProjetil.End(); ++it)
    {
        if((*it)->getLife())
        {
            (*it)->Update();
            (*it)->Draw();
        }
        else
        {
            FilaProjetil.deleteData(*it);
            it = FilaProjetil.Begin();
        }
    }
}

void ent::cha::jog::Player01::DrawProjetilPause()
{
    List<ent::cha::Projectile>::Iterator it;
    for(it = FilaProjetil.Begin(); it != FilaProjetil.End(); ++it)
    {
        (*it)->DrawPause();
    }
}

const long int ent::cha::jog::Player01::getLifePoints() const
{
    return(vida.getLifePoints());
}
