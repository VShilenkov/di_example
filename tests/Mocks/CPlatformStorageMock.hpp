#ifndef _TESTS_MOCKS_CPLATFORMSTORAGEMOCK_HPP_
#define _TESTS_MOCKS_CPLATFORMSTORAGEMOCK_HPP_

#include "IStorageService.hpp"
#include <gmock/gmock.h>

class CPlatformStorageMock : public IStorageService {
public:
  CPlatformStorageMock() = default;
  ~CPlatformStorageMock() = default;

  MOCK_METHOD(bool, registerCallback, (callback_t c), ());

  MOCK_METHOD(void, storeDataWithoutCallbackProvided, (int key, int value), ());
  MOCK_METHOD(void, storeDataWithCallbackProvided,
              (int key, int value, callback_t c), ());

  MOCK_METHOD(int, loadData, (int key), ());
};

#endif /* _TESTS_MOCKS_CPLATFORMSTORAGEMOCK_HPP_ */