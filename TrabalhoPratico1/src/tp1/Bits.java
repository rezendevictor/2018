package tp1;

public class Bits {
    byte[] transforma(String palavra){
           byte[] bits = new byte[128];

           int intAux, i, j;
           char charAux;
           String stringAux = null;
           StringBuilder strBuilder = new StringBuilder(128);

           for (i=0; i<16; i++){
                if(i>=palavra.length()){
                    /*
                    Caso as letras ja tenham acabado, preenche o resto do vetor com 0,
                    8 bits por vez (1 letra por vez)
                    */
                    strBuilder.append("00000000");
                }
               
               else{
                    /*
                    traduz cada char para uma string de binarios
                    e concatena essa string a stringAux
                    */
                    charAux = palavra.charAt(i);
                    stringAux = Integer.toBinaryString(charAux);
                    
                    intAux = Integer.toBinaryString(charAux).length();
                    while(intAux!=8){
                        /*
                        caso o numero em binario nao esteja em 8 bits,
                        adiciona um 0 a esquerda ate que esteja em 8 bits
                        */
                        stringAux = "0"+stringAux;
                        intAux++;
                    }
                    strBuilder.append(stringAux);  
                }     
            }
           
            stringAux = strBuilder.toString(); // para usar stringAux diretamente
            for(i=0; i<128; i++){
                /*
                percorre cada numero da stringAux, traduz ele para char, depois para byte
                subtrai 48 (pois 0 estava em 48, para ser 0)
                e coloca esse numero no vetor de bytes
                */
                charAux = stringAux.charAt(i);
                byte byteAux = (byte)charAux;
                byteAux -= 48;
                bits[i] = byteAux;
            }
           
            return bits;
    }
    
    
}
