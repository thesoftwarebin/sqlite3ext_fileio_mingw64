/*
    Copyright 2025 by Andrea Rossetti <andrear1979@hotmail.com>

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int printCallback(void* a_param, int argc, char** argv, char** column){
  for (int i=0;i<argc;i++){
    printf("%s\t", argv[i]);
  }
  printf("\n");
  return 0;
}
  
int main(int argc, char* argv[]){
  sqlite3 *db;
  sqlite3_open(":memory:", &db);
  sqlite3_enable_load_extension(db, 1 /*int onoff*/);
  sqlite3_load_extension(db, "fileio", 0, 0);

  sqlite3_exec(db,             /* An open database */
	       "select 'testfileio.exe length:' as col1, length(readfile('./testfileio.exe')) as col2", /* SQL to be evaluated */
	       printCallback,  /* Callback function */
	       NULL,           /* 1st argument to callback */
	       NULL            /* Error msg written here */
	       );

  return EXIT_SUCCESS;
}

