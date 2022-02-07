#include "CPlatformConsumer.hpp"
#include "IStorageService.hpp"
#include <iostream>

namespace {
int persistencyKey = 1101;
};

CPlatformConsumer::CPlatformConsumer(IStorageService *service)
    : mStorage(service), newResultsOfComputationObtained(false),
      lastComputationResult(0), lastStoreSuccess(false) {
  lastComputationResult = mStorage->loadData(persistencyKey);
  mStorage->registerCallback([this](uint8_t error) {
    if (!error) {
      std::cout << "CPlatformConsumer: class wide error handler: data stored "
                   "successfully"
                << std::endl;
      lastStoreSuccess = true;
      newResultsOfComputationObtained = false; // no new results after this action
    } else {
      std::cout << "CPlatformConsumer: class wide error handler: we lost our "
                   "progress!!!!"
                << std::endl;
      lastStoreSuccess = false;
    }
  });
}

CPlatformConsumer::~CPlatformConsumer() {
  if (newResultsOfComputationObtained) {
    mStorage->storeDataWithCallbackProvided(
        persistencyKey, lastComputationResult, [](uint8_t error) {
          if (!error) {
            std::cout << "CPlatformConsumer: local error handler: data stored "
                         "successfully"
                      << std::endl;
          } else {
            std::cout << "CPlatformConsumer: local error handler: we lost our "
                         "progress!!!!"
                      << std::endl;
          }
        });
  }
}

void CPlatformConsumer::fooooooo() {
  // we took old data from the persistency or from last run
  // and do one iteration of very complex calculation

  ++lastComputationResult;
  if (!newResultsOfComputationObtained)
    newResultsOfComputationObtained = true;
}

bool CPlatformConsumer::flush() {
  if (newResultsOfComputationObtained) {
    mStorage->storeDataWithoutCallbackProvided(persistencyKey,
                                               lastComputationResult);
  }

  return lastStoreSuccess;
}