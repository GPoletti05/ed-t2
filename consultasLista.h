#ifndef CONSULTAS_LISTA__H
#define CONSULTAS_LISTA__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "consulta.h"
#include "outSVG.h"
#include "list.h"
#include "./Objetos/forms.h"
#include "./Objetos/block.h"

/*Remove todas as quadras que estiverem inteiramente dentro do circulo e caso necessario cria retangulos com bordas arredondadas de cor fundo beige e borda olive*/
void treatDQ(FILE *arqTxt, FILE *arqSvgQ, List blocks, char id1[], Form circle, bool hash);

/*Coloca as formas do anel e circulo da consulta do dq apos o "treatDQ" para as novas formas inseridas ficarem sobrepostas*/
void printDQ(FILE *arqTxt, FILE *arqSvgQ, Form circle, bool hash);

/*Muda a cor da borda de todas as quadras que estiverem inteiramente dentro do circulo*/
void treatCBQ(FILE *arqTxt, List blocks, Form circle, char cstrk[]);

/*Muda as cores dos id informados*/
void treatPnt(FILE *arqTxt, List forms, char corb[], char corp[], char id1[]);

/*Muda as cores entre um id e outro*/
void treatPnts(FILE *arqTxt, List forms, char corb[], char corp[], char id1[], char id2[]);

/*Cria um retangulo com os formatos informados e uma reta que vai do centro desse retangulo ate a parte de cima do mapa, informa a area total das formas dentro do retangulo*/
void treatCAR(FILE *arqTxt, FILE *arqSvgQ, double x, double y, double w, double h, List blocks, List hydrants, List tLights, List rTowers);

#endif