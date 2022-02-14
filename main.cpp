#include "CPlatformConsumer.hpp"
#include "CPlatformStorageDelegate.hpp"
#include <iostream>

#include "di_example_config.hpp"

int main() {

  #if defined __clang__
    std::cout << "Build with clang" << std::endl;
  #elif defined __GNUC__
    std::cout << "Build with GCC" << std::endl;
  #endif 

  std::cout << VERSION_STRING << ". Commit: " << VERSION_GIT_HASH << ((VERSION_GIT_DIRTY) ? "*" : "") << std::endl;

  IStorageService *storage = new CPlatformStorageDelegate();

  // DEPENDENCY INJECTED HERE!
  CPlatformConsumer *consumer = new CPlatformConsumer(storage);

  for (int i = 0l; i < 5; ++i) {
    consumer->fooooooo();
    std::cout << consumer->getResult() << std::endl;
  }

  delete consumer;
  delete storage;
}