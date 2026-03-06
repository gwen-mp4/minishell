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

**02/03/2026 15:45 by gwen**:

-Modified signals so it manages SIGINT, SIGQUIT and SIGTSTP
-Added *signal_heredoc()* and *signal_child()*:
    *signal_heredoc()*:
        -Use the heredoc signal when using heredoc, I've modified the function *fill_doc()* so it manages signals but still need to be fix when exitting heredoc
    *signal_child()*:
        -Use the child signal when a child is processing (a command is executing), have to add, didn't add it.

**03/03/2026 12:00 by storck**:

-Fixed the problem that caused faulty fd redirection when executing a command without a set infile or outfile.
-Fixed an issue with Bulit-in commnads that caused them to behave weirdly at exit (needed Ctrl+D one more time for each built-ins executed before exiting minishell)
-Tested echo and pwd, all seems fine.
    TODO:   -test cd
            -code export
            -code unset
            -code env
            -code exit

**03/03/2026 14:00 by gwen**:

-It seems that there're several major problems while interpreting, *heredoc segfault*.
## Valgrind indicates:
    ==2268== Invalid read of size 8
    ==2268==    at 0x10ADCA: execution (in /mnt/c/Users/wenge/VS Code C/Coding/minishell/minishell)
    ==2268==    by 0x1095C7: main (in /mnt/c/Users/wenge/VS Code C/Coding/minishell/minishell)
    ==2268==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
    ==2268==
    ==2268==
    ==2268== Process terminating with default action of signal 11 (SIGSEGV)
    ==2268==  Access not within mapped region at address 0x0
    ==2268==    at 0x10ADCA: execution (in /mnt/c/Users/wenge/VS Code C/Coding/minishell/minishell)
    ==2268==    by 0x1095C7: main (in /mnt/c/Users/wenge/VS Code C/Coding/minishell/minishell)
    ==2268==  If you believe this happened as a result of a stack
    ==2268==  overflow in your program's main thread (unlikely but
    ==2268==  possible), you can try to increase the size of the
    ==2268==  main thread stack using the --main-stacksize= flag.
    ==2268==  The main thread stack size used in this run was 8388608.
If you can fix it
-Added some protections to input/output redirection so if fd < 0, return EXIT_FAILURE.
=======
**03/03/2026 17:00 by storck**:

-Continued builtins (unset, exit and export), still need to do env and some utils functions.

**add all builtin files and exec_builtin.c after finishing

**04/03/2026 16:10 by gwen**:

-Fixed heredoc, now it works (perfectly? still need more hardcore test)
-Fixed signals issues
-Need to fix norm (a lot, i'm not kidding)

**03/04/2026 17:00 by storck**:

-Gestion des variables: ce que ca fait pour l'instatnt
    -Si le av[0] d'un token de command contient un '=', cree une nouvelle variable dans data (il faut ajouter une securite pour empecher de creer plusieures variables avec le meme nom et plutot changer le content de la variable)
    -remonte tout les mots dans av[] de un, free le dernier;
-TODO: si $<NOM_D'UNE_VARIABLE> est lue ans une commane et est entre "", aller chercher le content de la variable et remplacer le $(...) par le content. (Doit etre fait avant que l'execution soit lancee).

**05/03/2026 14:15 by gwen**:

### I forgot to write but to the functions to test if commands/tokens work well, I've moved them into *debug.c* file in _Utils_
-Added SINGLE, DOUBLE, NO_QUOTE in cmd so you can work on expand ($) now
-Need to fix heredoc when EOF and then SIGINT (and check parsing if still good while managing quote or not)

**03/06/2026 10:30 by storck**:

-Attached the variable replacement process. Expand ($) should work fine now.
-Going to fix norminette for the rest of the day.
