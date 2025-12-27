# sqlite3ext_fileio_mingw64
This is a modified version of SQLite's `fileio` DLL extension, so that it compiles in Windows under MinGW64.

While `fileio` extension is compiled in the SQLite **shell** (`sqlite3.exe`), it's not part of the basic SQLite **DLL**.
This means that SQL functions `READFILE` and `WRITEFILE` are not available by default in your C program, this code will fail at runtime:

```.c
  char* sql = "select length(readfile('./testfileio.exe')) as length_of_file";
  sqlite3_exec(db, sql, printCallback, NULL, NULL);
```

This version of `fileio.dll` comes to the rescue, just prepend two configuration lines right after the database opening:

```.c
  sqlite3_enable_load_extension(db, 1 /*int onoff*/);
  sqlite3_load_extension(db, "fileio", 0, 0);

  char* sql = "select length(readfile('./testfileio.exe')) as length_of_file";
  sqlite3_exec(db, sql, printCallback, NULL, NULL);
```

See `testfileio.c` for a complete example.

# Fork history

[fileio.c from the main SQLite GH repo at revision 4a33eed](https://github.com/sqlite/sqlite/blob/4a33eed6e9d4e2e0d59c8bc26761555273314640/ext/misc/fileio.c) has been chosen as the initial starting point, then a Makefile and a test have been added.

# Compatibility notes

It has been compiled successfully on this setup: Windows 11 + MSYS2.0 + `/mingw64/bin/gcc` v.15.1.0.

# License terms

- the original fileio.c from SQLite comes with a no-copyright license (basically it's public domain)
- the modifications and additional files offered in this repository are licensed under the terms of LGPL 2.1.
