#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int fd;
    ssize_t numWritten;

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
    {
        usageErr("%s path <content>\n", argv[0]);
    }

    fd = open(argv[1], O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        errExit("open");
    }

    /* The beginnning of the offset is also controlled by the O_APPEND flag */
    lseek(fd, 0, SEEK_SET);

    numWritten = write(fd, argv[2], strlen(argv[2]));
    if (numWritten == -1)
    {
        errExit("write");
    }

    exit(EXIT_SUCCESS);
}
