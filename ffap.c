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
	int i,j, anzahlZuege, Umsteigzeit;
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

// von 23 nach 1
// min abf 90
// max ziel 1383
// umsteig 5


// Typ A Kanten
// im Startbahnhof	suche Ereignis welche von frühste start zeit aus möglich
	for(i=1;i<=anzahlZuege;i++){
		if(Zug[i].start==Sendung.start && Zug[i].zeitStart>Sendung.zeitStart){
			AdjMat[(2*anzahlZuege+1)][0]++;
			AdjMat[(2*anzahlZuege+1)][AdjMat[(2*anzahlZuege+1)][0]]=i;
			Eingangsgrad[(2*anzahlZuege+1)]++;
		}
	}

// Typ B Kanten
	for(i=1;i<=anzahlZuege;i++){
		AdjMat[i][0]=1;
		AdjMat[i][1]=anzahlZuege+i;
		Eingangsgrad[i]++;
	}
// Typ C Kanten
	for(i=1;i<=anzahlZuege;i++){
		for(j=1;j<=anzahlZuege;j++){
			if(Zug[i].zeitZiel+Umsteigzeit<Zug[j].zeitStart && Zug[i].ziel==Zug[j].start){
				AdjMat[anzahlZuege+i][0]++;
				Eingangsgrad[anzahlZuege+j]++;
				AdjMat[anzahlZuege+i][AdjMat[anzahlZuege+i][0]]=anzahlZuege+j;
			}	
		}
	}
// Typ D Kanten 
//im Zielbahnhof suche ereignis welche ereignis noch zeitlich ankommt
	for(i=1;i<=anzahlZuege;i++){
		if(Zug[i].ziel==Sendung.ziel && Zug[i].zeitZiel<Sendung.zeitZiel){
			AdjMat[(2*anzahlZuege+2)][0]++;
			AdjMat[(2*anzahlZuege+2)][AdjMat[(2*anzahlZuege+2)][0]]=i;
			Eingangsgrad[(2*anzahlZuege+2)]++;
		}
	}
// Kantengewicht

	for(i=1;i<=AdjMat[(2*anzahlZuege+2)][0];i++){
		Kantengewicht[(2*anzahlZuege+2)][i] = Zug[i].zeitZiel;
	}

// DAG

	int startKnoten = Sendung.start;
	int zielKnoten = Sendung.ziel;
	int * WeglaengeZuKnoten = GenerateIntVect ( anzahlKnoten + 1 );
	int * Vorgaenger = GenerateIntVect ( anzahlKnoten+1 );

	DAG ( anzahlKnoten, AdjMat, Kantengewicht, Eingangsgrad, startKnoten, zielKnoten, Vorgaenger, WeglaengeZuKnoten, 0 );

	for (i = 1; i <= anzahlKnoten; i++)
	{
		if (i != startKnoten)
		{
			ShowShortestPath ( anzahlKnoten, AdjMat, startKnoten, i, Vorgaenger, WeglaengeZuKnoten );
		}
	}	
	
	
//	ShowIntMat ( 1, 20, 0, 15, AdjMat, "Abfahrtsereignis" );
//	ShowIntMat ( 601, 630, 0, 20, AdjMat, "Ankunftsereignis" );
//	ShowIntVect( 0, 1202, Eingangsgrad, "Eingangsgrad" );
//	ShowIntMat ( 1201, 1201, 0, 20, AdjMat, "Aufkommensereignis" );	
//	ShowIntMat ( 1202, 1202, 0, 30, AdjMat, "Zustellungsereignis" );	
//	ShowIntMat ( 1202, 1202, 0, 30, Kantengewicht, "Kantengewicht" );
	
	FreeIntMat( anzahlKnoten+1, Kantengewicht );
	FreeIntMat( anzahlKnoten+1, AdjMat );
	free ( Eingangsgrad );
	free( Zug ); 
	return 0; 
}

