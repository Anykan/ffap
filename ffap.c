#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>

#define MAX 100000
#include "conv.h"
#include "dag.h"


struct Zuege
{
	int start;
	int ziel;
	int zeitStart;
	int zeitZiel;
};
struct Sendungen
{
	int start;
	int ziel;
	int zeitStart;
	int zeitZiel;
};

int main(int  argc, char ** argv )
{
	int i,j, anzahlZuege, Umsteigzeit, von, zu;
	struct Sendungen Sendung;
	system("cls");
	//Überprüfe Argumente
	if ( 2 != argc ) 
	{
		printf("\nProgrammaufruf: ffap.exe datei.txt \n"); 
		return 1; 
	}

	//Einlesen aus Datei
	FILE * file_data = fopen( argv[ 1 ], "r" );
	if( file_data == 0 )
	{
		printf("\n Problem: Datei %s konnte nicht geoeffnet werden.\n", argv[ 1 ] );
		return 1;
	}
	
	// Schreibe Daten in Sturktur
	fscanf( file_data, "%d", &anzahlZuege );
	struct Zuege * Zug = ( struct Zuege * ) calloc ( anzahlZuege+1, sizeof( struct Zuege ) );
	for( i = 1; i <= anzahlZuege; i++ ) 
	{
		fscanf( file_data, "%d %d %d %d",&((Zug[i])).start, &(Zug[i]).ziel, &(Zug[i]).zeitStart, &(Zug[i]).zeitZiel  );
	}
	fscanf( file_data, "%d %d %d %d %d",&(Sendung).start, &(Sendung).ziel, &(Sendung).zeitStart, &(Sendung).zeitZiel, &Umsteigzeit  );
	fclose( file_data );

// Erstellen Matrix für DAG
	int anzahlKnoten = (2*anzahlZuege)+2;
	int * Eingangsgrad = GenerateIntVect( anzahlKnoten+1 );
	int ** AdjMat = GenerateIntMat( anzahlKnoten+1, anzahlKnoten+1 );
	int ** Kantengewicht = GenerateIntMat( anzahlKnoten + 1, anzahlKnoten + 1 );


// Typ A Kanten
// im Startbahnhof	suche Ereignis welche von frühste start zeit aus möglich
	for(i=1;i<=anzahlZuege;i++){
		if(Zug[i].start==Sendung.start && Zug[i].zeitStart>Sendung.zeitStart){
			AdjMat[(2*anzahlZuege+1)][0]++;
			AdjMat[(2*anzahlZuege+1)][AdjMat[(2*anzahlZuege+1)][0]]=i;
			Eingangsgrad[i]++; //1-600
		}
	}

// Typ B Kanten
	for(i=1;i<=anzahlZuege;i++){
		AdjMat[i][0]=1;
		AdjMat[i][1]=anzahlZuege+i;
		Eingangsgrad[anzahlZuege+i]++; //601-1200
	}
// Typ C Kanten
	for(i=1;i<=anzahlZuege;i++){
		for(j=1;j<=anzahlZuege;j++){
			if(Zug[i].zeitZiel+Umsteigzeit<Zug[j].zeitStart && Zug[i].ziel==Zug[j].start){
				AdjMat[anzahlZuege+i][0]++;
				Eingangsgrad[j]++; //1-600
				AdjMat[anzahlZuege+i][AdjMat[anzahlZuege+i][0]]=j;
			}	
		}
	}
// Typ D Kanten 
//im Zielbahnhof suche ereignis welche ereignis noch zeitlich ankommt
	for(i=1;i<=anzahlZuege;i++){
		if(Zug[i].ziel==Sendung.ziel && Zug[i].zeitZiel<Sendung.zeitZiel){
			von = i+anzahlZuege;
			zu = 2*anzahlZuege+2; 
			AdjMat[von][0]++;
			AdjMat[von][AdjMat[von][0]]=zu;
			Eingangsgrad[zu]++; //1202
			Kantengewicht[von][zu]=Zug[i].zeitZiel;
		}
	}


// DAG

	int startKnoten = 2*anzahlZuege+1;
	int * WeglaengeZuKnoten = GenerateIntVect ( anzahlKnoten + 1 );
	int * Vorgaenger = GenerateIntVect ( anzahlKnoten+1 );

	DAG ( anzahlKnoten, AdjMat, Kantengewicht, Eingangsgrad, startKnoten, -1, Vorgaenger, WeglaengeZuKnoten, 0 );


	ShowShortestPath ( anzahlKnoten, AdjMat, startKnoten, 1202, Vorgaenger, WeglaengeZuKnoten );
	
/*
	ShowIntMat ( 1201, 1201, 0, 20, AdjMat, " AdjMat Abfahrtsereignis" );
	ShowIntMat ( 442, 442, 0, 20, AdjMat, " AdjMat Abfahrtsereignis" );
	ShowIntMat ( 1042, 1042, 0, 20, AdjMat, " AdjMat Abfahrtsereignis" );
	ShowIntMat ( 94, 94, 0, 20, AdjMat, " AdjMat Abfahrtsereignis" );
	ShowIntMat ( 694, 694, 0, 20, AdjMat, " AdjMat Abfahrtsereignis" );
	ShowIntMat ( 488, 488, 0, 20, AdjMat, " AdjMat Abfahrtsereignis" );
	ShowIntMat ( 1088, 1088, 0, 20, AdjMat, " AdjMat Abfahrtsereignis" );
	ShowIntMat ( 1202, 1202, 0, 20, AdjMat, " AdjMat Abfahrtsereignis" );
	ShowIntMat ( 1088, 1088, 1202, 1202, Kantengewicht, "Kanten Kantengewicht" );
	ShowIntVect ( 420, 450, Eingangsgrad, "Blaa" );
*/	
	free (WeglaengeZuKnoten);
	free (Vorgaenger);
	FreeIntMat( anzahlKnoten+1, Kantengewicht );
	FreeIntMat( anzahlKnoten+1, AdjMat );
	free ( Eingangsgrad );
	free( Zug ); 
	return 0; 
}

