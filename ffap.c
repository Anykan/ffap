#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conv.h"

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

// Typ B Kanten
	for(i=1;i<=anzahlZuege;i++){
		AdjMat[i][0]=1;
		AdjMat[i][1]=anzahlZuege+i;
	}
// Typ C
	for(i=1;i<=anzahlZuege;i++){
		for(j=1;j<=anzahlZuege;j++){
			if(Zug[i].zeitZiel+Umsteigzeit<Zug[j].zeitStart && Zug[i].ziel==Zug[j].start){  // Bahnhofüberprüfen ob start = ziel fehlt noch
				printf("%d -> %d\n",i,j); // hioer komm dag zeile 54 ff. wenn kannte existiret in spalt 0 ++ und nachfolger eintragen
			}
			
		}
	}

	FreeIntMat( anzahlKnoten+1, Kantengewicht );
	FreeIntMat( anzahlKnoten+1, AdjMat );
	free ( Eingangsgrad );
	free( Zug ); 
	return 0; 
}

