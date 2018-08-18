/*
https://www.gnu.org/software/libc/manual/html_node/Creating-a-Pipe.html

Here is an example of a simple program that creates a pipe.
This program uses the fork function (see Creating a Process) to create a child process.
The parent process writes data to the pipe, which is read by the child process.

大致意思就是，父进程先 fork() 出一个子进程
然后父进程向 pipe 里面写 "hello, world!\n", "goodbye, world!\n"
接着子进程从 pipe 读出上面的字符串

有一个疑问，这里没有使用 wait
由于并发的不确定性，某次执行的时候有可能先进入子进程，此时管道里啥东西都没有，按理来说这个时候是读不出东西来的
但是每次运行，都能读出 "hello, world!\n", "goodbye, world!\n"
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Read characters from the pipe and echo them to stdout. */
void read_from_pipe (int fd) {
	FILE *stream;
	int c;
	stream = fdopen(fd, "r");
	while ( ( c = fgetc(stream) ) != EOF ){
		putchar (c);
	}
	fclose (stream);
}

/* Write some random text to the pipe. */
void write_to_pipe (int fd) {
	FILE *stream;
	stream = fdopen(fd, "w");
	fprintf(stream, "hello, world!\n");
	fprintf(stream, "goodbye, world!\n");
	fclose(stream);
}

int main (void) {
	pid_t pid;
	int fd[2] = {0, 0};

	/* Create the pipe.
	 * succ: 0
	 * fail: -1
	*/
	if ( pipe (fd) ) {
		fprintf (stderr, "Pipe failed.\n");
		return EXIT_FAILURE;
	}

	/* Create the child process.
	 * succ: >= 0
	 * child: 0
	 * parent: > 0
	 * fail: -1
	*/
	pid = fork ();

	/* This is the child process. */
	if ( pid == (pid_t)0 ) {
		close( fd[1] );			// Close other end first.
		read_from_pipe( fd[0] );
		return EXIT_SUCCESS;
	}

	/* fork() failed. */
	else if ( pid < (pid_t)0 ) {
		fprintf (stderr, "Fork failed.\n");
		return EXIT_FAILURE;
	}

	/* This is the parent process. */
	else {
		close( fd[0] );			//Close other end first. 
		write_to_pipe( fd[1] );
		return EXIT_SUCCESS;
	}

}