#include "Groupings.h"

///M?TODOS DA CLASSE LISTA DE ENTIDADES

Groupings::ListaEntidade::ListaEntidade():
    lista()
    {

    }
Groupings::ListaEntidade::~ListaEntidade()
{
    limpar();
}

const unsigned long int Groupings::ListaEntidade::getSize() const
{
    return(lista.size());
}

void Groupings::ListaEntidade::incluirEntidade(ent::Entity* e)
{
    lista.push_back(e);
}

void Groupings::ListaEntidade::limpar()
{
    lista.clear();
}

void Groupings::ListaEntidade::Draw()
{
    for(register list<ent::Entity*>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        (*it)->Update();
        (*it)->Draw();
    }
}

const bool Groupings::ListaEntidade::eliminarInimigo(ent::cha::ini::Enemy* i)
{
    for(register list<ent::Entity*>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        if(i == (*it))
        {
            lista.erase(it);
            return(true);
        }
    }
    return(false);
}

const bool Groupings::ListaEntidade::eliminatePlayer(ent::cha::jog::Player* p)
{
    for(register list<ent::Entity*>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        if(p == (*it))
        {
            lista.erase(it);
            return(true);
        }
    }
    return(false);
}

void Groupings::ListaEntidade::Draw(const Vector2D<float>& p1)
{
    float xe = p1.x - 2100.0f;
    float xd = p1.x + 2100.0f;
    for(register list<ent::Entity*>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        if( (*it)->getPosition().x > xe && (*it)->getPosition().x < xd)
        {
            (*it)->Update();
            (*it)->Draw();
        }
    }
}

void Groupings::ListaEntidade::Draw(const Vector2D<float>& p1, const Vector2D<float>& p2)
{
    float xe, xd;
    xe = (p1.x + p2.x) / 2.0f;
    xd = xe;
    xe -= 2100.0f;
    xd += 2100.0f;
    for(register list<ent::Entity*>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        if( (*it)->getPosition().x > xe &&  (*it)->getPosition().x < xd )
        {
            (*it)->Update();
            (*it)->Draw();
        }
    }
}

void Groupings::ListaEntidade::DrawPause(const Vector2D<float>& v)
{
    for(register auto it = lista.begin(); it != lista.end(); ++it)//C++ 11
    {
        (*it)->DrawPause();
    }
}

void Groupings::ListaEntidade::putTexture()
{
    for(register list<ent::Entity*>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        (*it)->setTexture((*it)->getTexture());
    }
}

void Groupings::ListaEntidade::removeTexture()
{
    for(register list<ent::Entity*>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        ent::Entity::getGraphicManager()->removeTexture((*it)->getKey());
    }
}

void Groupings::ListaEntidade::savegame(const string name)
{
    string aux = name + ".dat";//extens?o do tipo do arquivo
    ofstream out;
    out.open(aux, ios::out);
    if(!out)
    {
        cerr << "Error: arquivo de save falhou" << endl;
        fflush(stdin);
        Sleep(3000); //cooldown
        return;
    }

    for(register list<ent::Entity*>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        out << (*it)->getID() << " " << (*it)->getLifePoints()<< " " << (*it)->getPosition().x << " ";
        out << (*it)->getPosition().y << " "<< (*it)->getVelocidade().x << " " << (*it)->getVelocidade().y << " ";
        out << (*it)->getCurrentImage().x << " " << (*it)->getCurrentImage().y << endl;
    }
    out << 66 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0;
    out.close();
}

///IMPLEMENTACOES DA CLASSE VECTOR DE INIMIGO

Groupings::VectorInimigo::VectorInimigo():
    vetor()
{

}

Groupings::VectorInimigo::~VectorInimigo()
{
    limpar();
}

const unsigned long int Groupings::VectorInimigo::getSize() const
{
    return(vetor.size());
}

const bool Groupings::VectorInimigo::incluirInimigo(ent::cha::ini::Enemy* i)
{
    if(i != NULL)
    {
        vetor.push_back(i);
        return(true);
    }
    return(false);
}

void Groupings::VectorInimigo::eliminarInimigo(const unsigned long int indice)
{
    if(indice >= 0lu && indice < getSize())
    {
        delete(vetor[indice]);
        it = vetor.begin();
        for(register unsigned long int i = 0lu; i < getSize(); i++)
        {
            if(i == indice)
            {
                vetor.erase(it);
                i = getSize();
            }
            it++;
        }
    }
}

void Groupings::VectorInimigo::limpar()
{
    for(register unsigned long int i = 0; i < vetor.size(); i++)
    {
        delete (vetor[i]);
    }
    vetor.clear();
}

ent::cha::ini::Enemy* Groupings::VectorInimigo::operator[](const unsigned long int i) const
{
    return(vetor[i]);
}

void Groupings::VectorInimigo::resetCollisions()
{
    unsigned long int i;
    for(i = 0lu; i < vetor.size(); i++)
    {
        vetor[i]->restartCollisions();
    }
}

///IMPLEMENTACOES DA CLASSE LISTA DE OBSTACULO

Groupings::ListaObstaculo::ListaObstaculo():
    lista()
{

}

Groupings::ListaObstaculo::~ListaObstaculo()
{
    limpar();
}

const unsigned long int Groupings::ListaObstaculo::getSize() const
{
    return(lista.getSize());
}

const bool Groupings::ListaObstaculo::insertObstacle(ent::obs::Obstacle* o) //REVIEW
{
    return(lista.insertList(o));
}

ent::obs::Obstacle* Groupings::ListaObstaculo::getObstaculo(const unsigned long int indice) const
{
    if(indice < getSize())
    {
        //return(lista.getData(indice));
        return(lista[indice]);
    }
    return(NULL);
}

void Groupings::ListaObstaculo::eliminarObstaculo(const unsigned long int i)
{
    lista.deleteData(i);
}

void Groupings::ListaObstaculo::limpar()
{
    unsigned long int i;
    for(i = 0; i < lista.getSize(); i++)
    {
        ent::obs::Obstacle* aux = lista[i];
        delete aux;
    }
    lista.clearList();
}

const bool Groupings::ListaObstaculo::ChecarColisoesEntreObstaculo(ent::obs::Obstacle* a, ent::obs::Obstacle* b)
{
    VB horizontal;
    VB vertical;
    Vector2D<float> thisPosition = a->getPosition();
    Vector2D<float> thisHalfSize = a->getHalfSize();
    Vector2D<float> otherPosition = b->getPosition();
    Vector2D<float> otherHalfSize = b->getHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
    float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

    if(intersectX < 0.0 && intersectY < 0.0)
    {
        a->setColisao(true);
        b->setColisao(true);

        if(intersectX > intersectY)
        {
            //COLISAO HORIZONTAL
            if(deltaX > 0.0f)
            {
                //COLISAO DA DIREITA DO REFERENCIAL

                if(a->getID() != 6)
                {
                    a->InitialUpdate();
                    a->Move(intersectX, 0.0f);
                    a->UpdatePosition();
                }

                if(b->getID() != 6)
                {
                    b->InitialUpdate();
                    b->Move(-intersectX, 0.0f);
                    b->UpdatePosition();
                }

                horizontal.y = true;
            }
            else
            {

                if(a->getID() != 6lu)
                {
                    a->InitialUpdate();
                    a->Move(-intersectX, 0.0f);
                    a->UpdatePosition();
                }

                if(b->getID() != 6lu)
                {
                    b->InitialUpdate();
                    b->Move(intersectX, 0.0f);
                    b->UpdatePosition();
                }

                horizontal.x = true;
            }
            a->setHorizontalCollision(horizontal);
            a->setHorizontalCollision(horizontal.y, horizontal.x);
        }
        else
        {
            //COLISAO VERTICAL
            if(deltaY > 0.0f)
            {
                //COLISAOA BAIXO DO REFERENCIAL
                if(a->getID() != 6lu)
                {
                    a->InitialUpdate();
                    a->Move(0.0f, intersectY);
                    a->UpdatePosition();
                }

                if(b->getID() != 6lu)
                {
                    b->InitialUpdate();
                    b->Move(0.0f, -intersectY);
                    b->UpdatePosition();
                }

                vertical.y = 1lu;
            }
            else
            {
                //COLISAOA CIMA DO REFERENCIAL

                if(a->getID() != 6lu)
                {
                    a->InitialUpdate();
                    a->Move(0.0f, -intersectY);
                    a->UpdatePosition();
                }

                if(b->getID() != 6lu)
                {
                    b->InitialUpdate();
                    b->Move(0.0f, intersectY);
                    b->UpdatePosition();
                }

                vertical.x = 1lu;
            }
            a->setVerticalCollision(vertical);
            b->setVerticalCollision(vertical.y, vertical.x);
        }
        return true;
    }
    return(false);
}

void Groupings::ListaObstaculo::ChecarColisoesEntreObstaculo()
{
    unsigned long int i;
    unsigned long int j;

    for(i = 0lu; i < (lista.getSize() - 1lu); i++)
    {
        for(j = i + 1lu; j < lista.getSize(); j++)
        {
            ChecarColisoesEntreObstaculo(lista[i], lista[j]);
        }
    }
}

void Groupings::ListaObstaculo::resetCollisions()
{
    unsigned long int i;
    for(i = 0lu; i < lista.getSize(); i++)
    {
        lista[i]->restartCollisions();
    }
}
