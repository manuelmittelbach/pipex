*This project has been created as part of the 42 curriculum by mmittelb.*

# pipex

## Description

`pipex` is a C program that explores how the Unix shell handles pipes, redirections, and process execution.

The purpose of the project is to build a deeper understanding of:

- processes and `fork()`
- inter-process communication with `pipe()`
- file descriptor duplication with `dup2()`
- program execution with `execve()`
- input/output redirections
- error handling and cleanup in multi-process programs

### Program Behavior

The mandatory program behaves like this shell command:

```bash
< infile cmd1 | cmd2 > outfile
```

So this:

```bash
./pipex infile "grep hello" "wc -l" outfile
```

is equivalent to:

```bash
< infile grep hello | wc -l > outfile
```

### How it works

1. **Create a pipe**

   - A pipe is created so the output of the first command can become the input of the second command.

2. **Fork the process**

   - The program creates a child process with `fork()`.
   - One process handles the first command, the other handles the second.

3. **Redirect input and output**

   - The first command reads from the input file and writes to the pipe.
   - The second command reads from the pipe and writes to the output file.

4. **Resolve and execute commands**

   - The program searches the `PATH` environment variable to find the executable.
   - Commands are split into arguments and executed with `execve()`.

5. **Handle errors and free resources**

   - File descriptors are closed when no longer needed.
   - On failure, allocated memory and open pipes are cleaned up before exiting.

### Bonus Program Overview

The bonus version extends `pipex` with two additional features:

- **Multiple pipes**
  - Supports more than two commands.
  - Example:

    ```bash
    ./pipex infile "cat" "grep 42" "wc -l" outfile
    ```

    behaves like:

    ```bash
    < infile cat | grep 42 | wc -l > outfile
    ```

- **here_doc**
  - Supports shell-like heredoc input.
  - Instead of reading from an input file, the program reads from standard input until the limiter is reached.
  - In `here_doc` mode, the output file is opened in append mode.

  Example:

  ```bash
  ./pipex here_doc LIMITER "cat" "wc -l" outfile
  ```

  behaves like:

  ```bash
  << LIMITER cat | wc -l >> outfile
  ```

The bonus source files are located in the `bonus/` folder.

## Instructions

### Compile mandatory part

```bash
make
```

This creates the executable `pipex`.

### Run mandatory part

Use the following format:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Example:

```bash
./pipex infile "cat" "tac" outfile
```

Equivalent shell behavior:

```bash
< infile cat | tac > outfile
```

### Compile bonus part

```bash
make bonus
```

This also creates the executable `pipex`, but with the bonus features enabled.

### Run bonus part

#### Multiple pipes

```bash
./pipex infile "cmd1" "cmd2" "cmd3" outfile
```

Example:

```bash
./pipex infile "cat" "grep hello" "wc -l" outfile
```

Equivalent shell behavior:

```bash
< infile cat | grep hello | wc -l > outfile
```

#### here_doc

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```

Example:

```bash
./pipex here_doc STOP "cat" "wc -c" outfile
```

Type lines into standard input and finish with the limiter:

```text
hello
42
STOP
```

Equivalent shell behavior:

```bash
<< STOP cat | wc -c >> outfile
```

## Project Structure

### Mandatory files

- `pipex.c` - main entry point for the mandatory program
- `execute_command.c` - command resolution and execution with `execve()`
- `error_handling.c` - file, pipe, and process error handling
- `helpers.c` / `libft_utils.c` / `ft_split.c` - utility functions
- `pipex.h` - mandatory header

### Bonus files

Located in the `bonus/` folder:

- `pipex_bonus.c` - bonus entry point
- `multiple_pipes_bonus.c` - support for multiple commands
- `here_doc_bonus.c` - heredoc handling
- `execute_command_bonus.c` - command execution for the bonus part
- `cleanup_bonus.c` - cleanup helpers for pipes and child processes
- `error_handling_bonus.c` - bonus error handling
- `get_next_line_bonus.c` - line-by-line input reading for `here_doc`
- `pipex_bonus.h` - bonus header

## Notes

- Commands should be passed in quotes when they contain spaces.
- The program searches executables through the `PATH` environment variable.
- If a command does not exist, the program prints a `command not found` error.
- The mandatory part expects exactly 4 arguments after the executable name.
- The bonus part accepts a variable number of commands.

## Credits / References

This project is inspired by standard Unix shell behavior and focuses on reproducing pipe and redirection mechanics using low-level system calls in C.
