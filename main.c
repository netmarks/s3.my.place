

//
// Efectuati adunarea a doua numere intregi
// reprezentate ca liste LDI
//
#include <stdio.h>
#include <stdlib.h>

typedef struct tmp {
    int exp;
    int coef;
    struct tmp* prev;
    struct tmp* next;
}Cifra;

typedef Cifra* NUM;

void Afiseaza(NUM x){
    printf("\n\t");
    if(!x) printf(" nimic"); else{
        int e=6;
        while(e>=0){
            if(x->exp == e){
                printf("%3d", x->coef);
                x = x->next;
            } else {
                printf("%3d", 0);
            }
            e--;
        }
    }
    printf("\n");
}


NUM aduna(NUM x, NUM y){
    // pozitionare pe cifra unitatilor
    NUM p = x;while(p->next)p=p->next;
    NUM q = y;while(q->next)q=q->next;

    int t =0;       // transport (cand suma cifrelor > 9)
    while(p || q){
       if(p && q){
            p->coef += (t + q->coef);
            //t = p->coef/10;
            //p->coef = p->coef%10;
       }
       if (p && !q) {
            p->coef += t;
            //t = p->coef/10;
            //p->coef = p->coef%10;
       }

       if (!p && q) {
           // insereaza digit
           p = (Cifra*)malloc(sizeof(Cifra));
           p->coef = (t + q->coef);
           p->exp = q->exp;
           p->prev = NULL;
           p->next = x;
           x = p;
           //t = p->coef/10;
           //p->coef = p->coef%10;
       }

       t = p->coef/10;
       p->coef = p->coef%10;

       if(p) p=p->prev;
       if(q) q=q->prev;
    }
    return x;
}


void Aduna(NUM *x, NUM y){
    // de verificat cazul in care
    // una sau ambele liste sunt NULL

    // pozitionare pe cifra unitatilor
    NUM p = *x; while(p->next)p=p->next;
    NUM q = y; while(q->next)q=q->next;

    int t =0;       // transport (cand suma cifrelor > 9)

    int N = 1;
    while(p || q){  // cat timp exista elemente intr-una din liste
        printf("\npasul %d",N++);
        Afiseaza(*x);
        Afiseaza(y);
        //if(N == 6)break;

        if(!p){
            printf("\n lista A - gata");
            // se insereaza in A cifra din B
            p = *x;
            p->prev = (Cifra*)malloc(sizeof(Cifra));
            p->prev->coef = t + q->coef;
            p->prev->exp = q->exp;
            p->prev->prev = NULL;
            p->prev->next = *x;
            x[0] = p->prev;
            p=NULL;
            q=q->prev;
            continue;
        } else
        if(!q) {
            // s-au terminat cifrele celui de-al doilea numar
            printf("\n lista B - gata");
            // actualizez transportul
            p->coef += t;
            t = p->coef/10;
            p->coef = p->coef%10;
            p=p->prev;
            continue;
        } else
       // cazul exponenti identici
       if(p->exp == q->exp){
            //printf("\n..==");
            p->coef += (t + q->coef);
            t = p->coef/10;
            p->coef = p->coef%10;

            if(p) p=p->prev;
            if(q) q=q->prev;
            continue;
       }
       // daca exponentul din a este mai mare
       if (p->exp > q->exp) {
            printf("\n..>>");
            // se insereaza digit in a (prima lista)
            // elementul din b
           NUM s = (Cifra*)malloc(sizeof(Cifra));
           s->coef = (t + q->coef);
           s->exp = q->exp;
           s->prev = p;
           s->next = p->next;
           p->next->prev =  s;
           p->next = s;

           t = p->coef/10;
           p->coef = p->coef%10;

           // trec la urmatorul element din b
           q = q->prev;
           printf("\np -> %d",p->coef);
           continue;
       }
       // daca exponentul din a este mai mic
       if (p->exp < q->exp) {
            printf("\n..<<");
            p=p->prev;
            continue;
       }

    }
    // ready
    compactare(x);
}



// initializare BIG NUMBER
NUM init(char* sir){
    //printf("\nam primit: %s de lungime %d", sir, sizeof(sir));
    int i;
    NUM numar=NULL;
    for(i=0;sir[i]/*i<sizeof(sir)*/;i++)
    {
        //printf("\n%d\t%c ",i,sir[i]);
        NUM cifra = (Cifra*)malloc(sizeof(Cifra));
        cifra->coef = sir[i]-'0';
        cifra->exp = 0;
        cifra->prev=NULL;
        cifra->next=NULL;

        if(!numar)
            numar=cifra;
        else{
            // adaugand o cifra in dreapta,
            // toti exponentii cresc cu 1
            NUM t = numar;
            while(t->next){
                t->exp = t->exp + 1;
                t=t->next;
            }
            t->exp=1;
            t->next = cifra;
            cifra->prev = t;
        }
    }
    // verific
    //NUM t = numar;while(t->next)t=t->next;
    //while(t){printf("\nV\t%d",t->coef);t=t->prev;}
    return numar;
}



void afiseaza(NUM x){
    printf("\n\t");
    if(!x) printf(" nimic"); else
    while(x != NULL){
        printf("%3d (%d)", x->coef, x->exp);
        x=x->next;
    }
    printf("\n");
}



void compactare(NUM *x){
    NUM p = *x;
    while(p){
        if(p->coef == 0){
           if(p->prev){
                // daca exista predecesor
                p->prev->next = p->next;
                p->next->prev = p->prev;
           } else {
                // daca nu exista predecesor
                // modific capul listei
                x[0] = p->next;
           }
        }
        p=p->next;
    }
}




int main()
{
    NUM a=init("100734");    // 1234     1234    18395   02611
    //afiseaza(a);


    //NUM b=init("4321");    // 1111     1271    02611   18395
    //afiseaza(b);

    //a=aduna(a,b);

    //afiseaza(a);
    compactare(&a);         // 21006

    //afiseaza(a);
    NUM b = init("1301");
    //afiseaza(c);
    //compactare(&b);         // 21006
    //afiseaza(b);
    //Afiseaza(b);


    Aduna(&a, b);

    afiseaza(a);
    //Afiseaza(a);

    printf("\n\n\nready\n\n");
    return 0;
}
