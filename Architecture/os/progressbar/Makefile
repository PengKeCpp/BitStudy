cc=gcc
bin=proc
file_lists=main.o proc.o

$(bin):$(file_lists)	
	$(cc) $^ -o $@
%.o:%.c
	$(cc) -c $<

.PHONY:clean
clean:
	rm -f $(file_lists) $(bin)

