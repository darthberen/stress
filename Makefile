CC     := gcc
CFLAGS := -Wall --std=gnu99 -g3 -Werror

all: memory_stressor

memory_stressor: memory/main.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

clean:
	rm -f vcpu_scheduler vcpu_scheduler.o
	rm -rf naive.o
