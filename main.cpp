#include "CPlatformConsumer.hpp"
#include "CPlatformStorageDelegate.hpp"
#include <iostream>

int main() {
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