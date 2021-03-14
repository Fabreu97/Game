#ifndef INCLUDED_GERENCIADOR_COLISAO_H
#define INCLUDED_GERENCIADOR_COLISAO_H

#include "Groupings.h"

namespace Manager
{
    class CollisionManager
    {
    private:

        ent::cha::jog::Player01* ptr1;
        ent::cha::jog::Player02* ptr2;

        Groupings::ListaObstaculo* LObstaculo;
        Groupings::VectorInimigo* VInimigo;

    public:

        CollisionManager();
        ~CollisionManager();

        void setJogador(ent::cha::jog::Player01* p1);
        void setJogador(ent::cha::jog::Player02* p2);

        void setListas(Groupings::ListaObstaculo* lo);
        void setListas(Groupings::VectorInimigo* vi);

        //COLISAO COM JOGADOR:
        const bool ChecarColisaoJogadorObstaculo(ent::cha::jog::Player* referencia, ent::obs::Obstacle* colisor);
        const bool ChecarColisaoJogadorInimigo(ent::cha::jog::Player* referencia, ent::cha::ini::Enemy* colisor);
        const bool ChecarColisaoProjetilInimigo(ent::cha::Projectile* referencia, ent::cha::ini::Enemy* colisor);
        const bool ChecarColisaoProjetilObstaculo(ent::cha::Projectile* referencia, ent::obs::Obstacle* colisor);
        void ChecarColisoesJogadoresObstaculos();
        void ChecarColisoesInimigosObstaculos();
        void ChecarColisoesJogadoresInimigosProjeteis();

        //COLISAO COM INIMIGO:
        const bool ChecarColisaoInimigoObstaculo(ent::cha::ini::Enemy* referencia, ent::obs::Obstacle* colisor);

        void ChecarCoisoesEntreObstaculos();
        void resetCollisions();
    };
}

#endif // INCLUDED_GERENCIADOR_COLISAO_H
