C++ = g++
DFLAGS = -Wall -g
#OFLAGS = -O3
#LFLAGS = -lpthread
CFLAGS = $(DFLAGS) $(OFLAGS) $(LFLAGS)

PROGS = ProducerProcess ConsumerProcess Terminator
OBJS = Utils.o Colors.o Process.o Queue.o iProducer.o iConsumer.o
RPC = RPC/IdManager_clnt.o RPC/IdManager_xdr.o

all: $(PROGS) clean

$(OBJS): %.o: %.cpp
	$(C++) -o $@ $(CFLAGS) -c $<

$(PROGS): %: %.cpp  $(RPC) $(OBJS)
	$(C++) -o $@ $< $(RPC) $(OBJS) $(CFLAGS)

clean:
	rm -f *.o

