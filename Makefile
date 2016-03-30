#
#    Makefile for send2java
#

TARGET	= send2java
PREFIX	:= /usr/local
BINDIR	:= $(PREFIX)/bin
CC	:= cc
RM	:= rm
CFLAGS	:= -O2 -g -Wall -pg
LDFLAGS	:=
CMDLINE	:= 0

SRCS	= $(wildcard *.c)
OBJS	= $(SRCS:.c=.o)
ARCH	= $(shell gcc -print-multiarch)

DEFCFLAGS = -DARCH=\"$(ARCH)\"

all: $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
ifeq ($(CMDLINE), 0)
	@echo "  BUILD   $@"
	@$(CC) $(LDFLAGS) $^ -o $@
else
	$(CC) $(LDFLAGS) $^ -o $@
endif

%.o: %.c %.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      $@"
	@$(CC) $(DEFCFLAGS) $(CFLAGS) -c $< -o $@
else
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c $< -o $@
endif

install-bin: $(TARGET)
	install -pd $(BINDIR)
	install -pm 755 $< $(BINDIR)/

install: install-bin

clean:
	-$(RM) -f $(OBJS)
	-$(RM) -f $(TARGET)

.PHONY: all install clean
