
#include "LinkedList.h"
#include "Cli.h"

#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

   // create CLI object
   Cli console;

   // print greating
   std::cout << "Welcome to Qwirkle!\n" << "-------------------\n" << std::endl;

   console.printMenu();



   // main loop
   while (!console.nextInput()) {
   }

   std::cout << "Goodbye" << std::endl;

   return EXIT_SUCCESS;
}
