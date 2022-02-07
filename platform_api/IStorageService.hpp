#ifndef _PLATFORM_API_ISTORAGESERVICE_HPP_
#define _PLATFORM_API_ISTORAGESERVICE_HPP_

#include <functional>

class IStorageService {
public:
  using error_t = uint8_t; /* 0 - no error */
  using callback_t = std::function<void(uint8_t)>;

  IStorageService() = default;
  virtual ~IStorageService() = default;

  virtual bool registerCallback(callback_t c) = 0;
  virtual void storeDataWithoutCallbackProvided(int key, int value) = 0;
  virtual void storeDataWithCallbackProvided(int key, int value,
                                             callback_t c) = 0;

  virtual int loadData(int key) = 0;
};

#endif /* _PLATFORM_API_ISTORAGESERVICE_HPP_ */