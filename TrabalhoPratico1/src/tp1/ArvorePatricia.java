package tp1;

import java.util.ArrayList;
import java.util.Arrays;

public class ArvorePatricia {
    
    
    private ArrayList<palavras> biblioteca = new ArrayList<>();
   
    private static abstract class PatNo { }
    private static class PatNoInt extends PatNo {
        int index; PatNo esq, dir;
    }  
    private static class PatNoExt extends PatNo {
        byte[] chave; // @{\it O tipo da chave depende da aplica\c{c}\~ao}@
    }
  
    private PatNo raiz;
    private int nbitsChave;
 
  // @{\it Verifica se p \'e n\'o externo}@
    private boolean eExterno (PatNo p) {    
        Class classe = p.getClass ();
        return classe.getName().equals(PatNoExt.class.getName());
    }

    private PatNo criaNoInt (int i, PatNo esq, PatNo dir) {
        PatNoInt p = new PatNoInt ();
        p.index = i; p.esq = esq; p.dir = dir;
        return p;
    }

    private PatNo criaNoExt (byte[] b) {
        PatNoExt p = new PatNoExt ();
        p.chave = b;
        return p;
    }
  
    private void pesquisa (byte[] b, PatNo t) {
        if (this.eExterno (t)) {
            PatNoExt aux = (PatNoExt)t;
            if (Arrays.equals(aux.chave, b)) System.out.println ("Elemento encontrado");
            else System.out.println ("Elemento nao encontrado");
        }
        else { 
            PatNoInt aux = (PatNoInt)t;
            if (b[aux.index]== 0) pesquisa (b, aux.esq);
            else pesquisa (b, aux.dir);
        }
    }

    private PatNo insereEntre (byte[] b, PatNo t, int i) {
        PatNoInt aux = null; 
        if (!this.eExterno (t)) aux = (PatNoInt)t;
        if (this.eExterno (t) || (i < aux.index)) { // @{\it Cria um novo n\'o externo}@
        PatNo p = this.criaNoExt (b);
        if (b[i] == 1) return this.criaNoInt (i, t, p);
        else return this.criaNoInt (i, p, t);
        }
        else {
        if (b[aux.index] == 1) 
            aux.dir = this.insereEntre (b, aux.dir, i);
            else aux.esq = this.insereEntre (b, aux.esq, i);
        return aux;
        }
    }
  
    private PatNo insere (byte[] b, PatNo t) {
    if (t == null) return this.criaNoExt (b);
    else {
      PatNo p = t;
      while (!this.eExterno (p)) {
        PatNoInt aux = (PatNoInt)p;
        if (b[aux.index] == 1) p = aux.dir; else p = aux.esq;
      }
      PatNoExt aux = (PatNoExt)p;
      int i = 1; // @{\it acha o primeiro bit diferente}@
      while ((i <= this.nbitsChave)&& 
             (b[i] == aux.chave[i])) i++;
      if (i > this.nbitsChave) {
        System.out.println ("Erro: chave ja esta na arvore"); 
        return t;
      }
      else return this.insereEntre (b, t, i);
    }
  }
  
    private void central (PatNo pai, PatNo filho, String msg) {
        if (filho != null) {
            if (!this.eExterno (filho)) {
            PatNoInt aux = (PatNoInt)filho; 
            central (filho, aux.esq, "ESQ");
            if (pai != null)
                System.out.println ("Pai: "+ ((PatNoInt)pai).index + " " + msg+ " Int: " + aux.index);
            else System.out.println ("Pai: "+ pai + " " + msg+ " Int: " + aux.index);
            central (filho, aux.dir, "DIR");
            } else {
            PatNoExt aux = (PatNoExt)filho;
            if (pai != null)
                System.out.println ("Pai: "+ ((PatNoInt)pai).index + " " + msg+ " Ext: " + Arrays.toString(aux.chave));
            else System.out.println ("Pai: "+ pai + " " + msg+ " Ext: " + Arrays.toString(aux.chave));
            }
        }
    }

    public void imprime () {
        this.central (null, this.raiz, "RAIZ");
    }

    public ArvorePatricia (int nbitsChave) {
        this.raiz = null; this.nbitsChave = nbitsChave; 
    }
  
    public void pesquisa (byte[] b) { this.pesquisa (b, this.raiz); }
    
  
    public void insere (byte[] b) { this.raiz = this.insere (b, this.raiz); } 

    public void insere (String palavra){
        /*
        metodo para inserir com string, o metodo chama a transformacao em bits
        e chama o metodo insere com os bits em um array de bytes
        */
        Bits stringToBits = new Bits();
        byte[] aux;
        System.out.println ("Palavra: " + palavra);
        aux = stringToBits.transforma(palavra);
        //System.out.println("palavra: " + Arrays.toString(aux));
        this.insere(aux);
    }
  
    public void pesquisa (String s){
        /*
        metodo para pesquisar com string, o metodo chama a transformacao em bits
        e chama a pesquisa com os bits em um array de bytes
        */
        Bits b = new Bits();
        byte[] aux;
        aux = b.transforma(s);
        this.pesquisa(aux);
    }
    
    public void consulta_palavra(String palavra, int posicao){
        for(palavras teste : this.biblioteca){
            if(palavra == teste.getPalavras()){
                teste.apareceu(posicao);
                break;
            }else{
                palavras nova = new palavras(palavra,posicao);
                this.biblioteca.add(nova);
            }
        }
        
    }
    
}

