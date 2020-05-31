/*
 * write1.c
 *
 * Test basic functionality of write() syscall (multi page)
 */

#include "stdio.h"
#include "stdlib.h"

int bigbuf1[6000];
int bigbuf2[6000];
int bigbufnum = 6000;


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

int do_open (char *fname) {
    int fd;

    printf ("opening %s...\n", fname);
    fd = open (fname);
    if (fd >= 0) {
	    printf ("...passed (fd = %d)\n", fd);
    } else {
	    printf ("...failed (%d)\n", fd);
	// exit (-1002);
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

int do_read(char *fname, char *buf, int len){
    int fd, amount;

    fd = do_open(fname);
    printf ("reading file %s...\n", fname);
    amount = read(fd, buf, len);
    if(amount >= 0){
        printf("...passed, read %d bytes \n", amount);
    }else
    {
        printf("...failed, error occurs \n");
    }

    return amount;
}

int main() {
    char *input = "read.txt";
    char *output = "write.txt";
    
    int amount = do_read(input, bigbuf1, bigbufnum);
    
    int fd = creat(output);
    printf("write %d bytes into file %d ... \n ", amount, output);
    int amount2 = write(fd, bigbuf1, amount);
    if(amount2 == amount){
        printf("... passed, wrote %d bytes \n", amount2);
    }else if (amount2 >= 0)
    {
        printf("... failed, wrote %d bytes but expected %d bytes\n", amount2, amount);
    }else
    {
        printf("...failed, error occurs \n");
    }

    int amount3 = do_read(output, bigbuf2, bigbufnum);
    int validate = strcmp(bigbuf1, bigbuf2);

    if(validate == 0){
        printf("...passed, two string matched \n");
    }else{
        printf("...failed, validate result = %d \n", validate);
    }

    return 0;
}
