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
    char *fname = "close.out";

    int fd = do_creat(fname);

    // --------------------------------------------
    printf("close file with an invalid file descriptor -1 \n");
    int res1 = close(-1);
    if(res1 < 0){
        printf("...passed, should not crash \n");
    }else{
        printf("...faild, should not success \n");
    }

    // --------------------------------------------
    printf("close file with an invalid file descriptor 16 \n");
    int res2 = close(16);
    if(res2 < 0){
        printf("...passed, should not crash \n");
    }else{
        printf("...faild, should not success \n");
    }

    // --------------------------------------------
    printf("close file (fd = %d) \n", fd);
    int res3 = close(fd);
    if(res3 == 0){
        printf("...passed, should close it \n");
    }else
    {
        printf("...failed, some error occurs \n");
    }

    // --------------------------------------------
    printf("after close, we can't read / write \n");
    
    char *str = "love!";
    char buf[30];

    int res4 = read(fd, buf, 0);
    int res5 = write(fd, str, strlen(str));

    if(res4 < 0 && res5 < 0){
        printf("...passed, read/write should not work \n");
    }else{
        printf("...failed, read %d - write %d", res4, res5);
    }

    // --------------------------------------------    
    printf("close a file twice \n");

    int res6 = close(fd);

    if(res6 < 0){
        printf("...passed, close should fail \n");
    }else{
        printf("...failed, bad thing \n");
    }

    return 0;
}
