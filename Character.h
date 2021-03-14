#ifndef INCLUDED_CHARACTER_H
#define INCLUDED_CHARACTER_H

#include "CollidingEntity.h"

namespace ent {
    namespace cha {
        class Character: public CollidingEntity {
        protected:
            bool life;
            bool dano;
            bool change_animation;
            bool flag_change_face;

            Vector2D<float> velocidade;
            Vector2D<unsigned long int> cont_imagem;
            Vector2D<unsigned long int> imagem_atual;
            Vector2D<float> width_height;
            Vector2D<float> left_top;

            bool face_certa;
            bool pode_pular;

            //Atributos pra Animação
            unsigned long int lestatico;
            unsigned long int landando;
            unsigned long int lsalto;
            unsigned long int lataque;
            unsigned long int ldano;

            float tempo_ciclo;
            float tempo_total;

        public:

            float galho;

        public:

            Character(const bool pp = true, const float change_time = 0.3f, const string c = "");
            virtual ~Character();

            void Dead(const bool l);
            const bool getLife() const;

            void setDano(const bool d);
            const bool getDano() const;

            const bool getFace() const;

            void setVelocidade(const Vector2D<float> v);
            void setVelocidade(const float x, const float y);
            const Vector2D<float> getVelocidade() const;
            void incrementarVelocidade(const Vector2D<float>& vel);
            void incrementarVelocidade(const float& x, const float& y);

            void setCurrentImage(const Vector2D<unsigned long int> v);
            void setCurrentImage(const unsigned long int x, const unsigned long int y);
            const Vector2D<unsigned long int> getCurrentImage() const;

            void setContImage(const Vector2D<unsigned long int> v);
            void setContImage(const unsigned long int x, const unsigned long int y);

            void PreencherLinhas(const unsigned long int estatico = 0lu, const unsigned long int andando = 0lu, const unsigned long int salto = 0lu, const unsigned long int ataque = 0lu, const unsigned long int dano = 0lu);

            void setTempoCiclo(const float t);
            const float getTempoCiclo() const;

            virtual void UpdateAnimacao() = 0;
            virtual void Update();
        };
    }
}

#endif // INCLUDED_CHARACTER_H
