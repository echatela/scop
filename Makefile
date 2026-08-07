NAME		:= scop

SRC_DIR		:= src
OBJ_DIR		:= obj
INC_DIR		:= include

CXX			:= c++
CXXSTD		?= c++17
CXXFLAGS	:= -Wall -Wextra -Werror -std=$(CXXSTD) -MMD -MP
CPPFLAGS	:= -I$(INC_DIR)
LDFLAGS		:=
LDLIBS		:=

SRCS		:= $(shell find $(SRC_DIR) -name '*.cpp')
OBJS		:= $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

RM			:= rm -f

# -----------------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) compile_commands.json

re: fclean
	$(MAKE) all

cdb:
	@command -v bear >/dev/null 2>&1 || \
		{ echo "cdb: bear not found (install bear)"; exit 1; }
	$(MAKE) fclean
	bear -- $(MAKE) all

-include $(DEPS)

.PHONY: all clean fclean re cdb
