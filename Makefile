RAYLIB_PATH     ?= $(realpath .)/raylib
SRC_DIR         ?= src
BUILD_DIR       ?= build

CFLAGS          = -Wextra -pedantic -std=c17 \
					$(INCLUDE_FLAGS)

CPPFLAGS        = -Wextra -pedantic -std=c++23 \
					$(INCLUDE_FLAGS)

INCLUDE_FLAGS   ?= -I$(RAYLIB_PATH)/src

LDFLAGS = libraylib.a \
	-lopengl32 -lgdi32 -lwinmm

C_FILES = $(SRC_DIR)/main.c \
			$(SRC_DIR)/stats.c

CPP_FILES = $(SRC_DIR)/world.cpp \
			$(SRC_DIR)/actor.cpp \
			$(SRC_DIR)/animation.cpp \

C_OBJS	:= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_FILES))
CPP_OBJS	:= $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CPP_FILES))


.PHONY: all
all: libraylib $(C_OBJS) $(CPP_OBJS)
	g++ -o main.exe $(C_OBJS) $(CPP_OBJS) $(LDFLAGS)

.PHONY: libraylib
libraylib:
	make -C $(RAYLIB_PATH)/src raylib \
		PLATFORM=PLATFORM_DESKTOP \
		RAYLIB_BUILD_MODE=RELEASE \
		RAYLIB_LIBTYPE=STATIC \
		RAYLIB_RELEASE_PATH=$(realpath .)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	gcc -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	g++ -c $< -o $@ $(CPPFLAGS)

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
	@rm -f main.exe || true
	@rm -f libraylib.a || true
	make -C $(RAYLIB_PATH)/src clean
