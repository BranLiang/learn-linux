#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
    int outputFd, openFlags, numRead;
    int option;
    char buf[BUF_SIZE];

    openFlags = O_CREAT | O_WRONLY;

    /* Parse the cmd option */
    option = getopt(argc, argv, "a");
    if (option == -1)
    {
        openFlags |= O_TRUNC;
    }

    while(option != -1)
    {
        switch (option)
        {
        case 'a':
            openFlags |= O_APPEND;
            break;
        default:
            break;
        }
        option = getopt(argc, argv, "a");
    }

    if (argv[optind] == NULL || strcmp(argv[1], "--help") == 0)
    {
        usageErr("%s [-a] file\n", argv[0]);
    }

    /* Open output file */
    outputFd = open(argv[optind], openFlags, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if (outputFd == -1)
    {
        errExit("opening file %s", argv[1]);
    }

    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
        if (write(outputFd, buf, numRead) != numRead)
        {
            fatal("write() returned error or partial write occurred");
        }
        if (write(STDOUT_FILENO, buf, numRead) != numRead)
        {
            fatal("write() returned error or partial write occurred");
        }
    }

    if (numRead == -1)
    {
        errExit("read");
    }

    if (close(outputFd) == -1)
    {
        errExit("close input");
    }

    exit(EXIT_SUCCESS);
}
