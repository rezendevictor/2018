/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ArvoreBinaria;

import Item.Item;

/**
 *
 * @author aluno
 */
public class ArvoreBinaria {

    private static class No {

        Item reg;
        No esq, dir;
    }

    //Codigos Retirados de Algoritmos e Estruturas de dados de Nivio Ziviani
    //Encontrado em : http://www2.dcc.ufmg.br/livros/algoritmos-java/cap5/transp/completo1/cap5.pdf
    private No raiz;
    public int rodou = 0;

    public ArvoreBinaria() {
        this.raiz = null;
    }

    private No insere(Item reg, No p) {
        if (p == null) {
            p = new No();
            p.reg = reg;
            p.esq = null;
            p.dir = null;
        } else if (reg.compara(p.reg) < 0) {
            p.esq = insere(reg, p.esq);
        } else if (reg.compara(p.reg) > 0) {
            p.dir = insere(reg, p.dir);
        } else {
            System.out.println("Erro : Registro ja existente");
        }
        return p;
    }

    private Item pesquisa(Item reg, No p) {
        rodou++;
        if (p == null) {
            return null;
        } // Registro não encontrado
        else if (reg.compara(p.reg) < 0) {
            return pesquisa(reg, p.esq); // se menor, vai para esquerda
        } else if (reg.compara(p.reg) > 0) {
            return pesquisa(reg, p.dir); // se maior vai para direita
        } else {
            return p.reg;
        }

    }

    private No antecessor(No q, No r) {
        if (r.dir != null) {
            r.dir = antecessor(q, r.dir);
        } else {
            q.reg = r.reg;
            r = r.esq;
        }
        return r;
    }

    public No retira(Item reg, No p) {
        if (p == null) {
            System.out.println("Erro : Registro nao encontrado");
        } else if (reg.compara(p.reg) < 0) {
            p.esq = retira(reg, p.esq);
        } else if (reg.compara(p.reg) > 0) {
            p.dir = retira(reg, p.dir);
        } else {
            if (p.dir == null) {
                p = p.esq;
            } else if (p.esq == null) {
                p = p.dir;
            } else {
                p.esq = antecessor(p, p.esq);
            }
        }
        return p;
    }

    public Item pesquisa(Item reg) {
        return this.pesquisa(reg, this.raiz);
    }

    public void insere(Item reg) {
        this.raiz = this.insere(reg, this.raiz);
    }

    public void retira(Item reg) {
        rodou++;
        this.raiz = this.retira(reg, this.raiz);
    }
    
    public No getRaiz() {
        return raiz;
    }

}
