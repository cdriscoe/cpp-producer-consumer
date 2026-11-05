CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -pthread
TARGET := producer-consumer

all: $(TARGET)

$(TARGET): src/producer_consumer.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
