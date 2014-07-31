CC = g++
CPPFLAGS = -Wall -ansi -pedantic -O3 -std=c++11

objects = Compress.o Compressor.o SSTree.o Tools.o CSA.o BitRank.o \
  ReplacePattern.o wtreebwt.o bittree.o rbtree.o CHgtArray.o CRMQ.o \
  SubblockRMQ.o Parentheses.o Hash.o LcpToParentheses.o

default: $(objects)
	$(CC) -o  Compress $(objects)

clean:
	rm -f core *.o *~ Compress 

depend:
	g++ -MM *.cpp > dependencies.mk

include dependencies.mk
