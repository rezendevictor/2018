////////////////////////////////////////////////////////////////
// FEITO POR: VICTOR FRANCO REZENDE E JOAO LUCAS LOPES  ////////
// DATA INICIAL ;  05/06/18  ///////////////////////////////////
// ULTIMA ALTERACAO; 05/06/18 //////////////////////////////////
////////////////////////////////////////////////////////////////


#include <stdio.h>


#define K 0.25
#define na 2
#define w 19.5648284

int main(int argc, char const *argv[]) {

  //Variavies
  double a, b, h, Vne, VN;
  a = 24.83;
  b = 256.78 ;
  h = 209.4 ;
  Vne = 0 ;
  VN = 0 ;


  //abrindo arquivos
  FILE *position;
  position = fopen( "aero.csv" , "w");
  if(position == NULL){
    printf("Arquivo inexistente!\n");
  }

  // 0 < a < 25
  for(a = 0; a <= 25; a++ ){
    // 200 < b < 300

    fprintf(position, " a ; %f \n" , a );
    fprintf(position, " b ; h ; Vn \n");

    for(b = 200; b <= 300; b++ ){
      // 160 < h < 250
      for(h = 160; h <= 250 ; h++){
        double X = (K*na*w*h);
        double N = (26.1*b);
        double Bz = (-2*b);
        double Az = (2*a);

        Vne = (X-N)/( Bz - Az );

        fprintf(position, "%f ; %f ; %f\n", b, h,Vne );

      }
    }
    fprintf(position, "FIM\n" );
  }
  fclose(position);
  //b*VN - a*Vn - k*na*w*h = 0

  return 0;
}
