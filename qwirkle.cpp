
#include "LinkedList.h"
#include "Cli.h"

#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

   Cli console;

   console.printMenu();

   // main loop
   while (!console.nextInput()) {
   }

   std::cout << "Goodbye" << std::endl;

   return EXIT_SUCCESS;
}
