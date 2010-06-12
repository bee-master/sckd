# ---------------------------------------------------------------------------
# Имя проекта

NAME	= main_proj

# Настройки компилятора и линкера

CC      = sdcc
CFLAGS  = -I./INCLUDE -c --stack-auto
LFLAGS  = --code-loc 0x2100 --xram-loc 0x6000 --stack-auto --stack-loc 0x80 

# Настройки системы автоинкремента версии сборки

PROJECT  = $(shell cat PROJECT)
VERSION  = $(shell cat VERSION)

PROJNAME = ${PROJECT}-${VERSION}
TARBALL  = ${PROJNAME}.tar

# Настройки M3P

M3P		 = m3p
COMPORT	 = /dev/ttyUSB0
COMLOG	 = $(COMPORT)_log.txt
BAUD	 = 9600	

# Каталоги с исходными текстами

SRC_DIR = SRC
# ---------------------------------------------------------------------------

all: main_proj

clean:
	-rm -f  $(NAME).hex \
			$(NAME).bin \
			$(NAME).map \
			$(NAME).mem \
			$(NAME).lnk \
			pm3p_*.txt \
			com?_log.txt \
			$(TARBALL).gz \
			$(SRC_DIR)/*.asm \
			$(SRC_DIR)/*.rel \
			$(SRC_DIR)/*.rst \
			$(SRC_DIR)/*.sym \
			$(SRC_DIR)/*.lst 

load:
	$(M3P) lfile load.m3p


dist:
	tar cvf $(TARBALL) *
	gzip $(TARBALL)

term:
	$(M3P) echo $(COMLOG) $(BAUD)  openchannel $(COMPORT) +echo 6 term -echo bye


LIST_SRC = \
$(SRC_DIR)/max.c \
$(SRC_DIR)/lsd.c \
$(SRC_DIR)/key.c \
$(SRC_DIR)/sram.c \
$(SRC_DIR)/timer.c \
$(SRC_DIR)/uart.c \
$(SRC_DIR)/sound.c \
$(SRC_DIR)/parser.c \
$(SRC_DIR)/conv.c \
$(SRC_DIR)/package.c \
$(SRC_DIR)/crc8.c \
$(SRC_DIR)/main_proj.c 

LIST_OBJ = $(LIST_SRC:.c=.rel)

main_proj : $(LIST_OBJ) makefile
	$(CC) $(LIST_OBJ) -o main_proj.hex $(LFLAGS)
	$(M3P) hb166 main_proj.hex main_proj.bin bye


$(LIST_OBJ) : %.rel : %.c makefile
	$(CC) -c $(CFLAGS) $< -o $@  
