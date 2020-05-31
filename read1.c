/*
 * open1.c
 *
 * Test basic functionality of open() syscall 
 */

#include "stdio.h"
#include "stdlib.h"

int bigbuf1[10240];
// int bigbuf2[10240];
int bigbufnum = 10240;

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

int main() {
    char *fname = "read.txt";
    // ---------------------------------------
    int fd = do_open(fname);

    printf("read a file %s with over-large size %d\n", fname, bigbufnum);

    int amount = read(fd, bigbuf1, bigbufnum);

    if(amount > 0){
        printf("...passed, read %d bytes\n", amount);
    }else{
        printf("...failed, error occurs\n");
    }

    do_close(fname);

    // ---------------------------------------
//    fd = do_open(fname);
//
//    printf("read a file %s with multi-page\n", fname);
//
//    int amount2 = read(fd, bigbuf1, amount);
//
//    if(amount2 != amount){
//        printf("...passed, read %d bytes\n", amount2);
//    }else{
//        printf("...failed, read %d bytes\n", amount2);
//    }
//
//    do_close(fname);
//
//    // --------------------------------------
//    fd = do_open(fname);
//
//    printf("read a file %s with small size %d\n", fname, 128);
//
//    char *smallbuf[130];
//    int amount3 = read(fd, smallbuf, 128);
//
//    if(amount3 == 128){
//        printf("...passed, read %d bytes\n", amount3);
//        printf("----------content----------\n %s \n", smallbuf);
//    }else{
//        printf("...failed, read %d bytes\n", amount3);
//    }
//
//
//    printf("read a file twice %s with small size %d\n", fname, 128);
//
//    // char *smallbuf[130];
//    amount3 = read(fd, smallbuf, 128);
//
//    if(amount3 == 128){
//        printf("...passed, read %d bytes\n", amount3);
//        printf("----------content----------\n %s \n", smallbuf);
//    }else{
//        printf("...failed, read %d bytes\n", amount3);
//    }
//
//    // --------------------------------------
//    printf("read a file %s with a too small buffer \n", fname);
//
//    // char *smallbuf[128];
//    int amount4 = read(fd, smallbuf, 150);
//
//    if(amount4 > 0){
//        printf("...passed, read %d bytes\n", amount4);
//        printf("----------content----------\n %s \n", smallbuf);
//    }else{
//        printf("...failed, read %d bytes\n", amount4);
//    }
//
//    // --------------------------------------
//    printf ("writing with an invalid buffer (should not crash, only return an error)...\n");
//
//    int r = read(fd, (char *) 0xBADFFF, 128);
//
//    if (r < 0) {
//        printf ("...passed (r = %d)\n", r);
//    } else {
//        printf ("...failed (r = %d)\n", r);
//        // exit (-6000);
//    }
//
//    // --------------------------------------
//    printf ("writing with an invalid count (should not crash, only return an error)...\n");
//
//    r = read(fd, smallbuf, -1);
//
//    if (r < 0) {
//        printf ("...passed (r = %d)\n", r);
//    } else {
//        printf ("...failed (r = %d)\n", r);
//        // exit (-6000);
//    }
//
//
//    // --------------------------------------
//    printf ("writing with a buffer that extends beyond the end of the\n");
//    printf ("address space.  write should return an error.\n");
//
//    r = read(fd, smallbuf, (80 * 1024));
//
//    if (r < 0) {
//        printf ("...passed (r = %d)\n", r);
//    } else {
//        printf ("...failed (r = %d)\n", r);
//        // exit (-6000);
//    }

    return 0;
}
