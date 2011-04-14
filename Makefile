SRC_DIR = src
OBJS = main.o dictionary.o
CFLAGS = -ansi -Wall

dictionary : $(OBJS)
	gcc -g -o dictionary_example $(OBJS)

%.o : $(SRC_DIR)/%.c
	gcc -g -c $(CFLAGS) $^ -o $@

.PHONY : check
check : 

.PHONY : clean
clean :
	rm -f dictionary_example
	rm -f $(OBJS)
