PROJECT		=	w3d
BINDIR		?=	.
BUILDDIR	?=	build
NAME		=	$(BINDIR)/w3d

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g

BLACK		=	"\033[0;30m"
RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[1;33m"
BLUE		=	"\033[0;34m"
MAGENTA		=	"\033[0;35m"
CYAN		=	"\033[0;36m"
WHITE		=	"\033[0;37m"
END			=	"\033[0m"

PRINT		=	@printf COL$(PROJECT)$(END)'\t'
PRPROJ		=	$(subst COL, $(BLUE), $(PRINT))
PRRM		=	$(subst COL, $(CYAN), $(PRINT))

SRCEX		=
SRC			=	$(filter-out $(SRCEX), $(filter %.c, $(shell ls)))
OBJECTS		=	$(addprefix $(BUILDDIR)/, $(SRC:%.c=%.o))

LIBLINK		=	-lgnl -lfmt -lvll -lcl -lvect -lft
LIBDIRS		:=	$(patsubst -l%, lib%, $(LIBLINK))
LIBS		:=	$(addsuffix .a, $(LIBDIRS))
LDFLAGS		:=	$(addprefix -L, $(LIBDIRS))
LIBLINK		+=	-lmlx
FRAMEWORKS	=	-framework OpenCL -framework OpenGL -framework AppKit
INCLUDES	+=	/System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/HIToolbox.framework/Versions/A/Headers
INCLUDES	+=	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Tk.framework/Versions/8.4/Headers/X11/
INCFLAGS	=	$(addprefix -I,$(INCLUDES))

all: $(NAME)

%.a: %
	$(PRPROJ)
	make --no-print-directory -C $<

$(BUILDDIR)/%.o: %.c
	@[ -d $(BUILDDIR) ] || mkdir $(BUILDDIR)
	$(PRPROJ)
	$(CC) $(INCFLAGS) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIBS)
	$(PRPROJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(FRAMEWORKS) $(OBJECTS) $(LIBLINK) -o $(NAME)
	@printf "OK\t"$(NAME)'\n'

.PHONY: clean sclean fclean re r ex

clean:
	$(PRRM)
	rm -rf $(BUILDDIR)

fclean: clean
	$(PRRM)
	rm -rf $(NAME)

ex: re
	$(NAME)

re: fclean all
