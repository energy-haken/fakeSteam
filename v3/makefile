TARGET_EXEC ?= v3
CC := clang
BUILD_DIR ?= ./build
TARGET_DIR ?= ./bin
SRC_DIRS ?= .

SRCS := $(shell find $(SRC_DIRS) -name "*.c" -not -name "list.c" -not -name "download.c")
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d -not -path "./.git/*" -not -path "./.git" -not -path "./.vscode" -not -path "./.vscode/*")
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS ?= $(INC_FLAGS) -MMD -MP -O3

$(TARGET_DIR)/$(TARGET_EXEC): $(OBJS)
	$(MKDIR_P) $(dir $@)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR) $(TARGET_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p

# Specialized servers
SERVERS := list download

SERVER_SRCS := operationsUtils.c
SERVER_OBJS := $(SERVER_SRCS:%=$(BUILD_DIR)/%.o)

$(TARGET_DIR)/%: $(BUILD_DIR)/%.o $(SERVER_OBJS)
	$(MKDIR_P) $(dir $@)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all

all: $(TARGET_DIR)/$(TARGET_EXEC) servers

.PHONY: servers

servers: $(SERVERS:%=$(TARGET_DIR)/%)

clean-servers:
	$(RM) $(SERVERS:%=$(TARGET_DIR)/%)
