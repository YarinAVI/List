#include <stdio.h>
#include "../include/list.h"
#include <string.h>
#include <stdlib.h>
Item ctor(CItem x) {
    size_t len = strlen(x);
    char * ret = calloc(len+1,sizeof(char));
    strcpy(ret,x);
    return ret;
}
int compar(CItem x, CItem y) {
    return strcmp(x,y);
}
void dtor(Item x) {
    free(x);
}

int main(void) {
    /*
    int x;
    int *xp = &x;
    int *xpe;
    int * const * xpp = &xp;
    //*xpp = NULL;
    xpp = &xpe;
    */
   List L = newList(ctor,dtor,(int (*)(CItem,CItem))strcmp);
   const char *testing[3] = {"Test1","Test2","Test3"};
   
   for(int i=0;i<3;i++) {
       ListInsert(L,testing[i]);
   }
   /* example of iterating the list... */
   /* note that ItemIt is infact a pointer to a constant pointer, that means 
      you can only use it to iterate the list and read/write to a specific item but not change
      the internal pointer to that item! */
   ItemIt begin = ListGetBeginIt(L);
   ItemIt end   = ListGetEndIt(L);
   while(begin!=end) {
       if(*begin)
       printf("%s\n",(char*)(*begin));
    begin++;
   }
   char*  t = ListFind(L,testing[2]);
   printf("found :%s\n",t);
   ListDestroy(L);
}