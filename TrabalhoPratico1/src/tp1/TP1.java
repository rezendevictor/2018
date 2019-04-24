package tp1;

import java.util.Arrays;

public class TP1 {

    /**
     * @param args the command line arguments
     * Passar os arquivos .txt (arq a ser lido e 'delimitadores' como parametro
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
       
        try {
            int posicao = 0;
            ArvorePatricia arvore = new ArvorePatricia(128); // parametro e o num bits das chaves
            ExtraiPalavra palavras = new ExtraiPalavra ("delimitadores.txt", "teste.txt");
            String palavra = null; int i = 1;
            while ((palavra = palavras.proximaPalavra())!=null){
                arvore.insere(palavra);
                arvore.consulta_palavra(palavra, posicao);
                posicao++;
            }
            System.out.println("Pesquisa: bagalha");
            arvore.pesquisa("bagalha");
            System.out.println("Pesquisa: baanana");
            arvore.pesquisa("baanana");
            palavras.fecharArquivos();
        } catch (Exception e) {System.out.println ("??" + e.getMessage ());}    
    }
}
