#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	// stack stores the lines to print out
	stack_t *s = initstack(); // freestack isn't freeing this, so valgrind says I have a memory leak, I don't know what to do with this
	if(argc == 2) {
		printf("Requested search of directory: %s\n", argv[1]);
		printDir(argv[1], 0);
	} else if(argc == 3) {
		printf("requested search of directory: %s with name %s\n", argv[1], argv[2]);
		searchDir(argv[1], 0, argv[2], s);
	} else printf("Usage: ./ls2 <path> [exact-match-pattern]\n");
	// printf("completed search");
	// push(s, "Hello1");
	// push(s, "Hello2");
	// push(s, "Hello3");

	// // print stack
	printstack(s);

	// // free up stack
	freestack(s); 
	return 0;
}
