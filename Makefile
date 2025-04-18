CC = arm-linux-gcc

SRC_DIR = src
BIN_DIR = bin

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $< -o $(BIN_DIR)/$@

version:
	$(CC) --version

clean:
	rm -rf $(BIN_DIR)

.PHONY: clean
