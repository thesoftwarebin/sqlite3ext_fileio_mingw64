CFLAGS=-O2 -DWIN32 -DFILEIO_WIN32_DLL
LDFLAGS=--shared

all: fileio.dll 

fileio.dll: fileio.o
	$(CC) $(LDFLAGS) $< -o$@

clean:
	$(RM) -f fileio.o fileio.dll 

