CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -MMD -MP 
SRC = src
BUILD = build

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SRCS))

PROGRAM = $(BUILD)/program.exe

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@del /f /q $(BUILD)\*.o >nul 2>&1
	@del /f /q $(BUILD)\*.d >nul 2>&1


# Her .cpp dosyasını .o yap
$(BUILD)/%.o: $(SRC)/%.cpp
	@if not exist $(BUILD) mkdir $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@del /f /q $(BUILD)\*.o >nul 2>&1


