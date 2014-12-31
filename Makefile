CC        = g++

IDIR      = HEADERS
SDIR      = SOURCES
ODIR      = $(SDIR)/obj
BDIR      = build

CFLAGS    = -I$(IDIR) -std=c++11 -Wall
LIBS      = 

EXEC      = air-scheduling

MAIN      = main

CLASSES   = Vertex Edge Graph Flight FlightEdgeDict FordFulkerson

DEFS      = hash_pair

DEPS      = $(patsubst %, $(IDIR)/%.h,$(DEFS)) $(patsubst %, $(IDIR)/%.h,$(CLASSES))
OBJ       = $(patsubst %, $(ODIR)/%.o,$(MAIN)) $(patsubst %, $(ODIR)/%.o,$(CLASSES))

_TARGETS  = $(EXEC)
TARGETS   = $(patsubst %, $(BDIR)/%,$(_TARGETS))

all: $(TARGETS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) $(ODIR)/.done
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/.done:
	mkdir $(ODIR)
	echo "file for checking if $(ODIR) exists" >$(ODIR)/.done

$(BDIR)/$(EXEC): $(OBJ)
	if [ ! -d "$(BDIR)" ]; then mkdir $(BDIR); fi
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

.PHONY: clean run

run: all
	$(BDIR)/$(EXEC)

clean:
	rm -rf $(BDIR) *~ rm $(IDIR)/*~ $(SDIR)/*~  $(ODIR)
