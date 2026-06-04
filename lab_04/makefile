CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -fPIC
UIC = /usr/lib64/qt6/libexec/uic
MOC = /usr/lib64/qt6/libexec/moc
INCDIR = inc
SRCDIR = src
BUILDDIR = release
UIDIR = ui
TARGET = $(BUILDDIR)/app

QTFLAGS = -I/usr/include/qt6 -I/usr/include/qt6/QtCore -I/usr/include/qt6/QtWidgets -I$(INCDIR) -I$(BUILDDIR)/moc -I.
QTLIBS = -lQt6Core -lQt6Widgets -lQt6Gui

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
SOURCES := $(filter-out $(SRCDIR)/Mainwindow.cpp, $(SOURCES))
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
OBJECTS += $(BUILDDIR)/Mainwindow.o

HEADERS = $(wildcard $(INCDIR)/*.hpp)
MOC_FILES = $(patsubst $(INCDIR)/%.hpp,$(BUILDDIR)/moc/moc_%.cpp,$(HEADERS))
MOC_OBJECTS = $(patsubst $(BUILDDIR)/moc/moc_%.cpp,$(BUILDDIR)/moc/moc_%.o,$(MOC_FILES))

UIS = $(wildcard $(UIDIR)/*.ui)
UI_HEADERS = $(patsubst $(UIDIR)/%.ui,$(INCDIR)/ui_%.h,$(UIS))

all: dirs $(UI_HEADERS) $(MOC_FILES) $(TARGET)

dirs:
	@mkdir -p $(BUILDDIR) $(BUILDDIR)/moc

$(INCDIR)/ui_%.h: $(UIDIR)/%.ui
	$(UIC) $< -o $@

$(BUILDDIR)/moc/moc_%.cpp: $(INCDIR)/%.hpp
	$(MOC) $< -o $@

$(BUILDDIR)/moc/moc_%.o: $(BUILDDIR)/moc/moc_%.cpp
	$(CXX) $(CXXFLAGS) $(QTFLAGS) -c $< -o $@

$(BUILDDIR)/Mainwindow.o: $(SRCDIR)/Mainwindow.cpp $(UI_HEADERS)
	$(CXX) $(CXXFLAGS) $(QTFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(QTFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) $(MOC_OBJECTS)
	$(CXX) $(CXXFLAGS) $(QTFLAGS) $^ $(QTLIBS) -o $@

clean:
	rm -rf $(BUILDDIR) $(INCDIR)/ui_*.h

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run dirs