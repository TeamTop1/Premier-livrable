#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avalam.h"
#include "topologie.h"

static void search(char *chaine);
void menu1(int *choix);
void menu2(int *choix);
void menu3(int *choix);
void viderBuffer();
void writePos(char * filename, T_Position p) ;

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void writePos(char * filename, T_Position p) {
	FILE * fp;
	int i;

	T_Score s = evaluerScore(p);


	// Le fichier ne devrait-il pas être préfixé par le PID du process ?
	// On devrait lui faire porter le nom du groupe, passé en ligne de commandes
	fp = fopen(filename,"w");

	// On écrit le trait
	fprintf(fp, "{\n%s:%d,\n",STR_TURN,p.trait);

	// On écrit les scores
	fprintf(fp, "%s:%d,\n",STR_SCORE_J,s.nbJ);
	fprintf(fp, "%s:%d,\n",STR_SCORE_J5,s.nbJ5);
	fprintf(fp, "%s:%d,\n",STR_SCORE_R,s.nbR);
	fprintf(fp, "%s:%d,\n",STR_SCORE_R5,s.nbR5);



	// Les colonnes // attention aux "," ?
	fprintf(fp, "%s:[\n",STR_COLS);

	// première
	fprintf(fp, "\t{%s:%d, %s:%d}",STR_NB,p.cols[0].nb, STR_COULEUR,p.cols[0].couleur);

	// autres
	for(i=1;i<NBCASES;i++) {
		fprintf(fp, ",\n\t{%s:%d, %s:%d}",STR_NB,p.cols[i].nb, STR_COULEUR,p.cols[i].couleur);
	}
	fprintf(fp,"\n]\n"); // avec ou sans "," ?

	fprintf(fp,"}");

	fclose(fp);
}

int main (int argc, char**argv) {
    //Var
    int numCase, numCaseD, choix, sauv, max, a, i, j, point_jaune, point_rouge, point_rouge5, point_jaune5, compteur, def;
    int colonne_ad[9];
    FILE *fp;
    char filename[100], chemin1[81], FEN[60], DEFAUT[30000];
    T_Score s;
    T_Position p;
    T_Colonne c;

    //Debut
    colonne_ad[0] = 0;
    colonne_ad[1] = 2;
    colonne_ad[2] = 6;
    colonne_ad[3] = 12;
    colonne_ad[4] = 20;
    colonne_ad[5] = 28;
    colonne_ad[6] = 36;
    colonne_ad[7] = 42;
    colonne_ad[8] = 46;
    colonne_ad[9] = 48;
    compteur = point_jaune = point_jaune5 = point_rouge = point_rouge5 = 0;
    strcpy(FEN,argv[1]);
    for(i=2;i<argc;i++)
    {
        printf("%s",argv[i]);
        strcat(FEN,argv[i]);
        printf("\n%s\n",FEN);
    }
    if(argc<=3)
    {
        puts("Quelle est le numero de votre diagramme ?");
        scanf("%d",&sauv);
    }
    else
    {
       sauv=atoi(argv[argc-1]);
    }
    if(argc-1==0)
    {
        puts("Vous avez oubliez d'entrer votre code FEN\nVeuillez le Saisir:");
        fgets(FEN,60,stdin);
    }
    if (strlen(FEN) <= 18) {
        puts("FEN pas assez long, FEN mis par defaut");
        strcpy(FEN,"Uu/UuUu/uUuUuU/UuUuUuUu/UuUuuUuU/uUuUuUuU/UuUuUu/UuUu/uU j");
        def=1;
    }
    menu3(&max);
    switch (max)
    {
        default:
        case 1:
            puts("Utilisation du chemin par defaut !");
            stpcpy(filename, "../../avalam-web/initial.json");
            break;
        case 2:
            puts("Quel chemin voulez vous utilisez ?");
            strcpy(filename,"../../avalam-web/");
            fgets(chemin1,80,stdin);
            strcat(filename,chemin1);
            break;
    };
    fp = fopen(filename, "w");
    fprintf(fp, "{\n");
    fprintf(fp, "%s:[\n", STR_COLS);
    a=0;
    i=0;
    do
    {
        switch (FEN[i])
        {
            case '/':
                a++;
                if (compteur < colonne_ad[a] && compteur<47)
                {
                    for (j = compteur; j < colonne_ad[a]; j++)
                    {
                        if (compteur == 47)
                        {
                            fprintf(fp, "\t{%s:%d, %s:%d}", STR_NB, 0, STR_COULEUR, VIDE);
                            a++;
                        }
                        else
                        {
                            fprintf(fp, "\t{%s:%d, %s:%d},\n", STR_NB, 0, STR_COULEUR, VIDE);
                        }
                        c.nb=0;
                        c.couleur=VIDE;
                        p.cols[compteur]=c;
                        compteur++;
                    }
                }
                break;
            case 'U':
                if (compteur == 47)
                {
                    fprintf(fp, "\t{%s:%d, %s:%d}", STR_NB, 1, STR_COULEUR, ROU);
                }
                else
                {
                    fprintf(fp, "\t{%s:%d, %s:%d},\n", STR_NB, 1, STR_COULEUR, ROU);
                }
                point_rouge++;
                c.nb=1;
                c.couleur=ROU;
                p.cols[compteur]=c;
                compteur++;
                break;
            case 'u':
                if (compteur == 47)
                {
                    fprintf(fp, "\t{%s:%d, %s:%d}", STR_NB, 1, STR_COULEUR, JAU);
                }
                else
                {
                    fprintf(fp, "\t{%s:%d, %s:%d},\n", STR_NB, 1, STR_COULEUR, JAU);
                }
                point_jaune++;
                c.nb=1;
                c.couleur=JAU;
                p.cols[compteur]=c;
                compteur++;
                break;
            case 'D':
                if (compteur == 47)
                {
                    fprintf(fp, "\t{%s:%d, %s:%d}", STR_NB, 2, STR_COULEUR, ROU);
                }
                else
                {
                    fprintf(fp, "\t{%s:%d, %s:%d},\n", STR_NB, 2, STR_COULEUR, ROU);
                }
                point_rouge++;
                c.nb=2;
                c.couleur=ROU;
                p.cols[compteur]=c;
                compteur++;
                break;
            case 'd':
                if (compteur == 47)
                {
                    fprintf(fp, "\t{%s:%d, %s:%d}", STR_NB, 2, STR_COULEUR, JAU);
                }
                else
                {
                    fprintf(fp, "\t{%s:%d, %s:%d},\n", STR_NB, 2, STR_COULEUR, JAU);
                }
                point_jaune++;
                c.nb=2;
                c.couleur=JAU;
                p.cols[compteur]=c;
                compteur++;
                break;
            case 'T':
                if (compteur == 47)
                {
                    fprintf(fp, "\t{%s:%d, %s:%d}", STR_NB, 3, STR_COULEUR, ROU);
                }
                else
                {
                    fprintf(fp, "\t{%s:%d, %s:%d},\n", STR_NB, 3, STR_COULEUR, ROU);
                }
                point_rouge++;
                c.nb=3;
                c.couleur=ROU;
                p.cols[compteur]=c;
                compteur++;
                break;
            case 't':
                if (compteur == 47)
                {
                    fprintf(fp, "\t{%s:%d, %s:%d}", STR_NB, 3, STR_COULEUR, JAU);
                }
                else
                {
                    fprintf(fp, "\t{%s:%d, %s:%d},\n", STR_NB, 3, STR_COULEUR, JAU);
                }
                point_jaune++;
                c.nb=3;
                c.couleur=JAU;
                p.cols[compteur]=c;
                compteur++;
                break;
            case 'Q':
                if (compteur == 47)
                {
                    fprintf(fp, "\t{%s:%d, %s:%d}", STR_NB, 4, STR_COULEUR, ROU);
                }
                else
                {
                    fprintf(fp, "\t{%s:%d, %s:%d},\n", STR_NB, 4, STR_COULEUR, ROU);
                }
                point_rouge++;
                c.nb=4;
                c.couleur=ROU;
                p.cols[compteur]=c;
                compteur++;
                break;
            case 'q':
                if (compteur == 47)
                {
                    fprintf(fp, "\t{%s:%d, %s:%d}", STR_NB, 4, STR_COULEUR, JAU);
                }
                else
                {
                    fprintf(fp, "\t{%s:%d, %s:%d},\n", STR_NB, 4, STR_COULEUR, JAU);
                }
                point_jaune++;
                c.nb=4;
                c.couleur=JAU;
                p.cols[compteur]=c;
                compteur++;
                break;
            case 'C':
                if (compteur == 47)
                {
                    fprintf(fp, "\t{%s:%d, %s:%d}", STR_NB, 5, STR_COULEUR, ROU);
                }
                else
                {
                    fprintf(fp, "\t{%s:%d, %s:%d},\n", STR_NB, 5, STR_COULEUR, ROU);
                }
                point_rouge5++;
                c.nb=5;
                c.couleur=ROU;
                p.cols[compteur]=c;
                compteur++;
                break;
            case 'c':
                if (compteur == 47)
                {
                    fprintf(fp, "\t{%s:%d, %s:%d}", STR_NB, 5, STR_COULEUR, JAU);
                }
                else
                {
                    fprintf(fp, "\t{%s:%d, %s:%d},\n", STR_NB, 5, STR_COULEUR, JAU);
                }
                point_jaune5++;
                c.nb=5;
                c.couleur=JAU;
                p.cols[compteur]=c;
                printf("%d,%d\n",p.cols[compteur].nb,p.cols[compteur].couleur);
                compteur++;
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                max=atoi(&FEN[i]);
                for (j=0; j < max; j++)
                {
                    c.nb=0;
                    c.couleur=VIDE;
                    p.cols[compteur]=c;
                    if (compteur == 47)
                    {
                        fprintf(fp, "\t{%s:%d, %s:%d}", STR_NB, 0, STR_COULEUR, VIDE);
                    }
                    else
                    {
                        fprintf(fp, "\t{%s:%d, %s:%d},\n", STR_NB, 0, STR_COULEUR, VIDE);
                    }
                    compteur++;
                }
                break;
            case ' ':
                break;
            case 'j':
                fprintf(fp, "\n],\n");
                fprintf(fp, "%s:%d,\n", "\"trait\"", JAU);
                p.trait = JAU;
                FEN[i+1]='\0';
                compteur=47;
                break;
            case 'r':
                fprintf(fp, "\n],\n");
                fprintf(fp, "%s:%d,\n", "\"trait\"", ROU);
                p.trait = ROU;
                FEN[i+1]='\0';
                compteur=47;
                break;
            default:
                fclose(fp);
                puts("ERREUR DANS VOTRE CODE FEN");
                menu1(&max);
                switch(max)
                {
                    default:
                    case 1:
                        puts("VOTRE CODE EST REMPLACE PAR CELUI PAR DEFAUT !");
                        strcpy(FEN,"Uu/UuUu/uUuUuU/UuUuUuUu/UuUuuUuU/uUuUuUuU/UuUuUu/UuUu/uU j");
                        def=1;
                        break;
                    case 2:
                        puts("Veuillez le Saisir votre code FEN:");
                        viderBuffer();
                        fgets(FEN,60,stdin);
                        break;
                };
                fp = fopen(filename, "w");
                fprintf(fp, "{\n");
                fprintf(fp, "%s:[\n", STR_COLS);
                i=-1;
                compteur=0;
                a=0;
                break;
        }
        if (compteur> colonne_ad[a+1])
        {
            fclose(fp);
            puts("ERREUR DANS VOTRE CODE FEN");
            menu1(&max);
            switch(max)
            {
                default:
                case 1:
                    puts("VOTRE CODE EST REMPLACE PAR CELUI PAR DEFAUT !");
                    strcpy(FEN,"Uu/UuUu/uUuUuU/UuUuUuUu/UuUuuUuU/uUuUuUuU/UuUuUu/UuUu/uU j");
                    def=1;
                    break;
                case 2:
                    puts("Veuillez le Saisir votre code FEN:");
                    viderBuffer();
                    fgets(FEN,60,stdin);
                    break;
            };
            fp = fopen(filename, "w");
            fprintf(fp, "{\n");
            fprintf(fp, "%s:[\n", STR_COLS);
            i=-1;
            compteur=0;
            a=0;
        }
        i++;
    }
    while (FEN[i] != '\0');
    fprintf(fp,"\"numdiag\": %d,\n",sauv);
    if(def==1)
    {
        fprintf(fp,"\"notes\":%s",DEFAUT);
    }
    else
    {
        menu2(&max);
        switch(max)
        {
            default:
            case 2:
                puts("Utilisation de la description par defaut !");
                fprintf(fp,"\"notes\":\"Position initiale. Les règles ne le précisant pas, nous choisirons de faire commencer la couleur la plus claire, ici les jaunes (à l'instar des échecs où les blancs commencent). Cela semble cohérent dans le mesure où les rouges semblent avantagés, car leurs pions ont globalement moins de voisins (148 voisins pour les jaunes contre 144 pour les rouges). Cela reste toutefois à prouver par la pratique.\"\n");
                break;
            case 1:
                puts("Utilisation de votre description !");
                viderBuffer();
                fgets(DEFAUT,1000,stdin);
                search(DEFAUT);
                fprintf(fp,"\"notes\":\"%s\"",DEFAUT);
                break;
        }
    }
    fprintf(fp, "}");
    fclose(fp);
    T_ListeCoups l = getCoupsLegaux(p);
    //afficherListeCoups(l);

    while(l.nb > 0)
    {

        printf("caseO ? : ");
        scanf("%d", &numCase);

        printf("caseD ? : ");
        scanf("%d", &numCaseD);

        printf("On joue %d -> %d\n", numCase, numCaseD);
        p = jouerCoup(p, numCase, numCaseD);
        //afficherPosition(p);
        writePos(filename, p);

        s = evaluerScore(p);
        afficherScore(s);

        l = getCoupsLegaux(p);
        //afficherListeCoups(l);
    }
}


void menu1(int *choix)
{
    puts("======MENU ERREUR======");
    puts("1) Utilisez le FEN par defaut");
    puts("2) Réécrire votre FEN");
    puts("=======================");
    scanf("%d",choix);
}

void menu2(int *choix)
{
    puts("Quelle description voulez vous utilisez");
    puts("======MENU DESCRIPTION======");
    puts("1) Réécrire votre description");
    puts("2) Utilisez la description par defaut");
    puts("============================");
    scanf("%d",choix);
}

void menu3(int *choix)
{
    puts("Quel chemin voulez vous utilisez ?");
    puts("=====MENU=====");
    puts("1) Utiliser le chemin de fichier par defaut");
    puts("2) Utiliser le chemin de votre fichier");
    puts("==============");
    scanf("%d",choix);
}

static void search(char *chaine)

{

    char *p = strchr(chaine, '\n');


    if (p)

    {

        *p = 0;

    }

}























