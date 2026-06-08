# ============================================
#   папки
# ============================================

SRC_DIR      := src
INC_DIR      := inc
RELEASE_DIR  := release
BUILD_DIR    := build

# ============================================
#   компилятор и флаги (для CLI)
# ============================================

CXX       := g++
CXX_FLAGS := -std=c++17 -I$(INC_DIR) -Wall -Werror -Wpedantic -Wextra

QT_LIBS  ?= -L/usr/lib64/qt6 -lQt6Core -lQt6Gui -lQt6Widgets
QT_FLAGS ?= -I/usr/include/qt6 -I/usr/include/qt6/QtCore -I/usr/include/qt6/QtWidgets -I/usr/include/qt6/QtGui

# ============================================
#   исходники
# ============================================

CLI_SOURCES := $(wildcard $(CLI_DIR)/*.cpp)
CLI_OBJECTS := $(patsubst $(CLI_DIR)/%.cpp, $(BUILD_CLI_DIR)/%.o, $(CLI_SOURCES))

# ============================================
#   основные цели
# ============================================

all: clean app

app: $(RELEASE_DIR)/app.exe

# ============================================
#   сборка исполняемых файлов
# ============================================

# Сборка приложения 
$(RELEASE_DIR)/app.exe: $(RELEASE_DIR) | $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake $(CURDIR) && make app
	cp $(BUILD_DIR)/app $@

# ============================================
#   служебные команды
# ============================================

$(RELEASE_DIR) $(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(RELEASE_DIR)

.PHONY: all clean app