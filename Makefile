CXX = g++
CXXFLAGS = -std=c++11

SRCS = PlayerMain.cpp
HEADERS = CardGame.h CardGameAdapter.h PlayerAdult.h PlayerBase.h PlayerYouth.h

TARGET = cardgame

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)