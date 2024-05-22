#参照先:https://d-rissoku.net/2013/06/makefile-%E5%88%A5%E3%83%87%E3%82%A3%E3%83%AC%E3%82%AF%E3%83%88%E3%83%AA%E3%81%AB%E4%B8%AD%E9%96%93%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB-%E8%87%AA%E5%8B%95%E4%BE%9D%E5%AD%98%E9%96%A2%E4%BF%82/


# ------------------------------------------
# Cmakeをつかおう！！！！！！！！！！！
# ------------------------------------------

# ターゲット
TARGET = prog.exe
SRC_DIR = src
BUILD_DIR = Build

# 
CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -pthread

# ヘッダディレクトリ
INC_DIR = $(addprefix -I,$(SRC_DIR)/)

# ライブラリディレクトリ
#LIB_DIR += -L/usr/lib

# リンクライブラリー
# LINK_LIB = -lrl

SRCS = $(shell find $(SRC_DIR) -name "*.c" -type f | xargs)
OBJS=$(addprefix $(BUILD_DIR)/,$(patsubst %.c,%.o,$(SRCS)))
DEPS=$(patsubst %.o,%.d, $(OBJS))

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR) $(TARGET)
	@echo "Deleted" $(BUILD_DIR)/* $(TARGET)

.PHONY release
release: CFLAGS += -O2
release: all

.PHONY debug
debug: CFLAGS += -g3 -ggdb -O0 -fsanitize=address
debug: all

.PHONY: all
release: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
 
$(TARGET) : $(OBJS)
	@echo "------------------------------------------------"
	@echo "Link"
	@echo "------------------------------------------------"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LINK_LIB)

$(BUILD_DIR)/%.o : %.c
	@echo "------------------------------------------------"
	@echo "Compile" $<
	@echo "------------------------------------------------"
	@mkdir -p $(dir $@)
	$(CC) -c -MMD -MP $(CFLAGS) $(INC_DIR) -o $@ $<
	@echo ""

# $(BUILD_DIR)/%.d : %.c
# 	@mkdir -p $(dir $@); \
# 	$(CC) -MM $(CFLAGS) $(INC_DIR) $< \
# 	| sed 's/$(notdir $*).o/$(subst /,\/,$(patsubst %.d,%.o,$@) $@)/' > $@ ; \
# 	[ -s $@ ] || rm -f $@

.PHONY: rebuild
rebuild: clean all

default: all
-include $(DEPS)
