#include "CPlatformStorageService.hpp"

#include <iostream>

bool CPlatformStorageService::registerCallback(callback_t c) {
  if (!mCallback)
    return false;
  mCallback = c;
  return true;
}

void CPlatformStorageService::storeDataWithoutCallbackProvided(int key,
                                                               int value) {
  if (!mCallback) {
    std::cout << "ERROR: REAL PLATFORM: no callback registered" << std::endl;
    return;
  }

  // do the actual job

  if (store(key, value)) {
    mCallback(0); // no error here
  } else {
    mCallback(27); // 27 - error code for some storage issue
  }
}

void CPlatformStorageService::storeDataWithCallbackProvided(int key, int value,
                                                            callback_t c) {
  if (!c) {
    std::cout << "ERROR: REAL PLATFORM: empty callback provided!" << std::endl;
    return;
  }

  if (store(key, value)) {
    c(0); // no error here
  } else {
    c(27); // 27 - error code for some storage issue
  }
}

int CPlatformStorageService::loadData(int key) { return 118; }

bool CPlatformStorageService::store(int key, int value) {
  return true; // we have nice service - it works all the time
}