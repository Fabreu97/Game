#ifndef INCLUDED_TELA_H
#define INCLUDED_TELA_H

#include "CollisionManager.h"

#define DELAY_PRESS_BUTTON 0.15f
#define INVISIBLE_TEXT_TIME 0.5f

using namespace Groupings;

namespace ent
{
    namespace screen
    {
        class Screen;

        class EstadoTela:
            public Entity
        {
        public:

            EstadoTela(const string c = "");
            virtual ~EstadoTela();

            void ChangeState(ent::screen::Screen* t, ent::screen::EstadoTela* s);

            virtual void run(ent::screen::Screen* t) = 0;
            virtual void play(ent::screen::Screen* t) = 0;
            virtual void pause(ent::screen::Screen* t) = 0;
            virtual void option(ent::screen::Screen* t) = 0;
            virtual void exit(ent::screen::Screen* t) = 0;
            void savegame();

            void putTexture();
            void removeTexture();
            virtual void DrawPause();

            static const float getTime();

        protected:

            ListaEntidade LEntidade;
            static float elapsed_time;
        };

        namespace phase
        {
            class Phase:
                public ent::screen::EstadoTela
            {
            protected:

                ent::cha::jog::Player01* ptr1;
                ent::cha::jog::Player02* ptr2;

                Groupings::VectorInimigo VInimigo;
                Groupings::ListaObstaculo LObstaculo;

                Manager::CollisionManager gc1;

                Vector2D<float> posicao_obst;

            public:

                Phase(const string c = "");
                ~Phase();

                void setJogador(ent::cha::jog::Player01* p1);
                void setJogador(ent::cha::jog::Player02* p2);

                void setTexture(const string t);

                //MÉTODOS GERAIS DO JOGO
                void VerificarInimigosMortos();

                ///MÉTODOS DA ENTIDADE FASE
                void InitialUpdate ();
                void UpdateGerenciador ();
                void Update ();
                void Draw();
                void DrawPause();


                ///MÉTODOS DE ADICIONAR OBSTACULOS INIMIGOS E JOGADORES
                void setObstacle(ent::obs::Obstacle* o);
                void setEnemy(ent::cha::ini::Enemy* e);

                ///METODOS DE LISTA DE ENTIDADE
                void adicionarEntidade(ent::Entity* e);

                void Draw(const Vector2D<float> pos1);
                void Draw(const Vector2D<float> pos1, const Vector2D<float> pos2);
                void DrawPauseMenuBackground();// the game stop


                ///METODOS DE VECTOR INIMIGO
                void adicionarInimigo01(const Vector2D<float> position);
                void adicionarInimigo01(const float x, const float y);
                void ChecarColisoesEntreInimigosObstaculos();
                void ChecarColisoesEntreJogadoresInimigosProjeteis();

                ///METODOS DE LISTA DE OBSTACULO
                void adicionarObstaculoPlataforma();
                void adicionarObstaculoPlataforma(const Vector2D<float> position);
                void adicionarObstaculoPlataforma(const float x, const float y);
                void adicionarObstaculoBau(const Vector2D<float> position);
                void adicionarObstaculoBau(const float x, const float y);
                void ChecarColisoesEntreJogadoresObstaculos();
                void ChecarColisoesEntreObstaculos();

                ///TENTATIVA DE PATRONIZAR A CRIACAO DE FASE
                void criarRetaPlataforma(const float distancia, const float y = 1000.0f);
                void criarRetaPlataforma(const unsigned long int qtde_plataformas = 1, const float y = 1000.0f);

                ///METODOS DE ESTADO DE TELA
                void run(ent::screen::Screen* t);//....................TO DO
                void play(ent::screen::Screen* t);//....................TO DO
                void pause(ent::screen::Screen* t);//....................TO DO
                void option(ent::screen::Screen* t);//....................TO DO
                void exit(ent::screen::Screen* t);//....................TO DO
            };
            class FaseVazia:
                public Phase
            {
            public:
                FaseVazia(const string c = "");
                ~FaseVazia();
            };
            class Fase01:
                public Phase
            {
            public:
                Fase01(const bool player1 = true, const bool player2 = false, const string c = "");
                ~Fase01();
            };

            class Fase02:
                public Phase
            {
            public:
                Fase02(const bool player1 = true, const bool player2 = false, const string c = "");
                ~Fase02();

            };

            class Fase03:
                public Phase
            {
            private:


            public:
                Fase03(const bool player1 = true, const bool player2 = false, const string c = "");
                ~Fase03();
            };
        }

        namespace menu
        {
            class MenuPause;

            class Button:
                public Entity
            {
            protected:

                bool click;
                bool active;

            public:

                Button(const string a = "Texture/Botoes/Play.png");
                ~Button();

                void setKey(const string k);
                const string getKey() const;

                const bool getClick() const;

                void setTexture(const string t);

                void InitialUpdate();
                void UpdateGerenciador();//............TO DO
                void Update();//.......................TO DO
                void Draw();
                void DrawPause();
            };

            class Game01:
                public Button
            {
            public:
                Game01(const string a = "Texture/Botoes/Player01.png");
                ~Game01();
            };

            class Game02:
                public Button
            {
            public:
                Game02(const string a = "Texture/Botoes/Player02.png");
                ~Game02();
            };

            class LoadGame:
                public Button
            {
            public:
                LoadGame(const string a = "Texture/Botoes/LoadGame.png");
                ~LoadGame();
            };

            class Option:
                public Button
            {
            public:
                Option(const string a = "Texture/Botoes/Option.png");
                ~Option();
            };

            class Exit:
                public Button
            {
            public:
                Exit(const string a = "Texture/Botoes/Exit.png");
                ~Exit();
            };

            class ButtonManager
            {
            private:

                deque<Button*> buttons;

            public:

                ButtonManager();
                ~ButtonManager();

                const long int getIndiceBotao();

                void InitialUpdate();
                void insertButton(ent::screen::menu::Button* b);
            };

            class Menu:
                public EstadoTela
            {
            protected:

                ButtonManager menu;

            public:

                Menu(const string c);
                virtual ~Menu();

            };

            class MenuInicial:
                public Menu
            {
            private:

                unsigned long int number_of_players;

            public:

                MenuInicial(const string c = "");
                ~MenuInicial();

                void setTexture(const string t);
                void InitialUpdate ();
                void UpdateGerenciador ();
                void Update ();
                void Draw ();

                void run(ent::screen::Screen* t);
                void play(ent::screen::Screen* t);
                void pause(ent::screen::Screen* t);
                void option(ent::screen::Screen* t);
                void loadGame(ent::screen::Screen* t);
                void exit(ent::screen::Screen* t);
            };

            class MenuPause:
                public Menu
            {
            private:

                ent::screen::phase::Phase* game;
                float time_text;

            public:

                MenuPause(ent::screen::phase::Phase* f = NULL);
                ~MenuPause();

                void setTexture(const string t);
                void InitialUpdate ();
                void UpdateGerenciador ();
                void Update ();
                void Draw ();
                void run(ent::screen::Screen* t);

                void play(ent::screen::Screen* t);
                void pause(ent::screen::Screen* t);
                void option(ent::screen::Screen* t);
                void exit(ent::screen::Screen* t);
            };

            class MenuOpcao:
                public Menu
            {
            public:

                MenuOpcao();
                ~MenuOpcao();

                void run(ent::screen::Screen* t);

                void setTexture(const string t);
                void InitialUpdate ();
                void UpdateGerenciador ();
                void Update ();
                void Draw ();

                void play(Screen* t);
                void pause(Screen* t);
                void option(Screen* t);
                void exit(Screen* t);

            };
        }

        class Screen
        {
        private:

            friend class EstadoTela;
            void ChangeState(EstadoTela* s);

        private:

            ent::screen::EstadoTela* _state;
            unsigned long int dif;

        public:

            Screen();
            ~Screen();

            void deleteState();

            void play(Screen* t);
            void pause(Screen* t);
            void option(Screen* t);
            void dificuldade(Screen* t);
            void putTexture();
            void removeTexture();
            void exit(Screen* t);

            void run();
        };
    }
}

#endif // INCLUDED_TELA_H
