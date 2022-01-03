#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fptr;

int count=0,count1=0;

void counter(){
    char c;
    int k=0;
    fptr=fopen("/Users/raisaghosh/Desktop/terminal app/task.txt","r");
    while((c=fgetc(fptr))!=EOF){
        if(c=='\n')
         k++;
    }
    fclose(fptr);
    count=k;

    k=0;
    fptr=fopen("/Users/raisaghosh/Desktop/terminal app/completed.txt","r");
    while((c=fgetc(fptr))!=EOF){
        if(c=='\n')
         k++;
    }
    fclose(fptr);
    count1=k;
   
}

void add(const char a[],const char b[]){

    fputs(a,fptr);
    fprintf(fptr,"\t");
    fputs(b,fptr);
    fprintf(fptr,"\n");
    printf("Added task : \"%s\" with priority %d\n",b,atoi(a));
   
}

void help(){
        printf("Usage:-\n");
        printf("./task add 2 Hello World        #Add a new item with priority 2 and text 'hello world' to the list\n");
        printf("./task ls       #Show incomplete priority list items sorted by priority in ascending order\n");
        printf("./task del NUMBER       #Delete the incomplete item with the given priority number\n");
        printf("./task done NUMBER        #Mark the incomplete iem with the given PRIORITY_NUMBER as complete\n");
        printf("./task help        #Show usage\n");
        printf("./task report        #Statistics\n");
}

int priority(char s[]){
    int i=0,k=0;
    char t[10];
    while(s[i]!='\t'){
        t[k++]=s[i++];
    }
    return atoi(t);
}

void display(char s[],int c){
    int i=0,k=0,x;
    char d[100];
    
    while(s[i]!='\t'){
        i++;
    }

    for(i=i+1;i<strlen(s)-1;i++){
        d[k++]=s[i];
    }
    d[k]='\0';
    
    printf("%d. %s [%d]\n",c,d,priority(s));
}

void ls(){
    char arr[count][1000],d[1000];
    int i=0,j,min,x,t=1,check=0,p;

    fptr=fopen("/Users/raisaghosh/Desktop/terminal app/task.txt","r");
    
    while (fgets(arr[i],1000, fptr)){
        i++;
    }

    fclose(fptr);

    for(i=0;i<count;i++){
        for(j=i+1;j<count;j++){
            min=priority(arr[i]);
            fflush(stdout);
            // printf("Minimum is%d\n",min);
            x=priority(arr[j]);
            fflush(stdout);
            // printf("x is%d\n",x);
            if(x<min){
                strcpy(d,arr[j]);
                strcpy(arr[j],arr[i]);
                strcpy(arr[i],d);
            }
        }
    }
        // printf("\ntttttt\n");
        // for(i=0;i<count;i++){
        //     printf("%s\n",arr[i]);
        // }
        fptr=fopen("/Users/raisaghosh/Desktop/terminal app/task.txt","w");

        for(i=0;i<count;i++){
                fputs(arr[i],fptr);
        }
        fclose(fptr);

        for(i=0;i<count;i++){
            // j=priority(arr[i]);
            // printf("\nprior is %d\n",priority(arr[i]));
            display(arr[i],t++);
        }
    }

void delpriority(int t){
    printf("Deleted task #%d\n",t);
    char arr[count][1000];
    int i=0;

    fptr=fopen("/Users/raisaghosh/Desktop/terminal app/task.txt","r");
    
    while (fgets(arr[i],1000, fptr)){
        i++;
    }

    fclose(fptr);

    fptr=fopen("/Users/raisaghosh/Desktop/terminal app/task.txt","w");

    for(i=0;i<count;i++){
        if(i+1==t)
            continue;
        else
            fputs(arr[i],fptr);
    }
    fclose(fptr);
}

void putincomplete(char a[]){
    FILE *tptr;
    char c[10000];
    int i=0,k=0;

    while(a[i]!='\t'){
        i++;
    }

    i++;

    tptr=fopen("/Users/raisaghosh/Desktop/terminal app/completed.txt","a+");

    while(a[i]!='\n'){
        c[k++]=a[i++];
    }
    c[k]='\n';

    fputs(c,tptr);


     fclose(tptr);
}

void donetask(int n){
    printf("Marked item as done.\n");
    char arr[count][1000];
    int i=0;

    fptr=fopen("/Users/raisaghosh/Desktop/terminal app/task.txt","r");
    
    while (fgets(arr[i],1000, fptr)){
        i++;
    }

    fclose(fptr);

    fptr=fopen("/Users/raisaghosh/Desktop/terminal app/task.txt","w");

    for(i=0;i<count;i++){
        if(i+1==n){
            putincomplete(arr[i]);
        }
            
        else{
            fputs(arr[i],fptr);
        }
            
    }

    fclose(fptr);
}

void report(){
     char arr[count1+count][1000];
    int i=0,k=0;

    fptr=fopen("/Users/raisaghosh/Desktop/terminal app/task.txt","r");
    
    while (fgets(arr[i],1000, fptr)){
        i++;
    }

    fclose(fptr);

    printf("Pending : %d\n",count);
    k=1;
    for(i=0;i<count;i++){
        display(arr[i],k++);
    }
    printf("\n");

    i=0;
    fptr=fopen("/Users/raisaghosh/Desktop/terminal app/completed.txt","r");
    
    while (fgets(arr[i],1000, fptr)){
        i++;
    }

    fclose(fptr);

    printf("Completed : %d\n",count1);
    k=1;
    for(i=0;i<count1;i++){
        printf("%d. %s",k++,arr[i]);
    }
}

int main(int argc, char const *argv[])
{
    int i,k;
    char c;

    counter();

    // printf("\nyyyyy%d %d\n",count,count1);
    
    if(argc==1){
        help();
    }
    
    if(argc>=2){

         if(strcmp(argv[1],"add")==0){  //1
        
             if(argv[2] == NULL)
        {
            printf("Error!");   
            exit(1);             
        }

        fptr=fopen("/Users/raisaghosh/Desktop/terminal app/task.txt","a+");

            if(fptr == NULL)
        {
            printf("Error!");   
            exit(1);             
        }

        add(argv[2],argv[3]);

        fclose(fptr);
        }


        if(strcmp(argv[1],"ls")==0){ //2
           ls();
        }


        if(strcmp(argv[1],"del")==0){ //3
           k=atoi(argv[2]);
           delpriority(k);
        }


        if(strcmp(argv[1],"done")==0){ //4
           k=atoi(argv[2]);
           donetask(k);
        }


        if(strcmp(argv[1],"help")==0){ //5
           help();
        }


        if(strcmp(argv[1],"report")==0){ //6
           report();

        }

    }


    return 0;
}
