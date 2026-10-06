#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

// procentul de litere mari din restul unui nume de functie
#define PMAREXTRA 10
// procentul de cifre din interiorul unui nume
#define PCIFRE 30

int n, scrise; // cate caractere trebuie generate, cate am generat

void scrie( int ch ) {
  fputc( ch, stdout );
  scrise++;
}

int litMica() {
  return 'a' + rand() % 26;
}

int litMare() {
  return 'A' + rand() % 26;
}

// lungime aleatoare intre 1 si maxl, dar care incape in ce a ramas
int lungime( int maxl ) {
  int l = 1 + rand() % maxl;
  if ( l > n - scrise )
    l = n - scrise;
  return l;
}

// genereaza l cifre
void cifre( int l ) {
  int i;
  for ( i = 0; i < l; i++ )
    scrie( '0' + rand() % 10 );
}

// genereaza un numar intreg sau, daca zec si mai e loc, unul zecimal
// partea de dupa punct poate fi vida: 3. este numar zecimal
// returneaza 1 daca numarul generat este zecimal
int numar( int maxl, int zec ) {
  int l;

  cifre( lungime( maxl ) );
  if ( !zec || scrise == n )
    return 0;

  scrie( '.' );
  l = rand() % (maxl + 1);
  if ( l > n - scrise )
    l = n - scrise;
  cifre( l );
  return 1;
}

// genereaza un nume de lungime l; daca e functie, pozitia mare are sigur
// litera mare, iar celelalte litere sunt mari cu sansa PMAREXTRA
void nume( int l, int functie ) {
  int i, mare;

  mare = rand() % l;
  for ( i = 0; i < l; i++ )
    if ( functie && i == mare )
      scrie( litMare() );
    else if ( i > 0 && rand() % 100 < PCIFRE )
      scrie( '0' + rand() % 10 );
    else if ( functie && rand() % 100 < PMAREXTRA )
      scrie( litMare() );
    else
      scrie( litMica() );
}

// genereaza intre minsp si maxsp separatori, cati incap
// fiecare separator e punct cu sansa ppunct, altfel spatiu
// dupa un numar intreg primul separator e sigur spatiu, altfel punctul
// l-ar face zecimal
void separatori( int minsp, int maxsp, int ppunct, int dupaIntreg ) {
  int s = minsp + rand() % (maxsp - minsp + 1);
  while ( s-- > 0 && scrise < n ) {
    if ( !dupaIntreg && rand() % 100 < ppunct )
      scrie( '.' );
    else
      scrie( ' ' );
    dupaIntreg = 0;
  }
}

int main( int argc, char **argv ) {
  struct timeval tv;
  int maxl, pnr, pzec, plipit, pfunc, ppunct, maxsp, functie, intreg;
  int nvar, nfunc, nint, nzec;

  if ( argc < 8 ) {
    fprintf( stderr, "Usage: %s <n caractere> <lung max atom> <numere %%> <zecimale %%> <numere lipite %%> <functii %%> <puncte separator %%> [<max separatori>]\n", argv[0] );
    return 1;
  }

  gettimeofday(&tv, NULL);
  srand( (int)(tv.tv_sec * 1000 + tv.tv_usec / 1000) );

#ifdef _WIN32
  _setmode( _fileno( stdout ), _O_BINARY ); 
#endif

  sscanf( argv[1], "%d", &n );
  sscanf( argv[2], "%d", &maxl );
  sscanf( argv[3], "%d", &pnr );
  sscanf( argv[4], "%d", &pzec );
  sscanf( argv[5], "%d", &plipit );
  sscanf( argv[6], "%d", &pfunc );
  sscanf( argv[7], "%d", &ppunct );
  maxsp = 3;
  if ( argc > 8 )
    sscanf( argv[8], "%d", &maxsp );

  nvar = nfunc = nint = nzec = scrise = 0;
  separatori( 0, maxsp, ppunct, 0 ); // textul poate incepe cu separatori
  while ( scrise < n ) {
    intreg = 0;
    if ( rand() % 100 < pnr ) { // un numar, eventual lipit de un nume
      if ( numar( maxl, rand() % 100 < pzec ) )
        nzec++;
      else {
        nint++;
        intreg = 1;
      }
      if ( scrise < n && rand() % 100 < plipit ) {
        functie = rand() % 100 < pfunc;
        nume( lungime( maxl ), functie );
        if ( functie )
          nfunc++;
        else
          nvar++;
        intreg = 0;
      }
    } else { // un nume
      functie = rand() % 100 < pfunc;
      nume( lungime( maxl ), functie );
      if ( functie )
        nfunc++;
      else
        nvar++;
    }
    separatori( 1, maxsp, ppunct, intreg ); // cel putin un separator
  }

  fputc( '\n', stdout );

  fprintf( stderr, "caractere:%d variabile:%d functii:%d intregi:%d zecimale:%d\n",
           scrise, nvar, nfunc, nint, nzec );

  return 0;
}
