#include "stdio.h"
#include "stdlib.h"

int main() {
    char* file = "creat.out";
    
    char *str = "roses are red\nviolets are blue\nI love Nachos\nand so do you\n";
    int len = strlen(str);

    printf("create a new file %s ...\n", file);
    int fd = creat(file);
    if(fd >1 && fd<16){
        printf("...passed (fd = %d) \n", fd);
    }else{
        printf("...failed  %d \n", fd);
        exit (-1001);
    }

    printf("write %d bytes into %s ... \n", file);
    int write_res = write(fd, str, len);    
    if(write_res == len){
        printf("...passed (wrote %d bytes) \n", write_res);
    }else if(write_res >=0 ){
        printf ("...failed (expected to write %d bytes, but wrote %d)\n", len, write_res);
        exit (-1002);
    }else{
        printf ("...failed (r = %d)\n", write_res);
        exit (-1003);
    }

    close(fd);

    // ----------------------------------------------------------------    
    char buffer[128];
    printf("create an existing file %s, just open it ...\n", file);
    fd = creat(file);
    
    printf ("reading %s into buffer...\n", file);
    int read_res = read (fd, buffer, len);
    if (read_res < 0) {
        printf ("...failed (r = %d)\n", read_res);
        // do_close (fd);
        // return;
    } else if (read_res != len) {
        printf ("...failed (expected to read %d bytes, but read %d)\n", len, read_res);
        // do_close (fd);
        // return;
    } else {
        printf ("...success\n");
    }

    int r = 0;
    printf ("validating %s...\n", file);
    while (r < len) {
        if (buffer[r] != str[r]) {
            printf ("...failed (offset %d: expected %c, read %c)\n",
                r, str[r], buffer[r]);
            // exit (-1006);
            break;
        }
	    r++;
    }
    if (r == len) {
	    printf ("...passed\n");
    }
    
    // ----------------------------------------------------------------
    char lfile[2000];
    
    char *ptr = "longname";

    int name_fd = open(ptr);

    int nameLength = read(name_fd, lfile, 1024);
    close(name_fd);
    printf("creat file with invalid file name (%d bytes) ...\n", nameLength);
    
    int fd2 = creat(lfile);
    if(fd2 > 1 && fd2 < 16){
        printf("...failed, should not create\n");
    }else
    {
        printf("...passed, should not create\n");
    }

    // ----------------------------------------------------------------
    char* wfile = "creat++.out";

    printf("creat file with invalid file name ...\n");
    fd2 = creat(wfile);
    // int fd2 = creat((char *) 0xBADFFF);
    if(fd2 > 1 && fd2 < 16){
        printf("...failed, should not create\n");
    }else
    {
        printf("...passed, should not create\n");
    }

    // ----------------------------------------------------------------
    char* mfile = "creat0.out";

    printf("create many file, run out of file descriptors\n");
    
    int i;
    for(i=0; i<14; ++i){
        mfile[5] = 'A' + i;
        printf("create file %s ...\n", mfile);
        int mfd= creat(mfile);

        if(i != 13){
            if(mfd < 0){
                printf("...failed, %s should create successfully...\n", mfile);
            }
        }else{
            if(mfd < 0){
                printf("...passed, should not create...\n");
            }else{
                printf("...failed, should not create...\n");
            }
        }
    }

    close(15);
    printf("after close, we cancreate a file %s...\n", mfile);

    fd = creat(mfile);

    if(fd >1 && fd<16){
        printf("...passed (fd = %d), \n", fd);
    }else{
        printf("...failed  %d\n", fd);
        exit (-1001);
    }
    
    return 0;
}
