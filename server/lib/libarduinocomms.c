#define _GNU_SOURCE

#include <stdio.h>
#include <libarduinocomms.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>

int arduino_init(arduino_t *interface, const char *filename) {
    interface->filename = filename;
    printf("Setting up arduino\n");

    int file;
    struct termios toptions;

    file = open(interface->filename, O_RDWR | O_NOCTTY | O_NDELAY);
    sleep(1);
    /* get current serial port settings */
    tcgetattr(file, &toptions);
    /* set 9600 baud both ways */
    cfsetispeed(&toptions, B9600);
    cfsetospeed(&toptions, B9600);
    /* 8 bits, no parity, no stop bits */
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    /* Canonical mode */
    toptions.c_lflag &= ~ICANON;
    /* commit the serial port settings */
    toptions.c_cc[VMIN] = 0;
    toptions.c_cc[VTIME] = 1;
    toptions.c_oflag = 0;

    toptions.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
    tcsetattr(file, TCSANOW, &toptions);

    printf("Opening arduino\n");
    interface->ptr = fopen(interface->filename, "r+");
    if(interface->ptr) {
        printf("Opened\n");
        interface->opened = 1;
        fgetpos(interface->ptr, &interface->pos_start);
        sleep(1);
    }
    return interface->opened;
}

int arduino_exit(arduino_t *interface) {
    fclose(interface->ptr);
    interface->opened = 0;
    return 0;
}

int arduino_sendchar(arduino_t *interface, const char c) {
    printf("Sending char\n");
    if(!interface->ptr) {
        return FILE_ERROR;
    }
    //fsetpos(interface->ptr, &interface->pos_start);
    fprintf(interface->ptr, "%c", c);
    fflush(interface->ptr);
}
int arduino_sendstring(arduino_t *interface, const char *string) {
    if(!interface->ptr) {
        return FILE_ERROR;
    }
    //sleep(1);
    printf("Sending string %s\n", string);
    //fsetpos(interface->ptr, &interface->pos_start);
    fflush(interface->ptr);
    fprintf(interface->ptr, "%s", string);
    fflush(interface->ptr);

}
int arduino_sendline(arduino_t *interface, const char *line) {
    printf("Sending line\n");
    if(!interface->ptr) {
        return FILE_ERROR;
    }
    //fsetpos(interface->ptr, &interface->pos_start);
    fprintf(interface->ptr, "%s\n", line);
    fflush(interface->ptr);
}

char arduino_readchar(arduino_t *interface) {
    printf("Reading char\n");
    if(!interface->ptr) {
        return FILE_ERROR;
    }
    //fsetpos(interface->ptr, &interface->pos_start);
    printf("Set position\n");
    char c = fgetc((FILE *)interface->ptr);
    fflush(interface->ptr);
    return c;
}
int arduino_readstring(arduino_t *interface, char *result, unsigned int size) {
    printf("Reading string\n");
    int c;
    unsigned int count;
    if(!interface->ptr) {
        return FILE_ERROR;
    }
    //fsetpos(interface->ptr, &interface->pos_start);
    fgets(result, size, interface->ptr);
    count = strlen(result);
    fflush(interface->ptr);
    return count;
}
int arduino_readline(arduino_t *interface, char *result) {
    printf("Reading line\n");
    int c;
    unsigned int count;
    if(!interface->ptr) {
        return FILE_ERROR;
    }
    //fsetpos(interface->ptr, &interface->pos_start);
    count = 0;
    while((c = fgetc(interface->ptr)) != '\n') { // Make it blocking
        if(c > 0 && c != EOF) result[count++] = (char)c;
        printf("%c\n", c);
    }
    if(count) result[count] = 0;
    fflush(interface->ptr);
    return count;
}

int arduino_readuntil(arduino_t *interface, char *result, char delimiter) {
    //printf("Reading until\n");
    int c;
    unsigned int count;
    if(!interface->ptr) {
        return FILE_ERROR;
    }
    //fsetpos(interface->ptr, &interface->pos_start);
    count = 0;
    while((c = fgetc(interface->ptr)) != delimiter) {
        if(c == EOF) {
            break;
        } else if(c > 0 && c != EOF) result[count++] = (char)c;

    }
    if(c == delimiter) result[count++] = (char)c;
    if(count) result[count] = 0;
    fflush(interface->ptr);
    return count;
}
