all: lottery stride

lottery: lottery.c
	gcc -Wall -Werror -lm -o lottery lottery.c

stride: stride.c
	gcc -Wall -Werror -lm -o stride stride.c
