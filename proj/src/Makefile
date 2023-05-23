# name of the program (Minix service)
PROG=proj

# No RegEx in Makefile for some reason
.PATH: ${.CURDIR}/drivers/graphics
.PATH: ${.CURDIR}/drivers/kbc
.PATH: ${.CURDIR}/drivers/timer
.PATH: ${.CURDIR}/sprites
.PATH: ${.CURDIR}/maps

# source code files to be compiled
SRCS = 	utils.c kbc.c keyboard.c mouse.c timer.c sprite.c graphics.c proj.c map.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
