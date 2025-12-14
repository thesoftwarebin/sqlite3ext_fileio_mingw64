CFLAGS=-O2 -DWIN32 -DFILEIO_WIN32_DLL
LDFLAGS=--shared
LDFLAGSTEST=-static-libgcc -Wl,-Bstatic
LIBSTEST=-lsqlite3

all: fileio.dll testfileio.exe

fileio.dll: fileio.o
	$(CC) $(LDFLAGS) $< -o$@

clean:
	$(RM) -f fileio.o fileio.dll testfileio.exe testfileio.o

testfileio.exe: testfileio.o fileio.dll
	$(CC) $(LDFLAGSTEST) -o$@ $< $(LIBSTEST)

test: testfileio.exe
	./testfileio.exe
