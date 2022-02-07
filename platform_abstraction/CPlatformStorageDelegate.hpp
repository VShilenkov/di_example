#ifndef _PLATFORM_ABSTRACTION_CPLATFORMSTORAGEDELEGATE_HPP_
#define _PLATFORM_ABSTRACTION_CPLATFORMSTORAGEDELEGATE_HPP_

#include "IStorageService.hpp"

class CPlatformStorageService;

class CPlatformStorageDelegate : public IStorageService {

public:
  CPlatformStorageDelegate();
  ~CPlatformStorageDelegate();

  bool registerCallback(callback_t c);
  void storeDataWithoutCallbackProvided(int key, int value);
  void storeDataWithCallbackProvided(int key, int value, callback_t c);

  int loadData(int key);

private:
  CPlatformStorageService *mRealPlatform;
};

#endif /* _PLATFORM_ABSTRACTION_CPLATFORMSTORAGEDELEGATE_HPP_ */