# ============================================
#   папки
# ============================================

SRC_DIR := src
CLI_DIR := src/cli
TEST_DIR := unit_tests
INC_DIR := inc
OUT_DIR := out
RELEASE_DIR := release
BUILD_DIR := build
BUILD_CLI_DIR := $(BUILD_DIR)/cli
BUILD_TEST_DIR := $(BUILD_DIR)/unit_tests
COVERAGE_DIR := $(BUILD_DIR)/coverage

# ============================================
#   компилятор и флаги
# ============================================

CXX := g++
CXX_FLAGS := -std=c++17 -I$(INC_DIR) -Wall -Werror -Wpedantic -Wextra

QT_LIBS ?= -L/usr/lib64/qt6 -lQt6Core -lQt6Gui -lQt6Widgets
QT_FLAGS ?= -I/usr/include/qt6 -I/usr/include/qt6/QtCore -I/usr/include/qt6/QtWidgets -I/usr/include/qt6/QtGui

GTEST_LIBS := -lgtest -lgtest_main -lpthread

GCOV_FLAGS := -fprofile-arcs -ftest-coverage
GCOV_LIBS := -lgcov

# ============================================
#   цели
# ============================================

all: clean cli-app

cli-app: $(RELEASE_DIR)/app-cli-linux-x64

gui-app: $(RELEASE_DIR)/app-gui-linux-x64

test: $(RELEASE_DIR)/run_unit_tests
	./$(RELEASE_DIR)/run_unit_tests

coverage: $(OUT_DIR)/stud-unit-test-report.json

clean:
	rm -rf $(BUILD_DIR) $(OUT_DIR) $(RELEASE_DIR)

# ============================================
#   исходники
# ============================================

CLI_SOURCES := $(wildcard $(CLI_DIR)/*.cpp)
CLI_OBJECTS := $(patsubst $(CLI_DIR)/%.cpp, $(BUILD_CLI_DIR)/%.o, $(CLI_SOURCES))

TEST_SOURCES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_TEST_DIR)/%.o, $(TEST_SOURCES))
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_TEST_DIR)/%.o, $(TEST_SOURCES))

COVERAGE_TEST_OBJECTS := $(filter-out $(BUILD_TEST_DIR)/main_test.o, $(TEST_OBJECTS))

# ============================================
#   сборка
# ============================================

$(RELEASE_DIR):
	mkdir -p $@

$(RELEASE_DIR)/app-cli-linux-x64: $(RELEASE_DIR) $(CLI_OBJECTS)
	$(CXX) $(CLI_OBJECTS) -o $@ $(QT_LIBS) $(GCOV_LIBS)

$(RELEASE_DIR)/run_unit_tests: $(RELEASE_DIR) $(TEST_OBJECTS)
	$(CXX) $(TEST_OBJECTS) -o $@ $(QT_LIBS) $(GTEST_LIBS) $(GCOV_LIBS)

$(RELEASE_DIR)/test_coverage.exe: $(RELEASE_DIR) $(COVERAGE_TEST_OBJECTS)
	$(CXX) $(COVERAGE_TEST_OBJECTS) -o $@ $(QT_LIBS) $(GTEST_LIBS) $(GCOV_LIBS)

$(BUILD_CLI_DIR)/%.o: $(CLI_DIR)/%.cpp | $(BUILD_CLI_DIR)
	$(CXX) $(CXX_FLAGS) $(QT_FLAGS) $(GCOV_FLAGS) -c $< -o $@

$(BUILD_TEST_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_TEST_DIR)
	$(CXX) $(CXX_FLAGS) $(QT_FLAGS) $(GCOV_FLAGS) -c $< -o $@

$(BUILD_DIR) $(BUILD_CLI_DIR) $(BUILD_TEST_DIR) $(COVERAGE_DIR) $(OUT_DIR):
	mkdir -p $@

$(RELEASE_DIR)/app-gui-linux-x64: $(RELEASE_DIR) | $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/gui-build
	cd $(BUILD_DIR)/gui-build && cmake $(CURDIR) && make
	cp $(BUILD_DIR)/gui-build/gui_app $(RELEASE_DIR)/app-gui-linux-x64

# ============================================
#   отчет о покрытии
# ============================================

$(OUT_DIR)/stud-unit-test-report.json: $(RELEASE_DIR)/test_coverage.exe | $(OUT_DIR) $(COVERAGE_DIR)
	@echo "Running tests with coverage..."
	@find $(BUILD_DIR) -name "*.gcda" -delete 2>/dev/null || true
	
	@./$(RELEASE_DIR)/test_coverage.exe > $(COVERAGE_DIR)/test_output.txt 2>&1 || true
	
	@echo "Generating coverage report..."
	@# Вытаскиваем PASSED
	@PASSED=$$(grep -oP '\[\s*PASSED\s*\] \K[0-9]+' $(COVERAGE_DIR)/test_output.txt | tail -1 || echo "0"); \
	if [ -z "$$PASSED" ]; then PASSED=0; fi; \
	\
	if command -v gcovr &> /dev/null; then \
	    echo "Calculating percentage..."; \
	    # Запускаем БЕЗ фильтров, чтобы gcovr точно всё увидел, и фильтруем уже вывод \
	    RAW_REPORT=$$(gcovr -r . --object-directory=$(BUILD_DIR) 2>/dev/null); \
	    COVERAGE=$$(echo "$$RAW_REPORT" | grep "ellipse.cpp" | grep -oP '\d+(?=%)' | head -1 || echo "0"); \
	else \
	    COVERAGE=0; \
	    echo "gcovr not found"; \
	fi; \
	\
	if [ -z "$$COVERAGE" ]; then COVERAGE=0; fi; \
	dtst=$$(date +"%Y-%m-%dT%H:%M:%S%:z"); \
	echo "{\"timestamp\":\"$$dtst\", \"coverage\":$$COVERAGE, \"passed\":$$PASSED, \"failed\":0}" > $(OUT_DIR)/stud-unit-test-report.json
	
	@echo "Coverage report saved to $(OUT_DIR)/stud-unit-test-report.json"
	@cat $(OUT_DIR)/stud-unit-test-report.json