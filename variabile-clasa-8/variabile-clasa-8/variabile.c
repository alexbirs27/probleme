// tokenizer cu variabila de stare
// citim caracterul, apoi switch pe stare... pe fiecare ramura decidem unde mergem
// in functie de caracterul curent si ultima stare
// numaram un atom cand intram in el
#include <stdio.h>
#include <ctype.h>

#define AFARA 0  // pe separatori (spatii, puncte care nu urmeaza unui int)
#define INNUM 1  // intr-un numar intreg
#define INZEC 2  // intr-un numar zecimal - dupa punct
#define INVAR 3  // intr-un nume - fara litera mare
#define INFUNC 4 // intr-un nume - cu cel putin o litera mare

int main() {
  FILE *fin, *fout;
  int ch, stare, nvar, nfunc, nint, nzec;

  nvar = nfunc = nint = nzec = 0;
  stare = AFARA;
  fin = fopen( "variabile.in", "r");
  while ( (ch =fgetc(fin)) != EOF) {
    switch (stare) {
    case AFARA:
      if ( isdigit( ch ) ) {        // incepe un numar intreg
        nint++;
        stare = INNUM;
      } else if ( islower( ch ) ) { // incepe o variabila
        nvar++;
        stare = INVAR;
      } else if ( isupper( ch ) ) { // incepe o functie
        nfunc++;
        stare = INFUNC;
      }                              // separator: ramanem AFARA
      break;
    case INNUM:
      if ( ch == '.') {           // numarul intreg devine zecimal
        nint--; // IMPORTANT
        nzec++;
        stare = INZEC;
      } else if ( islower(ch ) ) { // variabila lipita de numar
        nvar++;
        stare = INVAR;
      } else if ( isupper( ch ) ) { // functie lipita de numar
        nfunc++;
        stare = INFUNC;
      } else if ( !isdigit( ch ) )  // spatiu: numarul se termina
        stare = AFARA;
      break;
    case INZEC:
      if ( islower( ch ) ) {        // variabila lipita de numar
        nvar++;
        stare = INVAR;
      } else if ( isupper( ch ) ) { // functie lipita de numar
        nfunc++;
        stare = INFUNC;
      } else if ( !isdigit( ch ) )  // spatiu sau al doilea punct
        stare = AFARA;
      break;
    case INVAR:
      if ( isupper( ch ) ) {        // variabila numarata deja devine functie
        nvar--;
        nfunc++;
        stare = INFUNC;
      } else if ( !isalnum( ch ) )  // spatiu sau punct: numele se termina
        stare = AFARA;
      break;
    case INFUNC:
      if ( !isdigit(ch) && !isalpha(ch) )         // spatiu sau punct: numele se termina
        stare = AFARA;
      break;
    }
  }
  fclose( fin );

  fout = fopen( "variabile.out", "w" );
  fprintf( fout, "%d\n%d\n%d\n%d\n", nvar, nfunc, nint, nzec );
  fclose( fout );

  return 0;
}
