#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define PROGRAMNAME "CexDumper"
#define VERSION "v0.4"

void printUsage(char *fileName)
{
    printf("%s %s - C Hex Dumper\n\n", PROGRAMNAME, VERSION);
    printf("Usage: %s [options] <filename>\n\n", fileName);
    printf("Options:\n  -h        Show this help message\n  -v        Show version\n  -o <file> Write output to file");

    exit(EXIT_SUCCESS);
}

int saveToFile(char *inputFilePath, char *outputFilePath)
{
    FILE *fp;
    size_t length;
    char *buffer;
    unsigned int position = 0;

    fp = fopen(inputFilePath, "rb");

    if (!fp)
    {
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    fseek(fp, 0L, SEEK_END);
    length = ftell(fp);

    if (length == -1L)
    {
        perror("Could not get length of the file");
        fclose(fp);
        return EXIT_FAILURE;
    }

    fseek(fp, 0L, SEEK_SET);
    buffer = (char *)calloc(length, sizeof(char));

    if (buffer == NULL)
    {

        fclose(fp);
        perror("Could not allocate buffer using calloc");

        return EXIT_FAILURE;
    }

    if (fread(buffer, sizeof(char), length, fp) != length)
    {
        perror("Could not read whole file");
        fclose(fp);
        free(buffer);
        return EXIT_FAILURE;
    }
    fclose(fp);

    fp = fopen(outputFilePath, "wb");

    if (!fp)
    {
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < length; i = i + 2)
    {
        if (i % 16 == 0)
        {
            if (i != 0)
            {
                fprintf(fp, "\n");
            }

            fprintf(fp, "%08x", position);
        }

        if (length % 2 == 1 && position == length - 1)
        {
            fprintf(fp, " %x", buffer[i]);
            position = position + 1;
        }
        else
        {
            fprintf(fp, " %x%x", buffer[i], buffer[i + 1]);
            position = position + 2;
        }
    }
    fprintf(fp, "\n");
    fprintf(fp, "%08lx", length);

    fclose(fp);
    free(buffer);

    return 0;
}

int main(int argc, char *argv[])
{
    FILE *fp;
    size_t length;
    char *buffer;
    int opt;
    unsigned int position = 0;
    char *inputFilePath = NULL;
    char *outputFilePath = NULL;

    if (argc < 2)
    {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }
    inputFilePath = argv[argc - 1];

    while ((opt = getopt(argc, argv, ":o:hv")) != -1)
    {
        switch (opt)
        {
        case 'o':

            outputFilePath = optarg;
            int success = saveToFile(inputFilePath, outputFilePath);
            if (success != 0)
            {
                fprintf(stderr, "Could not save to file\n");
                return success;
            }

            break;
        case 'v':
            printf("%s %s\n\n", PROGRAMNAME, VERSION);
            exit(EXIT_SUCCESS);
            break;
        case 'h':
            printUsage(argv[0]);
            break;
        default:
            fprintf(stderr, "Please specify valid arguments");
            printUsage(argv[0]);

            break;
        }
    }
    if (outputFilePath != NULL)
    {
        return EXIT_SUCCESS;
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

    if (length == -1L)
    {
        perror("Could not get length of the file");
        fclose(fp);
        return EXIT_FAILURE;
    }

    buffer = (char *)calloc(length, sizeof(char));

    if (buffer == NULL)
    {
        perror("Could not allocate buffer using calloc");
        return EXIT_FAILURE;
    }

    if (fread(buffer, sizeof(char), length, fp) != length)
    {
        perror("Could not read whole file");
        fclose(fp);
        return EXIT_FAILURE;
    }
    fclose(fp);

    for (size_t i = 0; i < length; i = i + 2)
    {
        if (i % 16 == 0)
        {
            if (i != 0)
            {
                printf("\n");
            }

            printf("%08x", position);
        }
        if (length % 2 == 1 && position == length - 1)
        {
            printf(" %x", buffer[i]);
            position = position + 1;
        }
        else
        {
            printf(" %x%x", buffer[i], buffer[i + 1]);
            position = position + 2;
        }
    }
    printf("\n");
    printf("%08lx", length);

    free(buffer);

    return 0;
}
