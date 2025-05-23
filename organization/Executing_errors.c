That FD 4 isn’t something your code explicitly called open() on — it’s the pseudo-terminal (the slave side of /dev/pts/1) that your shell is running in. Valgrind by default reports all open descriptors ≥ 3 that it inherited from its parent, even if your program never touched them.
Why it shows up

    Inherited pty
    When you run under Valgrind in an interactive terminal, Valgrind itself opens /dev/pts/1 (or whatever your tty is) so it can capture the program’s input/output. Your shell inherits that descriptor but never closes it.

    Valgrind’s policy
    Valgrind considers “open file descriptor at exit” ≥ 3 to be a potential leak, regardless of whether your code opened it or merely inherited it.

What you can do

    Ignore it
    It’s not a leak in your code. It’s the terminal device that Valgrind opened for you. Functionally, it doesn’t hurt anything.
