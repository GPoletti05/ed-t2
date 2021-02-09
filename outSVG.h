#ifndef OUT_SVG
#define OUT_SVG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Objetos/forms.h"
#include "./Objetos/block.h"
#include "./Objetos/hydrant.h"
#include "./Objetos/traffic_light.h"
#include "./Objetos/radio_tower.h"

/*Nesse header encontra-se todas as funcoes relacionadas a saida de dados*/

/*Aloca memoria e recebe o nome do arquivo de saida em questao*/
void createOutputFileName(char **nameOut, char nameIn[]);

/*Aloca memoria e recebe o nome do arquivo de saida em questao, alem de tratar o '-'*/
void createOutputQryFileName(char **nameOut, char nameIn[], char nameQuery[]);

/*Recebe como parametros as informacoes para desenhar um circulo em um arquivo SVG*/
void printCircle(FILE *arqOut, Form circle);

/*Recebe como parametros as informacoes para desenhar um texto em um arquivo SVG*/
void printTextSvg(FILE *arqOut, Form text);

/*Recebe como parametros as informacoes para desenhar um retangulo em um arquivo SVG*/
void printRect(FILE *arqOut, Form rect);

/*Recebe como parametros as informacoes para desenhar um retangulo com bordas arredondadas em um arquivo SVG*/
void printRectRoundedCorners(FILE *arqOut, Form rect);

/*Recebe como parametros as informacoes para desenhar um texto em um arquivo SVG*/
void printText(FILE *arqOut, double x, double y, char text[], char fillColor[]);

/*Recebe como parametros as informacoes para desenhar um texto (com o text em formato double) em um arquivo SVG*/
void printTextDouble(FILE *arqOut, double x, double y, double text, char fillColor[]);

/*Recebe como parametros as informacoes para desenhar uma linha em um arquivo SVG*/
void printLine(FILE *arqOut, double x1, double y1, double x2, double y2, char color[]);

/*Recebe como parametros as informacoes para desenhar uma quadra em um arquivo SVG*/
void printBlock(FILE *arqOut, Block block);

/*Recebe como parametros as informacoes para desenhar um hidrante em um arquivo SVG*/
void printHydrant(FILE *arqOut, Hydrant hydrant);

/*Recebe como parametros as informacoes para desenhar um semaforo em um arquivo SVG*/
void printTrafficLight(FILE *arqOut, TrafficLight tLight);

/*Recebe como parametros as informacoes para desenhar uma radio-base em um arquivo SVG*/
void printRadioTower(FILE *arqOut, RadioTower rTower);

#endif