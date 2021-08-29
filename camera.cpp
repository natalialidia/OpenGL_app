// Natália Lídia Lima Coelho - 472327

#include "camera.h"

Camera::Camera() {
}

glm::vec3 Camera::getEye() {
    return this->eye;
}

glm::vec3 Camera::getAt() {
    return this->at;
}

glm::vec3 Camera::getUp() {
    return this->up;
}


glm::mat4 Camera::getCameraMatrix() {
    return this->camera_matrix;
}

void Camera::setEye(float x, float y, float z) {

    eye = glm::vec3(x,y,z);

}

void Camera::setAt(float x, float y, float z) {

    at = glm::vec3(x,y,z);

}

void Camera::setUp(float x, float y, float z) {

    up = glm::vec3(x,y,z);

}

void Camera::setCamera() {
   camera_matrix = glm::lookAt(eye, eye+at, up);
   glMultMatrixf(glm::value_ptr(camera_matrix));
}

void Camera::anda(int frente, int tras, int esq, int dir) {

    float velocidade = 0.15f;

    glm::vec3 pos = eye;

    glm::vec3 direcao = glm::vec3(at.x, 0, at.z);

    if (frente)
        pos += velocidade * direcao;

    if (tras)
        pos -= velocidade * direcao;

    if (esq)
        pos -= glm::normalize(glm::cross(at, up)) * velocidade;

    if (dir)
        pos += glm::normalize(glm::cross(at, up)) * velocidade;

    eye = pos;

}

void Camera::olha(float xoffset, float yoffset) {

    float sens = 0.1f;

    xoffset *= sens;
    yoffset *= sens;

    yaw   += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direcao;
    direcao.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direcao.y = sin(glm::radians(pitch));
    direcao.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direcao = glm::normalize(direcao);
    at = direcao;

}
