[![tstrassb's 42 stats](https://badge42.vercel.app/api/v2/clk7xyddm001108l1dlt4bjx7/stats?cursusId=21&coalitionId=354)](https://github.com/JaeSeoKim/badge42)

<h1 align="center">✋ BEWARE ✋</h1>

## If you are a 42 Student, do not copy/paste this project, it will be considered cheating and you will be grated -42.

# 42 Wolfsburg Cursus
## Minishell
## As beautiful as a shell

## This is the first group project of the common  core. </br>A big shoutout to my contributer: [Yana Dimitrova](https://github.com/ydimitro)

# Contents

1. [Common Instructions](#common)
2. [Mandatory Part](#manda)

# <a name="common">Common Instructions</a>

| Common Instructions | ![Logo_Monolith_small](https://user-images.githubusercontent.com/120580537/209333599-dc44418d-8ee7-42b6-8a4a-7ff328778d87.png) |
| ----- | ----- |
* Your project must be written in C.
* Your project must be written in accordance with the Norm. If you have bonus files/functions, they are included in the norm check and you will receive a 0 if there is a norm error inside.
* Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc) apart from undefined behaviors. If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
* All heap allocated memory space must be properly freed when necessary. No leaks will be tolerated.
* If the subject requires it, you must submit a Makefile which will compile your source files to the required output with the flags -Wall, -Wextra and -Werror, use cc, and your Makefile must not relink.
* Your Makefile must at least contain the rules $(NAME), all, clean, fclean and re.
* To turn in bonuses to your project, you must include a rule bonus to your Makefile, which will add all the various headers, librairies or functions that are forbidden on the main part of the project. Bonuses must be in a different file _bonus.{c/h} if the subject does not specify anything else. Mandatory and bonus part evaluation is done separately.
* If your project allows you to use your libft, you must copy its sources and its associated Makefile in a libft folder with its associated Makefile. Your project’s Makefile must compile the library by using its Makefile, then compile the project.
* We encourage you to create test programs for your project even though this work won’t have to be submitted and won’t be graded. It will give you a chance to easily test your work and your peers’ work. You will find those tests especially useful during your defence. Indeed, during defence, you are free to use your tests and/or the tests of the peer you are evaluating.
* Submit your work to your assigned git repository. Only the work in the git reposi- tory will be graded. If Deepthought is assigned to grade your work, it will be done after your peer-evaluations. If an error happens in any section of your work during Deepthought’s grading, the evaluation will stop.

<p align="right">
 <a href="https://github.com/Cerberus2290/minishell#-beware-">back to top</a>
</p>

# <a name="manda">Mandatory Part</a>

| Mandatory Part | ![Logo_Monolith_small](https://user-images.githubusercontent.com/120580537/209333599-dc44418d-8ee7-42b6-8a4a-7ff328778d87.png) |
|----------------| ----- |
| Program name | minishell |
| Turn in files | Makefile, *.h, *.c |
| Makefile | NAME, all, clean, fclean, re |
| Arguments | |
| External functs. | readline, rl_clear_history, rl_on_new_line,</br> rl_replace_line, rl_redisplay, add_history, </br>printf, malloc, free, write, access, open, read, </br>close, fork, wait, waitpid, wait3, wait4, signal, </br>sigaction, sigemptyset, sigaddset, kill, exit, </br>getcwd, chdir, stat, lstat, fstat, unlink, execve, </br>dup, dup2, pipe, opendir, readdir, closedir, </br>strerror, perror, isatty, ttyname, ttyslot, ioctl, </br>getenv, tcsetattr, tcgetattr, tgetent, tgetflag, </br>tgetnum, tgetstr, tgoto, tputs |
| Libft authorized | Yes |
| Description | Write a shell |

Your shell should:

* Display a **prompt** when waiting for a new command.
* Have a working **history**.
* Search and launch the right executable (based on the _PATH_ variable or </br>using a relative or an absolute path).
* Not use more than **one global variable**. Think about it. </br>You will have to explain its purpose.
* Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
* Handle ’ (single quote) which should prevent the shell from interpreting the meta- </br>characters in the quoted sequence.
* Handle " (double quote) which should prevent the shell from interpreting the meta- </br>characters in the quoted sequence except for $ (dollar sign).
* Implement **redirections**:
  * **<** should redirect input.
  * **>** should redirect output.
  * **<<** should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
  * **>>** should redirect output in append mode.
* Implement **pipes** (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
* Handle **environment variables** ($ followed by a sequence of characters) which should expand to their values.
* Handle **$?** which should expand to the exit status of the most recently executed foreground pipeline.
* Handle **ctrl-C, ctrl-D and ctrl-\\** which should behave like in bash.
* In interactive mode:
  * ctrl-C displays a new prompt on a new line. 
  * ctrl-D exits the shell.
  * ctrl-\ does nothing.
* Your shell must implement the following **builtins**:
  * echo with option -n
  * cd with only a relative or absolute path ◦ pwd with no options
  * export with no options
  * unset with no options
  * env with no options or arguments
  * exit with no options

The readline() function can cause memory leaks. You don’t have to fix them. </br>But that **doesn’t mean your own code, yes the code you wrote, can have memory leaks**.

### ℹ️ You should limit yourself to the subject description. </br>Anything that is not asked is not required. If you have any doubt about a requirement, take [bash](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/) as a reference. ℹ️ 

<p align="right">
 <a href="https://github.com/Cerberus2290/minishell#-beware-">back to top</a>
</p>