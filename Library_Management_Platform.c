#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

typedef struct LIVRE{
    char* TITRE;
    char* EDITION;
    char ANNEE[5];
    struct LIVRE *L;
}LIVRE;

typedef struct AUTEUR{
    char* NOM;
    int AGE;
    char* THEME;
    LIVRE *L;
    struct AUTEUR *A;
}AUTEUR;

int EST_MOT(char* Tx){
    int i=0,B=1;
    while ((B)&&(Tx[i]))
     if ((!(isalpha(Tx[i])))&&!(isspace(Tx[i]))) B=0;
        else i++;
    return(B);
}

int EST_ANNEE(char* Tx){
    int i=0,B=1;
    if (strlen(Tx)>4) B=0;
    while ((B)&&(Tx[i]))
     if (!(isdigit(Tx[i]))) B=0;
        else i++;
    return(B);
}

void AJOUTER(AUTEUR** LA){
    (*LA)=NULL;

    int NA;
    do{
    printf("\n NOMBRE D'AUTEURS: ");
    scanf("%d",&NA);
    } while (NA<0);

    AUTEUR* A;
    int i;
    char Tx[25];
    for(i=0;i<NA;i++){
        A=(AUTEUR*)malloc(sizeof(AUTEUR));

        system("cls");
        printf("\n AUTEUR n°%d",i+1);
        do {
            fflush(stdin);
            printf("\n  NOM: ");
            gets(Tx);
        }while (!(EST_MOT(Tx)));
        A->NOM=(char*)malloc(strlen(Tx)+1);
        strcpy(A->NOM,Tx);

        do {
            fflush(stdin);
            printf("\n  THEME: ");
            gets(Tx);
        }while (!(EST_MOT(Tx)));
        A->THEME=(char*)malloc(strlen(Tx)+1);
        strcpy(A->THEME,Tx);

        do{
            printf("\n  AGE: ");
            scanf("%d",&(A->AGE));
        }while ((A->AGE)<4);

        A->A=NULL;

        int NL;
        do{
            printf("\n NOMBRE DE LIVRE: ");
            scanf("%d",&NL);
         } while (NL<0);

         A->L=NULL;
         LIVRE* AUX;
         int j;
         for(j=0;j<NL;j++){
            AUX=(LIVRE*)malloc(sizeof(LIVRE));

            do {
            fflush(stdin);
            printf("\n TITRE: ");
            gets(Tx);
            }while (!(EST_MOT(Tx)));
            AUX->TITRE=(char*)malloc(strlen(Tx)+1);
            strcpy(AUX->TITRE,Tx);

            do {
            fflush(stdin);
            printf("\n EDITION: ");
            gets(Tx);
            }while (!(EST_MOT(Tx)));
            AUX->EDITION=(char*)malloc(strlen(Tx)+1);
            strcpy(AUX->EDITION,Tx);

            do{
            printf("\n ANNEE: ");
            gets(AUX->ANNEE);
            } while (!EST_ANNEE(AUX->ANNEE));
        (AUX->L)=A->L;
         A->L=AUX;
         }
         A->A=*LA;
         *LA=A;
        }
}

int RECHERCHER(AUTEUR *A,char* Tx){
    int B=0;
    while (A&&(!B)){
        if (!strcmp(A->NOM,Tx)) B=1;
        A=A->A;
    }
    return(B);
}

void AFFICHIER_LIVRE(LIVRE* L){
    while(L){
        printf("\n TITRE: %s\t EDITION: %s\t ANNEE: %s\n ",L->TITRE,L->EDITION,L->ANNEE);
        L=L->L;
    }
}

void AFFICHIER(AUTEUR* A){
    while(A){
        printf("\n NOM: %s\t THEME: %s\t AGE: %d\n ",A->NOM,A->THEME,A->AGE);
        AFFICHIER_LIVRE(A->L);
        A=A->A;
    }
}

void SAUVGARDER(AUTEUR* A){
    FILE *F;
    F=fopen("AUTEURS.txt","w");
    while(A){
    fprintf(F,"%s\t%s\t%d\n",A->NOM,A->THEME,A->AGE);
    LIVRE* L;
    L=A->L;
    while(L){
        fprintf(F,"%s\t%s\t%s\n ",L->TITRE,L->EDITION,L->ANNEE);
        L=L->L;
    }
        A=A->A;
    }
    fclose(F);
}

int main()
{
    AUTEUR* LA=NULL;

    MENU:
    system("cls");
    int C;
    printf("\n 1.AJOUTER\n 2.RECHERCHER\n 3.AFFICHAGE\n 4.SAUVGARDER\n 5.QUITTER\n ");
    scanf("%d",&C);
    switch(C){
    case 1: {system("cls");AJOUTER(&LA);system("cls");printf("\n OPERATION REUSSITE.");getch();goto MENU;}break;
    case 2: {
        char Tx[25];
            system("cls");
            do {
                fflush(stdin);
                printf("\n  NOM: ");
                gets(Tx);
            }while (!(EST_MOT(Tx)));
            if (RECHERCHER(LA,Tx)) {system("cls");printf("\n AUTEUR EXISTE. ");printf("\n NOM: %s\t THEME: %s\t AGE: %d\n ",LA->NOM,LA->THEME,LA->AGE);
                                    AFFICHIER_LIVRE(LA->L);getch();goto MENU;}
            else {printf("\n AUTEUR N'EXISTE PAS.\n ");getch();goto MENU;}
        };break;
    case 3: {AFFICHIER(LA);printf("\n ");getch();goto MENU;}break;
    case 4: {SAUVGARDER(LA);system("cls");printf("\n OPERATION REUSSITE.");getch();goto MENU;}break;
    case 5: {exit(EXIT_SUCCESS);};break;
    default:{printf("\n CHOIX INCORRECT.");exit(EXIT_SUCCESS);}
    }

    return 0;
}
