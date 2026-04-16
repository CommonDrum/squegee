CC = gcc
CFLAGS = -Wall -Wextra -g

BUILD = build
OUT = $(BUILD)/game

SRC = $(shell find . -name '*.c')
OBJ = $(patsubst ./%.c,$(BUILD)/%.o,$(SRC))

INC = $(addprefix -I,$(shell find . -path ./$(BUILD) -prune -o -type d -print))

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(BUILD)

run: $(OUT)
	./$(OUT)
