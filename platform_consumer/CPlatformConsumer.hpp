#ifndef _PLATFORM_CONSUMER_CPLATFORMCONSUMER_HPP_
#define _PLATFORM_CONSUMER_CPLATFORMCONSUMER_HPP_

class IStorageService;

class CPlatformConsumer {
public:
  CPlatformConsumer(IStorageService *service);
  ~CPlatformConsumer();

  void fooooooo(); // run some complex computation
  bool flush();    // forcely store data to the storage

  int getResult() const { return lastComputationResult; }

private:
  IStorageService *mStorage;
  bool newResultsOfComputationObtained;
  int lastComputationResult;
  bool lastStoreSuccess;
};

#endif /* _PLATFORM_CONSUMER_CPLATFORMCONSUMER_HPP_ */