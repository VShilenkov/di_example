#include "CPlatformConsumer.hpp"
#include "CPlatformStorageDelegate.hpp"
#include <iostream>

int main() {

  #if defined __clang__
    std::cout << "Build with clang" << std::endl;
  #elif defined __GNUC__
    std::cout << "Build with GCC" << std::endl;
  #endif 


  IStorageService *storage = new CPlatformStorageDelegate();

  // DEPENDENCY INJECTED HERE!
  CPlatformConsumer *consumer = new CPlatformConsumer(storage);

  for (int i = 0; i < 5; ++i) {
    consumer->fooooooo();
    std::cout << consumer->getResult() << std::endl;
  }

  delete consumer;
  delete storage;
}