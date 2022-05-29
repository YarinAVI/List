#include <stdio.h>
#include "../include/list.h"
#include <string.h>
#include <stdlib.h>
LItem ctor(CLItem x) {
    size_t len = strlen(x);
    char * ret = calloc(len+1,sizeof(char));
    strcpy(ret,x);
    return ret;
}
int compar(CLItem x, CLItem y) {
    return strcmp(x,y);
}
void dtor(LItem x) {
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
   List L = newList(ctor,dtor,(int (*)(CLItem,CLItem))strcmp);
   const char *testing[3] = {"Test1","Test2","Test3"};
   
   for(int i=0;i<3;i++) {
       ListInsert(L,testing[i]);
   }
   /* example of iterating the list... */
   /* note that LItemIt is infact a pointer to a constant pointer, that means 
      you can only use it to iterate the list and read/write to a specific item but not change
      the internal pointer to that item! */
   LItemIt begin = ListGetBeginIt(L);
   LItemIt end   = ListGetEndIt(L);
   while(begin!=end) {
       if(*begin)
       printf("%s\n",(char*)(*begin));
    begin++;
   }
   char*  t = ListFind(L,testing[2]);
   printf("found :%s\n",t);
   ListDestroy(L);
}