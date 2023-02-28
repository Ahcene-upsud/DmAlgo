#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then
#define false 0
#define true 1

/*Q1:
 * À partir d'une certaine valeur n on voit que calcule(n) tend vers une valeur 2,716667 qui est la valeur de e */
float Calcule(int n){

    float res = 1.;
    float cpt = 1.;
    for (int i = 1; i <= n; i++) {
        cpt *= i;
        res += 1. / cpt;
    }

    return res;

}
/* On s'arrête dans le cas ou l'iteration i-1 egal au resultat de l'iteration en cours, pour cela on pourra
* mettre une condition qui lorsque le resultat vaux le meme  resultat que l'iteration precedente on
* s'arrete et on renvoie le resultat*/
/*Q2 : */
double affiche50Terme(int n){

    if(n==0) {
        return -1;
    }else if(n==1){
        return Calcule(9)-2;
    }else{
        return (n*(affiche50Terme(n-1)))-1.;
    }
}

/* - En affichent les 50 premiers terme la suite tend vers l'infini
   - En changent le type de retour vers double, on remarque qu'on obtient plus de precision sur les grands valeurs U50  * /
/*Q3 : */

float power1(float x,float n){
    if(n == 0.0){
        return 1.0;
    }else{
        if(n>0.0){
            return power1(x,n-1)*x;
        }else{
            return 1.0/ power1(x,-n);
        }
    }
}

float power2(float x, float n){
    float res = 1.0;
    int test = n;
    if(n<0){
        test = -n;
    }
    for (int i = 1; i <= test; i++) {
        res *= x;
    }
    if(n<0) {
        return 1.0 / res;
    }else{
        return res;
    }
}


void power3_aux(int x,int n,int *res){
    if(n==0){
        return;
    }else{
        *res*=x;
        power3_aux(x,n-1,res);
    }
}

int power3(int x,int n){
    int res = 1;
    power3_aux(x,n, &res);
    return res;
}

int power4_aux(int x,int n,int res){
    if(n==0){
        return res ;
    }else{
        return power4_aux(x,n-1,res*x);
    }
}
int power4(int x, int n){
    return power4_aux(x,n,1);
}

int power5(int x,int n){
    if(n==0){
        return 1;
    }else{
        if(n%2==0){
            return power5(x,n/2)* power5(x,n/2);
        }else{
            return power5(x,n/2)* power5(x,n/2)*x;
        }
    }
}
int power6(int x ,int n){
    int y;
    if(n==0) {
        return 1;
    }else{
        y = power6(x,n/2);
        if(n%2==0) {
            return y * y;
        }else{
            return y*y*x;
        }
    }
}

int power7(int x ,int n){
    if(n==0){
        return 1;
    }else{
        if(n%2==0){
            return power7(x*x,n/2);

        }else{
            return power7(x*x,n/2)*x;
        }

    }
}

int pow(int x ,int n , int r){
    if(n==0){
        return r;
    }else{
        if(n%2==0) {
            return pow(x * x, n / 2, r);
        }else{
            return pow(x*x,n/2,r*x);
        }
    }
}
int power8(int x,int n){
    return pow( x ,  n , 1);}

void pow9(int x , int n , int *r){
    if(n!=0){
        if(n%2!=0) {
            *r = *r * x;
        }
        pow9(x*x,n/2,r);
    }

}
int power9(int x,int n){
    int r =1;
    pow9(x,n,&r);
    return r;
}
int power10(int x ,int n){
    int r=1;
    while(n!=0) {
        if (n % 2 != 0) {
            r = r * x;
        }
        n = n / 2;
        x = x * x;
    }
    return r;
}
/*Q4 : Akermann */
int Akermann(int m, int n){
    if ( m == 0){
        return n+1;
    }else{
        int res = 1;
        for(int i = 1;i<= n+1;i++){
            res = Akermann(m-1,res);
        }
        return res;
    }
}

int Akermann2(int m, int n){
    if(m==0){
        return n+1;
    }else{
        if(n==0){
            return Akermann2(m-1,1);
        }else{
            return Akermann2(m-1,Akermann2(m,n-1));
        }
    }
}

/* Q5: Suite un */
/*version recursive simple */
float suiteUn(int x){
    if(x == 1){
        return 1.;
    }else{
        return suiteUn(x-1) + 2/suiteUn(x-1);
    }
}
/*version iteratif*/
float suiteUn1(int x){
    float res =1.;
    for(int i=0 ; i<x ; i++){
        res = res + 2/res;
    }
    return res;
}
/*recursive avec s/procedure*/
void suiteUn2_aux(int x , float *acc){
    if(x == 1){
        *acc = 1.;
    }else{
        suiteUn2_aux(x-1 , acc);
        *acc = *acc+(2.0 / *acc);


    }
}
float suiteUn2(int x){
    float acc = 0;
    suiteUn2_aux(x,& acc);
    return acc;
}
int main() {
    for(int i =0; i<=50;i=i+1) {
       //printf("res %f \n", Calcule(i));
       printf("U%d= %f\n",i,affiche50Terme(i));
       }

    /*printf("Hello, World!\n");
    printf("res %d \n" ,power1(5,2));
    printf("res %d\n" ,power2(5,2));
    printf("res %d\n" ,power3(5,2));
    printf("res %d\n" ,power4(5,2));
    printf("res %d\n" ,power5(5,2));
    printf("res %d\n" ,power6(5,2));
    printf("res %d\n" ,power7(5,2));
    printf("res %d\n" ,power8(5,2));
    printf("res %d\n" ,power9(5,2));
    printf("res %d\n" ,power10(5,2));
    printf("res %f \n" ,power1(5.0,-3.0));
    printf("res %f \n" ,power2(5.0,-3.0));*/

    /*printf("res %d \n" ,Akermann(0,0));
    printf("res %d \n" ,Akermann(1,0));
    printf("res %d \n" ,Akermann(2,0));
    printf("res %d \n" ,Akermann(3,0));
    printf("res %d \n" ,Akermann(4,0));
    printf("res %d \n" ,Akermann(0,4));
    printf("res %d \n" ,Akermann(0,5));
    printf("res %d \n" ,Akermann(5,0));
    printf("res %d \n" ,Akermann2(4,0)); */
    /* Pour ce test A(6,0) le programme tourne sans donner de résultat*/
    //printf("res %d \n" ,Akermann(6,0));
    /* Il suffit juste de tester la formule (1+1/N)^N avec la fonction power */
    /*long N=10^12;
  printf("res %d \n" ,power1((1+(1/N)),N));
  printf("res %d\n" ,power2((1+(1/N)),N));
  printf("res %d\n" ,power3((1+(1/N)),N));
  printf("res %d\n" ,power4((1+(1/N)),N));
  printf("res %d\n" ,power5((1+(1/N)),N));
  printf("res %d\n" ,power6((1+(1/N)),N));
  printf("res %d\n" ,power7((1+(1/N)),N));
  printf("res %d\n" ,power8((1+(1/N)),N));
  printf("res %d\n" ,power9((1+(1/N)),N));
  printf("res %d\n" ,power10((1+(1/N)),N));*/
    return 0;
}
