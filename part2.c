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
/*----*/

typedef enum { FALSE , TRUE } Bool;

typedef struct Bloc {
    int nombre ;
    struct Bloc *suivant;
}Bloc;
typedef Bloc *Liste;

typedef struct  BlocBis {
    int nombre ;
    struct BlocBis *pred;
    struct BlocBis *suivant;
}BlocBis;

typedef BlocBis *ListeBis;

/* initialise une ListeBis � vide */
void initVideBis(ListeBis *L);

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la ListeBis en parametre est vide, 0 sinon */
bool estVideBis(ListeBis l);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la ListeBis en parametre */
int premierBis(ListeBis l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle ListeBis correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
ListeBis ajouteBis(int x, ListeBis l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la ListeBis en parametre: x est ajoute comme premier element */
void empileBis(int x, ListeBis* L);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle ListeBis correspondant a celle en parametre sans son premier element */
ListeBis suiteBis(ListeBis l);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la ListeBis en parametre: le premier element est retire */
void depileBis(ListeBis* l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ;
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
    *L = ajoute(x,*L);
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}


/*************************************************/
/*                                               */
/*                briques de base                */
/*                ListeBis                       */
/*************************************************/

//Fonctionnelle
void initVideBis( ListeBis *L)
{
    *L = NULL ;
}

//Fonctionnelle
bool estVideBis(ListeBis l)
{
    return l == NULL ;
}

//Fonctionnelle
int premierBis(ListeBis l)
{
    return l->nombre ;
}

//Fonctionnelle
ListeBis ajouteBis(int x, ListeBis l)
{
    ListeBis tmp = (ListeBis) malloc(sizeof(BlocBis));
    tmp->nombre = x ;
    ListeBis *p ;
    p = (ListeBis *) tmp;
    if(estVideBis(l)){
        tmp->suivant = NULL ;
        tmp->pred = (struct BlocBis *) p; //à modifier
    }else{
        tmp->suivant = l ;
    }
    tmp->pred = *(&l) ; //Correct
    return tmp;
}

//Fonctionnelle
void empileBis(int x, ListeBis *L)
{
    *L = ajouteBis(x,*L);
}

//Fonctionnelle
ListeBis suiteBis(ListeBis l)
{
    return l->suivant ;
}

//Fonctionnelle
ListeBis predBis(ListeBis l)
{
    return l->pred ;
}

//Non fonctionnel à 100%
void affiche_recBis(ListeBis l){
    if(estVideBis(l)){
        printf("\n");
    }else{
        affiche_recBis(suiteBis(l));
        if(predBis(l)!= NULL)
            printf("%d ", premierBis(predBis(l)));
    }
}

/*
void depileBis(Liste *L)
{
    BlocBis tmp = *L.pred
    //Liste tmp = *L ;
    *L = suite(*L) ;
    *L.pred = tmp ;
    free(tmp) ;
}*/

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
        return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
// *L non NULL ie liste non vide
{
    if ( ((**L).suivant) == NULL )
        depile(L) ;   // moralement : depile(& (*L)) ;
    else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
    if ( (*L) ISNOT NULL )
        VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
            L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
    }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }

}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
    printf("Double Affichage \n") ;
    affiche_rec(l) ;
    affiche_iter(l) ;

    printf("Longueur en double %d %d \n\n",
           longueur_rec(l),
           longueur_iter(l)
    ) ;
}







/* Part 2 */

/* Question 1*/
Bool ZEP123_aux(Liste l , int acc){
    if(estVide(l) || acc>3) {
        return false;
    }else if(premier(l)==0 && acc < 3) {
        return true;
    }else{
        ZEP123_aux(suite(l),acc++);
    }
}
Bool ZEP123(Liste l){
    return ZEP123_aux(l,0);
}

/*Question 2 */
bool PlusCourte(Liste l1 ,Liste l2){
    if(estVide(l1)) {
        if (estVide(l2)) {
            return false;
        } else {
            return true;
        }
    }else if(estVide(l2)){
        return false;
    }else{
        PlusCourte(suite(l1), suite(l2));
    }
}


/*Question 3 : version non terminal */
int NBOAK(Liste l ,int k ){
    if(estVide(l) || k==0){
        return 0;
    }else if(k>0){
        if(premier(l)==0){
            return 1+ NBOAK(suite(l),k-1);
        }else{
            return NBOAK(suite(l),k-1);
        }

    }
}



/*Question 3 : version terminal */
int NBOAK_Aux1(Liste l ,int k,int acc ){
    if(estVide(l) || k==0){
        return acc;
    }else if(k>0){
        if(premier(l)==0){
            return NBOAK_Aux1(suite(l),k-1, acc+=1);
        }else{
            return NBOAK_Aux1(suite(l),k-1,acc);
        }

    }
}
int NBOAK1(Liste l, int k){
    return NBOAK_Aux1(l,k,0);
}


/*Question 3 : version iteratif */
int NBOAK2(Liste l,int k){
    int res = 0;
    for(int i=0;i<=k-1;i++){
        if(premier(l)==0){
            res+=1;
        }
        l = suite(l);
    }
    return res;
}
/*Question 3 : version procedure */
void NBOAK_AUX3(Liste l,int k,int *acc){
    if(estVide(l)){
        if(k==0){
            *acc=0;
        }else{
            return;
        }
    }else{
        if(premier(l)==0){
            *acc+=1;
            NBOAK_AUX3(suite(l), k-1 ,acc);
        }else{
            NBOAK_AUX3(suite(l), k-1 ,acc);
        }
    }
}
int NBOAK3(Liste l , int k ){
    int acc=0;
    NBOAK_AUX3(l,k,&acc);
    return acc;
}
/*Question 4 : */
void NBOARK_aux(Liste l,int k,int *acc,int *k2){
    if(estVide(l)){
        *acc=0;
        *k2=0;
    }else{
        NBOARK_aux(suite(l),k,acc,k2);
        if(premier(l)==0 && (k>*k2)){
            *acc+=1;
        }

        *k2+=1;
    }

}

int NBOARK(Liste l ,int k) {
    int acc;
    int k2;
    NBOARK_aux(l, k, &acc, &k2);
    return acc;
}
/*Question 5 : version recursive simple*/
Liste fctBegaye(Liste l) {

    if (estVide(l)) {
        return l;
    } else {
        if (premier(l) > 0) {
            return ajoute(premier(l), ajoute(premier(l), fctBegaye(suite(l))));
        } else {
            return fctBegaye(suite(l));
        }
    }
}
/*fonctionnele*/
Liste fctBegaye1_aux(Liste l , Liste acc){
    if(estVide(l)){
        return acc;
    }else {
        if (premier(l) > 0) {

            return ajoute(premier(l), ajoute(premier(l), fctBegaye1_aux(suite(l), acc)));
        }
        return fctBegaye1_aux(suite(l), acc);
    }
}

Liste fct_Begaye1(Liste l1){
    Liste acc;
    initVide(&acc);
    return fctBegaye1_aux(l1,acc);

}
/*Question 5 : version recursive terminale*/
void fctBegaye1_aux_proc(Liste l , Liste *acc) {
    if (estVide(l)) {
        return;
    } else {
        fctBegaye1_aux_proc(suite(l), acc);
        if (premier(l) > 0) {
            empile(premier(l), acc);
            empile(premier(l), acc);
        }
    }
}

Liste fctBegaye1_proc(Liste l1){
    Liste acc;
    initVide(&acc);
    fctBegaye1_aux_proc(l1,&acc);
    return acc;
}

/* Q5 : version itérative */
Liste fct_Begaye2(Liste l) {
    Liste l2,l3;
    initVide(&l2);
    initVide(&l3);

    if (estVide(l)) {
        return l;
    } else {

        while (!estVide(l)) {
            if (premier(l) > 0) {

                l2 = ajoute(premier(l), ajoute(premier(l), l2));


                l = suite(l);
            } else {
                l = suite(l);
            }
        }

        while(!estVide(l2)){
            l3 = ajoute(premier(l2),l3);
            l2 = suite(l2);
        }

        return l3;
    }
}


/*Q6: */
void procBegaye_aux(Liste *l){
    if(estVide(*l)){
        return;
    }else{
        if(premier(*l)>0){
            empile(premier(*l),l);
            procBegaye_aux(&(**l).suivant -> suivant);
        }else{
            depile(l);
            procBegaye_aux(l);
        }
    }
}


Liste procBegaye(Liste l){
    procBegaye_aux(&l);
    return l;
}
/*Q7 : permutations */

/*          definition type Liste de Listes      */

typedef struct GrosseListe

{

    Liste premier;

    struct GrosseListe *eltSuivant;

} GrosseListe;



typedef GrosseListe *ListeDeListe;
/*************************************************/

/*                                               */

/*          definition des fonctions de base     */

/*                                               */

/*************************************************/

void initVideGl( ListeDeListe *L)

{

    *L = NULL ;

}



bool EstVidell(ListeDeListe l)

{

    return l == NULL ;

}



Liste premierLl(ListeDeListe l)

{

    return l -> premier ;

}



ListeDeListe ajouteLl(Liste x, ListeDeListe ll)

{

    ListeDeListe tmp = malloc(sizeof(ListeDeListe));

    tmp->premier = x ;

    tmp->eltSuivant = ll;

    return tmp ;

}



void empileLl(Liste x, ListeDeListe *L)

{

    *L = ajouteLl(x,*L) ;

}



ListeDeListe suiteLl(ListeDeListe l)

{

    return l -> eltSuivant;

}





void depileLl(ListeDeListe *L)

{

    ListeDeListe tmp = *L ;

    *L = suiteLl(*L) ;

    free(tmp) ;

}



void affiche_iterLl(ListeDeListe l)

{

    ListeDeListe L2 = l;

    while(!EstVidell(L2))

    {

        affiche_iter(premierLl(L2));

        L2 = suiteLl(L2);

    }

}





void VideListeliste(ListeDeListe *L)

{

    if(!(EstVidell(*L)))

    {

        depileLl(L);

        VideListeliste(L);

    }



}
/*----*/

ListeDeListe concaten(ListeDeListe l1, ListeDeListe l2, int *acc){//good

    if(EstVidell(l1)) {

        return l2;

    }else{

        *acc = *acc + 1;

        return ajouteLl(premierLl(l1), concaten(suiteLl(l1), l2, acc));

    }

}



ListeDeListe AETTL(int x, ListeDeListe ll, int *acc){

    if(EstVidell(ll)) {

        return ll;

    }else{

        *acc = *acc + 2;

        return ajouteLl(ajoute(x, premierLl(ll)), AETTL(x, suiteLl(ll), acc));

    }

}





ListeDeListe ATP(int x, Liste l, int *acc){

    if(estVide(l)){

        ListeDeListe res;

        initVideGl(&res);

        *acc = *acc + 2;

        return ajouteLl(ajoute(x, l), res);

    }else{

        *acc = *acc + 2;

        return ajouteLl(ajoute(x, l), AETTL(premier(l), ATP(x, suite(l), acc), acc));

    }

}





ListeDeListe ATLTP(int x, ListeDeListe ll, int *acc){

    if(EstVidell(ll)){

        return ll;

    }

    else

        return concaten(ATP(x, premierLl(ll), acc), ATLTP(x, suiteLl(ll), acc), acc);

}





ListeDeListe permutation(int n, int *acc){

    if(n == 0){

        ListeDeListe res;

        initVideGl(&res);

        Liste l;

        initVide(&l);

        empileLl(l, &res);

        *acc = *acc + 1;

        return res;

    }else

        return ATLTP(n, permutation(n - 1, acc), acc);

}



/*Fin part 2 */

int main(){


    //Liste l1;
    //initVide(&l1);
   Liste l ;
   initVide (&l) ;

    empile(4, &l) ;
    empile(0, &l) ;
    empile(-2, &l) ;
    empile(7, &l) ;
    empile(2, &l) ;
    empile(3, &l) ;

    poup(l) ;

     //printf("res %d",ZEP123(l));
    /*Liste l2 ;
    initVide (&l2);
    printf("la plus courte %d", PlusCourte(l,l2));*/

   /* printf("nb k  %d\n", NBOAK(l,5));
    printf("nb k  %d\n", NBOAK1(l,5));
    printf("nb k  %d\n", NBOAK2(l,5));
    printf("nb k  %d\n", NBOAK3(l,5)); */

    //printf("nb k %d", NBOARK(l,5));




    /*l = fct_Begaye(l);
    poup(l);*/

    /*l = fct_Begaye2(l);
    poup(l);*/

   /*l = fctBegaye1_proc(l);
    poup(l);*/


    /*l = procBegaye(l);
     poup(l);*/

/*
    VideListe(&l);
    VideListe(&l2);
*/
    /*ListeBis ll;
    initVideBis(&ll);

    empileBis(4, &ll) ;
    empileBis(0, &ll) ;
    empileBis(-2, &ll) ;
    empileBis(7, &ll) ;
    empileBis(2, &ll) ;
    empileBis(3, &ll) ;

    affiche_recBis(ll);*/
    /*ListeDeListe res;

    initVideGl(&res);



//Introduction de 4 listes à mettre dans la liste de listes (avec une liste vide)

    Liste t1;

    Liste t2;

    Liste t3;

    Liste t4;



    initVide(&t1);

    initVide(&t2);

    initVide(&t3);

    initVide(&t4);



    empile(9, &t1);

    empile(7, &t1);

    empile(3, &t1);



    empile(2, &t2);



    empile(8, &t3);

    empile(3, &t3);



    empileLl(t4, &res);

    empileLl(t3, &res);

    empileLl(t2, &res);

    empileLl(t1, &res);



    int acc = 0;

    affiche_iterLl(permutation(3, &acc));

    printf("\nNombre de malloc pour (n = 3) = %d\n", *(&acc));



    VideListe(&t1);

    VideListe(&t2);

    VideListe(&t3);

    VideListe(&t4);

    VideListeliste(&res); */
    return 0;
}
