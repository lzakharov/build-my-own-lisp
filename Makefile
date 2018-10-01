src = $(wildcard src/*.c)
obj = $(src:.c=.o)

lispy: $(obj)
	$(CC) -o $@ $^

.PHONY: clean
clean:
	rm -f $(obj) lispy
