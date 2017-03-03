
NAME = trainer
MAKE_FLAGS = -j4

BUILD=build

CFLAGS= -lSDL2
SRCS = core/main.cpp \
	   core/SdlWindow.cpp


all: $(NAME)

$(BUILD):
	mkdir $(BUILD)

$(NAME): $(BUILD)
	g++ -o $(BUILD)/$@ $(SRCS) $(CFLAGS) -Wl,-rpath,.
