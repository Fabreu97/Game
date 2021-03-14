#ifndef INCLUDED_ENTIDADE_H
#define INCLUDED_ENTIDADE_H

//AJUDA

//MACROS PARA IDENTIDADE DAS ENTIDADES
#define IDJOG01 1lu
#define IDJOG02 2lu
#define IDINI01 3lu
#define IDINI02 4lu
#define IDINI03 5lu
#define IDPLATF 6lu
#define IDOBS01 7lu
#define IDOBS02 8lu
#define IDOBS03 9lu
#define IDFASE1 10lu
#define IDFASE2 11lu
#define IDFASE3 12lu

//CHAVES DAS ENTIDADES
#define KEYPLA1 "Player01"
#define KEYPLA2 "Player02"
#define KEYENE1 "Enemy1"
#define KEYENE2 "Enemy2"
#define KEYENE3 "Enemy3"
#define KEYOBS1 "Obstacle1"
#define KEYOBS2 "Obstacle2"
#define KEYOBS3 "Obstacle3"
#define KEYPLT1 "Platform"
#define KEYPRO1 "Projectile"
#define KEYBAR1 "Life1"
#define KEYFAS1 "fase"


//JOGADOR
#define HEIGHTJUMPER 100.0f
#define QTD_VIDAS_JOG 6lu
#define TAMANHO_DA_TEXTURA_JOGADOR_X 70.3125f
#define TAMANHO_DA_TEXTURA_JOGADOR_Y 90.0f
#define TAMANHO_COLIDIVEL_JOGADOR_X 70.3125f
#define TAMANHO_COLIDIVEL_JOGADOR_Y 90.0f
#define SPEED_JOGADOR 300.0f
#define TEMPO_CICLO_PROJETIL 0.03f
#define CHANGE_TIME_ANIMATION_PLAYER01 0.1f

//Jogador
#define PUSH_BAU 0.75f
#define PUSH_CAIXOTE 0.75f
#define PUSH_PLATAFORMA 1.0f
#define PUSH_INIMIGO 1.0f

/*
 * TAMANHO COLIDIVEL X: 29/51 DP TAMANHO DA TEXTURA
 * TAM.X = 41
 * TAM.Y = 51
 */
 //JOGADOR 01
#define TAMANHO_DA_TEXTURA_JOGADOR01_X 130.0f
#define TAMANHO_DA_TEXTURA_JOGADOR01_Y 104.5098f
#define TAMANHO_COLIDIVEL_JOGADOR01_X 73.9215f
#define TAMANHO_COLIDIVEL_JOGADOR01_Y 102.0f
#define SPEED_JOGADOR01 300.0f


//Inimigo
#define ENEMY_LIVES 4lu

//INIMIGO01
#define VELINI01 300.0f;
#define CAMINI01 "Texture/tux_from_linux.png"
#define TAMANHO_DA_TEXTURA_INIMIGO01_X 70.3125f
#define TAMANHO_DA_TEXTURA_INIMIGO01_Y 90.0f
#define TAMANHO_COLIDIVEL_INIMIGO01_X 70.3125f
#define TAMANHO_COLIDIVEL_INIMIGO01_Y 90.0f

//PROJETIL
#define VELOCIDADE_PROJETIL 900.0f
#define TEMPO_VIDA_PROJETIL_JOGADOR 5.0f
#define PROJECTILE_DAMAGE 1l

//BARRA DE VIDA
#define TEMPO_INVUNERABILIDADE 2.0f

//Obstaculo e Inimigo
#define PUSH_INIMIGO_OBST 0.5f
#define PUSH_INIMIGO_PLATAFORMA 0.5f

//OBSTACULO 01 - BAU
#define BAU_SIZE_X 64.0f
#define BAU_SIZE_Y 64.0f

//CAMINHOS
#define BARRA_DE_VIDA "Texture/CCC.png"

#include "GraphicManager.h"
#include "List.h"

using namespace Manager;

namespace ent {
    class Entity
    {
    protected:

        unsigned long int id;
        string key; //id para Corpo
        string path;
        Vector2D<float> tam_tex;
        Vector2D<float> pos;

        static GraphicManager* control;

    public:

        Entity(const string c = "");
        virtual ~Entity();

        void setID(const unsigned long ID);
        const unsigned long int getID() const;

        const string getKey() const;

        virtual void setTexture(const string t) = 0;
        const string getTexture() const;

        virtual void setSizeTexture(const Vector2D<float> v);
        virtual void setSizeTexture(const float x, const float y);
        const Vector2D<float> getSizeTexture() const;

        void setPosition(const Vector2D<float> v);
        void setPosition(const float x, const float y);
        const Vector2D<float> getPosition() const;

        static void setGraphicManager(GraphicManager* pg);
        static GraphicManager* getGraphicManager();

        virtual void InitialUpdate () = 0;
        virtual void UpdateGerenciador () = 0;
        virtual void Update () = 0;
        virtual void Draw () = 0;
        virtual void DrawPause () = 0;
        //MÉTODOS PARA SAVE GAME
        virtual const long int getLifePoints() const;
        virtual const Vector2D<float> getVelocidade() const;
        virtual const Vector2D<unsigned long int> getCurrentImage() const;
    };
}

#endif // INCLUDED_ENTIDADE_H
