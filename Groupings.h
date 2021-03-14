#ifndef INCLUDED_GROUPINGS_H
#define INCLUDED_GROUPINGS_H

#include <list>
#include <queue>
#include <vector>
#include "Queue.h"
#include "Stack.h"
#include <algorithm>
#include "Player01.h" // contem Entidade
#include "Player02.h" // contem Entidade
#include "Enemy01.h" // contem Entidade
#include "Enemy02.h" // contem Entidade
#include "Enemy03.h" // contem Entidade
#include "Obstacle01.h" // contem Entidade
#include "Obstacle02.h" // contem Entidade
#include "Obstacle03.h" // contem Entidade
#include "Platform.h" // contem Entidade
#include <fstream>

namespace Groupings
{
    class ListaEntidade
    {
    private:

        //LISTA DE ENDEREÇOS DE ENTIDADE ALOCADAS DINAMICAMENTE
        list<ent::Entity*> lista;

    public:

        ListaEntidade();
        ~ListaEntidade();

        const unsigned long int getSize() const;

        void incluirEntidade(ent::Entity* e);
        void limpar();
        void Draw();
        void Draw(const Vector2D<float>& p1);
        void Draw(const Vector2D<float>& p1, const Vector2D<float>& p2);
        void DrawPause(const Vector2D<float>& v);
        const bool eliminarInimigo(ent::cha::ini::Enemy* i);
        const bool eliminatePlayer(ent::cha::jog::Player* p);
        void putTexture();
        void removeTexture();
        void savegame(const string name);
    };

    class VectorInimigo
    {
    private:

        vector<ent::cha::ini::Enemy*> vetor;
        vector<ent::cha::ini::Enemy*>::iterator it;

    public:

        VectorInimigo();
        ~VectorInimigo();

        const unsigned long int getSize() const;
        const bool incluirInimigo(ent::cha::ini::Enemy* i);
        void eliminarInimigo(const unsigned long int indice);
        void limpar();
        ent::cha::ini::Enemy* operator[](const unsigned long int i) const;
        void resetCollisions();
    };

    class ListaObstaculo
    {
    private:

        List<ent::obs::Obstacle> lista;

    public:

        ListaObstaculo();
        ~ListaObstaculo();

        const unsigned long int getSize() const;
        const bool insertObstacle(ent::obs::Obstacle* o); //..........REVIEW
        ent::obs::Obstacle* getObstaculo(const unsigned long int indice) const;
        void eliminarObstaculo(const unsigned long int i);//..............;;;;REVIEW E NÃO USAR
        void limpar();
        const bool ChecarColisoesEntreObstaculo(ent::obs::Obstacle* a, ent::obs::Obstacle* b);
        void ChecarColisoesEntreObstaculo();
        void resetCollisions();
    };
}

#endif // INCLUDED_GROUPINGS_H
