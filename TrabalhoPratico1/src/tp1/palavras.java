/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tp1;

import java.util.ArrayList;

/**
 *
 * @author victor
 */
public class palavras {
     private String palavras;
    ArrayList<Integer> posicoes = new ArrayList<>();

    public String getPalavras() {
        return palavras;
    }

    public void setPalavras(String palavras) {
        this.palavras = palavras;
    }
     
     public palavras (String palavras,int posicao){
         this.palavras = palavras;
         this.posicoes.add(posicao);
     }
    
     public void apareceu(int posicao){
       this.posicoes.add(posicao);  
     }
    
    
}
