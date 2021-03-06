#include "list.h"

#define NULO -1

typedef struct{
    Element element;
    char type[4];
    int previous, next;
}NodeImp;

typedef struct stList{
    NodeImp *node;
    int start, end;
    int free, size, maxSize;
}*ListImp;

List createList(int capacity){

    ListImp list = (ListImp) malloc(sizeof(struct stList));

    list->node = (NodeImp*) malloc(capacity * sizeof(NodeImp));
    list->maxSize = capacity;

    for(int i = 0; i < list->maxSize; i++){
        list->node[i].next = i + 1;
    }


    list->node[list->maxSize - 1].next = NULO;
    list->start = NULO;
    list->end = NULO;
    list->free = 0;
    list->size = 0;

    return list;
}

int getFirst(List listAux){
    ListImp list = (ListImp) listAux;

    if(!list->size)
        return NULO;

    return list->start;
}

int getNulo(){

    return NULO;
}

int getNext(List listAux, int i){
    ListImp list = (ListImp) listAux;

    return list->node[i].next;
}

int getPrevious(List listAux, int i){
    ListImp list = (ListImp) listAux;

    return list->node[i].previous;
}

int getFree(List listAux){
    ListImp list = (ListImp) listAux;
    int iFree;

    iFree = list->free;

    list->free = list->node[list->free].next;

    return iFree;
}

int getSize(List listAux){
    ListImp list = (ListImp) listAux;

    return list->size;
}

int getLast(List listAux){
    ListImp list = (ListImp) listAux;

    if(!list->size)
        return NULO;

    return list->end;
}

void insertElement(List listAux, Element element, char type[]){
    ListImp list = (ListImp) listAux;
    int iFree = getFree(listAux);
    if(list->size + 1 <= list->maxSize){
        if(list->start == NULO){
            list->node[iFree].element = element;
            list->node[iFree].next = NULO;
            list->node[iFree].previous = NULO;
            strcpy(list->node[iFree].type, type);
            list->start = 0;
            list->end = 0;
        }
        else{
            list->node[iFree].element = element;
            list->node[iFree].next = NULO;
            list->node[iFree].previous = list->end;
            strcpy(list->node[iFree].type, type);
            list->node[list->end].next = iFree;
            list->end = iFree;
        }
        list->size++;
    }
}

void insertBefore(List listAux, Element element, int index){
    ListImp list = (ListImp) listAux;
    int free = getFree(list);

    if(free == NULO){
        return;
    }

    if(list->size + 1 <= list->maxSize){
        if(list->node[index].previous == NULO){
            list->start = free;
        }
        list->node[free].next = index;
        list->node[free].previous = list->node[index].previous;
        list->node[free].element = element;
        list->node[index].previous = free;
        list->node[list->node[index].previous].next = free;
        list->size++;
    }
}

void insertAfter(List listAux, Element element, int index){
    ListImp list = (ListImp) listAux;
    int free = getFree(list);

    if(free == NULO){
        return;
    }

    if(list->size + 1 <= list->maxSize){
        if(list->node[index].next == NULO){
            list->end = free;
        }
        list->node[free].next = list->node[index].next;
        list->node[free].previous = index;
        list->node[free].element = element;
        list->node[index].next = free;
        list->node[list->node[index].next].previous = free;
        list->size++;
    }
}

void treatDelf(FILE *arqText, List listAux, char id[]){
    ListImp list = (ListImp) listAux;
    int index;

    for(int i = list->start; i != NULO; i = list->node[i].next){
        if(!strcmp(getFormId(list->node[i].element), id)){
            index = i;
            break;
        }
    }

    fprintf(arqText, "delf %s\n", id);

    if(!strcmp(list->node[index].type, "c")){
        fprintf(arqText, "%s %s %lf %lf %lf %s %s\n\n",list->node[index].type, id, getFormR(list->node[index].element), getFormX(list->node[index].element),getFormY(list->node[index].element), getFormStrokeColor(list->node[index].element), getFormFillColor(list->node[index].element));
    }
    else if(!strcmp(list->node[index].type, "t")){
        fprintf(arqText, "%s %s %lf %lf %s %s %s\n\n", list->node[index].type, id, getFormX(list->node[index].element),getFormY(list->node[index].element), getFormStrokeColor(list->node[index].element), getFormFillColor(list->node[index].element), getFormTxt(list->node[index].element));
    }
    else if(!strcmp(list->node[index].type, "r")){
        fprintf(arqText, "%s %s %lf %lf %lf %lf %s %s\n\n", list->node[index].type, id, getFormW(list->node[index].element),getFormH(list->node[index].element), getFormX(list->node[index].element), getFormY(list->node[index].element),getFormStrokeColor(list->node[index].element), getFormFillColor(list->node[index].element));
    }

    strcpy(list->node[index].type, "x");
}

void treatDelfs(FILE *arqText, List listAux, char id[], char id2[]){
    ListImp list = (ListImp) listAux;
    int begin = atoi(id), final = atoi(id2), index;

    fprintf(arqText, "delf* %s %s\n", id, id2);

    for(int i = begin; i <= final; i++){
        index = i;
        if(!strcmp(list->node[index].type, "c")){
            fprintf(arqText, "%s %d %lf %lf %lf %s %s\n\n",list->node[index].type, index, getFormR(list->node[index].element), getFormX(list->node[index].element),getFormY(list->node[index].element), getFormStrokeColor(list->node[index].element), getFormFillColor(list->node[index].element));
        }
        else if(!strcmp(list->node[index].type, "t")){
            fprintf(arqText, "%s %d %lf %lf %s %s %s\n\n", list->node[index].type, index, getFormX(list->node[index].element),getFormY(list->node[index].element), getFormStrokeColor(list->node[index].element), getFormFillColor(list->node[index].element), getFormTxt(list->node[index].element));
        }
        else if(!strcmp(list->node[index].type, "r")){
            fprintf(arqText, "%s %d %lf %lf %lf %lf %s %s\n\n", list->node[index].type, index, getFormW(list->node[index].element),getFormH(list->node[index].element), getFormX(list->node[index].element), getFormY(list->node[index].element),getFormStrokeColor(list->node[index].element), getFormFillColor(list->node[index].element));
        }   
        strcpy(list->node[i].type, "x");
    }
}

void deleteElement(List listAux, char id[]){
    ListImp list = (ListImp) listAux;
    int index;

    for(int i = list->start; i != NULO; i = list->node[i].next){
        if(!strcmp(getBlockCep(list->node[i].element), id)){
            index = i;
            break;
        }
    }

    if(index == list->start){
        list->start = list->node[index].next;
        list->node[list->node[index].next].previous = NULO;
    }
    else if(list->node[index].next == NULO){
        list->end = list->node[index].previous;
        list->node[list->end].next = NULO;
    }
    else{
        list->node[list->node[index].previous].next = list->node[index].next;
        list->node[list->node[index].next].previous = list->node[index].previous;
    }
    list->node[index].next = list->free;
    list->free = index;
    list->size--;
    free(list->node[index].element);
}

Element getElementByIndex(List listAux, int i){
    ListImp list = (ListImp) listAux;

    return list->node[i].element;
}

Element getElementById(List listAux, char id[], char type[]){
    ListImp list = (ListImp) listAux;

    for(int i = list->start; i != NULO; i = list->node[i].next){
        if(!strcmp(getFormId(list->node[i].element), id)){
            strcpy(type, list->node[i].type);
            return list->node[i].element;
        }
    }

    return NULL;
}

Element getElementByIdInLists(List list1, List list2, List list3, List list4, char id[], char type[]){
    Element element;

    element = getElementById(list1, id, type);
    if(element == NULL)
        element = getElementById(list2, id, type);
    if(element == NULL)
        element = getElementById(list3, id, type);
    if(element == NULL)
        element = getElementById(list4, id, type);

    return element;
}

void printList(List listAux, FILE *arqOut){
    ListImp list = (ListImp) listAux;

    for(int i = list->start; i != NULO; i = list->node[i].next){
        if(!strcmp(list->node[i].type, "c")){
            printCircle(arqOut, list->node[i].element);
        }
        if(!strcmp(list->node[i].type, "r")){
            printRect(arqOut, list->node[i].element);
        }
        else if(!strcmp(list->node[i].type, "t")){
            printTextSvg(arqOut, list->node[i].element);
        }
        else if(!strcmp(list->node[i].type, "q")){
            printBlock(arqOut, list->node[i].element);
        }
        else if(!strcmp(list->node[i].type, "h")){
            printHydrant(arqOut, list->node[i].element);
        }
        else if(!strcmp(list->node[i].type, "s")){
            printTrafficLight(arqOut, list->node[i].element);
        }
        else if(!strcmp(list->node[i].type, "rb")){
            printRadioTower(arqOut, list->node[i].element);
        }
    }
}

void deallocateList (List listAux, void (*freeElement)(Element element)){
    ListImp list = (ListImp) listAux;

    if (list->start == NULO){
        free(list->node);
        free(list);
        return;
    }

    int i = list->start;
    while(1){
        if(list->node[i].next == NULO){
            freeElement(list->node[i].element);
            free(list->node);
            free(list);
            break;
        }
        else{
            i = list->node[i].next;
            freeElement(list->node[list->node[i].previous].element);
        }
    }
}