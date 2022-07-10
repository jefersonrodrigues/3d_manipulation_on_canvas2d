/*********************************************************************
// Canvas2D
// Autor: Cesar Tadeu Pozzer
//        04/2021
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "Vetor.h"
#include "Vector2.h"

#define PI_2 6.28318530717
#define PI   3.14159265359
#define TAM 4
int mx, my; //coordenadas do mouse
int wheel_on, dir;

Vector3 v[8];
int tecla;
float ang = 0;
Vector3 vect[8];
Vector3 saida[8];
float d = 1000.0;
int maisX = 1000;
int maisY = 1000;
int maisZ = 4000;

Vector3 translationZ(Vector3 g, int tam){
    Vector3 resp;

    resp.x = g.x;
    resp.y = g.y;
    resp.z = g.z + tam;

    return resp;
}

Vector3 translationY(Vector3 g, int tam){
    Vector3 resp;

    resp.x = g.x;
    resp.y = g.y + tam;
    resp.z = g.z;

    return resp;
}

Vector3 translationX(Vector3 g, int tam){
    Vector3 resp;

    resp.x = g.x + tam;
    resp.y = g.y;
    resp.z = g.z;

    return resp;
}

Vector3 rollY(Vector3 g, float ang){
    Vector3 resp;
    resp.x = cos(ang)*g.x + sin(ang)*g.z;
    resp.y = g.y;
    resp.z = -sin(ang)*g.x + cos(ang)*g.z;

    return resp;
}

Vector3 rollX(Vector3 g){
    Vector3 resp;
    ang += 0.01;

    resp.x = g.x;
    resp.y = cos(ang)*g.y - sin(ang)*g.z;
    resp.z = sin(ang)*g.y + cos(ang)*g.z;

    return resp;
}

Vector3 rollZ(Vector3 g){
    Vector3 resp;
    ang += 0.01;

    resp.x = cos(ang)*g.x - sin(ang)*g.y;
    resp.y = sin(ang)*g.x + cos(ang)*g.y;
    resp.z = g.z;
    return resp;
}

Vector3 projeta(Vector3 p, float d){
    Vector3 resp;
    resp.x = (p.x*d) / p.z;
    resp.y = (p.y*d) / p.z;
    resp.z = 0;

    return resp;
}

void drawCube(Vector3* vec){
    glPointSize(7);
    color(0);
    point(vec[0].x, vec[0].y);
    point(vec[1].x, vec[1].y);
    point(vec[2].x, vec[2].y);
    point(vec[3].x, vec[3].y);
    color(2);
    //glPointSize(3);
    point(vec[4].x, vec[4].y);
    point(vec[5].x, vec[5].y);
    point(vec[6].x, vec[6].y);
    point(vec[7].x, vec[7].y);


    color(0);
    line(vec[0].x, vec[0].y, vec[1].x, vec[1].y);
    line(vec[1].x, vec[1].y, vec[2].x, vec[2].y);
    line(vec[2].x, vec[2].y, vec[3].x, vec[3].y);
    line(vec[3].x, vec[3].y, vec[0].x, vec[0].y);

    line(vec[4].x, vec[4].y, vec[5].x, vec[5].y);
    line(vec[5].x, vec[5].y, vec[6].x, vec[6].y);
    line(vec[6].x, vec[6].y, vec[7].x, vec[7].y);
    line(vec[7].x, vec[7].y, vec[4].x, vec[4].y);


    line(vec[0].x, vec[0].y, vec[4].x, vec[4].y);
    line(vec[1].x, vec[1].y, vec[5].x, vec[5].y);
    line(vec[2].x, vec[2].y, vec[6].x, vec[6].y);
    line(vec[3].x, vec[3].y, vec[7].x, vec[7].y);


}

Vector3* transf(){
    for(int i = 0; i<8; i++){
        vect[i] = v[i];
        //p[i] = center(p[i], p[i].x, p[i].y);
        vect[i] = rollY(vect[i], ang);
        vect[i] = translationY(vect[i], maisX);
        vect[i] = translationX(vect[i], maisY);
        vect[i] = translationZ(vect[i], maisZ);
        saida[i] = projeta(vect[i], d);
    }
    ang += 0.01;
    return saida;
}

void render(){
    transf();
    drawCube(saida);
    printf("\n D = %f", d);
    printf("\n X = %d", maisX);
    printf("\n X = %d", maisY);
    Sleep(10);
}
//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y){
    printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);
    mx = x; //guarda as coordenadas do mouse para exibir dentro da render()
    my = y;
    if(direction == 1){
        d += 10;
    }else if(direction == -1){
        d -= 10;
    }
}

//funcao chamada toda vez que uma tecla for pressionada
void keyboard(int key){
   printf("\nClicou Tecla: %d" , key);
    if(key == 202){
        maisX += 10;
    }else if(key == 200){
        maisX -= 10;
    }else if(key == 201){
        maisY += 10;
    }else if(key == 203){
        maisY -= 10;
    }
}


//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key){
    printf("\nLiberou Tecla: %d" , key);
}


int main(void){

    v[0].set(-100,  -100,  100);
    v[1].set(100,  -100,  100);
    v[2].set(100, 100,  100);
    v[3].set(-100, 100,  100);
    v[4].set(-100,  -100, -100);
    v[5].set(100,  -100, -100);
    v[6].set(100, 100, -100);
    v[7].set(-100, 100, -100);



    int screenWidth = 1024, screenHeight = 768; //largura e altura inicial da tela. Alteram com o redimensionamento de tela.
    init(&screenWidth, &screenHeight, "Canvas 2D");
    run();
}
