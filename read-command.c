// UCLA CS 111 Lab 1 command reading

// Copyright 2012-2014 Paul Eggert.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "command.h"
#include "command-internals.h"
#include "alloc.h"
#include <error.h>

#include <stdlib.h>
#include <stdio.h>
/* FIXME: You may need to add #include directives, macro definitions,
   static function definitions, etc.  */

/* FIXME: Define the type 'struct command_stream' here.  This should
   complete the incomplete type declaration in command.h.  */
struct command_stream
{
	command_t current;
	int count;
	command_t head;
};
   
   
int is_alpha(char c){
	if ( (c>='a' && c<='z') ||  (c>='A' && c<='Z') ||  (c>='0' && c<='9') || c=='!' || c=='%' || c=='+' || c==',' || c=='-' || c=='.' || c=='/' ||c==':' || c=='@' || c=='^' || c=='_') return 1; else return 0;
	}

int is_spec(char c){
	if (c== '<' ||c=='>' || c=='(' || c==')' || c==';' || c =='|' || c==' ' || c=='\t' || c == '\n') return 1; else return 0;
	}
	
void command_init(command_stream_t c)
{
	c->current = NULL;
	c->count = 0;
	c->head = NULL;
}
	
command_stream_t
make_command_stream (int (*get_next_byte) (void *),
		     void *get_next_byte_argument)
{
  /* FIXME: Replace this with your implementation.  You may need to
     add auxiliary functions and otherwise modify the source code.
     You can also use external functions defined in the GNU C Library.  */
	printf("make command stream\n");
	char* buffer = NULL;
	unsigned int bufLen = 0;
	char tmp;
	command_stream_t retval =(struct command_stream*)checked_malloc(sizeof(struct command_stream));
	
	command_init(retval);
	while ( (tmp = get_next_byte(get_next_byte_argument)) >= 0)
	{
		if (bufLen % 100 == 0) buffer = checked_realloc(buffer, bufLen+100);
		buffer[bufLen] = tmp;
		bufLen++;
	}
	printf("%d bytes read\n", bufLen);
	int* wds = NULL;
	unsigned int wdscount = 0;
	int inword = 0;
	int i;
	int size_int = sizeof(int);
	for (i=0; i<bufLen;i++)
	{
		printf("processing %c", buffer[i]);
		if (inword) 
			{if (is_alpha(buffer[i])) {printf("inword isalpha");wds[wdscount*2-1]++;}
			else if (is_spec(buffer[i]))
			{printf("inword isspec");wds = checked_realloc(wds, size_int*(2*wdscount+2)); inword =0; wds[wdscount*2]= i;wds[wdscount*2+1]= 1;wdscount++;}
			else if (buffer[i]=='#') {while (i<bufLen && buffer[i]!='\n' )i++;inword=0;}}
		else
			{if (is_alpha(buffer[i])) {printf("not inword isalpha"); wds = checked_realloc(wds, size_int*(2*wdscount+2)); inword =1; wds[wdscount*2]= i;wds[wdscount*2+1]=1;wdscount++;}
			else if (is_spec(buffer[i])) 
			{printf("not inword isspec");wds = checked_realloc(wds, size_int*(2*wdscount+2)); inword =0; wds[wdscount*2]= i;wds[wdscount*2+1]= 1;wdscount++;}
			else if (buffer[i]=='#') while (i<bufLen && buffer[i]!='\n' )i++;}
	}
	printf("%d words converted\n", wdscount);
	int j;
	for (i=0; i<wdscount;i++)
		for (j=0;j<wds[i*2+1];j++)
			printf("%c",buffer[wds[i*2]+j]);
  return 0;
}

command_t
read_command_stream (command_stream_t s)
{
  /* FIXME: Replace this with your implementation too.  */
  error (1, 0, "command reading not yet implemented");
  return 0;
}
