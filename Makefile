# Borland MAKE Version 3.6
BC_DIR   = C:\bc31
INC_DIR  = include
LIB_DIR  = lib
SRC_DIR  = src
H_DIR    = h
TEST_DIR = test
OUT_DIR  = output

BCC      = $(BC_DIR)\bin\bcc.exe
INC_PATH = $(BC_DIR)\include;$(INC_DIR);$(H_DIR);$(TEST_DIR)
LIB_PATH = $(BC_DIR)\lib

SOURCES  = $(SRC_DIR)\*.cpp $(TEST_DIR)\*.cpp
HEADERS  = $(H_DIR)\*.h $(TEST_DIR)\*.h
LIBS     = $(LIB_DIR)\*.lib
TARGET   = proj.exe

$(TARGET): $(BCC) $(SOURCES) $(HEADERS) $(LIBS) $(OUT_DIR)
	$(BCC) -mh -v -y -I$(INC_PATH) -L$(LIB_PATH) -n$(OUT_DIR) -e$(TARGET) $(SOURCES) $(LIBS)

$(OUT_DIR):
	if not exist $(OUT_DIR) md $(OUT_DIR)

all: $(TARGET)

clean: $(OUT_DIR)
	-del $(OUT_DIR)\*.obj
	-del $(OUT_DIR)\*.asm
	-del $(OUT_DIR)\$(TARGET)
