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

**06/03/2026 14:00 by gwen**:

#### -Tested (maybe) all possibilities with heredoc and it works perfectly well, fixed signals and heredoc
*for storck*:
__# -Tested some command and some didn't pass, need to fix__
        -_yes | head -n 5_ should end immediatly and print 5 y on a newline consecutively without any delay, that means maybe that a write-end pipe is still open somewhere and has to be closed.
        -_sleep 1 | echo hello_ should immediatly display hello without sleeping 1sec, a pipe is not closed properly
        -_yes | head -n 10000 | wc -l_ should display 10000 and not freeze
    **TL:DR**: it's essentially not closed pipe

**09/03/2026 18:55 by gwen**:

#### -Fixed sleep and yes problems, it was waitpid parent waiting for child problem (and not pipe closing problem)
     -Fixed potential leaks issues in execution and zombies
     -Changed strncmp (yes you did that) and ft_strncmp to ft_strcmp (that I've added the 05/03) to avoid error like "echo" still work if we write "ec"
### -If you use ft_strncmp again, make sure that it's correct, otherwise use ft_strcmp
# -Problem to fix:
#   -The command "cd" doesn't work
#   -filter_var has to be fixed asap cuz it segfault

**03/10/2026 16:45 by storck**:

-Fixed all problems with builtins except an issue with nset that don't work on exported values. Will fix tomorrow.

**11/03/2026 12:15 by gwen**:

-Improved displaying errors while parsing and lexing
-Fixed double free and leaks
## Commands I've test that didn't work
#### echo            | cat -e    *it should display $ on a newline instead of a newline*
#### echo -n -n      *it should not print anything, just a newline*
#### echo -n -n Hola Que     *it should print __Hola Que__ instead of __-n Hola Que__*
#### echo -nnnnnnnnnnn       *it should display a newine instead of __-nnnnnnnnnnn__, it should manage multiple n*
#### echo -n -nnn -nnnn      *same thing as above*
#### echo -n -nnn hola -nnnn     *same thing as above, it should display __hola -nnnn__ not on a newline*
#### export      *export doesn't work*
###     there're also other export errors display like **invalid option** and **event not found** that I'm not sure if we need to put it or not but I guess no because its not asked but just in case
####    I've also improved the error display in **exec_export** by adding details in error
###     I'm not sure if **!** is required in *export HOLA=bon!jour*
## 304/739 tests done (at least half or 1/3 of tests are skipped because of $)

**12/03/2026 11:15 by gwen**:

-Segfault when CTRL+D without writting any prompt
-Problem when freeing (clean_tokens), try *echo hola|||cat*, *echo hola > > bonjour*
## Commands I've test that didn't work
### If testing, make sure to exit minishell and then relaunch if you've unset real export
##### Code color, if **yellow**, it's optional, otherwise (base color) it's mandatory, **green** if it's solved
#### unset PATH --> ls       *it should display **ls: command not found** because we've unset PATH*
#### unset PATH --> cat Makefile *it should display **cat: command not found***
### unset PWD --> cd $PWD --> pwd       *it should go to $PWD but displays **No such file or directory** instead so pwd doesn't displays what wanted: /home/$USER*
~~### pwd -p      *it's an invalid option*~~
~~### pwd --p     *same as above*~~
~~### pwd ---p    *same as above*~~
~~### cd src obj      *it should display an error that says **too many arguments** when there's more than 1 argument in cd*~~
~~cd $HOME/goinfre~~    *it displays **No such file or directory** but it should **go to $HOME and go to goinfre***
~~cd "$PWD/src"~~       *it displays **No such file or directory** but it should **go to src***
~~cd $HOME/~~       *same as above, i think it's because it doesn't manage the slash '/'*
~~mkdir a --> mkdir a/b --> cd a/b --> rm -r ../../a --> echo $PWD --> echo $OLDPWD~~      *it should display the actual pwd path when doing echo $PWD, for example: **/home/$USER/minishell/a/b** but there's nothing, echo $OLDPWD is okay*
~~mkdir a --> cd a --> rm -r ../a --> echo $PWD --> echo $OLDPWD~~      *same as above, echo $PWD show nothing but $OLDPWD is okay*
### chmod 000 minishell     *there're 2 errors: **no such file or directory** and **command not found**, maybe change it to one by **permission denied**, i think you've created functions for that situation right?*
All tested, now going to use differents testers to see if it's right
And all segfault are managed from CTRL+D and redirections

**13/03/2026 14:45 by gwen**:

-Added exit code, now have to do for signals
## Tests that didn't pass
~~echo $~~      *it should print the dollar sign but there's nothing*
~~echo $?$~~    *it should print the exit code with the dollar sign at the end*
~~echo $:$= | cat -e~~      *it should display $:$=$*
~~echo " $ " | cat -e~~     *it should display as it should, test with bash*
~~echo $USER$HOME~~     *it should display what it should be but there's nothing (manage multiple dollar sign in a row)*
~~echo $HOME%~~     *it should display home with % at the end*
~~echo [$HOME]~~    *it should display home)*
~~echo [$TERM4~~    *it should display '[' but there's nothing*
~~echo [$TERM4]~~   *it should display '[]' but there's nothing*
~~echo "$"""~~      *it should display the dollar sign, take the single quote version as a reference*
~~echo $"HOME"~~    *it should not display the actual home but $HOME, take the single quote version as a reference*
~~echo $""HOME~~    *same as above*
~~echo "$HO"ME~~    *it should print __ME__ but it prints the actual home*
~~echo "$HO""ME"~~  *same as above*
~~echo "'$HO''ME'"~~    *it should print __'''ME'__ but there's nothing*
~~echo ''$HOME~~    *it should print the actual home*
~~echo $"HO""ME"~~  *it should not display the actual home but $HOME, take the single quote version as a reference*
~~echo "$"HOME~~    *it should not display the actual home but $HOME, take the single quote version as a reference*
~~echo $=HOME~~     *it should display what it should be*
~~echo $"HOLA"~~    *it should display $HOLA, but there's nothing, take single quote as a reference*
~~echo $DONTEXIST Hola~~    *there's a space before Hola, there should be no space*
~~echo "$DONTEXIST"Makefile~~   *it should display __Makefile__ (not the real)*
~~echo "$DONTEXIST""Makefile"~~     *same as above*
~~$?$?~~        *it should display __00: command not found__*
~~?$HOME~~      *it should print __command not found__ as error and not __No such file or directory__*
~~\$~~       *(there's backslash to ignore dollar command in README.md but it's just a dollar sign) it should print __command not found__ as error and not __Is a directory__*
~~\$HOMEdskjhfkdshfsd~~      *(there's backslash to ignore dollar command in README.md) it should print nothing*
~~"$HOMEdskjhfkdshfsd"~~    *it should print __command not found__ error instead of __Is a directory__*
~~\$DONTEXIST~~      *(there's backslash to ignore dollar command in README.md) it should print nothing*
~~$LESS$VAR~~       *it should print __-R: command not found__*
~~export $DONTEXIST~~       *it should print the export list*
~~export $?~~       *it should print __'0': invalid identifier__*
~~export HO$?LA=bonjour  --> env~~		*it should print __HO(exit_code)LA=bonjour__*

**13/03/2026 17:45 by storck**:

Fixed ab bunch of errors (those in ~~dash~~). The ones left might require touching the lexing and parsing because of quotes.

**16/03/2026 23:30 by gwen**:

So i checked how the bash works, in reality, in lexing, it copies all the prompt, including the quotes, so i just let the lexing copies the quotes too, so you have to manage the '$' sign in the expander and remove it after (before execution, that's how bash works)
You've said that it should look like this:
av[0] = $HO
av[1] = ME
but in reality, it should be like this:
av[0] = "$HO""ME"
as i wrote earlier, bash remove the quotes after expanding before execution.

**17/03/2026 14:00 by gwen**:

-Changed the whole thing for lexing, parsing and variables, changed echo and export too, now it works!
-Removed unused t_quote_type because it's useless now, the program manages all in expanding before execution
-Added signals for SIGINT and SIGQUIT
*I've used a tester (the first one that appears on a search fire fire emoji) and there's some errors, some minors (that will be set as ### (3 hashtags) before the test and some more important, tests come from the tester, not me, so you have to adjust the prompt)*
### cd $PWD     *exit code should be 1 but it's 0 and it should print **many arguments** but there's nothing*
echo <"./test_files/infile" "bonjour       42"      *the output should be **bonjour       42** but it indicates error and it quits the minishell?*
cat <"./test_files/file name with spaces"       *it should do nothing because the file is empty but it says no such file or directory, maybe it doesn't manage spaces?*
in short, i let you see by yourself using the tester but it's generally the redirections that doesn't works (except heredoc)

**19/03/2026 by gwen**:

-Not sure about these errors if we should manage them or not:
export T="echo segfault | grep segfault"  -->  $T       *bash prints "segfault | grep segfault" but for us, it prints command not found*


-unset PATH --> cd /bin --> ls      *ls should work, basically if we are in the command's folder, it can find it even if PATH is unset.*


*This project has been created as part of the 42 curriculum by gwen, storck*

# Minishell

### Description

The intent of this project is to replicate the behaviour of of a shell. It must work with the following features implemented:

-Display a prompt when waiting for a new command.
-Have a working history.
-Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
-Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
-Handle ’ (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.
-Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).
-Implement the following redirections:
    < should redirect input.
    > should redirect output.
    << should be given a delimiter, then read the input until a line containing the
    delimiter is seen. However, it doesn’t have to update the history.
    >> should redirect output in append mode.
-Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
-Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
-Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
-Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
-In interactive mode:
    ctrl-C displays a new prompt on a new line.
    ctrl-D exits the shell.
    ctrl-\ does nothing.
-Have the following built-in commands:
    echo with option -n
    cd with only a relative or absolute path
    pwd with no options
    export with no options
    unset with no options
    env with no options or arguments
    exit with no options

### Instructions

Compile with:
    make

Execute with:
    ./minishell

Delete .o files with:
    make clean

Delete .o file and ./minishell with:
    make fclean

Recompile with:
    make re

### Resources

The following article was particularly usefull in the beginning of this project to help s build our road map, understand the loging of a shell and how to breakdown the lexing and parsing of of the commands inputed in our minishell.
[text](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)

No AI was used in the making of this project.
