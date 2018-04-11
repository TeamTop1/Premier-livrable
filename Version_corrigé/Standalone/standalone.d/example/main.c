#include <stdio.h>
#include <string.h>
#include "avalam.h"
#include "topologie.h"

void writePos(char * filename, T_Position p);
static void search(char *chaine);
void viderBuffer();

int main(int argc, char ** argv){
	int numCase, numCaseD, choix,i;
	char chemin[300],espace[2];
	T_Score s ;


	T_Position p = getPositionInitiale();
	//afficherPosition(p);
	strcpy(espace," ");
	printf("%d",argc);
	/*
	for(i=0;i<argc;i++)
	{
		printf("%d",i);
		printf("%s\n",argv[i]);
	}
	 */
	//printf("Sortie 1");
	if(argc==1)
	{
		//printf("hey");
		puts("Quel chemin voulez vous utilisez ?");
		puts("=====MENU=====");
		puts("1) Utiliser le chemin de fichier par defaut");
		puts("2) Utiliser le chemin de votre fichier");
		puts("==============");
		printf("Donner votre choix (1 ou 2)");
		scanf("%d",&choix);
		switch (choix)
		{
			case 1:
			{
				puts("Le chemin utilisé est celui par defaut");
				strcpy(chemin,"/var/www/html/avalam-web/data.json");
				break;
			}
			case 2:
			{
				printf("Quel est le chemin de votre fichier ?\nExemple:/var/www/html/avalam-web/data.json");
				fgets(chemin,300,stdin);
				break;
			}
			default:
			{
				puts("Le chemin utilisé est celui par defaut");
				strcpy(chemin,"/var/www/html/avalam-web/data.json");
				break;
			}
		}
	}
	else
	{
		//printf("hey2");
		for(i=1;i<argc;i++)
		{
			if(i==1)
			{
				strcat(chemin,argv[i]);
			}
			else
			{
				strcat(chemin,espace);
				strcat(chemin,argv[i]);
			}
		}
	}
	writePos(chemin, p);

	T_ListeCoups l = getCoupsLegaux(p);
	//afficherListeCoups(l);
	viderBuffer();

	while(l.nb > 0) {

		printf("caseO ? : ");
		scanf("%d",&numCase);

		printf("caseD ? : ");
		scanf("%d",&numCaseD);

		printf("On joue %d -> %d\n", numCase, numCaseD);
		p = jouerCoup(p, numCase,numCaseD);
		//afficherPosition(p);
		writePos(chemin, p);

		s = evaluerScore(p);
		//afficherScore(s);
		
		l = getCoupsLegaux(p);
		afficherListeCoups(l);
}
	if
			(s.nbJ > s.nbR) puts("\nLa victoire est pour les Jaunes !\n");
	else if
			(s.nbJ < s.nbR) puts("\nLa victoire est pour les Rouges !\n");
	else
	{

			if (s.nbJ5 > s.nbR5) puts("\nLa victoire est pour les Jaunes !\n");
			else if (s.nbJ5 < s.nbR5) puts("\nLa victoire est pour les Rouges !\n");
			else puts("\nIl y a égalité !\n");
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

static void search(char *chaine)

{
	char *p = strchr(chaine, '\n');

	if (p)
	{
		*p = 0;
	}
}

void viderBuffer()
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}
