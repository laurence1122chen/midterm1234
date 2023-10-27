#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/times.h>

// calling convention is an implementation-level (low-level) scheme 
// for how subroutines or functions receive parameters from their caller 
// and how they return a result
struct FileStream{
    char *buffer;   //buffer content
    size_t size;    //buffer size
    size_t position;//current seek position
};
int readfn(void	*fstream, char *buf, int nbytes){
    struct FileStream *fs = (struct FileStream *)fstream;
    if (fs->position >= fs->size) { //EOF
        return 0;
    }

    size_t bytes_to_read = (fs->position + nbytes > fs->size) ? (fs->size - fs->position) : nbytes;
    memcpy(buf, fs->buffer + fs->position, bytes_to_read);
    fs->position += bytes_to_read;
    return bytes_to_read;
}
int writefn(void *fstream, const char *buf, int nbytes){
    struct FileStream *fs = (struct FileStream *)fstream;
    // if total size is over the allocated buffer size, resize the buffer
    int size = nbytes;
    if (fs->position + size > fs->size) { 
        fs->buffer = realloc(fs->buffer, fs->position + size);
        if (fs->buffer == NULL) { // Error
            return 0; 
        }
        fs->size = fs->position + size;
    }
    memcpy(fs->buffer + fs->position, buf, size);
    fs->position += size;
    return size;
}
off_t seekfn(void *fstream, off_t offset, int whence){
    struct FileStream *fs = (struct FileStream *)fstream;
    switch (whence) {
        //from head
        case SEEK_SET:
            if (offset < 0 || offset > fs->size) {
                return -1; // Error
            }
            fs->position = offset;
            break;
        //from last move
        case SEEK_CUR:
            if (fs->position + offset < 0 || fs->position + offset > fs->size) {
                return -1; // Error
            }
            fs->position += offset;
            break;
        //from end
        case SEEK_END:
            if (offset > 0 || fs->size + offset < 0) {
                return -1; // Error
            }
            fs->position = fs->size + offset;
            break;
        default:
            return -1; // Error
    }
    return 0;
}
int closefn(void *fstream){
    struct FileStream *fs = (struct FileStream *)fstream;
    free(fs->buffer);
    free(fs);
    return 0;
}
FILE *fmemopen(void *buf, size_t size, const char *restrict){
    struct FileStream *fs = malloc(sizeof(struct FileStream));
    if (fs == NULL) {
        return NULL;
    }
    //init
    fs->buffer = buf;
    fs->size = size;
    fs->position = 0;
    return funopen( fs, readfn, writefn, seekfn, closefn);
}
void ff(int ss){
    
}
int main(int argc, char **argv){
    char buffer[20*1024*1024];
    FILE *fs = fmemopen(buffer, sizeof(buffer), "w");
    if(fs == NULL) {
        perror("Error creating custom stream");
        exit(EXIT_FAILURE);
    }
    FILE *source = fopen("./source2", "r");

    struct tms tmsstart,tmsend;
    static long base= 0;
    base=sysconf( _SC_CLK_TCK );
    clock_t start = times(&tmsstart);
    char readbuf[1];
    while(fread(readbuf, 1, sizeof(readbuf), source) > 0){
        fwrite(readbuf, 1, sizeof(readbuf),fs);
    }
    clock_t end = times(&tmsend);
    printf("User CPU Time: %.3f\n",(tmsend.tms_utime-tmsstart.tms_utime)/(double) base);
    printf("System CPU Time: %.3f\n",(tmsend.tms_stime-tmsstart.tms_stime)/(double) base);
    printf("Clock Time: %.3f\n",(end - start)/(double) base);
    
    FILE *output = fopen("./output1", "w");
    fwrite(fs,1,sizeof(fs),output);

    fclose(fs);
    fclose(output);






    char buffer1[20*1024*1024];
    fs = fmemopen(buffer1, sizeof(buffer1), "w");
    if(fs == NULL) {
        perror("Error creating custom stream");
        exit(EXIT_FAILURE);
    }
    source = fopen("./source2", "r");

    base= 0;
    base=sysconf( _SC_CLK_TCK );
    start = times(&tmsstart);
    char readbuf1[32];
    while(fread(readbuf1, 1, sizeof(readbuf1), source) > 0){
        fwrite(readbuf1, 1, sizeof(readbuf1),fs);
    }
    end = times(&tmsend);
    printf("User CPU Time: %.3f\n",(tmsend.tms_utime-tmsstart.tms_utime)/(double) base);
    printf("System CPU Time: %.3f\n",(tmsend.tms_stime-tmsstart.tms_stime)/(double) base);
    printf("Clock Time: %.3f\n",(end - start)/(double) base);
    
    output = fopen("./output2", "w");
    fwrite(fs,1,sizeof(fs),output);

    fclose(fs);
    fclose(output);


    char buffer2[20*1024*1024];
    fs = fmemopen(buffer2, sizeof(buffer2), "w");
    if(fs == NULL) {
        perror("Error creating custom stream");
        exit(EXIT_FAILURE);
    }
    source = fopen("./source2", "r");

    base= 0;
    base=sysconf( _SC_CLK_TCK );
    start = times(&tmsstart);
    char readbuf2[1024];
    while(fread(readbuf2, 1, sizeof(readbuf2), source) > 0){
        fwrite(readbuf2, 1, sizeof(readbuf2),fs);
    }
    end = times(&tmsend);
    printf("User CPU Time: %.3f\n",(tmsend.tms_utime-tmsstart.tms_utime)/(double) base);
    printf("System CPU Time: %.3f\n",(tmsend.tms_stime-tmsstart.tms_stime)/(double) base);
    printf("Clock Time: %.3f\n",(end - start)/(double) base);
    
    output = fopen("./output3", "w");
    fwrite(fs,1,sizeof(fs),output);

    fclose(fs);
    fclose(output);



    char buffer3[20*1024*1024];
    fs = fmemopen(buffer3, sizeof(buffer3), "w");
    if(fs == NULL) {
        perror("Error creating custom stream");
        exit(EXIT_FAILURE);
    }
    source = fopen("./source2", "r");

    base= 0;
    base=sysconf( _SC_CLK_TCK );
    start = times(&tmsstart);
    char readbuf3[4096];
    while(fread(readbuf3, 1, sizeof(readbuf3), source) > 0){
        fwrite(readbuf3, 1, sizeof(readbuf3),fs);
    }
    end = times(&tmsend);
    printf("User CPU Time: %.3f\n",(tmsend.tms_utime-tmsstart.tms_utime)/(double) base);
    printf("System CPU Time: %.3f\n",(tmsend.tms_stime-tmsstart.tms_stime)/(double) base);
    printf("Clock Time: %.3f\n",(end - start)/(double) base);
    
    output = fopen("./output4", "w");
    fwrite(fs,1,sizeof(fs),output);

    fclose(fs);
    fclose(output);



    char buffer4[20*1024*1024];
    fs = fmemopen(buffer4, sizeof(buffer4), "w");
    if(fs == NULL) {
        perror("Error creating custom stream");
        exit(EXIT_FAILURE);
    }
    source = fopen("./source2", "r");

    base= 0;
    base=sysconf( _SC_CLK_TCK );
    start = times(&tmsstart);
    char readbuf4[4096];
    while(fgets(readbuf4, sizeof(readbuf4), source) != NULL){
        fputs(readbuf4, fs);
    }
    end = times(&tmsend);
    printf("User CPU Time: %.3f\n",(tmsend.tms_utime-tmsstart.tms_utime)/(double) base);
    printf("System CPU Time: %.3f\n",(tmsend.tms_stime-tmsstart.tms_stime)/(double) base);
    printf("Clock Time: %.3f\n",(end - start)/(double) base);
    
    output = fopen("./output5", "w");
    fwrite(fs,1,sizeof(fs),output);

    fclose(fs);
    fclose(output);



    char buffer5[20*1024*1024];
    fs = fmemopen(buffer5, sizeof(buffer5), "w");
    if(fs == NULL) {
        perror("Error creating custom stream");
        exit(EXIT_FAILURE);
    }
    source = fopen("./source2", "r");

    base= 0;
    base=sysconf( _SC_CLK_TCK );
    start = times(&tmsstart);
    char c;
    c = fgetc(source);
    while(c != EOF){
        fputc(c, fs);
        c = fgetc(source);
    }
    end = times(&tmsend);
    printf("User CPU Time: %.3f\n",(tmsend.tms_utime-tmsstart.tms_utime)/(double) base);
    printf("System CPU Time: %.3f\n",(tmsend.tms_stime-tmsstart.tms_stime)/(double) base);
    printf("Clock Time: %.3f\n",(end - start)/(double) base);
    
    output = fopen("./output6", "w");
    fwrite(fs,1,sizeof(fs),output);

    fclose(fs);
    fclose(output);

    





    // //(1)
    // fprintf(fs, "hello, world");

    // //(2)
    // fseek(fs, 7, SEEK_SET);

    // //(3)
    //     //-world part
    // char readbuf[20];
    // fread(readbuf, 1, 5, fs);
    // readbuf[5] = '\0';
    // printf("%s\n", readbuf);
    //     //-hello, world part
    // fseek(fs, 0, SEEK_SET); //reset seek position to head
    // fread(readbuf, 1, 12, fs);
    // readbuf[12] = '\0';
    // printf("%s\n", readbuf);

    // //(4)
    
    return 0;
}
