#include "CPlatformStorageDelegate.hpp"

#include "CPlatformStorageService.hpp"

CPlatformStorageDelegate::CPlatformStorageDelegate()
    : mRealPlatform(new CPlatformStorageService()) {}

CPlatformStorageDelegate::~CPlatformStorageDelegate() { delete mRealPlatform; }

bool CPlatformStorageDelegate::registerCallback(callback_t c) {
  return mRealPlatform->registerCallback(c);
}

void CPlatformStorageDelegate::storeDataWithoutCallbackProvided(int key,
                                                                int value) {
  mRealPlatform->storeDataWithoutCallbackProvided(key, value);
}

void CPlatformStorageDelegate::storeDataWithCallbackProvided(int key, int value,
                                                             callback_t c) {
  mRealPlatform->storeDataWithCallbackProvided(key, value, c);
}

int CPlatformStorageDelegate::loadData(int key) {
  return mRealPlatform->loadData(key);
}