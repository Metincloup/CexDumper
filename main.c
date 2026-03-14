#include <stdio.h>
#include <stdlib.h>

#define PROGRAMNAME "CexDumper"
#define VERSION "v0.0.1"

void printUsage(char const *fileName)
{

    printf("Usage: %s <filename>", fileName);
    // Print arguments here
}

int main(int argc, char const *argv[])
{
    printf("%s %s - C Hex Dumper\n\n", PROGRAMNAME, VERSION);

    FILE *fp;
    size_t length;
    char *buffer;
    unsigned int position = 0;
    const char *filePath;

    if (argc < 2)
    {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }
    filePath = argv[1];

    fp = fopen(filePath, "rb");
    if (!fp)
    {
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    fseek(fp, 0L, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    printf("File length is : %ld \n", length);

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
    //  Don't print text and length in the future
    printf("Text in %s file:\n%s\n\n\n\n", filePath, buffer);

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
    printf("%08x", position);

    free(buffer);
    return 0;
}
