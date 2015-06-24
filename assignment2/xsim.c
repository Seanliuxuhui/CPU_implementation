#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define X_INSTRUCTIONS_NOT_NEEDED
#include "xis.h"
#include "xcpu.h"

#define TICK_ARG 1
#define IMAGE_ARG 2
#define INTERRUP_ARG 3

int main( int argc, char **argv ) {

  FILE *fp;
  struct stat fs;
  xcpu cs;
  unsigned char *mem;
  int ticks;
  int interrupt;
  unsigned int i;
  unsigned int j;
  
  if( ( argc < 4 ) || ( sscanf( argv[TICK_ARG], "%d", &ticks ) != 1 ) ||
      ( ticks < 0 )|| (sscanf(argv[INTERRUP_ARG], "%d", &interrupt ) != 1) ) {
    printf( "usage: xsim <ticks> <obj file>\n" );
    printf( "      <ticks> is number instructions to execute (0 = forever)\n" );
    printf( "      <image file> xis object file created by or xasxld\n" );
    return 1;
  }
  
  mem = (unsigned char *)malloc( XIS_MEM_SIZE );
  if( !mem ) {
    printf( "error: memory allocation (%d) failed\n", XIS_MEM_SIZE );
    exit( 1 );
  }
  memset( mem, I_BAD, XIS_MEM_SIZE );
  
  if( stat( argv[IMAGE_ARG], &fs ) ) {
    printf( "error: could not stat image file %s\n", argv[IMAGE_ARG] );
    return 1;
  } else if( fs.st_size > XIS_MEM_SIZE ) {
    printf( "Not enough memory to run all the programs." );
    return 1;
  }

  fp = fopen( argv[IMAGE_ARG], "rb" );
  if( !fp ) {
    printf( "error: could not open image file %s\n", argv[IMAGE_ARG] );
    return 1;
  } else if( fread( mem, 1, fs.st_size, fp ) != fs.st_size ) {
    printf( "error: could not read file %s\n", argv[IMAGE_ARG] );
    return 1;
  }
  fclose( fp );

  memset( &cs, 0, sizeof( xcpu ) );
  cs.memory = mem;
  
  for( i = 0; ( ticks < 1 ) || ( i < ticks ); i++ ) {
    if( (interrupt != 0)&& (i % interrupt == 0 ) && ( i != 0)){
       // fprintf(stdout,"round times : %d\n", i);
     if( !(xcpu_exception(&cs, X_E_INTR) ) ){
          fprintf(stdout,"Exception error, CPU has halted.\n"); 
          return 0;
       }
     }
    if( !xcpu_execute( &cs ) ) {
      printf( "CPU has halted.\n" );
      return 0;
    }
  }

  printf( "CPU ran out of time.\n" );
  return 0;
}


