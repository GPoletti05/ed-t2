#include "inSVG.h"

void checkFile(FILE *arq, char fname[]){

    if(arq == NULL){
        printf("Arquivo nao encontrado: %s\n", fname);
        exit(1);
    }
}

void receiveParameters(int argc, char *argv[], char **pathIn, char **nameIn, char **nameConsulta, char **pathOut){
    int i = 1;

    while(i < argc){
        if(strcmp("-e", argv[i]) == 0){
            i++;
            *pathIn = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*pathIn, argv[i]);
        }
        else if(strcmp("-f", argv[i]) == 0){
            i++;
            *nameIn = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*nameIn, argv[i]);
        }
        else if(strcmp("-q", argv[i]) == 0){
            i++;
            *nameConsulta = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*nameConsulta, argv[i]);
        }
        else if(strcmp("-o", argv[i]) == 0){
            i++;
            *pathOut = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(*pathOut, argv[i]);
        }
        i++;
    }
}

void treatFileName(char nameIn[], char **nameInT){
    int i = 0, j = 0, save;
    bool valid = false;

    *nameInT = (char *)malloc((strlen(nameIn) + 1) * sizeof(char));
    if(nameIn[0] == '.'){
        if(nameIn[1] == '.')
            i = 2;
        else
            i = 1;
    }

    while(1){
        if(nameIn[i] == '/'){
            save = i;
            valid = true;
        }
        else if(nameIn[i] == '.' && i != 0){
            if(valid){
                save++;
                break;
            }
            else{
                strcpy(*nameInT, nameIn);
                return;
            }
        }
        i++;
    }
    while(nameIn[save] != '\0'){
        (*nameInT)[j] = nameIn[save];
        j++;
        save++;
    }
}

void allocateFileMamory(char fname[], char path[], char **arq){

    if(path[strlen(path) - 1] == '/'){
        *arq = (char *)malloc((strlen(path) + strlen(fname) + 1) * sizeof(char));
        sprintf(*arq, "%s%s", path, fname);
    }
    else{
        *arq = (char *)malloc((strlen(path) + strlen(fname) + 2) * sizeof(char));
        sprintf(*arq, "%s/%s", path, fname);
    }

}

void scanNX(FILE *arq, int *nx, int *nq, int *nh, int *ns, int *nr){

    fscanf(arq, "%d", nx);
    fscanf(arq, "%d", nq);
    fscanf(arq, "%d", nh);
    fscanf(arq, "%d", ns);
    fscanf(arq, "%d", nr);
}

void scanCircle(FILE *arqIn, List figures, char cw[]){
    char id[32];
    double r, x, y;
    char strokeColor[24], fillColor[24];

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &r);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fscanf(arqIn, "%s", strokeColor);
    fscanf(arqIn, "%s", fillColor);

    Form circle = createCircle(id, x, y, r, strokeColor, fillColor, cw);

    insertElement(figures, circle, "c");
}

void scanRect(FILE *arqIn, List figures, char rw[]){
    char id[32];
    double x, y, w, h;
    char strokeColor[24], fillColor[24];

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &w);
    fscanf(arqIn, "%lf", &h);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fscanf(arqIn, "%s", strokeColor);
    fscanf(arqIn, "%s", fillColor);

    Form rect = createRect(id, x, y, w, h, strokeColor, fillColor, 0, rw);

    insertElement(figures, rect, "r");
}

void scanTextSvg(FILE *arqIn, List figures, char tw[]){
    double x, y;
    int ver = 0;
    char id[32];
    char strokeColor[24], fillColor[24], txt[100], strokeColorDef[24], fillColorDef[24];

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    if(ver == 0){
        fscanf(arqIn, "%s", strokeColor);
        strcpy(strokeColorDef, strokeColor);
        ver++;
    }
    if(ver == 1){
        fscanf(arqIn, "%s", fillColor);
        strcpy(fillColorDef, fillColor);
        ver++;
    }
    fgets(txt, 100, arqIn);

    Form text = createText(id, x, y, strokeColorDef, fillColorDef, txt, tw);

    insertElement(figures, text, "t");
}

void scanBlock(FILE *arqIn, List blocks, char fillColor[], char strokeColor[], char sw[]){
    char cep[64];
    double x, y, w, h;

    fscanf(arqIn, "%s", cep);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fscanf(arqIn, "%lf", &w);
    fscanf(arqIn, "%lf", &h);

    Block block = createBlock(cep, x, y, w, h, strokeColor, fillColor, sw);

    insertElement(blocks, block, "q");
}

void scanHydrant(FILE *arqIn, List hydrants, char fillColor[], char strokeColor[], char sw[]){
    char id[32];
    double x, y;

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);

    Hydrant hydrant = createHydrant(id, x, y, strokeColor, fillColor, sw);

    insertElement(hydrants, hydrant, "h");
}

void scanTrafficLight(FILE *arqIn, List tLights, char fillColor[], char strokeColor[], char sw[]){
    char id[32];
    double x, y;

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);

    TrafficLight tLight = createTrafficLight(id, x, y, strokeColor, fillColor, sw);

    insertElement(tLights, tLight, "s");
}

void scanRadioTower(FILE *arqIn, List rTowers, char fillColor[], char strokeColor[], char sw[]){
    char id[32];
    double x, y;

    fscanf(arqIn, "%s", id);
    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);

    RadioTower rTower = createRadioTower(id, x, y, strokeColor, fillColor, sw);

    insertElement(rTowers, rTower, "rb");
}

void changeColor(FILE *arqIn, char fillColor[], char strokeColor[], char sw[]){

    fscanf(arqIn, "%s", sw);
    fscanf(arqIn, "%s", fillColor);
    fscanf(arqIn, "%s", strokeColor);
    
}

void changeThickness(FILE *arqIn, char cw[], char rw[]){

    fscanf(arqIn, "%s", cw);
    fscanf(arqIn, "%s", rw);
}

void scanText(FILE *arqIn, FILE *arqOut, FILE *arqOut2){
    double x, y;
    char text[128];

    fscanf(arqIn, "%lf", &x);
    fscanf(arqIn, "%lf", &y);
    fgets(text, 128, arqIn);

    printText(arqOut, x, y, text, "black");
    if(arqOut2 != NULL)
        printText(arqOut2, x, y, text, "black");
}

void scanO(FILE *arqQuery, char j[], char k[]){

    fscanf(arqQuery, "%s", j);
    fscanf(arqQuery, "%s", k);
}

void scanPnt(FILE *arqQuery, char j[], char corb[], char corp[]){
    fscanf(arqQuery, "%s", j);
    fscanf(arqQuery, "%s", corb);
    fscanf(arqQuery, "%s", corp);
}

void scanPnts(FILE *arqQuery, char j[], char k[], char corb[], char corp[]){
    fscanf(arqQuery, "%s", j);
    fscanf(arqQuery, "%s", k);
    fscanf(arqQuery, "%s", corb);
    fscanf(arqQuery, "%s", corp);
}

void scanI(FILE *arqQuery, char j[], double *x, double *y){

    fscanf(arqQuery, "%s", j);
    fscanf(arqQuery, "%lf", x);
    fscanf(arqQuery, "%lf", y);
}

void scanDQ(FILE *arqQuery, bool *hash, char id[], double *r){
    char hashVer[50];

    fscanf(arqQuery, "%s", hashVer);
    if(!strcmp(hashVer, "#")){
        *hash = true;
        fscanf(arqQuery, "%s", id);
        fscanf(arqQuery, "%lf", r);
    }
    else{
        *hash = false;
        strcpy(id, hashVer);
        fscanf(arqQuery, "%lf", r);
    }
}

Element scanCBQ(FILE *arqQuery, char cstrk[]){
    double x, y, r;

    fscanf(arqQuery, "%lf", &x);
    fscanf(arqQuery, "%lf", &y);
    fscanf(arqQuery, "%lf", &r);
    fscanf(arqQuery, "%s", cstrk);

    Form circle = createCircle("0", x, y, r, "black", "none", "1");

    return circle;
}

void scanCAR(FILE *arqQuery, double *x, double *y, double *w, double *h){

    fscanf(arqQuery, "%lf", x);
    fscanf(arqQuery, "%lf", y);
    fscanf(arqQuery, "%lf", w);
    fscanf(arqQuery, "%lf", h);
}