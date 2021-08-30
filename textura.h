#ifndef TEXTURA_H
#define TEXTURA_H

class Textura {
    private:
        int largura, altura, num_canais;
        unsigned char *dados;
        unsigned int tex_id;

    public:
        Textura();

        void carrega(char *arquivo);
        unsigned int getTexId();
};

#endif // TEXTURA_H
