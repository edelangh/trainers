
NAME = trainer
MAKE_FLAGS = -j4

BUILD=build

CFLAGS= -lSDL2 -lcurl
FLAGS = -std=c++14

SRCDIR = core
SRCS = main.cpp \
	   Parser.cpp \
	   CliInterface.cpp \
	   Test.cpp \
	   Trainer.cpp \
	   Args.cpp \
	   SdlWindow.cpp \

DEPENDENCIE = core/IInterface.hpp

INCLUDES = -I $(SRCDIR)

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/,$(subst .cpp,.o,$(SRCS)))

all: $(NAME)

$(BUILD):
	mkdir $(BUILD)

$(NAME): $(BUILD) $(OBJS)
	g++ -o $(BUILD)/$@ $(OBJS) $(CFLAGS) -Wl,-rpath,.

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPENDENCIE)
	g++ $(INCLUDES) $(FLAGS) -c $< -o $@

clean:
	rm $(OBJS)

fclean: clean

re: fclean all

test: all
	./$(BUILD)/$(NAME)
