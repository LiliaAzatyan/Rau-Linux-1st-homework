#include <stdio.h>
#include <stdlib.h>
int main()
{
    int num;
    scanf("%d", &num);
    FILE * fptr[num];
    for(int i = 0; i < num; i++){
        fptr[i] = fopen("File_<i-th>", "w");
        fprintf(fptr, "Hello World");
        
        //fclose(fptr);
    }

    return 0;
}
