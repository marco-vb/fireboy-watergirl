# name of the program (Minix service)
PROG=proj

# No RegEx in Makefile for some reason
.PATH: ${.CURDIR}/drivers/graphics
.PATH: ${.CURDIR}/drivers/kbc
.PATH: ${.CURDIR}/drivers/timer

# source code files to be compiled
SRCS = 	utils.c keyboard.c mouse.c kbc.c timer.c graphics.c proj.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
