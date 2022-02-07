#ifndef _PLATFORM_IMPLEMENTATION_CPLATFORMSTORAGESERVICE_HPP_
#define _PLATFORM_IMPLEMENTATION_CPLATFORMSTORAGESERVICE_HPP_

#include <functional>

// Real platform implementation which we only have headers
// But for simplicity and visibility we do our own implementation

class CPlatformStorageService {
public:
  using error_t = uint8_t; /* 0 - no error */
  using callback_t = std::function<void(uint8_t)>;

  CPlatformStorageService() : mCallback(nullptr) {}

  ~CPlatformStorageService() = default;

  bool registerCallback(callback_t c);
  void storeDataWithoutCallbackProvided(int key, int value);
  void storeDataWithCallbackProvided(int key, int value, callback_t c);

  int loadData(int key);

private:
  bool store(int key, int value);

private:
  callback_t mCallback;
};

#endif /* _PLATFORM_IMPLEMENTATION_CPLATFORMSTORAGESERVICE_HPP_ */