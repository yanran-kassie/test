/*
 * open1.c
 *
 * Test basic functionality of open() syscall 
 */

#include "stdio.h"
#include "stdlib.h"

void do_creat (char *fname) {
    int fd;

   printf ("creating %s...\n", fname);
    fd = creat (fname);
    if (fd > 1 && fd < 16) {
	    printf ("...passed (fd = %d)\n", fd);
    } else {
	    printf ("...failed (%d)\n", fd);
        return;
        // exit (-1001);
    }
    
    close(fd);
    printf("fd is close: %d\n", fd);
}

void multi_creat(char *base_fname, int pos, int num){
    printf("multiple creat() operations: create %d files...\n", num);
    
    int i;
    printf("%s\n",base_fname);

    for(i=0; i<num; ++i){
       
       *( base_fname + pos) = 'A' + i;
	printf("creating %s...\n", base_fname);

        do_creat(base_fname);
    }
}

int do_open (char *fname) {
    int fd;

    printf ("opening %s...\n", fname);
    fd = open (fname);
    // if (fd >= 0) {
	//     printf ("...passed (fd = %d)\n", fd);
    // } else {
	//     printf ("...failed (%d)\n", fd);
	//     // exit (-1002);
    // }
    return fd;
}


int main() {
    printf("ssssss\n");
    char fname[] = "open0.out";


    
    

    // ---------------------------------------------
    char fname1[] = "open1.out";
    printf("open an non-existing file %s (should not crash, only return an error)...\n", fname1);
    int fd = open(fname1);
    if(fd < 0){
	    printf("..passed, fd = %d",fd);
    }else{
	    printf("...failed, fd = %d", fd);
	    close(fd);
    }

    multi_creat(&fname1,4,14);
    /*
    
    int fd = open(fname1);
    if(fd < 0){
        printf("...failed\n");
    }else{
        printf("...passed, fd = %d \n", fd);
    }
    */

    // ---------------------------------------------
    printf("open with an invalid file name (should not crash, only return an error)...\n");

    char *wname = "open++.out";
    int fd2 = open(wname);

    if(fd2 > 1 && fd2 < 16){
        printf("...failed\n");
    }else
    {
        printf("...passed, should not create, fd = %d\n",fd2);
    }

    // ---------------------------------------------
    printf("open with an invalid file name address (should not crash, only return an error)...\n");

    int fd3 = open((char *) 0xBADFFF);    

    if(fd3 > 1 && fd3 < 16){
        printf("...failed\n");
    }else{
        printf("...passed, should not create, fd = %d\n", fd3);
    }
    
    // ---------------------------------------------
    char lfile[2000];
    char *ptr = "longname";
    int name_fd = open(ptr);
    printf("open long name file with fd = %d",name_fd);
    int nameLength = read(name_fd, lfile, 1024);
    close(name_fd);
    printf("close fd = %d",name_fd);

    printf("open file with invalid file name (%d bytes) (should not crash, only return an error)...\n", nameLength);
    
    int fd4 = open(lfile);
    if(fd4 > 1 && fd4 < 16){
        printf("...failed\n");
    }else{
        printf("...passed, should not create, fd = %d\n", fd4);
    }

    // ---------------------------------------------
    printf("open with no free fd (should not crash, only return an error)...\n");

    int i;
    
    for(i=0; i<15; ++i){
        *(fname+4) = 'A' + i;

        int filed = do_open(fname);

        if(i!=14){
            if(filed==-1){
                printf("...failed, should open successfully, fd = %d \n ", filed);
            }
        }else{
            if(filed!=-1){
                printf("...failed, should not open successfully, fd = %d \n ", filed);
            }else{
                printf("...passed\n ");
            }
        }

    }

    close(13);

    printf("After close, should open file %s successfully \n ", fname);

    int fd5 = do_open(fname);

    if(fd5 > 1 && fd5 < 15){
        printf("...passed\n", fd5);
    }else{
        printf("...failed, fd = %d \n", fd5);
    }

    // ---------------------------------------------
    printf("open  twice \n");
    int fd6 = do_open(fname);

    if(fd6 > 1 && fd6 < 15){
        printf("...failed, fd = %d \n", fd6);
    }else{
        printf("...passed, fd = %d \n", fd6);
    }

    close(3);
    fd6 = do_open(fname);
    if(fd6>1 && fd6 < 15){
	    printf("...passed\n");
    }else{
	    printf("...failed, fd = %d \n",fd6);
    }


    return 0;
}
