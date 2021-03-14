#include "Game.h"

Game::Game()
{
    g = new GraphicManager();
    Entity::setGraphicManager(g);
    g->addBody("Player01");
    g->addBody("Player02");
    g->addBody("Enemy1");
    g->addBody("Enemy2");
    g->addBody("Enemy3");
    g->addBody("Obstacle1");
    g->addBody("Obstacle2");
    g->addBody("Obstacle3");
    g->addBody("Platform");
    g->addBody("Projectile");
    g->addBody("Life1");
    g->addBody("phase");

    t = new Screen();
}

Game::~Game()
{
    Entity::setGraphicManager(NULL);
    delete g;
    g = NULL;
    delete(t);
}

void Game::Executar()
{
    //g->setFramerateLimit(120lu);
    bool tex = true;
    float time = 0.0f;
    while(g->isOpen())
    {
        g->set_Delta_Time();
        time += g->get_Delta_Time();
        //cout << "Time: " << g->get_Delta_Time() << endl;
        while(g->pollEvent())
        {
            if(g->closed())
            {
                g->close();
            }
            if(g->Resized())
            {
                g->ResizeView();
            }
        }
        t->run();
        if(g->isPR() && time > 0.15f)
        {
            time = 0.0f;
            if(tex)
            {
                t->removeTexture();
                tex = false;
            }
            else
            {
                t->putTexture();
                tex = true;
            }
        }
    }
}
