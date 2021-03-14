#ifndef INCLUDED_JOGO_H
#define INCLUDED_JOGO_H

#define TAMANHO_DO_JOGADOR_X 84.0f
#define TAMANHO_DO_JOGADOR_Y 120.0f

#include "Screen.h"

using namespace ent;
using namespace cha;
using namespace jog;
using namespace ini;
using namespace obs;
using namespace screen;
using namespace phase;
using namespace Groupings;
using namespace Manager;

class Game
{
private:

    GraphicManager* g;
    Screen* t;

public:

    Game();  //....................................................TO REVIEW
    ~Game(); //....................................................TO REVIEW

    void Executar ();//............................................TO REVIEW

};

#endif // INCLUDED_JOGO_H
