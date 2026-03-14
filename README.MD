# CexDumper v0.2 - C Hex Dumper

Hex Dumper written in C.

## Compilation

You can compile the project using GCC or any other standard C compiler:

```bash
gcc main.c -o CexDumper -Wall -Werror
```

## How to Run

Provide the input file path as an argument when running:

```bash
./CexDumper <filename>
```

**Example:**

```bash
./CexDumper example.txt
```

## TODOs

- [ ] Update README file
- [x] Read text file and print to console
- [x] Take arguments for "output file" "verbose" "help" "version" etc.
- [x] Turn text into hex and print
- [ ] Save hex to output file
- [ ] put ascii version of the hex on the right side
