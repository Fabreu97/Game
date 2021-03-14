#include "CollisionManager.h"

#define COLLISION_DAMAGE 1lu

using namespace Manager;

CollisionManager::CollisionManager()
{
    ptr1 = NULL;
    ptr2 = NULL;
    LObstaculo = NULL;
    VInimigo = NULL;
}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::setJogador(ent::cha::jog::Player01* p1)
{
    ptr1 = p1;
}

void CollisionManager::setJogador(ent::cha::jog::Player02* p2)
{
    ptr2 = p2;
}

void CollisionManager::setListas(Groupings::ListaObstaculo* lo)
{
    this->LObstaculo = lo;
}

void CollisionManager::setListas(Groupings::VectorInimigo* vi)
{
    this->VInimigo = vi;
}

const bool CollisionManager::ChecarColisaoJogadorObstaculo(ent::cha::jog::Player* referencia, ent::obs::Obstacle* colisor)
{
    VB horizontal(false,false);
    VB vertical(false,false);
    Vector2D<float> thisPosition = referencia->getPosition();
    Vector2D<float> thisHalfSize = referencia->getHalfSize();
    Vector2D<float> otherPosition = colisor->getPosition();
    Vector2D<float> otherHalfSize = colisor->getHalfSize();

    if(referencia->getFace())
    {
        thisPosition.x -= referencia->galho;
    }
    else
    {
        thisPosition.x += referencia->galho;
    }

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
    float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

    if(intersectX < 0.0f && intersectY < 0.0f)
    {
        colisor->Update();
        referencia->setColisao(true);
        colisor->setColisao(true);

        if(intersectX < intersectY)
        {
            //Colisão Vertical
            if(deltaY > 0.0f)
            {
                // colisao de BAIXO pra CIMA
                referencia->Move( 0.0f, +intersectY  * colisor->getPush());
                colisor->Move( 0.0f, -intersectY  * (1.0f - colisor->getPush()) );

                vertical.y = 1;
            }
            else
            {
                //colisao de CIMA pra BAIXO
                referencia->Move( 0.0f, -intersectY  * colisor->getPush() );
                colisor->Move( 0.0f, +intersectY  * (1.0f - colisor->getPush()));

                vertical.x = 1;
            }
            referencia->setVerticalCollision(vertical);
        }
        else
        {
            //Colisao Horizontal
            if(deltaX > 0.0f)
            {
                // colisao da ESQUERDA para DIREITA
                referencia->Move( +intersectY  * colisor->getPush() * 0.1, 0.0f );
                colisor->Move( -intersectY  * (1.0f - colisor->getPush()), 0.0f);

                horizontal.y = 1lu;
            }
            else
            {
                //colisao de DIREITA pra ESQUERDA
                referencia->Move( -intersectY * colisor->getPush() * 0.1, 0.0f);
                colisor->Move( intersectY * (1.0f - colisor->getPush()), 0.0f);

                horizontal.x = 1lu;
            }
            referencia->setHorizontalCollision(horizontal);
        }
        colisor->UpdatePosition();
        return(true);
    }
    return(false);
}

const bool CollisionManager::ChecarColisaoJogadorInimigo(ent::cha::jog::Player* referencia, ent::cha::ini::Enemy* colisor)
{
    VB horizontal(false,false);
    VB vertical(false,false);
    Vector2D<float> thisPosition = referencia->getPosition();
    Vector2D<float> thisHalfSize = referencia->getHalfSize();
    Vector2D<float> otherPosition = colisor->getPosition();
    Vector2D<float> otherHalfSize = colisor->getHalfSize();

    if(referencia->getFace())
    {
        thisPosition.x -= referencia->galho;
    }
    else
    {
        thisPosition.x += referencia->galho;
    }

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
    float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

    if(intersectX < 0.0f && intersectY < 0.0f)
    {
        colisor->Update();
        if(intersectX > intersectY)
        {
            //COLISAO HORIZONTAL
            if(deltaX > 0.0f)
            {
                //colisao da esquerda para direita
                referencia->Move(intersectX);
                colisor->Move(-intersectX * 0.1f);
                horizontal.y = true;
            }
            else
            {
                //colisao da direita para esquerda
                referencia->Move(-intersectX * 1.0f);
                colisor->Move(intersectX * 0.1f);
                horizontal.x = true;
            }
            referencia->setDano(true);
            referencia->setHorizontalCollision(horizontal);
        }
        else
        {
            //COLISAO VERTICAL
            if(deltaY > 0.0f)
            {
                //colisão a baixo da referencia
                referencia->Move(0.0f, intersectY);

                vertical.y = 1lu;
                colisor->setDano(true);
            }
            else
            {
                referencia->Move(0.0f, -intersectY);

                vertical.x = 1lu;
            }
            referencia->setVerticalCollision(vertical);
        }
        colisor->UpdatePosition();

        return(true);
    }
    return(false);
}

void CollisionManager::ChecarColisoesJogadoresObstaculos()
{
    if(LObstaculo != NULL)
    {
        if(ptr1 != NULL)
        {
            unsigned long int i;
            unsigned long int j;
            for(i = 0lu; i < LObstaculo->getSize(); i++)
            {
                ent::obs::Obstacle* aux1 = LObstaculo->getObstaculo(i);
                for(j = 0lu; j < ptr1->getSizeListaProjetil(); j++)
                {
                    ent::cha::Projectile* pro1 = ptr1->getProjetil(j);
                    if(ChecarColisaoProjetilObstaculo(pro1, aux1))
                    {
                        pro1->setColisao(true);
                    }
                }
                ChecarColisaoJogadorObstaculo(ptr1, aux1);
            }
        }

        if(ptr2 != NULL)
        {
            unsigned long int i;
            unsigned long int j;
            for(i = 0lu; i < LObstaculo->getSize(); i++)
            {
                ent::obs::Obstacle* aux2 = LObstaculo->getObstaculo(i);
                for(j = 0lu; j < ptr2->getSizeListaProjetil(); j++)
                {
                    ent::cha::Projectile* pro2 = ptr2->getProjetil(j);
                    if(ChecarColisaoProjetilObstaculo(pro2, aux2))
                    {
                        pro2->setColisao(true);
                    }
                }
                ChecarColisaoJogadorObstaculo(ptr2, aux2);
            }
        }
    }
}

const bool CollisionManager::ChecarColisaoInimigoObstaculo(ent::cha::ini::Enemy* referencia, ent::obs::Obstacle* colisor)
{
    VB horizontal(false,false);
    VB vertical(false,false);
    Vector2D<float> thisPosition = referencia->getPosition();
    Vector2D<float> thisHalfSize = referencia->getHalfSize();
    Vector2D<float> otherPosition = colisor->getPosition();
    Vector2D<float> otherHalfSize = colisor->getHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
    float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);


    if(intersectX < 0.0f && intersectY < 0.0f)
    {
        referencia->InitialUpdate();
        colisor->Update(); //atualiza o tamanho e a posição

        referencia->setColisao(true);
        colisor->setColisao(true);

        if(intersectX < intersectY)
        {
            //Colisão Vertical
            if(deltaY > 0.0f)
            {
                // colisao de BAIXO pra CIMA
                referencia->Move( 0.0f, +intersectY  * 1.0f);

                vertical.y = 1lu;
            }
            else
            {
                //colisao de CIMA pra BAIXO
                referencia->Move( 0.0f, -intersectY  * colisor->getPush() );

                vertical.x = 1lu;
            }
            referencia->setVerticalCollision(vertical);
        }
        else
        {
            //Colisao Horizontal
            if(deltaX > 0.0f)
            {
                // colisao da ESQUERDA para DIREITA
                referencia->Move( +intersectY  * colisor->getPush() * 0.1, 0.0f );
                //ent::Entidade::getGerenciadorGrafico()->get_Delta_Time()

                horizontal.y = 1lu;

            }
            else
            {
                //colisao de DIREITA pra ESQUERDA
                referencia->Move( -intersectY * colisor->getPush() * 0.1, 0.0f);

                horizontal.x = 1lu;
            }
            referencia->setHorizontalCollision(horizontal);
        }
        referencia->UpdatePosition();
        //colisor->UpdatePosition();
        return(true);
    }
    return(false);
}

void CollisionManager::ChecarColisoesInimigosObstaculos()
{
    if(VInimigo != NULL)
    {
        if(LObstaculo != NULL)
        {
            unsigned long int i;
            unsigned long int j;
            for(i = 0lu; i < VInimigo->getSize(); i++)
            {
                ent::cha::ini::Enemy* aux = (*VInimigo)[i];
                for(j = 0lu; j < LObstaculo->getSize(); j++)
                {
                    ChecarColisaoInimigoObstaculo(aux, LObstaculo->getObstaculo(j));
                }
            }
        }
    }
}

const bool CollisionManager::ChecarColisaoProjetilInimigo(ent::cha::Projectile* referencia, ent::cha::ini::Enemy* colisor)
{
    VB horizontal(false, false);
    VB vertical(false, false);
    Vector2D<float> thisPosition = referencia->getPosition();
    Vector2D<float> thisHalfSize = referencia->getHalfSize();
    Vector2D<float> otherPosition = colisor->getPosition();
    Vector2D<float> otherHalfSize = colisor->getHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
    float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);


    if(intersectX < 0.0f && intersectY < 0.0f)
    {
        referencia->InitialUpdate();
        if(intersectY < intersectX)
        {
            //COLISAO HORIZONTAL
            if(deltaX > 0.0f)
            {
                referencia->Move(intersectX, 0.0f);
                horizontal.y = true;
            }
            else
            {
                referencia->Move(-intersectX, 0.0f);
                horizontal.x = true;

            }
        }
        else
        {
            //COLISÃO VERTICAL
            if(deltaY > 0.0f)
            {
                referencia->Move(0.0f, intersectY);
            }
            else
            {
                referencia->Move(0.0f, -intersectY);
            }
        }
        referencia->UpdatePosition();
        //referencia->setHorizontalCollision(horizontal);
        //referencia->setVerticalCollision(vertical);
        colisor->setHorizontalCollision(horizontal.inverse()); //mudar o valor de x para y e vice versa
        colisor->setVerticalCollision(vertical.inverse());
        return(true);
    }
    return(false);
}

const bool CollisionManager::ChecarColisaoProjetilObstaculo(ent::cha::Projectile* referencia, ent::obs::Obstacle* colisor)
{
    Vector2D<float> thisPosition = referencia->getPosition();
    Vector2D<float> thisHalfSize = referencia->getHalfSize();
    Vector2D<float> otherPosition = colisor->getPosition();
    Vector2D<float> otherHalfSize = colisor->getHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
    float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

    if(intersectX < 0.0f && intersectY < 0.0f)
    {
        referencia->InitialUpdate();
        if(deltaX > 0.0f)
        {
            referencia->Move(intersectX);
        }
        else
        {
            referencia->Move(-intersectX);
        }
        referencia->UpdatePosition();
        return(true);
    }
    return(false);
}

void CollisionManager::ChecarColisoesJogadoresInimigosProjeteis()
{
    if(VInimigo != NULL)
    {
        if(ptr1 != NULL)
        {
            unsigned long int i,j;
            for(i = 0lu; i < VInimigo->getSize(); i++)
            {
                ent::cha::ini::Enemy* ini01 = (*VInimigo)[i];
                for(j = 0lu; j < ptr1->getSizeListaProjetil(); j++)
                {
                    ent::cha::Projectile* pro1 = ptr1->getProjetil(j);
                    if(ChecarColisaoProjetilInimigo(pro1, ini01))
                    {
                        if(!pro1->getColisao())
                        {
                            ini01->setDano(true);
                            ini01->Damage(pro1->attackForce());
                        }
                        pro1->setColisao(true);

                    }
                }
                ptr1->setDano(false);
                if(ChecarColisaoJogadorInimigo(ptr1, ini01))
                {
                    if(ptr1->getDano())
                    {
                        ptr1->Damage(COLLISION_DAMAGE);
                    }
                }
            }
        }
        if(ptr2 != NULL)
        {
            unsigned long int i;
            unsigned long int j;
            for(i = 0lu; i < VInimigo->getSize(); i++)
            {
                ent::cha::ini::Enemy* ini02 = (*VInimigo)[i];
                for(j = 0lu; j < ptr2->getSizeListaProjetil(); j++)
                {
                    ent::cha::Projectile* pro2 = ptr2->getProjetil(j);
                    if(ChecarColisaoProjetilInimigo(pro2, ini02))
                    {
                        pro2->setColisao(true);
                        ini02->setDano(true);
                    }
                }
                if(ChecarColisaoJogadorInimigo(ptr2, ini02))
                {

                }
            }
        }
    }
}

void CollisionManager::ChecarCoisoesEntreObstaculos()
{
    LObstaculo->ChecarColisoesEntreObstaculo();
}

void CollisionManager::resetCollisions()
{
    LObstaculo->resetCollisions();
    VInimigo->resetCollisions();
}
