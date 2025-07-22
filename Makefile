CXX = g++


QTDIR = C:\Qt\6.6.1\mingw_64

SRC = src
BUILD = build
INCLUDE = include
PROGRAM = $(BUILD)/ManoComputerEmulator.exe



MOC = $(QTDIR)/bin/moc.exe
QT_CFLAGS = -I$(QTDIR)/include -I$(QTDIR)/include/QtCore -I$(QTDIR)/include/QtGui -I$(QTDIR)/include/QtWidgets
QT_LIBS = -L$(QTDIR)/lib -lQt6Widgets -lQt6Gui -lQt6Core



CXXFLAGS = -g -std=c++17 -Wall -I$(INCLUDE) -MMD -MP $(QT_CFLAGS)

LDFLAGS = $(QT_LIBS)


SRCS = $(wildcard $(SRC)/*.cpp)


MOC_HEADERS = $(INCLUDE)/mainwindow.h $(INCLUDE)/screenwidget.h $(INCLUDE)/emulatorcore.h


MOC_SRCS = $(patsubst $(INCLUDE)/%.h,$(BUILD)/moc_%.cpp,$(MOC_HEADERS))


OBJS = $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SRCS)) \
       $(patsubst $(BUILD)/%.cpp,$(BUILD)/%.o,$(MOC_SRCS))



all: $(PROGRAM)


$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)
	@echo.
	@echo Build finished: $(PROGRAM)

$(BUILD)/moc_%.cpp: $(INCLUDE)/%.h
	@if not exist $(BUILD) mkdir $(BUILD)
	@echo Generating moc for $<
	$(MOC) $< -o $@

$(BUILD)/%.o: $(SRC)/%.cpp
	@if not exist $(BUILD) mkdir $(BUILD)
	@echo Compiling $<
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/%.o: $(BUILD)/%.cpp
	@echo Compiling $<
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	@if exist $(BUILD) ( \
		echo Cleaning build directory... && \
		del /f /q $(BUILD)\*.* && \
		rmdir $(BUILD) \
	) else ( \
		echo Build directory does not exist. Nothing to clean. \
	)

-include $(OBJS:.o=.d)

.PHONY: all clean