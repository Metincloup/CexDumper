#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define PROGRAMNAME "CexDumper"
#define VERSION "v0.3"

void printUsage(char *fileName)
{
    printf("%s %s - C Hex Dumper\n\n", PROGRAMNAME, VERSION);
    printf("Usage: %s [options] <filename>\n\n", fileName);
    printf("Options:\n  -h        Show this help message\n  -v        Verbose output\n  -V        Show version\n  -o <file> Write output to file");

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{

    FILE *fp;
    size_t length;
    char *buffer;
    int opt;
    unsigned int position = 0;
    char *inputFilePath;
    char *outputFilePath;

    if (argc < 2)
    {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    inputFilePath = argv[argc - 1];

    while ((opt = getopt(argc, argv, ":o:hvV")) != -1)
    {
        switch (opt)
        {
        case 'o':
            printf(optarg);
            outputFilePath = argv[optind];
            break;
        case 'v':
            printf("%s %s\n\n", PROGRAMNAME, VERSION);
            exit(EXIT_SUCCESS);
            break;
        case 'h':
            printUsage(argv[0]);
            break;

        default:
            break;
        }
    }

    fp = fopen(inputFilePath, "rb");
    if (!fp)
    {
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    fseek(fp, 0L, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    buffer = (char *)calloc(length, sizeof(char));
    if (buffer == NULL)
    {
        perror("Could not allocate buffer using calloc");
        return EXIT_FAILURE;
    }

    if (fread(buffer, sizeof(char), length, fp) != length)
    {
        perror("Could not read whole file");
        return EXIT_FAILURE;
    }
    fclose(fp);

    for (size_t i = 0; i < length; i = i + 2)
    {
        if (i % 16 == 0)
        {
            printf("\n");
            printf("%08x ", position);
        }
        printf("%x%x ", buffer[i], buffer[i + 1]);
        position = position + 2;
    }
    printf("\n");
    printf("%08lx", length);

    free(buffer);
    return 0;
}
