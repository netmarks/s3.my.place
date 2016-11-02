#include <graphics.h>
#include <iostream>
#include <math.h>
#define PI 3.141592

using namespace std;

typedef struct nod {
    int x, y;           // coordonate varf poligon
    float a;            // unghiul de rotatie al poligonului
    struct nod *next;
}Nod;

int main() {
    // coordonatele figurii
    int figura[] = {0,0,-2,2,3,0,-2,-2,0,0};

    int x, y, rx=200, ry=150;       // razele folosite la desenul elipsei
    int xo=300, yo=200;             // centrul desenului
    int pas = 5;                    // pasul unghiului elipsei
    int u_el = -30;                  // rotatia elipsei
    Nod *elps=NULL, *p=NULL, *nou;
    for(int i=0;i<360;i+=pas) {     // generam punctele pentru elipsa
        x = xo + rx*cos(i*PI/180);
        y = yo + ry*sin(i*PI/180);
        nou = new Nod;
        nou->x = x; nou->y = y;
        nou->a = i;
        if(elps) {
            p->next = nou;
            p = nou;
        } else {
            elps = nou;
            p = nou;
        }
    }

    // rotatie elipsa cu 30 grade
    Nod *nelps=NULL, *np;
    for(Nod *p=elps;p;p=p->next) {
        nou = new Nod;
        nou->x = xo+(p->x-xo)*cos(u_el*PI/180)-(p->y-yo)*sin(u_el*PI/180);
        nou->y = yo+(p->x-xo)*sin(u_el*PI/180)+(p->y-yo)*cos(u_el*PI/180);
        nou->a = p->a;
        if(nelps) {
            np->next = nou;
            np = nou;
        } else {
            nelps = nou;
            np=nou;
        }
    }


    initwindow(600,400);              // fereastra setata ca de doua ori
    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();

    setwritemode(XOR_PUT);
    for(Nod *p=nelps;p;p=p->next) {   // desenam punctele elipsei
        circle(p->x,p->y,2);
    }
    int cfig[10];

    // for(Elipsa *p=nelps;p;p=p->urm) { //animatia figurii
    p=nelps;
    // lista circulara
    while(p->next) p=p->next;
    p->next = nelps;

    setcolor(7);

    while(1) {                   //animatia figurii
        for(int i=0;i<=8;i+=2) { //se calculeaza coordonatele noi ale figurii: translatie, scalare, rotatie
            cfig[i] = p->x + (figura[i]*10)*cos((p->a+90+u_el)*PI/180)-(figura[i+1]*10)*sin((p->a+90+u_el)*PI/180);
            cfig[i+1] = p->y + (figura[i]*10)*sin((p->a+90+u_el)*PI/180)+(figura[i+1]*10)*cos((p->a+90+u_el)*PI/180);
        }
        drawpoly(5,cfig); // se deseneaza noua figura
        delay(40);        // asteptam 40 ms
        if(kbhit())break;
        drawpoly(5,cfig); // redesenarea sterge figura
        p=p->next;
    }
    while(!kbhit());
    closegraph();
    return 0;
}
