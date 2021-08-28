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
