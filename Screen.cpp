#include "Screen.h"

///METODOS DE ESTADO DE TELA

float ent::screen::EstadoTela::elapsed_time = 0.0f;

ent::screen::EstadoTela::EstadoTela(const string c):
    Entity(c)
    {
        elapsed_time = 0.0f;
    }

ent::screen::EstadoTela::~EstadoTela()
{
    elapsed_time = 0.0f;
}

void ent::screen::EstadoTela::ChangeState(ent::screen::Screen* t, ent::screen::EstadoTela* s)
{
    t->ChangeState(s);
}

void ent::screen::EstadoTela::savegame()
{
    LEntidade.savegame("save");
}

void ent::screen::EstadoTela::putTexture()
{
    LEntidade.putTexture();
}

void ent::screen::EstadoTela::removeTexture()
{
    LEntidade.removeTexture();
}

void ent::screen::EstadoTela::DrawPause(){}

const float ent::screen::EstadoTela::getTime()
{
    return(elapsed_time);
}

///METODOS DE FASE

ent::screen::phase::Phase::Phase(const string c):
    ent::screen::EstadoTela(c)
{
    id = 10;
    ptr1 = NULL;
    ptr2 = NULL;
    key = "phase";
    LEntidade.incluirEntidade(this);
    control->setSize(key, VF(1600, 800));
    control->setColor(key, 100, 180, 200);

    posicao_obst = Vector2D<float>(0.0f, 1000.0f);
    gc1.setListas(&LObstaculo);
    gc1.setListas(&VInimigo);
}

ent::screen::phase::Phase::~Phase()
{
    LEntidade.limpar();
    VInimigo.limpar();
    LObstaculo.limpar();

    if(ptr1 != NULL)
    {
        delete(ptr1);
    }
    if(ptr2 != NULL)
    {
        delete(ptr2);
    }
}

void ent::screen::phase::Phase::setJogador(ent::cha::jog::Player01* p1)
{
    if(ptr1 != NULL)
    {
        LEntidade.eliminatePlayer(ptr1);
        delete ptr1;
    }
    ptr1 = p1;
    LEntidade.incluirEntidade(ptr1);
    gc1.setJogador(p1);
}

void ent::screen::phase::Phase::setJogador(ent::cha::jog::Player02* p2)
{
    if(ptr1 != NULL)
    {
        LEntidade.eliminatePlayer(ptr1);
        delete ptr2;
    }
    ptr2 = p2;
    LEntidade.incluirEntidade(static_cast<Entity*> (ptr2) );
    gc1.setJogador(p2);
}

void ent::screen::phase::Phase::setTexture(const string t)
{
    path = t;
    control->setTexture(key, path);
}

void ent::screen::phase::Phase::VerificarInimigosMortos()
{
    unsigned long int i;
    for(i = 0; i < VInimigo.getSize(); i++)
    {
        ent::cha::ini::Enemy* enemy = VInimigo[i];
        if(!enemy->getLife())
        {
            LEntidade.eliminarInimigo(enemy);
            VInimigo.eliminarInimigo(i); //deleto o inimigo
        }
    }
}

void ent::screen::phase::Phase::InitialUpdate ()
{

}
void ent::screen::phase::Phase::UpdateGerenciador ()
{
    control->setSize(key, tam_tex);
    pos = control->getPosition(key);
}
void ent::screen::phase::Phase::Update ()
{
    setPosition(control->getPositionView());
    control->setPosition(key, pos);

}

void ent::screen::phase::Phase::setObstacle(ent::obs::Obstacle* o)
{
    LObstaculo.insertObstacle(o);
    LEntidade.incluirEntidade(static_cast<ent::Entity*> (o) );
}

void ent::screen::phase::Phase::setEnemy(ent::cha::ini::Enemy* e)
{
    VInimigo.incluirInimigo(e);
    LEntidade.incluirEntidade(static_cast<ent::Entity*> (e) );
}

void ent::screen::phase::Phase::adicionarEntidade(ent::Entity* e)
{
    LEntidade.incluirEntidade(e);
}

void ent::screen::phase::Phase::Draw()
{
    //LEntidade.Draw();
    control->Draw(key);
}

void ent::screen::phase::Phase::Draw(const Vector2D<float> pos1)
{
    LEntidade.Draw(pos1);
}

void ent::screen::phase::Phase::Draw(const Vector2D<float> pos1, const Vector2D<float> pos2)
{
    control->Draw(key);
    LEntidade.Draw(pos1, pos2);
}

void ent::screen::phase::Phase::DrawPauseMenuBackground()
{
    LEntidade.DrawPause(control->getPositionView());
}

void ent::screen::phase::Phase::DrawPause()
{
    control->Draw(key);
}

//VECTOR DE INIMIGO

void ent::screen::phase::Phase::adicionarInimigo01(const Vector2D<float> position)
{
    ent::cha::ini::Enemy01* inimigo = new ent::cha::ini::Enemy01 ();
    inimigo->setPosition(position);

    VInimigo.incluirInimigo(inimigo);
    LEntidade.incluirEntidade(static_cast<ent::Entity*> (inimigo));
}

void ent::screen::phase::Phase::adicionarInimigo01(const float x, const float y)
{
    ent::cha::ini::Enemy01* inimigo = new ent::cha::ini::Enemy01 ();
    inimigo->setPosition(x, y);
    inimigo->InitialUpdate();

    VInimigo.incluirInimigo(inimigo);
    LEntidade.incluirEntidade(static_cast<ent::Entity*>(inimigo));
}

void ent::screen::phase::Phase::ChecarColisoesEntreInimigosObstaculos()
{
    gc1.ChecarColisoesInimigosObstaculos();
}

void ent::screen::phase::Phase::ChecarColisoesEntreJogadoresInimigosProjeteis()
{
    gc1.ChecarColisoesJogadoresInimigosProjeteis();
}

void ent::screen::phase::Phase::adicionarObstaculoPlataforma()
{
    ent::obs::Platform* p = new ent::obs::Platform(posicao_obst);
    posicao_obst.x += 2000.0f;

    LObstaculo.insertObstacle(p);
    adicionarEntidade(p);
}

void ent::screen::phase::Phase::adicionarObstaculoPlataforma(const Vector2D<float> position)
{
    ent::obs::Platform* p = new ent::obs::Platform(position);
    p->InitialUpdate();

    LObstaculo.insertObstacle(p);
    adicionarEntidade(p);
}

void ent::screen::phase::Phase::adicionarObstaculoPlataforma(const float x, const float y)
{
    ent::obs::Platform* p = new ent::obs::Platform(Vector2D<float>(x,y));
    LObstaculo.insertObstacle(p);
    p->InitialUpdate();
    adicionarEntidade(p);
}

void ent::screen::phase::Phase::adicionarObstaculoBau(const Vector2D<float> position)
{
    ent::obs::Obstacle01* aux = new ent::obs::Obstacle01();
    aux->setPosition(position);
    aux->InitialUpdate();
    LObstaculo.insertObstacle(static_cast<ent::obs::Obstacle*> (aux) );
    adicionarEntidade(static_cast<ent::Entity*> (aux) );
}

void ent::screen::phase::Phase::adicionarObstaculoBau(const float x, const float y)
{
    ent::obs::Obstacle01* aux = new ent::obs::Obstacle01();
    aux->setPosition(Vector2D<float>(x,y));
    aux->InitialUpdate();
    LObstaculo.insertObstacle(static_cast<ent::obs::Obstacle*> (aux) );
    adicionarEntidade(aux);
}

void ent::screen::phase::Phase::ChecarColisoesEntreJogadoresObstaculos()
{
    gc1.ChecarColisoesJogadoresObstaculos();
}

void ent::screen::phase::Phase::ChecarColisoesEntreObstaculos()
{
    LObstaculo.ChecarColisoesEntreObstaculo();
}

void ent::screen::phase::Phase::criarRetaPlataforma( const float distancia, const float y)
{
    unsigned long int t = static_cast<int>(distancia / 2000.0f);
    criarRetaPlataforma(y,t);
}

void ent::screen::phase::Phase::criarRetaPlataforma(const unsigned long int qtde_plataformas, const float y)
{
    unsigned long int i;
    posicao_obst.y = y;
    for(i = 0lu; i < qtde_plataformas; i++)
    {
        adicionarObstaculoPlataforma();
    }
}

void ent::screen::phase::Phase::run(ent::screen::Screen* t)
{
    if(ptr1 != NULL)
    {
        if(ptr2 != NULL)
        {
            control->Centralize(ptr1->getPosition(), ptr2->getPosition());
            ptr1->restartCollisions();
            ptr2->restartCollisions();
        }
        else
        {
            control->Centralize(ptr1->getPosition());
            ptr1->restartCollisions();
        }
    }
    else
    {
        if(ptr2 != NULL)
        {
            control->Centralize(ptr2->getPosition());
            ptr2->restartCollisions();
        }
        else
        {
            //CHAMA O MENU DE MORTE
        }
    }
    control->setView();
    gc1.resetCollisions();
    this->ChecarColisoesEntreJogadoresInimigosProjeteis();
    this->ChecarColisoesEntreJogadoresObstaculos();
    this->ChecarColisoesEntreObstaculos();
    this->ChecarColisoesEntreInimigosObstaculos();
    VerificarInimigosMortos();
    control->clear(100,180,200);
    if(ptr2 != NULL)
    {
        this->Draw(ptr1->getPosition(), ptr2->getPosition());
    }
    else
    {
        this->Draw(ptr1->getPosition());
    }

    control->display();
    elapsed_time += control->get_Delta_Time();
    if(control->isPP() && elapsed_time > DELAY_PRESS_BUTTON)
    {
        pause(t);
    }
}
void ent::screen::phase::Phase::play(ent::screen::Screen* t)
{

}
void ent::screen::phase::Phase::pause(ent::screen::Screen* t)
{
    ChangeState(t, new ent::screen::menu::MenuPause(this));
}
void ent::screen::phase::Phase::option(ent::screen::Screen* t)
{

}
void ent::screen::phase::Phase::exit(ent::screen::Screen* t)
{

}

///MÉTODOS DE FASE VAZIA
ent::screen::phase::FaseVazia::FaseVazia(const string c):
    ent::screen::phase::Phase(c)
{
    id = IDFASE3;
}

ent::screen::phase::FaseVazia::~FaseVazia()
{

}

///MÉTODOS DE FASE 01

ent::screen::phase::Fase01::Fase01(const bool player1, const bool player2, const string c):
    ent::screen::phase::Phase(c)
{
    id = IDFASE1;
    if(player1)
    {
        ptr1 = new ent::cha::jog::Player01(HEIGHTJUMPER);
        ptr1->setTexture("Texture/Marco.png");
        LEntidade.incluirEntidade(ptr1);
        gc1.setJogador(ptr1);
    }

    if(player2)
    {
        ptr2 = new ent::cha::jog::Player02(HEIGHTJUMPER);
        ptr2->setSize(TAMANHO_COLIDIVEL_JOGADOR_X, TAMANHO_COLIDIVEL_JOGADOR_Y);
        ptr2->setSizeTexture(TAMANHO_DA_TEXTURA_JOGADOR_X, TAMANHO_DA_TEXTURA_JOGADOR_Y);
        ptr2->setPosition(700.f, 800.0f);
        ptr2->setContImage(3,9);
        ptr2->PreencherLinhas(0,1);
        ptr2->setSpeed(SPEED_JOGADOR);
        ptr2->setTempoCiclo(0.2);
        ptr2->setTexture("Texture/n_linux.png");
        ptr2->InitialUpdate();
        LEntidade.incluirEntidade(ptr2);
        gc1.setJogador(ptr2);
    }

    this->criarRetaPlataforma(2lu);
    this->criarRetaPlataforma(3lu, 800.0f);
    this->criarRetaPlataforma(5lu, 1000.0f);
    this->criarRetaPlataforma(1lu, 800.0f);
    this->adicionarObstaculoBau(500.0f, 700.0f);
    this->adicionarObstaculoBau(1300.0f, 700.0f);
    this->adicionarObstaculoBau(8000.0f, 300.0f);
    this->adicionarInimigo01(800.0f, 750.0f);
    this->adicionarInimigo01(250.0f, 750.0f);
    this->adicionarInimigo01(1500.0f, 0.0f);
    this->adicionarInimigo01(2500.0f, 0.0f);
    this->adicionarInimigo01(3500.0f, 0.0f);
    this->adicionarInimigo01(6000.0f, 0.0f);
    int a = rand()%8001;
    this->adicionarInimigo01(a, 0.0f);
    a = rand()%7869;
    this->adicionarInimigo01(a, 0.0f);
    a = rand()%7890;
    this->adicionarInimigo01(a, 0.0f);
    a = rand()%7815;
    this->adicionarInimigo01(a, 0.0f);
    a = rand()%7969;
    this->adicionarInimigo01(a, 0.0f);
    a = rand()%6869;
    this->adicionarInimigo01(a, 0.0f);
    a = rand()%6867;
    this->adicionarInimigo01(a, 0.0f);
    a = rand()%9000;
    this->adicionarInimigo01(a, 0.0f);
    a = rand()%8888;
    this->adicionarInimigo01(a, 0.0f);
    a = rand()%15000;
    this->adicionarInimigo01(a, 0.0f);
    a = rand()%16000;
    this->adicionarInimigo01(a, 0.0f);
    a = rand()%12589;
    this->adicionarInimigo01(a, 0.0f);
}

ent::screen::phase::Fase01::~Fase01()
{

}

///MÉTODOS DE FASE 02

ent::screen::phase::Fase02::Fase02(const bool player1, const bool player2, const string c):
    ent::screen::phase::Phase(c)
{
    id = IDFASE2;
}

ent::screen::phase::Fase02::~Fase02()
{

}

///MÉTODOS DE FASE 03

ent::screen::phase::Fase03::Fase03(const bool player1, const bool player2, const string c):
    ent::screen::phase::Phase(c)
{
    id = IDFASE3;
}

ent::screen::phase::Fase03::~Fase03()
{

}

///MÉTODOS DE BOTAO

ent::screen::menu::Button::Button(const string a):
    Entity(a),
    click(false),
    active(false)
{
    tam_tex.x = 375.0f;
    tam_tex.y = 150.0f;
}

ent::screen::menu::Button::~Button()
{

}

void ent::screen::menu::Button::setKey(const string k)
{
    key = k;
}

const string ent::screen::menu::Button::getKey() const
{
    return(key);
}

const bool ent::screen::menu::Button::getClick() const
{
    return(click);
}

void ent::screen::menu::Button::setTexture(const string t)
{
    path = t;
    control->setTexture(key, path);
}

void ent::screen::menu::Button::InitialUpdate()
{
    control->AdicionarBotaoNoMenu(key, path, pos, tam_tex);
    click = false;
    active = false;
}

void ent::screen::menu::Button::UpdateGerenciador()
{

}

void ent::screen::menu::Button::Update()
{
    float xx = abs(control->getPositionMouse().x - (control->getPositionWindow().x + control->getSizeWindow().x/2.0 + (control->getPositionButton(key).x * control->WindowRation()) ) );
    float yy = abs(control->getPositionMouse().y - ( (control->getPositionWindow().y + 27.5f) + (control->getSizeWindow().y)/2.0 + (control->getPositionButton(key).y * control->WindowRation()) ) );
    active = false;
    if(xx <= (tam_tex.x * control->WindowRation() / 2.0f) )
    {
        if(yy <= (tam_tex.y * control->WindowRation()/ 2.0f))
        {
            active = true;
            if(control->isM_Left() || control->isPEnter())
            {
                click = true;
            }
        }
    }
}

void ent::screen::menu::Button::Draw()
{
    //control->DrawMap(key);
    control->DrawMapBotao(key, active);
}

void ent::screen::menu::Button::DrawPause(){}

///METODOS DO BOTAO Player01

ent::screen::menu::Game01::Game01(const string a):
    Button(a)
{
    setKey("1Player");
}
ent::screen::menu::Game01::~Game01()
{

}

///METODOS DO BOTAO Player02

ent::screen::menu::Game02::Game02(const string a):
    Button(a)
{
    setKey("2Player");
}
ent::screen::menu::Game02::~Game02()
{

}

///MÉTODOS DE BOTAO LOAD GAME

ent::screen::menu::LoadGame::LoadGame(const string a):
    Button(a)
{
    setKey("LoadGame");
}
ent::screen::menu::LoadGame::~LoadGame()
{

}
///MÉTODOS DO BOTAO OPTION

ent::screen::menu::Option::Option(const string a):
    Button(a)
{
    setKey("Option");
}
ent::screen::menu::Option::~Option()
{

}

///METODOS DO Button BOTAO Exit

ent::screen::menu::Exit::Exit(const string a):
    Button(a)
{
    setKey("Exit");
}
ent::screen::menu::Exit::~Exit()
{

}

///MÉTODOS DE GERENCIADOR DE BOTOES

ent::screen::menu::ButtonManager::ButtonManager()
{

}

ent::screen::menu::ButtonManager::~ButtonManager()
{
    for(unsigned long int i = 0lu; i < buttons.size(); i++)
    {
        delete(buttons[i]);
    }
    buttons.clear();
}

const long int ent::screen::menu::ButtonManager::getIndiceBotao()
{
    deque<Button*>::iterator it;
    for(it = buttons.begin(); it != buttons.end(); ++it)
    {
        if((*it)->getClick())
        {
            return((*it)->getID());
        }
    }
    return(-1l);
}

void ent::screen::menu::ButtonManager::InitialUpdate()
{
    unsigned long int i = 0lu;
    deque<Button*>::iterator it;
    for(it = buttons.begin(); it != buttons.end(); ++it)
    {
        (*it)->InitialUpdate();
        ent::Entity::getGraphicManager()->ajustarBotoes((*it)->getKey(), buttons.size(), i);
        (*it)->setSizeTexture(ent::Entity::getGraphicManager()->getSizeButton((*it)->getKey()));
        (*it)->setPosition(ent::Entity::getGraphicManager()->getPositionButton((*it)->getKey()));
        (*it)->setID(i);
        i++;
    }
}

void ent::screen::menu::ButtonManager::insertButton(ent::screen::menu::Button* b)
{
    buttons.push_back(b);
}

///METODOS DE MENU

ent::screen::menu::Menu::Menu(const string c):
    EstadoTela(c)
{

}

ent::screen::menu::Menu::~Menu()
{

}

///METODOS DE MENU INICIAL

ent::screen::menu::MenuInicial::MenuInicial(const string c):
    Menu(c),
    number_of_players(0lu)
{
    ent::screen::menu::Button* aux = new ent::screen::menu::Game01();
    menu.insertButton(aux);
    LEntidade.incluirEntidade(aux);

    aux = new ent::screen::menu::Game02();
    menu.insertButton(aux);
    LEntidade.incluirEntidade(aux);

    aux = new ent::screen::menu::LoadGame();
    menu.insertButton(aux);
    LEntidade.incluirEntidade(aux);

    aux = new ent::screen::menu::Option();
    menu.insertButton(aux);
    LEntidade.incluirEntidade(aux);

    aux = new ent::screen::menu::Exit();
    menu.insertButton(aux);
    LEntidade.incluirEntidade(aux);

    InitialUpdate();
}

ent::screen::menu::MenuInicial::~MenuInicial(){}

void ent::screen::menu::MenuInicial::run(ent::screen::Screen* t)
{
    switch(menu.getIndiceBotao())
    {
    case 0lu:
        {
            number_of_players = 1lu;
            play(t);
            break;
        }
    case 1lu:
        {
            number_of_players = 2lu;
            play(t);
            break;
        }
    case 2lu:
        {
            loadGame(t);
            break;
        }
    case 3lu:
        {
            option(t);
            break;
        }
    case 4lu:
        {
            exit(t);
            break;
        }
    default: // -1(long int)
        {
            control->setView();
            control->clear(100, 180, 200);
            Draw();
            control->display();
            break;
        }
    }
}

void ent::screen::menu::MenuInicial::setTexture(const string t)
{
    path = t;
}

void ent::screen::menu::MenuInicial::InitialUpdate ()
{
    menu.InitialUpdate();
}

void ent::screen::menu::MenuInicial::UpdateGerenciador ()
{

}

void ent::screen::menu::MenuInicial::Update ()
{

}

void ent::screen::menu::MenuInicial::Draw ()
{
    LEntidade.Draw(control->getPositionView());
}


void ent::screen::menu::MenuInicial::play(ent::screen::Screen* t)
{
    t->deleteState();
    if(number_of_players == 1)
    {
        ChangeState(t, new ent::screen::phase::Fase01(true));
    }
    else
    {
        ChangeState(t, new ent::screen::phase::Fase01(true, true));
    }
}

void ent::screen::menu::MenuInicial::pause(ent::screen::Screen* t)
{

}

void ent::screen::menu::MenuInicial::option(ent::screen::Screen* t)
{

}

void ent::screen::menu::MenuInicial::loadGame(ent::screen::Screen* t)
{
    //
    ifstream in;
    in.open("save.dat", ios::in);
    if(!in)
    {
        cerr << "ERRO EM ABRIR O ARQUIVO" << endl;
        fflush(stdin);
        //Sleep(3000);
        return;
    }

    ent::screen::phase::Phase* _fase = NULL;

    while(!in.eof())
    {
        //id qtdvidas posx posy velx vely atualimagemx atualimagemy key
        int id;
        int life_points;
        VF pos, vel;
        VLU current_image;
        in >> id >> life_points >> pos.x >> pos.y >> vel.x >> vel.y >> current_image.x >> current_image.y;
        cout << id  << " " << life_points << " " << pos.x << " " << pos.y << " " << vel.x << " " << vel.y << " " << current_image.x << " " << current_image.y << endl;
        switch(id)
        {
        case 1:
            {
                ent::cha::jog::Player01* p1 = new ent::cha::jog::Player01(HEIGHTJUMPER);
                p1->setTexture("Texture/Marco.png");
                p1->Damage(6 - life_points);
                p1->setPosition(pos);
                p1->setVelocidade(vel);
                p1->setCurrentImage(current_image);
                p1->InitialUpdate();
                if(_fase != NULL)
                {
                    _fase->setJogador(p1);
                }
                break;
            }
        case 2:
            {
                ent::cha::jog::Player02* p1 = new ent::cha::jog::Player02(HEIGHTJUMPER);
                p1->Damage(6 - life_points);
                p1->setPosition(pos);
                p1->setVelocidade(vel);
                p1->setCurrentImage(current_image);
                p1->InitialUpdate();
                if(_fase != NULL)
                {
                    _fase->setJogador(p1);
                }
                break;
            }
        case 3:
            {
                ent::cha::ini::Enemy01* enemy = new ent::cha::ini::Enemy01();
                enemy->setLifePoints(life_points);
                enemy->setPosition(pos);
                enemy->setVelocidade(vel);
                enemy->setCurrentImage(current_image);
                enemy->InitialUpdate();
                if(_fase != NULL)
                {
                    _fase->setEnemy(enemy);
                }
                break;
            }
        case 4:
            {
                ent::cha::ini::Enemy02* enemy = new ent::cha::ini::Enemy02();
                enemy->setLifePoints(life_points);
                enemy->setPosition(pos);
                enemy->setVelocidade(vel);
                enemy->setCurrentImage(current_image);
                enemy->InitialUpdate();
                if(_fase != NULL)
                {
                    _fase->setEnemy(enemy);
                }
                break;
            }
        case 5:
            {
                ent::cha::ini::Enemy03* enemy = new ent::cha::ini::Enemy03();
                enemy->setLifePoints(life_points);
                enemy->setPosition(pos);
                enemy->setVelocidade(vel);
                enemy->setCurrentImage(current_image);
                enemy->InitialUpdate();
                if(_fase != NULL)
                {
                    _fase->setEnemy(enemy);
                }
                break;
            }
        case 6:
            {
                ent::obs::Platform* obs = new ent::obs::Platform(pos);
                obs->setVelocidade(vel);
                obs->setCurrentImage(current_image);
                obs->InitialUpdate();
                if(_fase != NULL)
                {
                    _fase->setObstacle(obs);
                }
                break;
            }
        case 7:
            {
                ent::obs::Obstacle01* obs = new ent::obs::Obstacle01(pos);
                obs->setVelocidade(vel);
                obs->setCurrentImage(current_image);
                obs->InitialUpdate();
                if(_fase != NULL)
                {
                    _fase->setObstacle(obs);
                }
                break;
            }
        case 8:
            {
                ent::obs::Obstacle02* obs = new ent::obs::Obstacle02(pos);
                obs->setVelocidade(vel);
                obs->setCurrentImage(current_image);
                obs->InitialUpdate();
                if(_fase != NULL)
                {
                    _fase->setObstacle(obs);
                }
                break;
            }
        case 9:
            {
                ent::obs::Obstacle03* obs = new ent::obs::Obstacle03(pos);
                obs->setVelocidade(vel);
                obs->setCurrentImage(current_image);
                obs->InitialUpdate();
                if(_fase != NULL)
                {
                    _fase->setObstacle(obs);
                }
                break;
            }
        case 10:
            {
                ent::screen::phase::Phase* f = new ent::screen::phase::Phase();
                f->setPosition(pos);
                control->setPositionView(pos);
                f->InitialUpdate();
                _fase = f;
                break;
            }
        case 11:
            {
                break;
                //TO DO
            }
        case 12:
            {
                break;
                //TO DO
            }
        case 66:
            {
                break;
            }

        }
    }
    in.close();
    t->deleteState();
    //ent::screen::menu::MenuPause* m = new ent::screen::menu::MenuPause(_fase);
    ChangeState(t, _fase);
}

void ent::screen::menu::MenuInicial::exit(ent::screen::Screen* t)
{
    //t->deleteState();
    control->close();
}

///MÉTODOS DE MENU DE PAUSE

ent::screen::menu::MenuPause::MenuPause(ent::screen::phase::Phase* f):
    ent::screen::menu::Menu("Texture/menuPause.png"),
    game(f),
    time_text(INVISIBLE_TEXT_TIME)
{
    pos = control->getPositionView();
}
ent::screen::menu::MenuPause::~MenuPause()
{

}

void ent::screen::menu::MenuPause::run(ent::screen::Screen* t)
{
    elapsed_time += control->get_Delta_Time();
    if( control->isPP() && (elapsed_time > DELAY_PRESS_BUTTON) )
    {
        game->savegame();
        EstadoTela* _state = game;
        t->deleteState();
        ChangeState(t, _state);
        return;
    }
    //control->setView();
    control->clear();
    Draw();
    control->display();
}

void ent::screen::menu::MenuPause::setTexture(const string t){path = t;}
void ent::screen::menu::MenuPause::InitialUpdate (){}
void ent::screen::menu::MenuPause::UpdateGerenciador (){}
void ent::screen::menu::MenuPause::Update (){}

void ent::screen::menu::MenuPause::Draw ()
{
    time_text -= control->get_Delta_Time();
    game->DrawPauseMenuBackground();
    if(time_text > 0.0f)
    {
        control->setFillColorText(255,255,255);
        control->setStringText(" --- P A U S E ---");
        VF aux;
        aux.x = control->getPositionView().x - 150 ;
        aux.y = control->getPositionView().y - 50 ;
        control->setPositionText(aux);
        control->setCharacterSizeText(32);
        control->DrawTextMY();
    }
    else
    {
        if(time_text < -INVISIBLE_TEXT_TIME)
        {
            time_text = INVISIBLE_TEXT_TIME;
        }
    }
}

void ent::screen::menu::MenuPause::play(ent::screen::Screen* t){}
void ent::screen::menu::MenuPause::pause(ent::screen::Screen* t){}
void ent::screen::menu::MenuPause::option(ent::screen::Screen* t){}
void ent::screen::menu::MenuPause::exit(ent::screen::Screen* t){}

///MÉTODOS DE TELA

ent::screen::Screen::Screen():
    //_state(new ent::screen::phase::Fase01())
    _state(new ent::screen::menu::MenuInicial())
{

}

ent::screen::Screen::~Screen()
{
    deleteState();
}

void ent::screen::Screen::ChangeState(EstadoTela* s)
{
    _state = s;
}

void ent::screen::Screen::deleteState()
{
    if(_state != NULL)
    {
        delete(_state);
        _state = NULL;
    }
}

void ent::screen::Screen::play(Screen* t)
{
    _state->play(this);
}

void ent::screen::Screen::pause(Screen* t)
{
    _state->pause(this);
}

void ent::screen::Screen::option(Screen* t)
{
    _state->option(this);
}

void ent::screen::Screen::dificuldade(Screen* t)
{

}

void ent::screen::Screen::putTexture()
{
    _state->putTexture();
}

void ent::screen::Screen::removeTexture()
{
    _state->removeTexture();
}

void ent::screen::Screen::exit(Screen* t)
{
    _state->exit(this);
}

void ent::screen::Screen::run()
{
    _state->run(this);
}
