NAME = bokeh_emu
PROGRAM = $(NAME).exe
CXXFLAGS= -O2

LDFLAGS=-lopencv_core.dll -lopencv_highgui.dll -lopencv_imgcodecs.dll -lopencv_imgproc.dll -lm 
OBJECTS=$(NAME).o

.SUFFIXES: .cpp .o

$(PROGRAM): $(OBJECTS)
	$(CXX)  $^  -o $(PROGRAM) $(LDFLAGS) 

.c.o:
	$(CXX) -c $(CXXFLAGS) $<

.PHONY:clean
clean:
	rm -f $(NAME).exe  *.o
