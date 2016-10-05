//Deklaration eigener Funktionen
int *		GenerateIntVect( int entries ); 
double *	GenerateDoubleVect( int entries ); 
char *		GenerateCharVect( int entries ); 
int **		GenerateIntMat( int rows, int columns ); 
double **	GenerateDoubleMat( int rows, int columns ); 
char **		GenerateCharMat ( int rows, int columns );
void		ShowIntVect( int startEntry, int endEntry, int * Vect, const char * varname ); 
void		ShowDoubleVect( int startEntry, int endEntry, double * Vect, const char * varname ); 
void 		ShowCharVect( int startEntry, int endEntry, char * Vect, const char * varname );
void		ShowIntMat( int startRow, int endRow, int startColumn, int endColumn, int ** Mat, const char * varname ); 
void		ShowDoubleMat( int startRow, int endRow, int startColumn, int endColumn, double ** Mat, const  char * varname ); 
void 		ShowCharMat( int startRow, int endRow, int startColumn, int endColumn, char ** Mat, const char * varname );
void		FreeIntMat( int rows, int ** Mat ); 
void		FreeDoubleMat( int rows, double ** Mat ); 
void		FreeCharMat( int rows, char ** Mat ); 
void		Break( ); 
void		Wait( int timeToWait ); 

//Definition eigener Funktionen
void ShowIntVect( int startEntry, int endEntry, int * Vect, const char * varname )
{
	int i; 
	printf( "\n\n%s:\n\n", varname ); 
	printf( "      : " ); 
	for( i = startEntry; i <= endEntry; i++ ) 
	{
		printf( "%6i ", i ); 
	}
	printf( "\n" ); 
	printf( "......." ); 
	for( i = startEntry; i <= endEntry; i++ ) 
	{
		printf( "......." ); 
	}
	printf( "\n      : " ); 
	for( i = startEntry; i <= endEntry; i++ ) 
	{
		printf( "%6i ", Vect[ i ] ); 
	}
	printf( "\n" ); 
}

void ShowDoubleVect( int startEntry, int endEntry, double * Vect, const char * varname )
{
	int i; 
	printf( "\n\n%s:\n\n", varname ); 
	printf( "      : " ); 
	for( i = startEntry; i <= endEntry; i++ ) 
	{
		printf( "%8i ", i ); 
	}
	printf( "\n" ); 
	printf( "......." ); 
	for( i = startEntry; i <= endEntry; i++ ) 
	{
		printf( "........." ); 
	}
	printf( "\n      : " ); 
	for( i = startEntry; i <= endEntry; i++ ) 
	{
		printf( "%8.3lf ", Vect[ i ] ); 
	}
	printf( "\n" ); 
}

void ShowCharVect( int startEntry, int endEntry, char * Vect, const char * varname )
{
	int i; 
	printf( "\n\n%s:\n\n", varname ); 
	printf( "      : " ); 
	for( i = startEntry; i <= endEntry; i++ ) 
	{
		printf( "%3i ", i ); 
	}
	printf( "\n" ); 
	printf( "......." ); 
	for( i = startEntry; i <= endEntry; i++ ) 
	{
		printf( "...." ); 
	}
	printf( "\n      : " ); 
	for( i = startEntry; i <= endEntry; i++ ) 
	{
		printf( "%3c ", Vect[ i ] ); 
	}	
	printf( "\n" ); 
}


void ShowIntMat( int startRow, int endRow, int startColumn, int endColumn, int ** Mat, const char * varname )
{
	int i, j; 
	printf( "\n\n%s:\n\n", varname ); 

	printf( "      : " ); 
	for( i = startColumn; i <= endColumn; i++ ) 
	{
		printf( "%6i ", i ); 
	}
	printf( "\n" ); 
	printf( "......." ); 
	for( i = startColumn; i <= endColumn; i++ ) 
	{
		printf( "......." ); 
	}
	printf( "\n" ); 
	for( i = startRow; i <= endRow; i++ ) 
	{
 		printf( "%4i  : ", i ); 
		for( j = startColumn; j <= endColumn; j++ ) 
		{
			printf( "%6i ", Mat[ i ][ j ] ); 
		}
		printf( "\n" ); 
	}
}

void ShowDoubleMat( int startRow, int endRow, int startColumn, int endColumn, double ** Mat, const char * varname )
{
	int i, j; 
	printf( "\n\n%s:\n\n", varname ); 

	printf( "      : " ); 
	for( i = startColumn; i <= endColumn; i++ ) 
	{
		printf( "%8i ", i ); 
	}
	printf( "\n" ); 
	printf( "......." ); 
	for( i = startColumn; i <= endColumn; i++ ) 
	{
		printf( "........." ); 
	}
	printf( "\n" ); 
	for( i = startRow; i <= endRow; i++ ) 
	{
		printf( "%4i  : ", i ); 
		for( j = startColumn; j <= endColumn; j++ ) 
		{
			printf( "%8.3lf ", Mat[ i ][ j ] ); 
		}
		printf( "\n" ); 
	}
}

void ShowCharMat( int startRow, int endRow, int startColumn, int endColumn, char ** Mat, const char * varname )
{
	int i, j; 
	printf( "\n\n%s:\n\n", varname ); 

	printf( "      : " ); 
	for( i = startColumn; i <= endColumn; i++ ) 
	{
		printf( "%3i ", i ); 
	}
	printf( "\n" ); 
	printf( "......." ); 
	for( i = startColumn; i <= endColumn; i++ ) 
	{
		printf( "...." ); 
	}
	printf( "\n" ); 
	for( i = startRow; i <= endRow; i++ ) 
	{
		printf( "%4i  : ", i ); 
		for( j = startColumn; j <= endColumn; j++ ) 
		{
			printf( "%3c ", Mat[ i ][ j ] ); 
		}
		printf( "\n" ); 
	}
}

double ** GenerateDoubleMat( int rows, int columns )
{
	int i; 
	double ** Matrix; 
	Matrix = (double **) calloc( rows, sizeof( double * ) ); 
	if ( Matrix == NULL )
	{
		printf( "\nSpeicher konnte nicht allokiert werden." ); 
	}

	for( i = 0; i < rows; i++ )
	{
		Matrix[ i ] = (double *) calloc( columns, sizeof( double ) ); 
		if ( Matrix[ i ] == NULL )
		{
			printf( "\nSpeicher konnte nicht allokiert werden." ); 
		}
	}
	return Matrix; 
}

int ** GenerateIntMat( int rows, int columns )
{
	int i; 
	int ** Matrix; 
	Matrix = (int **)  calloc( rows, sizeof( int * ) ); 
	if ( Matrix == NULL )
	{
		printf( "\nSpeicher konnte nicht allokiert werden." ); 
	}
	for( i = 0; i < rows; i++ )
	{
		Matrix[ i ] = (int *) calloc( columns, sizeof( int ) ); 
		if ( Matrix[ i ] == NULL )
		{
			printf( "\nSpeicher konnte nicht allokiert werden." ); 
		}
	}
	return Matrix; 
}

char ** GenerateCharMat ( int rows, int columns )
{
	int i;
	char ** Matrix;
	Matrix = (char **) calloc( rows, sizeof( char * ) );
	if ( Matrix == NULL )
	{
		printf ( "\nSpeicher konnte nicht allokiert werden." );
	}

	for ( i = 0; i < rows; i++ )
	{
		Matrix[ i ] = (char *) calloc( columns, sizeof( char ) );
		if ( Matrix[ i ] == NULL )
		{
			printf ( "\nSpeicher konnte nicht allokiert werden." );
		}
	}
	return Matrix;
}

double * GenerateDoubleVect( int entries )
{
	double * Vect; 
	Vect = (double *) calloc( entries, sizeof( double ) ); 
	if ( Vect == NULL )
	{
		printf( "\nSpeicher konnte nicht allokiert werden." ); 
	}
	return Vect; 
}

int * GenerateIntVect( int entries )
{
	int * Vect; 
	Vect = (int *) calloc( entries, sizeof( int ) ); 
	if ( Vect == NULL )
	{
		printf( "\nSpeicher konnte nicht allokiert werden." ); 
	}
	return Vect; 
}

char * GenerateCharVect( int entries )
{
	char * Vect; 
	Vect = (char *) calloc( entries, sizeof( char ) ); 
	if ( Vect == NULL )
	{
		printf( "\nSpeicher konnte nicht allokiert werden." ); 
	}
	return Vect; 
}

void FreeDoubleMat( int rows, double ** Mat )
{
	int i; 

	for( i = 0; i < rows; i++ )
	{
		free( Mat[ i ] ); 
	}

	free( Mat ); 
}

void FreeIntMat( int rows, int ** Mat )
{
	int i; 

	for( i = 0; i < rows; i++ )
	{
		free( Mat[ i ] ); 
	}

	free( Mat ); 
}

void FreeCharMat( int rows, char ** Mat )
{
	int i; 

	for( i = 0; i < rows; i++ )
	{
		free( Mat[ i ] ); 
	}

	free( Mat ); 
}

void Break( )
{	
	printf( "\n\nDruecke 'ENTER' um fortzufahren.\n" ); 
    while ( getchar ( ) != '\n' )		
	; 
}

void Wait( int timeToWait )
{
	printf( "\n" ); 

	clock_t timeStart, timeEnd; 
	double timeDuration; 
	timeStart = clock( ); 

	do 
	{	
		timeEnd = clock( ); 
		timeDuration = (double)( timeEnd - timeStart )/( double )CLOCKS_PER_SEC; 
	}
	while( timeDuration <= timeToWait ); 
}

