#include "block.h"

typedef struct stBlock{
    char cep[32], strokeColor[24], fillColor[24], sw[12];
    double x, y, w, h;
}*BlockImp;

Block createBlock(char cep[], double x, double y, double w, double h, char strokeColor[], char fillColor[], char sw[]){
    BlockImp block = (BlockImp)malloc(sizeof(struct stBlock));

    strcpy(block->cep, cep);
    block->x = x;
    block->y = y;
    block->w = w;
    block->h = h;
    strcpy(block->strokeColor, strokeColor);
    strcpy(block->fillColor, fillColor);
    strcpy(block->sw, sw);

    return block;
}

char *getBlockCep(Block b){
    BlockImp block = (BlockImp) b;

    return block->cep;
}

double getBlockX(Block b){
    BlockImp block = (BlockImp) b;

    return block->x;
}

double getBlockY(Block b){
    BlockImp block = (BlockImp) b;

    return block->y;
}

double getBlockW(Block b){
    BlockImp block = (BlockImp) b;

    return block->w;
}

double getBlockH(Block b){
    BlockImp block = (BlockImp) b;

    return block->h;
}

char *getBlockStrokeColor(Block b){
    BlockImp block = (BlockImp) b;
    //printf("Stroke color: %s\n ", block->strokeColor);
    return block->strokeColor;
}

char *getBlockFillColor(Block b){
    BlockImp block = (BlockImp) b;
   // printf("Fill color: %s\n ", block->fillColor);
    return block->fillColor;
}

char *getBlockSw(Block b){
    BlockImp block = (BlockImp) b;
    //printf("Sw: %s\n ", block->sw);
    return block->sw;
}

void setBlockX(Block b, double x){
    BlockImp block = (BlockImp) b;

    block->x = x;
}

void setBlockY(Block b, double y){
    BlockImp block = (BlockImp) b;

    block->y = y;
}

void setBlockStrokeColor(Block b, char strokeColor[]){
    BlockImp block = (BlockImp) b;

    strcpy(block->strokeColor, strokeColor);
}

void setBlockFillColor(Block b, char fillColor[]){
    BlockImp block = (BlockImp) b;

    strcpy(block->fillColor, fillColor);
    
}

void freeBlock(Block b){
    BlockImp block = (BlockImp) b;

    free(block);   
}