OPTS=-Wall -g -std=c++11
OBJS=pracc4.o ToDo.o Project.o List.o Task.o Util.o
CC=g++

prac3: $(OBJS)
	$(CC) $(OPTS) $(OBJS) -o pracc4

pracc4.o: pracc4.cc ToDo.h Project.h Util.h
	$(CC) $(OPTS) -c pracc4.cc

ToDo.o: ToDo.cc ToDo.h Project.h Util.h
	$(CC) $(OPTS) -c ToDo.cc

Project.o: Project.cc Project.h List.h Util.h
	$(CC) $(OPTS) -c Project.cc

List.o: List.cc List.h Task.h Util.h
	$(CC) $(OPTS) -c List.cc

Task.o: Task.cc Task.h Util.h
	$(CC) $(OPTS) -c Task.cc

Util.o: Util.cc Util.h
	$(CC) $(OPTS) -c Util.cc

clean:
	rm $(OBJS)
