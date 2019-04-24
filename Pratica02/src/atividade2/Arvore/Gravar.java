/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ArvoreBinaria;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

/**
 *
 * @author aluno
 */
public class Gravar {

    public void ler(ArrayList<Integer> numbers, ArrayList<Double> time) {
        System.out.println("Comparacoes :");

        for (int a : numbers) {
            System.out.println(a + "; ");
        }

        System.out.println("Tempos :");
        for (double a : time) {
            System.out.println(a + "; ");
        }

    }

}
