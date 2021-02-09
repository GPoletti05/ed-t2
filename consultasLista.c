#include "consultasLista.h"

void treatDQ(FILE *arqTxt, FILE *arqSvgQ, List blocks, char id1[], Form circle, bool hash){
    Block block;
    Form rectRoundCorners;
    int tam = getSize(blocks);

    fprintf(arqTxt, "dq %s %lf\n", id1, getFormR(circle));
    fprintf(arqTxt, "\tEquipamento Urbano: %s (%lf %lf)\n", id1, getFormX(circle), getFormY(circle));

    if(hash == false){
        for(int i = 0; i < tam; i++){
            block = getElementByIndex(blocks, i);
            if(quadInsideCirc(block, circle, "de")){
                fprintf(arqTxt, "\tQuadra Removida: %s\n", getBlockCep(block));
                deleteElement(blocks, getBlockCep(block));
            }
        }
    }

    else{
        for(int i = 0; i < tam; i++){
            block = getElementByIndex(blocks, i);
            if(quadInsideCirc(block, circle, "de")){
                fprintf(arqTxt, "\tQuadra Removida: %s\n", getBlockCep(block));
                Form rectRoundCorners = createRect("0", getBlockX(block), getBlockY(block), getBlockW(block), getBlockH(block), "olive", "beige", 0, "5");
                printRectRoundedCorners(arqSvgQ, rectRoundCorners);
                deleteElement(blocks, getBlockCep(block));
            }
        }

    }
}

void printDQ(FILE *arqTxt, FILE *arqSvgQ, Form circle, bool hash){
    Form ring1 = createCircle("0", getFormX(circle), getFormY(circle), 18, "blue", "none", "5");
    Form ring2 = createCircle("0", getFormX(circle), getFormY(circle), 13, "lightblue", "none", "5");

    printCircle(arqSvgQ, ring1);
    printCircle(arqSvgQ, ring2);
    printCircle(arqSvgQ, circle);

    free(ring1);
    free(ring2);
}

void treatPnt(FILE *arqText, List forms, char corb[], char corp[], char id1[]){
    Form form;
    int i = atoi(id1);
    form = getElementByIndex(forms, i);

    double xF = getFormX(form);
    double yF = getFormY(form);

    fprintf(arqText, "pnt %d %s %s\nx:%lf y:%lf\n\n", i, corp, corb, xF, yF);

    setFormCorbCorp(form, corb, corp);
}

void treatPnts(FILE *arqText, List forms, char corb[], char corp[], char id1[], char id2[]){
    Form form;

    int begin = atoi(id1), final = atoi(id2), i;

    for(i = begin;i <=final;i++){

        form = getElementByIndex(forms, i);

        double xF = getFormX(form);
        double yF = getFormY(form);

        fprintf(arqText, "pnt %d %s %s\nx:%lf y:%lf\n\n", i, corp, corb, xF, yF);

        setFormCorbCorp(form, corb, corp);
    }
}

void treatCAR(FILE *arqTxt, FILE *arqSvgQ, double x, double y, double w, double h, List blocks, List hydrants, List tLights, List rTowers){
    char strokeColorR[24], fillColorR[24];
    double areaTotal = 0;
    Block block;
    Hydrant hydrant;
    TrafficLight tLight;
    RadioTower rTower;

    strcpy(strokeColorR, "red");
    strcpy(fillColorR, "none");

    Form rect = createRect("0", x, y, w, h, strokeColorR, fillColorR, 0, "5");

    printRect(arqSvgQ, rect);

    for(int i = getFirst(blocks); i != getNulo(); i = getNext(blocks, i)){
        block = getElementByIndex(blocks, i);
        if(quadInsideRect(block, rect)){
            areaTotal = areaTotal + getBlockW(block) * getBlockH(block);
            printTextDouble(arqSvgQ, getBlockX(block) + getBlockW(block) / 2, getBlockY(block) + getBlockH(block) / 2,  (getBlockW(block) * getBlockH(block)), "pink");
            fprintf(arqTxt, "Cep: %s Area: %lf\n", getBlockCep(block), (getBlockW(block) * getBlockH(block)));
            
        }
    }

    for(int i = getFirst(hydrants); i != getNulo(); i = getNext(hydrants, i)){
        hydrant = getElementByIndex(hydrants, i);
        if(hydrantInsideRect(hydrants, rect)){
            areaTotal = areaTotal + (3.14 * 36);            
        }
        
    }

    for(int i = getFirst(tLights); i != getNulo(); i = getNext(tLights, i)){
        tLight = getElementByIndex(tLights, i);
        if(tlightInsideRect(tLights, rect)){
            areaTotal = areaTotal + (100);            
        }
        
    }

    for(int i = getFirst(rTowers); i != getNulo(); i = getNext(rTowers, i)){
        rTower = getElementByIndex(rTowers, i);
        if(rTowerInsideRect(tLight, rect)){
            areaTotal = areaTotal + (3.14 * 81);            
        }
        
    }

    fprintf(arqTxt, "Area total: %lf\n", areaTotal);

    printLine(arqSvgQ, x+w/2, y+h/2,  x+w/2, 0, "red");

    printTextDouble(arqSvgQ,  x+w/2,  10,  areaTotal, "black");


    free(rect);
}

void treatCBQ(FILE *arqTxt, List blocks, Form circle, char cstrk[]){
    Block block;
    
    fprintf(arqTxt, "cbq %lf %lf %lf %s\n", getFormX(circle), getFormY(circle), getFormR(circle), cstrk);
    for(int i = getFirst(blocks); i != getNulo(); i = getNext(blocks, i)){
        block = getElementByIndex(blocks, i);
        if(quadInsideCirc(block, circle, "de")){
            setBlockStrokeColor(block, cstrk);
            fprintf(arqTxt, "\tCor da borda da quadra alterada: %s\n", getBlockCep(block));
        }
    }
}

