# Borland MAKE Version 3.6
BC_DIR   = C:\bc31
INC_DIR  = include
LIB_DIR  = lib
SRC_DIR  = src
H_DIR    = h
USER_DIR = user
TEST_DIR = test
OUT_DIR  = output

BCC      = $(BC_DIR)\bin\bcc.exe
INC_PATH = $(BC_DIR)\include;$(INC_DIR);$(H_DIR);$(USER_DIR);$(TEST_DIR)
LIB_PATH = $(BC_DIR)\lib
OPTIONS  = -mh -v -y -I$(INC_PATH) -L$(LIB_PATH) -n$(OUT_DIR)

SRC      = $(SRC_DIR)\*.cpp
USER_SRC = $(SRC) $(USER_DIR)\*.cpp
TEST_SRC = $(SRC) $(TEST_DIR)\*.cpp
LIBS     = $(LIB_DIR)\*.lib
USER_EXE = os1_user.exe
TEST_EXE = os1_test.exe

$(USER_EXE): $(OUT_DIR) $(BCC) $(USER_SRC) $(LIBS)
	$(BCC) $(OPTIONS) -e$(USER_EXE) $(USER_SRC) $(LIBS)

$(TEST_EXE): $(OUT_DIR) $(BCC) $(TEST_SRC) $(LIBS)
	$(BCC) $(OPTIONS) -e$(TEST_EXE) $(TEST_SRC) $(LIBS)

$(OUT_DIR):
	if not exist $(OUT_DIR) md $(OUT_DIR)

user: $(USER_EXE)

test: $(TEST_EXE)

all: user test

clean: $(OUT_DIR)
	-del $(OUT_DIR)\*.obj
	-del $(OUT_DIR)\*.asm
	-del $(OUT_DIR)\*.exe
