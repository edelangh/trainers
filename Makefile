

all: $(NAME)

$(NAME): 
	g++ main.cpp -I libs/SFGUI/include -L libs/SFGUI/lib -lsfgui 
