# CexDumper v0.4

Small hex dumper written in C.

## What It Does

- Reads a file in binary mode
- Prints file bytes in hex format to terminal
- Can save hex dump output to a file
- Supports basic CLI flags

## Build

Compile with GCC:

```bash
gcc main.c -o CexDumper -Wall -Werror
```

## Usage

```bash
./CexDumper [options] <input_file>
```

## Options

- `-h` Show help
- `-v` Show program version
- `-o <file>` Save dump output to file

## Examples

Print dump to terminal:

```bash
./CexDumper example.txt
```

Save dump to file:

```bash
./CexDumper -o output.hex example.txt
```

Show version:

```bash
./CexDumper -v
```

Show help:

```bash
./CexDumper -h
```

## Output Format

- Each line starts with an offset
- Hex byte groups are printed after the offset
- Final file length/offset summary is printed at the end

## Roadmap

- [x] Read file and print dump to console
- [x] Add CLI options (`-h`, `-v`, `-o`)
- [x] Save hex dump to output file
- [ ] Add canonical hex + ASCII view
- [ ] Add output formats (octal, decimal)
- [ ] Add skip/length arguments
