#ifndef INCLUDED_GRAPHIC_MANAGER
#define INCLUDED_GRAPHIC_MANAGER

#include "Vector2D.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <windows.h>

#define MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER 175.0f

typedef Vector2D<int>               VI;
typedef Vector2D<unsigned int>      VU;
typedef Vector2D<size_t>            VS;
typedef Vector2D<long int>          VL;
typedef Vector2D<unsigned long int> VLU;
typedef Vector2D<float>             VF;
typedef Vector2D<double>            VD;
typedef Vector2D<bool>              VB;

using namespace std;

namespace Manager
{
    class GraphicManager
    {
    private:
        class Body
        {
        private:

            sf::RectangleShape body;
            sf::Texture texture;
            sf::IntRect uvRect;

            string path;

        public:

            Body(const VF size = Vector2D<float>(100.0f, 200.0f), const string ptexture = "imagem/tux_from_linux.png");
            ~Body();

            void setPosition (const VF position);
            void setPosition (const float x, const float y);
            const VF getPosition () const;
            void setSize (const VF size_);
            void setSize (const float x, const float y);
            const VF getSize () const;
            void setTexture (const string ptexture);
            const string getTexture() const;
            const VF getTextureSize() const;
            void putTexture ();
            void noTexture();
            void setIntRect (const float width, const float height, const float left, const float top);
            void setTextureRect ();
            void setColor (const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alfa = 255);
            void move (const float x, const float y);
            void move (const VF moviment);
            sf::RectangleShape* getBody();

            //Sobrecarga de Operadores
            const bool operator == (const Body& c) const;
            const bool operator == (const Vector2D<float>& p) const;
            const bool operator != (const Body& c) const;
            const bool operator != (const Vector2D<float>& p) const;
        };

        class Text
        {
        private:
            sf::Text text;
            sf::Font font;

        public:
            Text();
            ~Text();

            const bool setFont(const string font);
            void setFillColor(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alfa = 255);
            void setString(const string s);
            void setPosition(const VF position);
            void setCharacterSize(size_t size);
            sf::Text* getText();
        };

    private:

        sf::RenderWindow window;
        sf::View view;
        sf::Event evento;
        sf::Clock clock;

        int number_of_players;
        float swy; // initial window size
        static float delta_time; //time of loop

        sf::RectangleShape* ptrR;
        Body HealthBar01;
        Body HealthBar02;
        map<string, Body*> manager;
        Text text;

        Body* getSecond(const string key);

    public:

        GraphicManager(const string name = "The Game", const Vector2D<unsigned int> window_size = Vector2D<unsigned int>(1600u, 800u));
        ~GraphicManager();

        //Ooerações com Janela
        bool isOpen();
        bool pollEvent();
        void setView(); //Colocar a Camera na Janela
        void setPositionView(VF position);
        VF getPositionView() const;
        void clear();
        void clear(const unsigned char,const unsigned char,const unsigned char);
        void display();
        void close();
        const bool closed();
        void ResizeView();
        bool Resized();
        void setTitle(const string nome_da_janela);
        void setVerticalSyncEnabled(const bool chave); //Deixa o loop com a mesma velocidade que seu monitor
        void setFramerateLimit(const unsigned long int vel); //colocar a velocidade por frame(1s / time = tempo do loop) RECOMENDAVEL POR VOLTA DE 100 A 60
        void setFramerateLimitTime(const float time);
        const VF getPositionWindow() const;//HERE
        float WindowRation();
        const VF getSizeWindow() const;
        const VF getSizeView() const;

        //Operações com a Camera(View) da Janela
        void Centralize(const float x1, const float y1, const float x2, const float y2);
        void Centralize(const VF v1, const VF v2);
        void Centralize(const float x, const float y);
        void Centralize(const VF v);

        //Desenhar na Tela
        void DrawLife01();
        //void DrawLife02();

        //Detectar Teclas Preenchionadas
        const bool isPW() const;
        const bool isPS() const;
        const bool isPA() const;
        const bool isPD() const;
        const bool isPR() const;
        const bool isPP() const;
        const bool isPEnter() const;
        const bool isP_UP() const;
        const bool isP_Down() const;
        const bool isP_Left() const;
        const bool isP_Right() const;
        const bool isP_ALT() const;
        const bool isP_Space() const;

        //Mouse Preenchionado
        const bool isM_Left() const;
        const bool isM_Right() const;

        const VF getPositionMouse() const;

        void set_Delta_Time();
        static float get_Delta_Time();

        void removeTexture();
        void putTexture();

        //Métodos Dedicados ao Body de Corações
        void setPositionLife01();
        void setSizeLife01(const Vector2D< float> v);
        void setSizeLife01(const  float x, const  float y);
        void setTextureLife01(const string t);
        VF getTextureSizeLife01() const;
        void setIntRectLife01(const float width, const float height, const float left, const float top);
        void setTextureRectLife01();
        void moveLife01(const VF v);
        void moveLife01(const float x, const float y);

        //Métodos Dedicados ao Body de Corações
        void setPositionLife02();
        void setSizeLife02(const Vector2D< float> v);
        void setSizeLife02(const  float x, const  float y);
        void setTextureLife02(const string t);
        VF getTextureSizeLife02() const;
        void setIntRectLife02(const float width, const float height, const float left, const float top);
        void setTextureRectLife02();
        void moveLife02(const VF v);
        void moveLife02(const float x, const float y);

        //MÉTODOS DO CORPO SERA DICIOANDO NO MAP MENU
        Body* getMap(const string key);
        const bool ThereIsThisKey(const string key);
        void AdicionarBotaoNoMenu(const string key, const string texture, const VF position, const VF sizeB);
        void ajustarBotoes(const string key, const unsigned long int qtd_botoes, const unsigned long int indice);
        VF getPositionButton(const string key);
        VF getSizeButton(const string key);
        void DrawMap(const string key);
        void DrawMapBotao(const string key, const bool active);

        //MÉTODOS DO CORPO DENTRO DA ESTRUTURA MAP
        void addBody(const string key);
        void setPosition(const string key, const VF position);
        void setPosition(const string key, const float x, const float y);
        const VF getPosition(const string key);
        void setSize(const string key, const VF tam);
        void setSize(const string key, const float x, const float y);
        const VF getSize(const string key);
        void setTexture(const string key, const string texture);
        void removeTexture(const string key);
        const string getTexture(const string key);
        const VF getTextureSize(const string key);
        void setIntRect(const string key, const float width, const float height, const float left, const float top);
        void setTextureRect(const string key);
        void Move(const string key, const VF movement);
        void Move(const string key, const float x, const float y);
        void Draw(const string key);
        void setColor(const string key, const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alfa = 255);

        //TEXT
        const bool setFontText(const string f);
        void setFillColorText(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alfa = 255);
        void setStringText(const string s);
        void setPositionText(const VF position);
        void setPositionText(const float x, const float y);
        const VF getPositionText() const;
        void setCharacterSizeText(size_t size);
        void DrawTextMY();
        void DrawTextMY(const string t);
    };
}

#endif // INCLUDED_GRAPHIC_MANAGER
