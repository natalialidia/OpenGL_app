#include "textura.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/gl.h>
#include <QDebug>

Textura::Textura() {
    largura = altura = num_canais = tex_id = 0;
}

void Textura::carrega(char *arquivo) {

    stbi_set_flip_vertically_on_load(true);

    // carrega imagem
    dados = stbi_load(arquivo, &largura, &altura, &num_canais, 0);

    if (!dados) {
        qDebug() << "Arquivo "<< arquivo << " não pôde ser carregado";
    } else {
        qDebug() << "Arquivo "<< arquivo << " carregado com sucesso";
    }

    glGenTextures(1, &tex_id);

    //habilita textura
    glBindTexture(GL_TEXTURE_2D, tex_id);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // passa para o OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, dados);

    // desabilita textura
    glBindTexture(GL_TEXTURE_2D, 0);

    // libera memória
    stbi_image_free(dados);

}

unsigned int Textura::getTexId() {
    return tex_id;
}
