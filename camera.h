// Natália Lídia Lima Coelho - 472327

#ifndef CAMERA_H
#define CAMERA_H

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class Camera {
    private:
        glm::vec3 eye;
        glm::vec3 at;
        glm::vec3 up;
        glm::mat4 camera_matrix;

        float yaw, pitch;

    public:
        Camera();
        glm::vec3 getEye();
        glm::vec3 getAt();
        glm::vec3 getUp();
        glm::mat4 getCameraMatrix();
        void setEye(float x, float y, float z);
        void setAt(float x, float y, float z);
        void setUp(float x, float y, float z);
        void setCamera();

        void anda(int frente, int tras, int esq, int dir);
        void olha(float xoffset, float yoffset);
};

#endif // CAMERA_H
