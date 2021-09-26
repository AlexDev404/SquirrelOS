/*
Copyright 2021 Harvey Xing 
Licensed under MIT ( https://github.com/xing1357/SimpleOS/blob/main/LICENSE )
*/

#include "shell.h"
#include "cpu/cpuid/cpuid.h"
#include "apps/textedit/textedit.h"
#include "apps/calculator/calculator.h"
#include "apps/serialapp/serialapp.h"
#include "apps/slang/slang.h"

void type()
{
  // get the filename
  print_string("\nEnter file name: ");
  string filename = readStr();
  // read it
  char* content = (char*) malloc(file_size(filename));
  int response = file_read(filename, content);
  if (response == FILE_NOT_FOUND)
  {
    print_string("File not found\n");
  }
  print_string("\n");
  print_string(content);
  print_string("\n");
  kfree(filename);
  kfree(content);
}

void run(){
	print_string("\nEnter App to Run: ");
	string app = readStr();
	if(strcmp(app, "textedit")){
		text_editor();
	}
	else if(strcmp(app, "calc")){
		calculator();
	}
	else if(strcmp(app, "serialapp")){
		serial_port_app();
	}
	else if(strcmp(app, "slang")){
		slang_app();
	}
	else {
		print_string("\nApp Not Found\nAvailable Applications:\n1. textedit\n2. calc\n3. serialapp\n4. slang");
	}
}

void rm(){
	print_string("\nEnter File to Remove: ");
	string filename = readStr();
	file_remove(filename);
	print_string("\nRemoved File: ");
	print_string(filename);
	print_string("\n");
}

void ls()
{
  char* name;
  for (int i = 0; i < file_count(); ++i)
  {
    name = file_get_name(i);
    if (name != FILE_NOT_FOUND)
    {
      print_string(name);
	  int size = file_size(name);
	  print_string("\t");
	  print_int(size);
      print_string("\n");
    }
  }
}
void touch(){
	print_string("\nEnter Filename: ");
	string filename = readStr();
	file_make(filename);
	print_string("\nCreated File: ");
	print_string(filename);
	print_string("\n");
}

void echo()
{
	print_string("\n");
	string str = readStr();
	print_string("\n");
	print_string(str);
	print_string("\n");
}


void help()
{
	print_string("\nAbout: About the OS\n");
	print_string("cpuinfo: Information about the cpu\n");
	print_string("echo: echo text into the terminal\n");
	print_string("rand: Random Integer Between 1 and 100\n");
	print_string("clear: Clear the Screen\n");
	print_string("page: Test Paging\n");
	print_string("panic: TRIGGER A KERNEL PANIC!!!\n");
	print_string("date: Print Date\n");
	print_string("time: Print Time\n");
	print_string("ls: List the Files\n");
	print_string("touch: Create a file\n");
	print_string("rm: Remove a file\n");
	print_string("run: SimpleOS Applauncher\n");
	print_string("shutdown: Shutdown SimpleOS\n");
}

void about()
{
	print_string("\nSquirrelOS v0.0.1");
	print_string("\nBy Immanuel Garcia\n");
}


// MAIN CODE

void launch_shell(string prompt)
{
	string ch = (string) malloc(200); 
	int counter = 0;
	do
	{	

		print_string(prompt);
		// print_string("\n STRING LENGTH OF PROMPT IS ");
		// print_int(strlen(prompt));
		ch = readStr(true);

		if(strcmp(ch,"help"))
	    {
    		help();
	    }

	    else if(strcmp(ch,"echo"))
	    {
    		echo();
	    }
	    else if(strcmp(ch,"cpuinfo"))
	    {
	    	cpuid_test();
	    }
	    else if(strcmp(ch, "about"))
	    {
	    	about();
	    }
	    else if(strcmp(ch, "rand"))
	    {
	    	print_string("\n");
			srand(_timestamp_eax()); // Our Source of Entropy for the rand() function
	    	string randint = int_to_string(rand(100));
	    	print_string(randint);
	    	print_string("\n");
	    }
	    else if(strcmp(ch, "clear")){
	    	clearScreen();
	    }
	    else if(strcmp(ch, "page")){
	    	print_string("\n");
	    	page();
	    }
	    else if(strcmp(ch, "panic")){
	    	panic("User");
	    }
	    else if(strcmp(ch, "date")){
	    	rtc_date();
	    }
	    else if(strcmp(ch, "time")){
	    	rtc_time();
	    }
		else if(strcmp(ch, "find")){
			string file = readStr();
			bool fileExists = file_exists(file);
			if (fileExists == true){
				print_string("\nFile Found\n");
			}
			else if(fileExists == false) {
				print_string("\nFile not Found\n");
			}
		}
		else if(strcmp(ch, "ls")){
			print_string("\n");
			ls();
			print_string("\n");
		}
		else if(strcmp(ch,"touch")){
			type();
			print_string("\n");
		}
		else if(strcmp(ch, "rm")){
			rm();
		}
		else if(strcmp(ch, "type")){
			type();
		}
		else if(strcmp(ch, "run")){
			run();
		}
		else if(strcmp(ch, "shutdown")){
			acpiPowerOff();
		}
		else if(isspace(ch)){
			print_string("\n");
		}
		else if(strcmp(ch, "strlen")){
			print_string("\nEnter String: ");
			string stringOne = readStr();
			print_string("\n");
			print_int(strlen(stringOne));
			print_string("\n");
		}
		else
	    {
	       print_string("\n");
	       print_string(ch);
	       print_string(": ");
		   print_string("Command not found\n\n");
	    } 
	} while (!strcmp(ch,"exit"));
}



