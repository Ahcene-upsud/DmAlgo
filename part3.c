#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;
/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/
typedef struct bloc_image
{ bool toutnoir ;
    struct bloc_image * fils[4] ;
} bloc_image ;
typedef bloc_image *image ;

/* Question1 */
image construit_blanc() {
    image img = (image) malloc(sizeof(bloc_image));
    img = NULL;
    return img;
}

image construit_noir() {
    image img = (image) malloc(sizeof(bloc_image));
    img->toutnoir = TRUE;
    img->fils[0] = NULL;
    img->fils[1] = NULL;
    img->fils[2] = NULL;
    img->fils[3] = NULL;
    return img;
}

image construit_composee(image i1, image i2, image i3, image i4) {
    image img = (image) malloc(sizeof(bloc_image));
    img->toutnoir = FALSE;
    img->fils[0] = i1;
    img->fils[1] = i2;
    img->fils[2] = i3;
    img->fils[3] = i4;
    return img;
}

/* Question 2 : */
// affichage normal
void affiche_image(image i1){
    if(i1 == NULL){
        printf("B");
    }else if (i1->toutnoir){
        printf("N");
    }else{
        printf("(") ;
        affiche_image(i1->fils[0]);
        affiche_image(i1->fils[1]);
        affiche_image(i1->fils[2]);
        affiche_image(i1->fils[3]);
        printf(")");
    }
}

// affichage en profondeur
void affiche_image_aux(image i1,int acc){
    if(i1 == NULL){
        printf("B%d ",acc);
    }else if (i1->toutnoir){
        printf("N%d ", acc);
    }else{
        printf("(") ;
        affiche_image_aux(i1->fils[0] ,acc+1);
        affiche_image_aux(i1->fils[1],acc+1);
        affiche_image_aux(i1->fils[2],acc+1);
        affiche_image_aux(i1->fils[3],acc+1);
        printf(")");
    }
}
void affiche_image_profendeur(image i1){
    affiche_image_aux(i1,0);
}
/*Question 3 */
image Lecture(){
    image img;
    char carac;
    scanf("%c",&carac);
    if(carac  == 'B'){
        return construit_blanc();
    }else if(carac == 'N'){
        return construit_noir();
    }else if(carac == '('){
        img = construit_composee(NULL,NULL,NULL,NULL);
        //img = construit_composee(Lecture(),Lecture(),Lecture(),Lecture());
        //instruction qui renvoies une image inversée, impossible de l'appliquer directement dans Construit_composée
        img -> fils[0] = Lecture();
        img -> fils[1] = Lecture();
        img -> fils[2] = Lecture();
        img -> fils[3] = Lecture();
        scanf("%c",&carac);
        return img;
    }
    return Lecture();
}
/* Question 4 */
/**
 * Teste si l'image est tout blanche
 * @param i1, une image
 * @return vraie si l'image est toute blanche, faux sinon
 */
bool estBlanche(image i1){
    if(i1 == NULL){
        return TRUE;
    }else{
        if(i1->toutnoir) {
            return FALSE;
        }else {
            return estBlanche(i1->fils[0])
                   && estBlanche(i1->fils[1])
                   && estBlanche(i1->fils[2])
                   && estBlanche(i1->fils[3]);
        }
    }
}

/**
 * Teste si l'image est toute noire
 * @param i1, une image
 * @return vraie si l'image est toute noire, faux sinon
 */
bool estNoir(image i1) {
    if (i1 == NULL) {
        return FALSE;
    } else {
        if (i1->toutnoir) {
            return TRUE;
        } else {
            return estNoir(i1->fils[0])
                   && estNoir(i1->fils[1])
                   && estNoir(i1->fils[2])
                   && estNoir(i1->fils[3]);
        }
    }
}
/* Question 5 */
/**
 * Transforme toute la diagonale principale de l'image en pixels noires
 * @param img, une image
 * @param p, une profondeur (un entier)
 * @return l'image transformée avec la diagonale principale en pixels noirs
 */
image Diagonale(image img ,int p) {
    if (p == 0) {
        if (img == NULL) {
            return construit_noir();
        } else {
            return img;
        }
    } else {
        return construit_composee(Diagonale(img->fils[0], p - 1), img->fils[1], img->fils[2],
                                  Diagonale(img->fils[3], p - 1));

    }
}

/* Question 6 */
/**
 * Tourne l'image de 45° dans le sens des aiguilles d'une montre
 * @param i1, une image
 * @return l'image tourné de 45°
 */
image quartDeTour(image i1){
    if(i1==NULL){
        construit_blanc();
    }else {
        if (i1->toutnoir) {
            construit_noir();
        } else {
            construit_composee(quartDeTour(i1->fils[2]), quartDeTour(i1->fils[0]), quartDeTour(i1->fils[3]),
                               quartDeTour(i1->fils[1]));
        }
    }
}

/* Question 7 */
/*image Negatif(image img){
    if(img == NULL){
        return construit_noir();
    }else{
        if(img -> toutnoir == TRUE){
            return construit_blanc();
        }
        else{
            return construit_composee(Negatif(img -> fils[0]), Negatif(img -> fils[1]), Negatif(img -> fils[2]), Negatif(img -> fils[3]));
        }
    }
}
 */
//Sous-procédure de la fonction Négatif
void Negatif_AUX(image *img) {
    if (*img == NULL) {
        *img = construit_noir();
    } else {
        if ((*img)->toutnoir == TRUE) {
            *img = construit_blanc();
        } else {
            Negatif_AUX(&(*img)->fils[0]);
            Negatif_AUX(&(*img)->fils[1]);
            Negatif_AUX(&(*img)->fils[2]);
            Negatif_AUX(&(*img)->fils[3]);
        }
    }
}

/**
 * Transforme l'image en son négatif (les pixels blancs deviennent noirs et inversement)
 * @param img, une image
 * @return le négatif de l'image img
 */
image Negatif(image img){
    image img2 = img;
    Negatif_AUX (&img2);
    return img2;
}

/* Question 8 */
//Fonctions utilisées dans SimplifieProfP

/**
 * Regarde si la sous-image est entièrement blanche
 * @param i1, une image
 * @return vraie si la sous-image est toute blanche, faux sinon
 */
bool checkBlanc(image i1){
        return i1->fils[0] == NULL && i1->fils[1] == NULL && i1->fils[2] == NULL && i1->fils[3] == NULL;
    }


/**
 * Regarde si la sous-image est entièrement noire
 * @param i1, une image
 * @return vraie si la sous-image est toute noire, faux sinon
 */
bool checkNoir(image i1){
        return i1->fils[0]->toutnoir  && i1->fils[1]->toutnoir && i1->fils[2]->toutnoir && i1->fils[3]->toutnoir;
}

/**
 * Transforme une sous-image composée toute noire/blanche en une image noire/blanche à une certaine profondeur
 * @param i1, une image
 * @param p, une profndeur désirée
 * @return l'image i1 où les sous-images composées sont simplifiées en des images noires/blanches
 */
image SimplifieProfP(image i1 , int p){
    if(p == 0) {
        if (i1 == NULL) {
            return construit_blanc();
        }else {
            if (i1->toutnoir) {
                return construit_noir();
            } else {
                if (checkBlanc(i1)) {
                    return construit_blanc();
                } else {
                    if (checkNoir(i1)) {
                        return construit_noir();
                    } else {
                        return i1;
                    }
                }
            }
        }
    }else{
        return construit_composee(SimplifieProfP(i1->fils[0],p-1) , SimplifieProfP(i1->fils[1] ,p-1) ,SimplifieProfP(i1->fils[2] ,p-1),SimplifieProfP(i1->fils[3] ,p-1));
    }
}
/* Question 9 */
/**
 * Regarde si l'image img1 est incluse dans l'image img2 (càd si là où les pixels noirs sont présents dans img1 sont forcément présents dans img2)
 * @param img1, l'image à tester
 * @param img2, l'image avec qui on va tester img1
 * @return vraie si img1 est incluse dans img2, faux sinon
 */
bool incluse(image img1,image img2) {
    if (img1 == NULL) {
        return TRUE;
    } else {
        if (img1->toutnoir) {
            if (img2->toutnoir) {
                return TRUE;
            } else {
                return FALSE;
            }
        }else{
                return incluse(img1->fils[0], img2->fils[0])
                       && incluse(img1->fils[1], img2->fils[1])
                       && incluse(img1->fils[2], img2->fils[2])
                       && incluse(img1->fils[3], img2->fils[3]);
            }
    }
}
/* Question 10 */
// La fonction qui calcule le maximum de 4 nombres
// la fonction utilisée pour HBM
int max4(int a, int b, int c, int d) {
    int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    if (d > max) max = d;
    return max;
}

//sous-fonction de la fonction HMB
int HMB_aux(image i1,int acc){
    if(i1 == NULL){
        return acc;
    }else{
        if(i1->toutnoir) {
            return -1;
        }else {
            return max4(HMB_aux(i1->fils[0], acc+1), HMB_aux(i1->fils[1], acc+1), HMB_aux(i1->fils[2], acc+1),
                        HMB_aux(i1->fils[3], acc+1));
        }
    }
}

/**
 * Renvoie la hauteur max d'une sous-image blanche dans une image
 * @param i1, une image
 * @return la hauteur max des blancs dans une image
 */
int HMB(image i1){
    return HMB_aux(i1,0);
}

/* Question 11 */
/*fonction hauteur*/
/*
int hauteur(image i1){
    if(i1 == NULL || i1->toutnoir){
        return 0;
    }else{
        return 1+ max4(hauteur(i1->fils[0]), hauteur(i1->fils[1]),hauteur(i1->fils[2]),hauteur(i1->fils[3]));
    }
}
 */
/*fonction garder image jusqu'à profondeur p */
/*
image GIJP(image i1 , int p ) {
    if (p == 0) {
        image i2 = i1;
        return construit_blanc();
    } else {
        return construit_composee(GIJP(i1->fils[0], p - 1), GIJP(i1->fils[1], p - 1), GIJP(i1->fils[2], p - 1),
                                  GIJP(i1->fils[3], p - 1));
    }
}
 */
/* fonction blanchit pixel sous image */
/*
image BPSI(image i1 ,int x ,int y ,int xa , int ya) {
    if (i1 == NULL || i1->toutnoir) {
        if (xa == x && ya == y) {
            return construit_blanc();
        } else {

        }
    } else {
        return construit_composee(BPSI(i1->fils[0], x, y, xa + 1, ya + 1), BPSI(i1->fils[1], x, y, xa + 1, ya + 1),
                                  BPSI(i1->fils[2], x, y, xa + 1, ya + 1), BPSI(i1->fils[3], x, y, xa + 1, ya + 1));

    }
}
 */
/*fonction qui cree une image jusqu'à profondeur p */
/*
image CIJP(image i1,int p){
    if(p==0){
        construit_composee(construit_blanc(),construit_blanc(),construit_blanc(),construit_blanc());
    }else{
        construit_composee(CIJP(i1->fils[0],p-1),CIJP(i1->fils[1],p-1),CIJP(i1->fils[2],p-1),CIJP(i1->fils[3],p-1));
    }
}
*/
/*
image BPP(image i1 ,int p , int x,int y) {
    if (p == 0) {
        if (hauteur(i1) == 0) {
            return construit_blanc();
        } else {
                if (x == 0 && y == 0) {
                    return construit_composee(i1->fils[0], i1->fils[1], construit_blanc(), i1->fils[3]);
                }
                else if (x == 1 && y == 0) {
                    return construit_composee(construit_blanc(), i1->fils[1], i1->fils[2], i1->fils[3]);

                }
                else if (x == 0 && y == 1) {
                    return construit_composee(i1->fils[0], i1->fils[1], i1->fils[2], construit_blanc());

                }
                else  {
                    return construit_composee(i1->fils[0], construit_blanc(), i1->fils[2], i1->fils[3]);
                }

            }
        } else {
        if (hauteur(i1) >= p) {
            return BPP(BPSI(GIJP(i1,p), x, y, 0, 0),p-1,x,y);
        }else{
            return BPP(BPSI(CIJP(i1,p),x,y,0,0),p-1,x,y);
        }

    }


}
*/

/* main */
        int main(){
    image imgB = construit_blanc(); //B
    image imgN = construit_noir();  //N
    image imgnoir = construit_composee(construit_noir(),construit_noir(),construit_noir(), construit_composee(construit_noir(),construit_noir(),construit_noir(),construit_noir())); //(NNN(NNNN))
    image imgex = construit_composee(construit_noir(),construit_blanc(),construit_blanc(), construit_composee(construit_noir(),construit_noir(),construit_noir(),construit_noir())); //(NBB(NNNN))
    image imgBlanc = construit_composee(construit_blanc(),construit_blanc(), construit_composee(construit_blanc(),construit_blanc(),construit_blanc(),
                                                                                          construit_composee(construit_blanc(),construit_blanc(),construit_blanc(),construit_blanc())),construit_blanc()); //(BB(BBB(BBBB))B)
    image imgQuartDeTour = construit_composee(construit_composee(construit_blanc(),construit_noir(),construit_noir(),construit_noir()),construit_blanc(),
                                    construit_composee(construit_noir(),construit_noir(),construit_blanc(),construit_blanc()),construit_noir()); //((BNNN)B(NNBB)N)
    image BBB_BBB_ = construit_composee(construit_blanc(),construit_blanc(),construit_blanc(), construit_composee(construit_blanc(),construit_blanc(),construit_blanc(),construit_blanc()))  ;
    image NBNB = construit_composee(construit_noir(),construit_blanc(),construit_noir(),construit_blanc());
    image N_NBNN_NN_BNB = construit_composee(construit_composee(construit_noir(), construit_composee(construit_noir(),construit_blanc(),construit_noir(),construit_noir()),construit_noir(),construit_noir()),construit_blanc(),construit_noir(),construit_blanc());

    printf("Affichage des images exemples applicables aux questions de la partie 3\n");
    affiche_image(imgB);printf("\n");
    affiche_image(imgN);printf("\n");
    affiche_image(imgnoir);printf("\n");
    affiche_image(imgex);printf("\n");
    affiche_image(imgBlanc);printf("\n");
    affiche_image(imgQuartDeTour);printf("\n\n");

    /*Q2*/
    printf("Affichage de quelques images exemples (simple/profondeur)\n");
    affiche_image(imgB);printf("\n");
    affiche_image(imgN);printf("\n");
    affiche_image(imgex);printf("\n");

    affiche_image_profendeur(imgB);printf("\n");
    affiche_image_profendeur(imgN);printf("\n");
    affiche_image_profendeur(imgex);printf("\n");
    printf("\n");

    /*Q3*/
    printf("tapez une chaine de caracteres a transformer en image\n");
    image testLec = Lecture();
    printf("Affichage de l'image cree :");
    affiche_image(testLec);

    /*Q4*/
    printf("\n\nImage noire a tester: ");
    affiche_image(imgnoir);printf("\n");
    if(estNoir(imgnoir))
        printf("L'image est toute noire\n\n");
    else
        printf("L'image n'est pas toute noire\n\n");

    printf("image blanche a tester: ");
    affiche_image(imgBlanc);printf("\n");
    if(estBlanche(imgBlanc))
        printf("L'image est toute blanche\n\n");
    else
        printf("L'image n'est pas toute blanche\n\n");

    /*Q5*/
    printf("Image a diagonaliser : ");
    affiche_image(imgBlanc);
    printf("\nImage Diagonalisee : ");
    affiche_image(Diagonale(imgBlanc,1));

    /*Q6*/
    printf("\n\nImage a tourner : "); affiche_image(imgQuartDeTour);
    printf("\nImage tournee: ");
    affiche_image(quartDeTour(imgQuartDeTour));

    /*Q7*/
    printf("\n\nImage avant transformation Negative: ");affiche_image(imgex);printf("\n");
    printf("Image negative: ");affiche_image(Negatif(imgex));

    /*Q8*/
    printf("\n\nImage a simplifier pour une profondeur 1 : ");
    affiche_image(imgex);
    printf("\nResulat de l image simplifiee : ");affiche_image(SimplifieProfP(imgex, 1));
    /*Q9*/
    printf("\n\nEst ce que : ");
    affiche_image(imgex);printf(" est incluse dans : ");affiche_image(imgnoir);
    if(incluse(imgex, imgnoir))
        printf("?\nl'image 1 est incluse dans l'image 2\n\n");
    else
        printf("?\nl'image 1 n'est pas incluse dans l'image 2\n\n");

    /*Q10*/
    printf("L'image a tester : ");affiche_image(imgBlanc);
    printf("\nLa hauteur max des blancs est de : ");
    printf(" %d\n",HMB(imgBlanc));
    return 0;
        }
