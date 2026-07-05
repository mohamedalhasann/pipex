# pipex

`pipex` is a 42 project that recreates a basic shell pipe, it takes one input file, runs two commands, and writes the result to an output file

## Build

```bash
make
```

## usage

```bash
./pipex infile "cmd1" "cmd2" outfile
```

example:
```bash
./pipex input.txt "cat" "wc -l" output.txt
```

this reads from `input.txt`, sends it through `cat`, pipes the result to `wc -l`, saves the final output in `output.txt`