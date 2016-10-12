int TopSort(int anzahlKnoten, int ** AdjMat, int ** Kantengewicht, int * Eingangsgrad, int * TopologischeSortierung);
int DAG ( int anzahlKnoten, int ** AdjMat, int ** Kantengewicht, int * Eingangsgrad, int startKnoten, int zielKnoten, int * Vorgaenger, int * WeglaengeZuKnoten, int printDetails );
int ShowShortestPath ( int anzahlKnoten, int ** AdjMat, int startKnoten, int zielKnoten, int * Vorgaenger, int * WeglaengeZuKnoten );


int TopSort ( int anzahlKnoten, int ** AdjMat, int ** Kantengewicht, int * Eingangsgrad, int * TopologischeSortierung )
{
	int i, j;
	int knoten;

	int anzahlDerKnotenInTopSort = 0;
	do {
		knoten=0;
		for ( i = 1; i <= anzahlKnoten; i++ ){
			if ( Eingangsgrad[ i ] == 0 ){
				anzahlDerKnotenInTopSort++;
				TopologischeSortierung[ anzahlDerKnotenInTopSort ] = i;	
				Eingangsgrad[i]=(-1);
				knoten=i;
				break;
			}
		}
		if(knoten == 0){
			system ("cls");
			printf ("Netzwerk ist nicht Kreisfrei");
			break;
		}
		for ( j = 1; j <= AdjMat[knoten][0]; j++ ){
			Eingangsgrad[ AdjMat[knoten][j] ]--;
		}
		
	}while (anzahlDerKnotenInTopSort<anzahlKnoten);
	
	return 0;
}

int DAG ( int anzahlKnoten, int ** AdjMat, int ** Kantengewicht, int * Eingangsgrad, int startKnoten, int zielKnoten, int * Vorgaenger, int * WeglaengeZuKnoten, int printDetails )
{
	int i, j, k, ii;
	int * TopologischeSortierung;	//entspricht Vektor t im Quellcode auf Vorlesungsfolien
	TopologischeSortierung = GenerateIntVect ( anzahlKnoten+1 );

	TopSort ( anzahlKnoten, AdjMat, Kantengewicht, Eingangsgrad, TopologischeSortierung );
//	ShowIntVect ( 270, 300, TopologischeSortierung, "TopologischeSortierung" );	
	for (j=1;j<=anzahlKnoten;j++){
		WeglaengeZuKnoten[j]=MAX;
		Vorgaenger[j]=MAX;
		if(TopologischeSortierung[j]==startKnoten){
			i=j;
		}
	}
	WeglaengeZuKnoten[startKnoten]=0;
	Vorgaenger[startKnoten]=0;

	for(i;i<=anzahlKnoten;i++){
		if(WeglaengeZuKnoten[TopologischeSortierung[i]]<MAX){
			for(k=1;k<=AdjMat[TopologischeSortierung[i]][0];k++){
				j = AdjMat[TopologischeSortierung[i]][k];
				if(WeglaengeZuKnoten[j]>WeglaengeZuKnoten[TopologischeSortierung[i]]+Kantengewicht[TopologischeSortierung[i]][j]){
					WeglaengeZuKnoten[j]=WeglaengeZuKnoten[TopologischeSortierung[i]]+Kantengewicht[TopologischeSortierung[i]][j];
					Vorgaenger[j]=TopologischeSortierung[i];
				}
			}
		}
	}
	
//	ShowIntVect( 1, anzahlKnoten, Vorgaenger, "Vorgaenger" );
//	ShowIntVect ( 1, anzahlKnoten, WeglaengeZuKnoten, "WeglaengeZuKnoten" );	
//	ShowIntMat ( 1, anzahlKnoten, 0, anzahlKnoten, AdjMat, "AdjMat" );


	if (TopologischeSortierung != NULL) free ( TopologischeSortierung );

	return 1;
}


int ShowShortestPath ( int anzahlKnoten, int ** AdjMat, int startKnoten, int zielKnoten, int * Vorgaenger, int * WeglaengeZuKnoten )
{
	if ( WeglaengeZuKnoten[ zielKnoten ] < MAX )
	{	
		printf ( "\nKuerzester Weg von Startknoten %d zu Zielknoten %d mit Weglaenge %d:  ", startKnoten, zielKnoten, WeglaengeZuKnoten[ zielKnoten ] );
		int vorg = zielKnoten;
		int from_tmp = startKnoten;
		int vorg_tmp;
		while (from_tmp != zielKnoten)
		{
			vorg = zielKnoten;

			while (from_tmp != vorg)
			{
				vorg_tmp = vorg;
				vorg = Vorgaenger[ vorg ];
			}
			printf ( "%d -> %d, ", vorg, vorg_tmp );
			from_tmp = vorg_tmp;
		}
		printf ( "\n" );
	}
	else
	{
		printf ( "\nEs exisitiert kein Weg von Startknoten %d zu Zielknoten %d!\n", startKnoten, zielKnoten );
	}

	return 1;
}
