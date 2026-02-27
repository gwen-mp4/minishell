# Minishell Project

**IMPORTANT (by gwen at 9:00)**
Always work on another branch if the other person is working too, firstly, create a new branch and work on it, here's the plan.

*git checkout master* (to be on the master branc, if already the case)
*git pull* (to update the branch)
*git checkout -b __my-branch__* (to create and go to the newly created branch named *my-branch*)

While working
_git add *_
*git commit -m "..."*
*git push -u origin __my-branch__* (to push your branch and make you local branch into remote branch, after this command used a first time, you can use normal git push, if you're going back to master, simply git push if you're working on it for some reasons)

After finished
*git checkout master*
*git pull*
*git merge __my-branch__* (to merge your branch into master, do it at the end of the day when you're leaving)
*git push*


# Progress: 
Sid 
**11/02/2026 - 16:00** : created header file with all includes and defined a basic node structure for the parsing list. Imported libft. Did pre-parsing (cleaning) process: remove empty "" & '' and simplify spaces. Started node list creation process (completely broken, will fix tomorrow).


**11/02/2026 16:04 by gwen**:

-Added macros in *minishell.h* to let VSCode recognize sigaction struct in signal.h
-Created Makefile, to complete and test
**To do list**
-Reorganize .c files by putting them in src directory (to test Makefile)
-Put Libft functions in **libft** directory (has to be created) and put *minishell.h* in **includes** directory

**12/02/2026 16:30 by gwen**:

-Added lexing directory, modified *parsing-nodes.c* into *create_tokens.c*
-Modified *create_node* into *create_token*, so it creates a new token and add it to the back of the list with the function *add_back_token*, when detecting special characters or word.
-Added *is_space()* and *is_operator()*
-Still working on the function *lexing()*, need to add a function that check quotes if it's single quote or double quote and activate a mode to write every character indide it until the corresponding closing quote (except if there's backslash \ behind it) to the _token_ as value. If there's not corresponding closing quote, then return *"Error"*.

**12/02/2026 21:18 by gwen**:

-Added *handle_word()* and *handle_operator()* in the *lexer()* function so it will create a token and add them to the chained list, normally, a prompt like __echo "hello 'world'" | cat -e__ will be properly separated but it has to be tested, if there's any issue, feel free to modify it and note the modified line.

**13/02/2026 16:12 by gwen**:

-Modified *error_cleanup()* to print error when quote unmatched and moved the cleaning tokens into *clean_tokens()*. Also modified *clean_tokens* so there'll be no segfault, but still segfault sometimes when turning on signals and exit.
-All tests passed for lexing, as said before, need to fix segfault when exitting but I think we can fix it after environment and etc... are all setup for better understanding on how to fix
-And most importantly, *Makefile* is done, please add additional source files in SRC and make (and also, if you have modified the header file betweentimes, do *make re*)

**13/02/2026 18:30 by storck**:

-Added fd in and out to data structure. Started the process of interpreting the command in token list: "<" opens infile, ">" opens or create outfile in truncate mode, ">>" opens or create outfile in  append mode. Also imported usefull functions from pipex: process to get command paths from env and process for forking, piping, redirecting fd and opening input and output files.
-started pipe execution process. Will need tweaking to work with the token list logic.

**16/02/2026 12:54 by gwen**:

-Fixed segfault if quote error
-Added *t_quote* struct and added to *t_data*
-Modified the lexing so that it doesn't take quote/unnecessary quote, e.g: echo "hello 'world'" -> echo hello 'world'
-Backslashes are not required in the subject (keep in my mind)
-Added *s_cmd* struct, have to complete *s_redirs* struct
-Going to start parsing next time, separate the prompt into av (argv) and redirs (<, <<, >, >>) with the pipe (|) as separator
e.g: _cat < test.txt > out | grep t | wc -l_ is going to be:

__cmd1:__
*av = ["cat", NULL]*
*redirs = [< test.txt, > out]*
*next = cmd2*

__cmd2:__
*av = ["grep", "t", NULL]*
*redirs = []*
*next = cmd3*

__cmd3:__
*av = ["wc", "-l", NULL]*
*redirs = []*
*next = NULL*

**17/02/2026 19:00 by gwen**:

-Added *s_cmd* and *s_redir* struct and added it to *s_data*
-Added parsing, adding tokens to commands, WORD into **argv and REDIRS into *redir
-Added free commands that free argv, redirs and command and added the functions in free_data()
-Moved Error/error.c into Utils directory
-Created free.c in Utils and moved free_data() in free.c
-Have to test it presented as previous written plan
To-do: add 42 header for Parsing/create_cmd.c, Parsing/parsing_utils.c and Utils/free.c


**18/02/2026 14:30 by storck**:

-Started the execution process that matches the parsing, needs testing.
-Need discution to match proprely the parsing and execution.

**20/02/2026 15:15 by gwen**:

-Lexing and parsing are all good, perhaps need to fix free (at the end)
-Started to manage and print error if the prompt if invalid

**20/02/2026 18:30 by storck**:

-Adapted the file descriptor redirection process to work with the parsing output, might need fixing for case with 0 pipe (aka signe command prompts).
-Started the process for HEREDOC. Opens a temporary file and write the read from readline() up to the limiter, then uses it's fd as if "<<" was "<".
TODO: Use unlink after the prompt process has ended to destroy the file created.

=======
**23/02/2026 13:00 by storck**:

-Debbuged and started testing the execution of commands. Remaining Buggs:
    ~~- Doesn't read Infile (Cause fd redirection issues sometiems but not others, content is never red);~~
    ~~- Error when passing a pipe (More fd redirection issues)~~
    ~~- Simple command with both input and output file cause infinite loop.~~

**25/02/2026 15:00 by storck**:

-Fixed simple commands that was broken because was trying to process as a pipe. ~~Need to fix processes with pipes.~~
-Fixed when managing pipes, seems to work but new issue: cmd exits program.
-Fixed the problem for single cmd, working on a fix for pipe cmd. Problems seems to happen on next readline(), as if an emprty line was red.

**26/02/2026 12:00 by storck**:

-All pipes are piping! Call me the plumber!

**27/02/2026 13:00 by storck**:

-Started addinf builting cmds, need testing.
    TODO builtins:  -export
                    -unset
                    -env
                    -exit
-Found a bug when processing pipe with undefined read or write pipe.