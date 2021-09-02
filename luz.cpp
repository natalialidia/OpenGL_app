#include "luz.h"
#include "glm/gtc/type_ptr.hpp"

Luz::Luz() {
    luz_amb = glm::vec3(.20f, .20f, .20f);
    luz_dif = glm::vec3(1.0f, 1.0f, 1.0f);
    luz_esp = glm::vec3(1.0f, 1.0f, 1.0f);

    dec_a = 0.1f;
    dec_b = 0.7f;
    dec_c = 1.8f;

    exp_dec = 16;

    tipo = 0;
}

glm::vec3 Luz::getPosLuz() {
    return this->pos_luz;
}

void Luz::setTipo(int tipo) {
    this->tipo = tipo;
}

void Luz::setPosLuz(glm::vec3 pos_luz) {
    this->pos_luz = pos_luz;
}

void Luz::setDirLuz(glm::vec3 dir_luz) {
    this->dir_luz = dir_luz;
}

void Luz::setAngLuz(float ang_luz) {
    this->ang_luz = ang_luz;
}

void Luz::setDecB(float dec_a) {
    this->dec_a = dec_a;
}

void Luz::setDecC(float dec_a) {
    this->dec_a = dec_a;
}

void Luz::setExpDec(float exp_dec) {
    this->exp_dec = exp_dec;
}

void Luz::setDecA(float dec_a) {
    this->dec_a = dec_a;
}

void Luz::setLuzAmb(glm::vec3 luz_amb){
    this->luz_amb = luz_amb;
}

void Luz::setLuzDif(glm::vec3 luz_dif){
    this->luz_dif = luz_dif;
}

void Luz::setLuzEsp(glm::vec3 luz_esp){
    this->luz_esp = luz_esp;
}

void Luz::setMatDif(glm::vec3 mat_dif) {
    this->mat_dif = mat_dif;
}

void Luz::setMatAmb(glm::vec3 mat_amb) {
    this->mat_amb = mat_amb;
}

void Luz::setMatEsp(glm::vec3 mat_esp) {
    this->mat_esp = mat_esp;
}

void Luz::setMatExp(float mat_exp) {
    this->mat_exp = mat_exp;
}

glm::vec3 Luz::calcIluminacao(glm::vec3 pos_cam, glm::vec3 pos, glm::vec3 normal, glm::mat4 n_matrix, glm::mat4 mv_matrix) {

    glm::vec3 cor = luz_amb * mat_amb; // ambiente

    glm::vec3 n, l, r, v;

    glm::vec3 mv_pos = glm::vec3(mv_matrix * glm::vec4(pos, 1.0f)); // move a posição para coordenada de câmera

    n = glm::vec3(n_matrix * glm::vec4(normal, 0)); // move a normal para coordenada de câmera
    n = glm::normalize(n);

    float decaimento_dist = 1;
    float decaimento_bordas = 1;

    switch (tipo) {
        case 0:
        case 1: {

            l = this->pos_luz - mv_pos;
            l = glm::normalize(l);

            float distancia = glm::length(l);

            decaimento_dist = 1.0f/(dec_a +
                                    dec_b * distancia +
                                    dec_c * (distancia*distancia));

            if (tipo == 1) {

                float theta = glm::dot(l, glm::normalize(-this->dir_luz));

                if (theta <= glm::cos(glm::radians(ang_luz))) {
                    return cor; //aplica somente a ambiente caso esteja fora do cone
                }

                decaimento_bordas = powf(theta, exp_dec);

            }

            break;
        }
        case 2: {

            l = -this->dir_luz;
            l = glm::normalize(l);

            break;
        }
    }

    v = pos_cam - mv_pos;
    v = glm::normalize(v);

    r = 2 * glm::dot(n,l) * n - l;
    r = glm::normalize(r);

    cor += luz_dif * mat_dif * glm::max((glm::dot(l,n)), 0.0f) +
           luz_esp * mat_esp * powf(glm::max((glm::dot(v,r)), 0.0f), mat_exp);

    cor *= decaimento_dist;

    cor *= decaimento_bordas;

    return cor;

}
