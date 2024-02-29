#include "ppm.hpp"
#define XYPOS(x, y) ((x * 3) + (y * w * 3))
void ppm::teste()
{
    for (int y = 0; y < h; y++)
    {
        float v = (float)y / (float)h;
        for (int x = 0; x < w; x++)
        {
            float u = (float)x / (float)w;

            int p = XYPOS(x, y);
            unsigned char r, g, b;
            r = u * 255;
            g = 100;
            b = 100;
            pxl[p] = r;
            pxl[p + 1] = g;
            pxl[p + 2] = b;
        }
    }
}
void ppm::salvar(string caminho)
{
    ofstream arq(caminho);
    arq << "P6\n"
        << w << " " << h << "\n255\n";
    arq.write(reinterpret_cast<char *>(pxl.data()), w * h * 3 * sizeof(unsigned char));
}
ppm::ppm(int w, int h) : w(w), h(h)
{
    pxl.resize(w * h * 3, 255);
    teste();
}
ppm::ppm(string caminho)

{
    ifstream arq(caminho);
    if (arq.is_open() == false)
    {
        printf("Nao foi possivel abrir a imagem \"%s\"\n", caminho.c_str());
        exit(0);
    }
    arq >> code;
    char c;
    while (arq >> c)
    {
        if (c == '#')
        {
            // se o primeiro charactere é um tralha, entao le o restante da linha (comentario )e a imprime
            std::string linha;
            std::getline(arq, linha);
            printf("comentario encontrado \"%s\"\n", linha.c_str());
        }
        else
        {
            // nao é um comentario , "devolve" o caractere e continua a leitura do arquivo
            arq.putback(c);
            break;
        }
    }

    arq >> w >> h >> cores;

    // cout << code << "\n" << w << "\n" << h << "\n" << cores << "\n";
    pxl.resize(w * h * 3, 0);
    if (cores > 255)
    {
        cout << "VAI PRECISAR CONVERTER \n";
        vector<unsigned short int> pxl2(w * h * 3, 0);
        arq.read(reinterpret_cast<char *>(pxl2.data()), w * h * 3 * sizeof(unsigned short int));
        for (int i = 0; i < w * h * 3; i++)
        {
            pxl[i] = (unsigned char)(((float)pxl2[i] / (float)cores) * 255);
        }
    }
    else
    {
        arq.get();
        arq.read(reinterpret_cast<char *>(pxl.data()), w * h * 3);
    }
    arq.close();
}

ppm::~ppm()
{
}
void ppm::print()
{
    for (int y = 0; y < h; y++)
    {
        printf("\n");
        for (int x = 0; x < w; x++)
        {
            int r = XYPOS(x, y);
            printf("(%d|%d|%d)", pxl[r], pxl[r + 1], pxl[r + 2]);
        }
    }
    cout << "\n";
}
void ppm::get(unsigned char &r, unsigned char &g, unsigned char &b, int x, int y)
{
    int pos = XYPOS(x, y);
    r = pxl[pos];
    g = pxl[pos + 1];
    b = pxl[pos + 2];
};
void ppm::set(unsigned char r, unsigned char g, unsigned char b, int x, int y)
{
    int pos = XYPOS(x, y);
    pxl[pos] = r;
    pxl[pos + 1] = g;
    pxl[pos + 2] = b;
};
