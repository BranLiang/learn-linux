#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int fd, openFlags;
    int i;
    int x = 0;

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
    {
        usageErr("%s filename num-bytes [x]\n", argv[0]);
    }

    if (argc == 4 && strcmp(argv[3], "x") == 0)
    {
        x = 1;
    }

    if (x)
    {
        openFlags = O_RDWR | O_CREAT;
    }
    else
    {
        openFlags = O_RDWR | O_CREAT | O_APPEND;
    }


    fd = open(argv[1], openFlags, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        errExit("open");
    }

    for (i = 0; i < atoi(argv[2]); i++)
    {
        if (x)
        {
            if (lseek(fd, 0, SEEK_END) == -1)
            {
                errExit("lseek");
            }
        }
        if (write(fd, "a", 1) == -1)
        {
            errExit("write");
        }
    }

    exit(EXIT_SUCCESS);
}
