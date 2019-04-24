/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package atividade2.Arvore;

import Item.Item;

/**
 *
 * @author aluno
 */
public class ArvoreSBB {

    private static class No {

        Item reg;
        No esq, dir;
        byte incE, incD;
    }
    private static final byte Horizontal = 0;
    private static final byte Vertical = 1;
    private No raiz;
    private boolean propSBB;
    public int rodou = 0;
// Entram aqui os métodos privados das transparências 21, 40,

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
        rodou ++;
        if (p == null) {
            return null;
        } // Registro não encontrado
        else if (reg.compara(p.reg) < 0) {
            return pesquisa(reg, p.esq);
        } else if (reg.compara(p.reg) > 0) {
            return pesquisa(reg, p.dir);
        } else {
            return p.reg;
        }
    }

    public ArvoreSBB() {
        this.raiz = null;
        this.propSBB = true;
    }

    public Item pesquisa(Item reg) {
        return this.pesquisa(reg, this.raiz);
    }

    public void insere(Item reg) {
        this.raiz = insere(reg, null, this.raiz, true);
    }

    public void retira(Item reg) {
        this.raiz = this.retira(reg, this.raiz);
    }
// Entra aqui o método para imprimir a árvore da tranaparência 29

    public void imprime() {
        this.central(this.raiz);
    }

    private void central(No p) {
        if (p != null) {
            central(p.esq);
            System.out.println(p.reg.toString());
            central(p.dir);
        }
    }

    private No ee(No ap) {
        No ap1 = ap.esq;
        ap.esq = ap1.dir;
        ap1.dir = ap;
        ap1.incE = Vertical;
        ap.incE = Vertical;
        ap = ap1;
        return ap;
    }

    private No ed(No ap) {
        No ap1 = ap.esq;
        No ap2 = ap1.dir;
        ap1.incD = Vertical;
        ap.incE = Vertical;
        ap1.dir = ap2.esq;
        ap2.esq = ap1;
        ap.esq = ap2.dir;
        ap2.dir = ap;
        ap = ap2;
        return ap;
    }

    private No dd(No ap) {
        No ap1 = ap.dir;
        ap.dir = ap1.esq;
        ap1.esq = ap;
        ap1.incD = Vertical;
        ap.incD = Vertical;
        ap = ap1;
        return ap;
    }

    private No de(No ap) {
        No ap1 = ap.dir;
        No ap2 = ap1.esq;
        ap1.incE = Vertical;
        ap.incD = Vertical;
        ap1.esq = ap2.dir;
        ap2.dir = ap1;
        ap.dir = ap2.esq;
        ap2.esq = ap;
        ap = ap2;
        return ap;
    }

    private No insere(Item reg, No pai, No filho, boolean filhoEsq) {
        if (filho == null) {
            filho = new No();
            filho.reg = reg;
            filho.incE = Vertical;
            filho.incD = Vertical;
            filho.esq = null;
            filho.dir = null;
            if (pai != null) {
                if (filhoEsq) {
                    pai.incE = Horizontal;
                } else {
                    pai.incD = Horizontal;
                }
            }
            this.propSBB = false;
        } else if (reg.compara(filho.reg) < 0) {
            filho.esq = insere(reg, filho, filho.esq, true);
            if (!this.propSBB) {
                if (filho.incE == Horizontal) {
                    if (filho.esq.incE == Horizontal) {
                        filho = this.ee(filho); // transformação esquerda - esquerda
                        if (pai != null) {
                            if (filhoEsq) {
                                pai.incE = Horizontal;
                            } else {
                                pai.incD = Horizontal;
                            }
                        }
                    } else if (filho.esq.incD == Horizontal) {
                        filho = this.ed(filho); // transformação esquerda - direita
                        if (pai != null) {
                            if (filhoEsq) {
                                pai.incE = Horizontal;
                            } else {
                                pai.incD = Horizontal;
                            }
                        }
                    }
                } else {
                    this.propSBB = true;
                }
            }
        } else if (reg.compara(filho.reg) > 0) {
            filho.dir = insere(reg, filho, filho.dir, false);
            if (!this.propSBB) {
                if (filho.incD == Horizontal) {
                    if (filho.dir.incD == Horizontal) {
                        filho = this.dd(filho); // transformação direita - direita
                        if (pai != null) {
                            if (filhoEsq) {
                                pai.incE = Horizontal;
                            } else {
                                pai.incD = Horizontal;
                            }
                        }
                    } else if (filho.dir.incE == Horizontal) {
                        filho = this.de(filho); // transformação direita - esquerda
                        if (pai != null) {
                            if (filhoEsq) {
                                pai.incE = Horizontal;
                            } else {
                                pai.incD = Horizontal;
                            }
                        }
                    }
                } else {
                    this.propSBB = true;
                }
            }
        } else {
            System.out.println("Erro : Registro ja existente");
            this.propSBB = true;
        }
        return filho;
    }

    private No esqCurto(No ap) {
        if (ap.incE == Horizontal) {
            ap.incE = Vertical;
            this.propSBB = true;
        } else if (ap.incD == Horizontal) {
            No ap1 = ap.dir;
            ap.dir = ap1.esq;
            ap1.esq = ap;
            ap = ap1;
            if (ap.esq.dir.incE == Horizontal) {
                ap.esq = this.de(ap.esq);
                ap.incE = Horizontal;
            } else if (ap.esq.dir.incD == Horizontal) {
                ap.esq = this.dd(ap.esq);
                ap.incE = Horizontal;
            }
            this.propSBB = true;
        } else {
            ap.incD = Horizontal;
            if (ap.dir.incE == Horizontal) {
                ap = this.de(ap);
                this.propSBB = true;
            } else if (ap.dir.incD == Horizontal) {
                ap = this.dd(ap);
                this.propSBB = true;
            }
        }
        return ap;
    }

    private No dirCurto(No ap) {
        if (ap.incD == Horizontal) {
            ap.incD = Vertical;
            this.propSBB = true;
        } else if (ap.incE == Horizontal) {
            No ap1 = ap.esq;
            ap.esq = ap1.dir;
            ap1.dir = ap;
            ap = ap1;
            if (ap.dir.esq.incD == Horizontal) {
                ap.dir = this.ed(ap.dir);
                ap.incD = Horizontal;
            } else if (ap.dir.esq.incE == Horizontal) {
                ap.dir = this.ee(ap.dir);
                ap.incD = Horizontal;
            }
            this.propSBB = true;
        } else {
            ap.incE = Horizontal;
            if (ap.esq.incD == Horizontal) {
                ap = this.ed(ap);
                this.propSBB = true;
            } else if (ap.esq.incE == Horizontal) {
                ap = this.ee(ap);
                this.propSBB = true;
            }
        }
        return ap;
    }

    private No antecessor(No q, No r) {
        if (r.dir != null) {
            r.dir = antecessor(q, r.dir);
            if (!this.propSBB) {
                r = this.dirCurto(r);
            }
        } else {
            q.reg = r.reg;
            r = r.esq;
            if (r != null) {
                this.propSBB = true;
            }
        }
        return r;
    }

    private No retira(Item reg, No ap) {
        if (ap == null) {
            System.out.println("Erro : Registro nao encontrado");
            this.propSBB = true;
        } else if (reg.compara(ap.reg) < 0) {
            ap.esq = retira(reg, ap.esq);
            if (!this.propSBB) {
                ap = this.esqCurto(ap);
            }
        } else if (reg.compara(ap.reg) > 0) {
            ap.dir = retira(reg, ap.dir);
            if (!this.propSBB) {
                ap = this.dirCurto(ap);
            }
        } else { // encontrou o registro
            this.propSBB = false;
            if (ap.dir == null) {
                ap = ap.esq;
                if (ap != null) {
                    this.propSBB = true;
                }
            } else if (ap.esq == null) {
                ap = ap.dir;
                if (ap != null) {
                    this.propSBB = true;
                }
            } else {
                ap.esq = antecessor(ap, ap.esq);
                if (!this.propSBB) {
                    ap = this.esqCurto(ap);
                }
            }
        }
        return ap;
    }
}
