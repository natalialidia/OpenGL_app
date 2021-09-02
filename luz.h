#ifndef LUZ_H
#define LUZ_H

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class Luz {
    private:
        int tipo; // 0: pontual, 1: spotlight, 2: direcional
        glm::vec3 pos_luz;
        glm::vec3 dir_luz;
        float ang_luz;

        float dec_a;
        float dec_b;
        float dec_c;
        float exp_dec;

        glm::vec3 luz_amb;
        glm::vec3 luz_dif;
        glm::vec3 luz_esp;

        glm::vec3 mat_dif;
        glm::vec3 mat_amb;
        glm::vec3 mat_esp;
        float mat_exp;


    public:
        Luz();

        glm::vec3 getPosLuz();

        void setTipo(int tipo);

        void setPosLuz(glm::vec3 pos_luz);
        void setDirLuz(glm::vec3 dir_luz);
        void setAngLuz(float ang_luz);

        void setDecA(float dec_a);
        void setDecB(float dec_b);
        void setDecC(float dec_c);
        void setExpDec(float exp_dec);

        void setLuzAmb(glm::vec3 luz_amb);
        void setLuzDif(glm::vec3 luz_dif);
        void setLuzEsp(glm::vec3 luz_esp);

        void setMatDif(glm::vec3 mat_dif);
        void setMatAmb(glm::vec3 mat_amb);
        void setMatEsp(glm::vec3 mat_esp);
        void setMatExp(float mat_exp);

        glm::vec3 calcIluminacao(glm::vec3 pos_cam, glm::vec3 pos, glm::vec3 normal, glm::mat4 n_matrix, glm::mat4 mv_matrix);

};

#endif // LUZ_H
