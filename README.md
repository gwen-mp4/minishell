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