// solutia bruta: memoram tot textul, apoi il parcurgem cu un indice si
// citim atomii unul cate unul, fara variabila de stare
// verificam ca intrarea respecta restrictiile
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#define MAXLEN 2000000

char text[MAXLEN + 2];

int main() {
  FILE *fin, *fout;
  int n, i, mare, nvar, nfunc, nint, nzec;

  fin = fopen( "variabile.in", "r" );
  n = fread( text, sizeof( char ), MAXLEN + 2, fin );
  fclose( fin );

  // textul se termina cu '\n', restul sunt litere, cifre, spatii si puncte
  assert( n >= 1 && text[n - 1] == '\n' );
  n--;
  assert( n <= MAXLEN );
  for ( i = 0; i < n; i++ )
    assert( isdigit( text[i] ) || islower( text[i] ) || isupper( text[i] )
            || text[i] == ' ' || text[i] == '.' );
  text[n] = ' '; 

  nvar = nfunc = nint = nzec = 0;
  i = 0;
  while ( i < n ) {
    if ( isdigit( text[i] ) ) { // un numar
      while ( isdigit( text[i] ) )
        i++;
      if ( text[i] == '.' ) { // punct imediat dupa cifre: zecimal
        i++;
        while ( isdigit( text[i] ) )
          i++;
        nzec++;
      } else
        nint++;
    } else if ( isalpha( text[i] ) ) { // un nume, pana la primul separator
      mare = 0;
      while ( isalnum( text[i] ) ) {
        if ( isupper( text[i] ) )
          mare = 1;
        i++;
      }
      if ( mare )
        nfunc++;
      else
        nvar++;
    } else // separator: spatiu sau punct care nu urmeaza unui intreg
      i++;
  }

  fout = fopen( "variabile.out", "w" );
  fprintf( fout, "%d\n%d\n%d\n%d\n", nvar, nfunc, nint, nzec );
  fclose( fout );

  return 0;
}
