package tp1;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
public class Item{
  private byte[] chave;
  
  
  
  // @{\it outros componentes do registro}@

  
  public Item (byte[] chave) { this.chave = chave; }
 

  
  
  public int compara (Item it) {
    Item item = (Item) it;
    for(int i = 0; i<128; i++){
        if (this.chave[i] < item.chave[i]) return -1;
        else if (this.chave[i] > item.chave[i]) return 1;
    }
        return 0;
    
    }
  
  public void alteraChave (Object chave) {
    String ch = (String) chave; 
     this.chave = ch.getBytes()  ;
  }
  
  public Object recuperaChave () { return new String (this.chave); }
  
  public String toString () { return "" + this.chave; }
  
  public void gravaArq (RandomAccessFile arq) throws IOException {
    arq.write(chave);
  }
  
  public void leArq (RandomAccessFile arq) throws IOException {
    this.chave = Files.readAllBytes((Path) arq);
  }
 
  public static int tamanho () { return 128; /* @{\it 4 bytes}@ */ }
}