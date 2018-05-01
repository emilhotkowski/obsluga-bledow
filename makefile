CC=g++
CFLAGS=-Wall -std=c++0x -pthread -L/usr/lib/mysql -lmysqlclient
OFILES=serverThread.o tcpUtil.o loginUtil.o dbUtil.o logger.o

all: serwerTCP.cpp $(OFILES)
	$(CC) serwerTCP.cpp $(OFILES) -o serwer $(CFLAGS)

serverThread.o:  serverThread/serverThread.h serverThread/serverThread.cpp
	$(CC) -c serverThread/serverThread.h serverThread/serverThread.cpp $(CFLAGS)

tcpUtil.o: tcpUtil/tcpUtil.h tcpUtil/tcpUtil.cpp
	$(CC) -c tcpUtil/tcpUtil.h tcpUtil/tcpUtil.cpp $(CFLAGS)

loginUtil.o: functions/loginUtil.h functions/loginUtil.cpp
	$(CC) -c functions/loginUtil.h functions/loginUtil.cpp $(CFLAGS)

dbUtil.o: dbUtil/dbUtil.h dbUtil/dbUtil.cpp
	$(CC) -c dbUtil/dbUtil.h dbUtil/dbUtil.cpp $(CFLAGS)

logger.o: logging/logger.h logging/logger.cpp
	$(CC) -c logging/logger.h logging/logger.cpp $(CFLAGS)


clean: 
	rm serwer $(OFILES)