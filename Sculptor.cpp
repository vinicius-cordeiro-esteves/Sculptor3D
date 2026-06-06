#include "Sculptor.h"
#include "voxel.h"
#include <iostream>
#include <fstream>
#include <iomanip>


Sculptor::Sculptor(int _nx, int _ny, int _nz) {
    nx = _nx; ny = _ny; nz = _nz;

    v = new Voxel**[nx];
    for (int i = 0; i < nx; i++) {
        v[i] = new Voxel*[ny];
        for (int j = 0; j < ny; j++) {
            v[i][j] = new Voxel[nz]();
        }
    }
}


Sculptor::~Sculptor() {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            delete[] v[i][j];
        }
        delete[] v[i];
    }
    delete[] v;
}


void Sculptor::setColor(float r, float g, float b, float alpha) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = alpha;
}

void Sculptor::putVoxel(int x, int y, int z) {
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].show = true;
        v[x][y][z].r = this->r;
        v[x][y][z].g = this->g;
        v[x][y][z].b = this->b;
        v[x][y][z].a = this->a;
    }
}

void Sculptor::cutVoxel(int x, int y, int z) {
    if (x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz) {
        v[x][y][z].show = false;
    }
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    if (x0 < 0) x0 = 0;
    if (x1 >= nx) x1 = nx - 1;
    if (y0 < 0) y0 = 0;
    if (y1 >= ny) y1 = ny - 1;
    if (z0 < 0) z0 = 0;
    if (z1 >= nz) z1 = nz - 1;
    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            for (int k = z0; k <= z1; k++) {
                this->v[i][j][k].show = true;
                this->v[i][j][k].r = this->r;
                this->v[i][j][k].g = this->g;
                this->v[i][j][k].b = this->b;
                this->v[i][j][k].a = this->a;
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    if (x0 < 0) x0 = 0;
    if (x1 >= nx) x1 = nx - 1;
    if (y0 < 0) y0 = 0;
    if (y1 >= ny) y1 = ny - 1;
    if (z0 < 0) z0 = 0;
    if (z1 >= nz) z1 = nz - 1;
    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            for (int k = z0; k <= z1; k++) {
                this->v[i][j][k].show = false;
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if ((i - xcenter)*(i - xcenter) + (j - ycenter)*(j - ycenter) + (k - zcenter)*(k - zcenter) <= radius * radius) {
                    this->v[i][j][k].show = true;
                    this->v[i][j][k].r = this->r;
                    this->v[i][j][k].g = this->g;
                    this->v[i][j][k].b = this->b;
                    this->v[i][j][k].a = this->a;
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
    for (int i = 0; i < this->nx; i++) {
        for (int j = 0; j < this->ny; j++) {
            for (int k = 0; k < this->nz; k++) {
                if ((i - xcenter)*(i - xcenter) + (j - ycenter)*(j - ycenter) + (k - zcenter)*(k - zcenter) <= radius * radius) {
                    this->v[i][j][k].show = false;
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                float dx = (float)((i - xcenter) * (i - xcenter)) / (rx * rx);
                float dy = (float)((j - ycenter) * (j - ycenter)) / (ry * ry);
                float dz = (float)((k - zcenter) * (k - zcenter)) / (rz * rz);

                if (dx + dy + dz <= 1.0f) {
                    this->v[i][j][k].show = true;
                    this->v[i][j][k].r = this->r;
                    this->v[i][j][k].g = this->g;
                    this->v[i][j][k].b = this->b;
                    this->v[i][j][k].a = this->a;
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    for (int i = 0; i < this->nx; i++) {
        for (int j = 0; j < this->ny; j++) {
            for (int k = 0; k < this->nz; k++) {
                float dx = (float)((i - xcenter) * (i - xcenter)) / (rx * rx);
                float dy = (float)((j - ycenter) * (j - ycenter)) / (ry * ry);
                float dz = (float)((k - zcenter) * (k - zcenter)) / (rz * rz);

                if (dx + dy + dz <= 1.0f) {
                    this->v[i][j][k].show = false;
                }
            }
        }
    }
}

void Sculptor::writeOFF(const char* filename) {
    std::ofstream fout;
    fout.open(filename);
    if (!fout.is_open()) {
        std::cerr << "Erro!"  << "\n";
        return;
    }

    int Nvoxels = 0;
    for (int i = 0; i < nx; i++)
        for (int j = 0; j < ny; j++)
            for (int k = 0; k < nz; k++)
                if (v[i][j][k].show) Nvoxels++;

    const int vertices_por_cubo = 8;
    const int faces_por_cubo = 6;
    const int vertices_por_face = 4;

    fout << "OFF\n" << vertices_por_cubo * Nvoxels << " " << faces_por_cubo * Nvoxels << " 0\n";

    // centralizando cubo tridimensional em 000
    float d[vertices_por_cubo][3] = {
        {-0.5,  0.5, -0.5},
        {-0.5, -0.5, -0.5},
        { 0.5, -0.5, -0.5},
        { 0.5,  0.5, -0.5},
        {-0.5,  0.5,  0.5},
        {-0.5, -0.5,  0.5},
        { 0.5, -0.5,  0.5},
        { 0.5,  0.5,  0.5}
    };

    // vertices
    for (int i = 0; i < nx; i++)
        for (int j = 0; j < ny; j++)
            for (int k = 0; k < nz; k++)
                if (v[i][j][k].show)
                    for (int v_idx = 0; v_idx < vertices_por_cubo; v_idx++)
                        fout << i + d[v_idx][0] << " " << j + d[v_idx][1] << " " << k + d[v_idx][2] << "\n";

    const int atras_esq_cima   = 0;
    const int atras_esq_baixo  = 1;
    const int atras_dir_baixo  = 2;
    const int atras_dir_cima   = 3;
    const int frente_esq_cima  = 4;
    const int frente_esq_baixo = 5;
    const int frente_dir_baixo = 6;
    const int frente_dir_cima  = 7;

    // faces para fechar o cubo
    int faces[faces_por_cubo][vertices_por_face] = {
        // face atras
        {atras_esq_cima,  atras_dir_cima,  atras_dir_baixo, atras_esq_baixo},
        // face frente
        {frente_esq_cima, frente_esq_baixo, frente_dir_baixo, frente_dir_cima},
        // face esquerda
        {atras_esq_cima,  atras_esq_baixo, frente_esq_baixo, frente_esq_cima},
        // face direita
        {atras_dir_cima,  atras_dir_baixo, frente_dir_baixo, frente_dir_cima},
        // face cima
        {atras_esq_cima,  atras_dir_cima,  frente_dir_cima,  frente_esq_cima},
        // face baixo
        {atras_esq_baixo, frente_esq_baixo, frente_dir_baixo, atras_dir_baixo}
    };

    // face e cor
    int vertice_atual = 0;
    fout << std::fixed << std::setprecision(2);

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show) {
                    for (int f_idx = 0; f_idx < faces_por_cubo; f_idx++) {
                        fout << vertices_por_face << " "
                             << vertice_atual + faces[f_idx][0] << " "
                             << vertice_atual + faces[f_idx][1] << " "
                             << vertice_atual + faces[f_idx][2] << " "
                             << vertice_atual + faces[f_idx][3] << " "
                             << v[i][j][k].r << " " << v[i][j][k].g << " "
                             << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    }
                    vertice_atual += vertices_por_cubo;
                }
            }
        }
    }

    fout.close();
}
