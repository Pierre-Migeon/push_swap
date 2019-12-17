

This is the 42 project, push_swap, a part of the algorithms branch. The goal was to sort a list of unique integers using two stacks (stack_a and stack_b) using a set of seven different command options, and the challenge was to do so using as few of the commands as possible. Two programs were written, "push_swap", and "checker." The first, push_swap, takes as input a list, and generates a sequence of commands that will sort the list. This list of commands, printed to standard output, defines the steps that must be taken to sort the list. These commands can then be input into the "checker" program in order to verify that the list has been sorted. 

To compile, run:

	make all

Usage:

	push_swap [-w] [-v] [-c] [-p] sequence_of_numbers
	 (use -w to print the shortest algorithm by name after run)
	 (use -v for visualizer mode)
	 (use -c for colored visualizer mode)
	 (use -p to print sorted list)

	checker [-p] sequence_of_numbers sequence_of_commands
	 (use -p to print the sequence of numbers that results from sorting the list in the manner requested)

	tester num_elements_in_list num_replicates mode
	 (mode: either -1 to test the number of commands required to solve or -2 to run using checker to verify correct output)

9 commands may be used to sort the list, which is initially entirely stored in stack_a. The 9 commands are essentially 3 different operations performed on either stack_a, stack_b, or on both. The first operation is swap, which exchanges the first and second values in either stack_a (command sa), stack_b (sb) or both (ss). The second operation is to rotate the stack, which moves the first element of the stack to end of the stack. This operation becomes ra (rotate a), rb (rotate b), or rr (rotate both). Finally, you may reverse rotate the stacks, which moves the last element of the stack to the first position of the stack, and may be performed on stack_a (rra), stack_b (rrb) or both (rrr).

If push_swap successfully produces correct output, then the checker program will print "OK" to the terminal, or "KO" otherwise. Incorrect input is not tolerated, and will result in "Error" being printed to stdout. Examples of incorrect input to either push_swap or checker include duplicates in the list to be sorted, non-integers, and non-numbers, or for checker, incorrectly typed or non-existent commands. Commands may be piped into checker, or they may be typed directly on the terminal.

Running in Visual + color mode:

![visual mode](https://user-images.githubusercontent.com/8321639/69909034-3a7ea300-13a9-11ea-9d10-152a145615b8.png)

Example:

![example](https://user-images.githubusercontent.com/8321639/68898697-d1c6d380-06e4-11ea-9628-ed01dd13e3d3.png)

Many algorithms were tested during development, but currently only one is being used. The code is intended to built on to use multiple algorithms and run the best (least commands) as the output. This feature is being developed.

I have also written a program to test push_swap, which will produce random lists of numbers and run push_swap with them. You can specify the length of the list tested, the number of tests to run, and the type of testing mode. Right now there are two testing modes. The -1 flag runs push_swap piped to word count, in order to test the number of commands produced. The -2 flag runs push_swap and pipes the output in to the checker program, to determine whether or not the output that push_swap generates is accurate. This program can be used to verify the robustness, accuracy, and general efficiency of the push_swap program.
