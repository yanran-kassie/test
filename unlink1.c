#include "stdio.h"
#include "stdlib.h"

int do_creat (char *fname) {
    int fd;

    printf ("creating %s...\n", fname);
    fd = creat (fname);
    if (fd >= 0) {
    	printf ("...passed (fd = %d)\n", fd);
    } else {
	    printf ("...failed (%d)\n", fd);
	    // exit (-1001);
    }
    return fd;
}


void do_close (int fd) {
    int r;

    printf ("closing %d...\n", fd);
    r = close (fd);
    if (r < 0) {
    	printf ("...failed (r = %d)\n", r);
	// exit (-1003);
    }
}

int main() {
    char *fname = "unlink.out";


    // ----------------------------------------------
    printf("unlink file after close file \n");

    int fd = do_creat(fname);
    do_close(fd);

    int res1 = unlink(fname);

    if(res1 == 0){
        printf("...passed, should unlink file %s \n", fname);
    }else{
        printf("...failed, some error occur \n");
    }

    // ----------------------------------------------
    printf("unlink file without close file, should also release file descriptor \n");

    fd = do_creat(fname);
    // do_close(fd);

    int res2 = unlink(fname);

    if(res2 == 0){
        printf("...passed, should unlink file %s \n", fname);
    }else{
        printf("...failed, some error occur \n");
    }

    char buf[10];

    printf("after unlink, read this file cause error \n");
    int res3 = read(fd, buf, 10);
    if(res3 < 0){
        printf("...passed, read should fail \n");
    }else{
        printf("...failed, unlink don't release file descriptor \n");
    }
    
    // ----------------------------------------------
    printf("unlink a file twice should cause an error \n");

    int res4 = unlink(fname);
    if(res4 < 0){
        printf("...passed, unlink should fail \n");
    }else{
        printf("...failed, error occurs");
    }


    return 0;
}
