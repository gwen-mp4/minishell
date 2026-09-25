*This project has been created as part of the 42 curriculum by gwen, storck*

# Minishell

### Description

The intent of this project is to replicate the behaviour of of a shell. It must work with the following features implemented:

- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
- Handle ’ (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).
- Implement the following redirections:
  - < should redirect input.
  - > should redirect output.
  - << should be given a delimiter, then read the input until a line containing the
    delimiter is seen. However, it doesn’t have to update the history.
  - >> should redirect output in append mode.
- Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
- Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
- In interactive mode:
  - ctrl-C displays a new prompt on a new line.
  - ctrl-D exits the shell.
  - ctrl-\ does nothing.
- Have the following built-in commands:
  - echo with option -n
  - cd with only a relative or absolute path
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options

### Instructions

Compile with:

    make

Execute with:

    ./minishell

Delete .o files with:

    make clean

Delete .o file and minishell with:

    make fclean

Recompile with:

    make re

### Resources

The following article was particularly usefull in the beginning of this project to help us build our road map, understand the logic of a shell and how to breakdown the lexing and parsing of of the commands inputed in our minishell.

[text](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)

No AI was used in the making of this project.
