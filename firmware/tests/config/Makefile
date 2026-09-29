TARGET_ERRNO = errno_unit_test

ifndef BUILD_DIR
    BUILD_DIR = $(CURDIR)
endif

CC = gcc

INC = ../../

CFLAGS = -fpic -std=c99 -Wall -pedantic \
         -Wshadow \
         -Wpointer-arith \
         -Wcast-qual \
         -Wstrict-prototypes \
         -Wmissing-prototypes \
         -DSTM32F1 \
         -I$(INC) \
         -I../../tests/freertos_sim \
         -I../../hal/include

.PHONY: all
all: errno_test

.PHONY: errno_test
errno_test: $(BUILD_DIR)/errno_test.o
	$(CC) $^ -lcmocka -o $(BUILD_DIR)/$(TARGET_ERRNO)

$(BUILD_DIR)/errno_test.o: errno_test.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/$(TARGET_ERRNO) \
	      $(BUILD_DIR)/*.o
