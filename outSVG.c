#include "outSVG.h"

void createOutputFileName(char **nameOut, char nameIn[]){
    int i = 0;

    *nameOut = (char *)malloc((strlen(nameIn) + 1) * sizeof(char));

    while(nameIn[i] != '.'){
        (*nameOut)[i] = nameIn[i];
        i++;
    }
}

void createOutputQryFileName(char **nameOut, char nameIn[], char nameQuery[]){
    int i = 0, j = 0;

    *nameOut = (char *)malloc((strlen(nameIn) + strlen(nameQuery)) * sizeof(char));
    while(nameIn[i] != '.'){
        (*nameOut)[i] = nameIn[i];
        i++;
        j++;
    }
    strcat(*nameOut, "-");
    i = 0;
    j++;
    while(nameQuery[i] != '.'){
        (*nameOut)[j] = nameQuery[i];
        i++;
        j++;
    }
}

/*Printa as informacoes de circulo armazenadas no vetor de struct e formatadas para SVG no arquivo SVG*/
void printCircle(FILE *arqOut, Form circle){
    fprintf(arqOut, "\n<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", getFormX(circle),
     getFormY(circle), getFormR(circle), getFormStrokeColor(circle), getFormFillColor(circle), getFormSw(circle));
}

void printTextSvg(FILE *arqOut, Form text){
    fprintf(arqOut, "\n<text x=\"%f\" y=\"%f\" stroke=\"%s\" stroke-width=\"0.5\" fill=\"%s\">%s</text>\n", getFormX(text),
     getFormY(text), getFormStrokeColor(text), getFormFillColor(text), getFormTxt(text));
}

/*Printa as informacoes de retangulo armazenadas no vetor de struct e formatadas para SVG no arquivo SVG*/
void printRect(FILE *arqOut, Form rect){

    fprintf(arqOut, "\n<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-dasharray=\"%d\" stroke-width=\"%s\"/>\n",
    getFormX(rect), getFormY(rect), getFormW(rect), getFormH(rect), getFormStrokeColor(rect), getFormFillColor(rect), getFormStroke(rect), getFormSw(rect));
}

void printRectRoundedCorners(FILE *arqOut, Form rect){

    fprintf(arqOut, "\n<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" rx=\"15\" stroke=\"%s\" fill=\"%s\" stroke-dasharray=\"%d\" stroke-width=\"%s\"/>\n",
    getFormX(rect), getFormY(rect), getFormW(rect), getFormH(rect), getFormStrokeColor(rect), getFormFillColor(rect), getFormStroke(rect), getFormSw(rect));
}

/*Printa as informacoes de texto armazenadas em variaveis locais no vetor de struct e formatadas para SVG no arquivo SVG*/
void printText(FILE *arqOut, double x, double y, char text[], char fillColor[]){

    fprintf(arqOut, "\n<text x=\"%lf\" y=\"%lf\" fill=\"%s\">%s</text>\n", x, y, fillColor, text);
}

void printTextDouble(FILE *arqOut, double x, double y, double text, char fillColor[]){

    fprintf(arqOut, "\n<text x=\"%lf\" y=\"%lf\" fill=\"%s\">%.3lf</text>\n", x, y, fillColor, text);
}

void printLine(FILE *arqOut, double x1, double y1, double x2, double y2, char color[]){

    fprintf(arqOut, "\n<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>\n", x1, y1, x2, y2, color);
}

void printBlock(FILE *arqOut, Block block){

    fprintf(arqOut, "\n<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" stroke-dasharray=\"0\" stroke-width=\"%s\"/>\n",
    getBlockX(block), getBlockY(block), getBlockW(block), getBlockH(block), getBlockStrokeColor(block), 
    getBlockFillColor(block), getBlockSw(block));
    
}

void printHydrant(FILE *arqOut, Hydrant hydrant){
    fprintf(arqOut, "\n<circle cx=\"%lf\" cy=\"%lf\" r=\"6\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", getHydrantX(hydrant), 
    getHydrantY(hydrant), getHydrantStrokeColor(hydrant), getHydrantFillColor(hydrant), getHydrantSw(hydrant));

    printText(arqOut, getHydrantX(hydrant) - 4.5, getHydrantY(hydrant) + 4, "H", getHydrantStrokeColor(hydrant));
}

void printTrafficLight(FILE *arqOut, TrafficLight tLight){
    fprintf(arqOut, "\n<rect x=\"%lf\" y=\"%lf\" width=\"10\" height=\"10\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", 
    getTrafficLightX(tLight) - 5, getTrafficLightY(tLight) - 5, getTrafficLightStrokeColor(tLight), getTrafficLightFillColor(tLight), getTrafficLightSw(tLight));

    printText(arqOut, getTrafficLightX(tLight) - 3.5, getTrafficLightY(tLight) + 4, "S", getTrafficLightStrokeColor(tLight));
}

void printRadioTower(FILE *arqOut, RadioTower rTower){
    fprintf(arqOut, "\n<circle cx=\"%lf\" cy=\"%lf\" r=\"9\" stroke=\"%s\" fill=\"%s\" stroke-width=\"%s\"/>\n", 
    getRadioTowerX(rTower), getRadioTowerY(rTower), getRadioTowerStrokeColor(rTower), getRadioTowerFillColor(rTower), getRadioTowerSw(rTower));

    printText(arqOut, getRadioTowerX(rTower) - 7.5, getRadioTowerY(rTower) + 4, "RB", getRadioTowerStrokeColor(rTower));
}
