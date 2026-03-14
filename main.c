#include <stdio.h>
#include <stdlib.h>

#define PROGRAMNAME "CexDumper"
#define VERSION "v0.0.1"

int main(int argc, char const *argv[])
{
    printf("%s %s - C Hex Dumper\n\n", PROGRAMNAME, VERSION);

    FILE *fp;
    size_t length;
    char *buffer;
    char *filePath = "example.txt"; // Temporary filePath until recieving from arguments

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

    printf("Text in %s file:\n%s\n", filePath, buffer);

    free(buffer);
    return 0;
}
