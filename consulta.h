#ifndef CONSULTA__H
#define CONSULTA__H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "outSVG.h"
#include "./Objetos/forms.h"
#include "list.h"

/*Nesse header encontra-se todas as funcoes relacionadas ao arquivo de consulta(.qry), aqui são feitas as verificacoes
e os calculos matematicos*/

/*Calcula a distancia euclidiana entre dois pontos*/
double distEuclid(double x1, double y1, double x2, double y2);

/*Determina a coordenada(x ou y), pertencente a um certo intervalo, mais proxima de uma coordenada(x ou y)*/
double clamp(double xC, double min, double max);

/*Verifica se uma figura (c ou r) esta colidindo com outra (c ou r)*/
void treatO(FILE *arqTxt, FILE *arqSvgQ, Form figure1, Form figure2, char type1[], char type2[]);

/*Verifica se um ponto esta dentro de um circulo, retangulo ou quadra*/
bool pointInsideFigure(double x, double y, Element element, char type[], char side[]);

/*Verifica se um ponto (x,y) esta dentro ou fora de uma figura (c ou r)*/
void treatI(FILE *arqTxt, FILE *arqSvgQ, Form figure, double x, double y, char type[]);

/*Desenha um retangulo que envolve dois circulos(continuo em caso de colisao, tracejado caso contrario)*/
void rectSurroundsCircle(FILE *arqSvgQ, Form figure1, Form figure2, bool collision);

/*Desenha um retangulo que envolve dois retangulos(continuo em caso de colisao, tracejado caso contrario)*/
void rectSurroundsRect(FILE *arqSvgQ, Form figure1, Form figure2, bool collision);

/*Desenha um retangulo que envolve um circulo e um retangulo(continuo em caso de colisao, tracejado caso contrario)*/
void rectSurroundsCircleAndRect(FILE *arqSvgQ, Form figure1, Form figure2, bool collision);

/*Retorna true se a quadra esta inteiramente dentro do circulo, false caso contrario*/
bool quadInsideCirc(Block block, Form circle, char side[]);

/*Retorna true se uma quadra esta inteiramente dentro de um retangulo, false caso contrario*/
bool quadInsideRect(Block block, Form rect);

/*Retorna true se um semaforo esta inteiramente dentro de um retangulo, false caso contrario*/
bool tlightInsideRect(TrafficLight tLight, Form rect);

/*Retorna true se uma radio base esta inteiramente dentro de um retangulo, false caso contrario*/
bool rTowerInsideRect(RadioTower rtower, Form rect);

/*Retorna true se um hidrante esta inteiramente dentro de um retangulo, false caso contrario*/
bool hydrantInsideRect(Hydrant hydrants, Form rect);

#endif
