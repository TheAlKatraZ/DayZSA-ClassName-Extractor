
CXX = g++
CXXFLAGS = -std=c++17 -static-libstdc++ -static-libgcc #--verbose
CXXFLAGS_Debug = -g -Wall -std=c++17 -static-libstdc++ -static-libgcc
CXXLIBS_STATIC_W = -Wl,-Bstatic -lstdc++ -lpthread -lwinpthread -ltinyxml2

CXXLIBS_W = -L./deps/lib/
CXXINCLUDEDIRS = -I./include/
CXXINCLUDEDIRS_W = -I./include/ -I./deps/include/


all:
	g++ $(CXXFLAGS_Debug) ./main.cpp -o ./XMLExtractor.exe $(CXXINCLUDEDIRS_W) $(CXXLIBS_STATIC_W) $(CXXLIBS_W)
