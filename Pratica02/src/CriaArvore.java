/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import ArvoreBinaria.Gravar;
import Item.Item;
import atividade2.Arvore.ArvoreSBB;
import java.util.ArrayList;
import java.util.Random;

/**
 *
 * @author aluno
 */
public class CriaArvore {

    public static void main(String[] args) throws Exception {

        ArvoreSBB dicionario = new ArvoreSBB();

        Random rand = new Random();
        ArrayList<Integer> numbers = new ArrayList<Integer>();
        ArrayList<Integer> comparacoes = new ArrayList<Integer>();
        ArrayList<Double> time = new ArrayList<Double>();

        Gravar teste = new Gravar();

        int insert; //numero a ser inserido
        int NUM_MAX;
        double relogio;

        for (NUM_MAX = 10000; NUM_MAX != 110000; NUM_MAX = NUM_MAX + 10000) { // Executa de 1k em 1k
            for (insert = 0; insert < NUM_MAX; insert++) { //gera os numeros
                numbers.add(insert); // insere os numeros no Arraylist
            }
            for (int a : numbers) {
                Item item = new Item(a);
                dicionario.insere(item);
            } // arvore construida

            relogio = System.nanoTime();
            //Comparacoes feitas aqui

            Item inexiste = new Item(NUM_MAX + 1);
            dicionario.pesquisa(inexiste);

            //*****************************************
            comparacoes.add(dicionario.rodou - 1);
            dicionario.rodou = 0;
            time.add((double) System.nanoTime() - relogio);

            for (int a : numbers) {
                Item retirado = new Item(a);
                dicionario.retira(retirado);
            }//limpa arvore

            numbers.clear(); // limpa os numeros;

        }

        teste.ler(comparacoes, time);

       
    }
}
