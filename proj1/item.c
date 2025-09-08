#include "item.h"
#include <stdio.h>

struct item{
    char procedimento[101];
};

ITEM* item_criar(void){
    ITEM* item = malloc(sizeof(ITEM*));
    return item;
}


