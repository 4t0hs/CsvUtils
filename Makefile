#参照先:https://d-rissoku.net/2013/06/makefile-%E5%88%A5%E3%83%87%E3%82%A3%E3%83%AC%E3%82%AF%E3%83%88%E3%83%AA%E3%81%AB%E4%B8%AD%E9%96%93%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB-%E8%87%AA%E5%8B%95%E4%BE%9D%E5%AD%98%E9%96%A2%E4%BF%82/

SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)
BUILD_DIR = Build

OBJS=$(addprefix $(BUILD_DIR)/,$(patsubst %.c,%.o,$(SRCS)))
DEPS=$(patsubst %.o,%.d, $(OBJS))

CC = gcc -g3 -ggdb -O0
TARGET = prog.exe
CFLAGS += $(addprefix -I,$(SRC_DIR)/)
LDFLAGS = -pthread
#ヘッダディレクトリ
INC_DIR = -I/usr/local/include
INC_DIR += 
#リンクライブラリー
#LIB_DIR = -L/usr/local/lib
#LIB_DIR += -L/usr/lib
# LINK_LIB = -larchive
LINK_LIB += -lrt

default: clean all

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
 
$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LINK_LIB)

$(BUILD_DIR)/%.o : %.c
	mkdir -p $(dir $@); \
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.d : %.c
	mkdir -p $(dir $@); \
	$(CC) -MM $(CFLAGS) $< \
	| sed 's/$(notdir $*).o/$(subst /,\/,$(patsubst %.d,%.o,$@) $@)/' > $@ ; \
	[ -s $@ ] || rm -f $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
-include $(DEPS)
