#include <gtest/gtest.h>

#include "CPlatformConsumer.hpp"
#include "Mocks/CPlatformStorageMock.hpp"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::InvokeArgument;
using ::testing::Return;
using ::testing::SaveArg;

TEST(platform_consumer_suite, construction_only) {
  // Arrange
  CPlatformStorageMock storage;

  // Expectations on calls
  // No behavior, just declare that we expect this happens
  EXPECT_CALL(storage, loadData(_));
  EXPECT_CALL(storage, registerCallback(_));

  // Act
  CPlatformConsumer *consumer = new CPlatformConsumer(&storage);

  // Assert
  SUCCEED();
}

TEST(platform_consumer_suite, construction_destruct) {
  // Arrange
  CPlatformStorageMock storage;

  // Expectations on calls
  // No behavior, just declare that we expect this happens
  EXPECT_CALL(storage, loadData(_));
  EXPECT_CALL(storage, registerCallback(_));

  // Act
  CPlatformConsumer consumer(&storage);

  // Assert
  SUCCEED();
}

TEST(platform_consumer_suite, check_initial_state) {
  // Arrange
  CPlatformStorageMock storage;
  int lastStoredValue = 33;

  // Expectations on calls
  EXPECT_CALL(storage, loadData(_)).WillOnce(Return(lastStoredValue));
  EXPECT_CALL(storage, registerCallback(_));

  // Act
  CPlatformConsumer consumer(&storage);

  // Assert
  EXPECT_EQ(consumer.getResult(), lastStoredValue);
}

TEST(platform_consumer_suite, flush_no_changes) {
  // Arrange
  CPlatformStorageMock storage;
  IStorageService::callback_t classwide;

  // Expectations on calls
  EXPECT_CALL(storage, loadData(_));
  EXPECT_CALL(storage, registerCallback(_))
      .WillOnce(DoAll(SaveArg<0>(&classwide), Return(true)));
  // Not expect this function to be called
  EXPECT_CALL(storage, storeDataWithoutCallbackProvided(_, _))
      .Times(testing::Exactly(0));

  // Act
  CPlatformConsumer consumer(&storage);
  bool flushresult = consumer.flush();

  // Assert  // default commit state is false
  EXPECT_FALSE(flushresult);
}

TEST(platform_consumer_suite, flush_on_changes_failure_storing) {
  // Arrange
  CPlatformStorageMock storage;
  IStorageService::callback_t classwide;

  // Expectations on calls
  EXPECT_CALL(storage, loadData(_));
  EXPECT_CALL(storage, registerCallback(_))
      .WillOnce(DoAll(SaveArg<0>(&classwide), Return(true)));
  // failure on saving
  EXPECT_CALL(storage, storeDataWithoutCallbackProvided(_, _))
      .WillOnce(Invoke([&classwide]() { classwide(23); }));

  // has to be called, we have new results, but haven't save them
  EXPECT_CALL(storage, storeDataWithCallbackProvided(_, _, _));

  // Act
  CPlatformConsumer consumer(&storage);
  consumer.fooooooo(); // run one iteration
  bool flushresult = consumer.flush();

  // Assert  // default commit state is false
  EXPECT_FALSE(flushresult);
}

TEST(platform_consumer_suite, flush_on_changes_success_storing) {
  // Arrange
  CPlatformStorageMock storage;
  IStorageService::callback_t classwide;

  // Expectations on calls
  EXPECT_CALL(storage, loadData(_));
  EXPECT_CALL(storage, registerCallback(_))
      .WillOnce(DoAll(SaveArg<0>(&classwide), Return(true)));
  // success on saving
  EXPECT_CALL(storage, storeDataWithoutCallbackProvided(_, _))
      .WillOnce(Invoke([&classwide]() { classwide(0); }));
  // shouldn't be called - we save evrything manually
  EXPECT_CALL(storage, storeDataWithCallbackProvided(_, _, _)).Times(0);

  // Act
  CPlatformConsumer consumer(&storage);
  consumer.fooooooo(); // run one iteration
  bool flushresult = consumer.flush();

  // Assert  // default commit state is false
  EXPECT_TRUE(flushresult);
}

TEST(platform_consumer_suite, flush_on_destruction_fail_saving) {
  // Arrange
  CPlatformStorageMock storage;
  IStorageService::callback_t classwide;

  // Expectations on calls
  EXPECT_CALL(storage, loadData(_));
  EXPECT_CALL(storage, registerCallback(_))
      .WillOnce(DoAll(SaveArg<0>(&classwide), Return(true)));
  // call lambda with error
  EXPECT_CALL(storage, storeDataWithCallbackProvided(_, _, _))
      .WillOnce(InvokeArgument<2>(23));

  // Act
  CPlatformConsumer consumer(&storage);
  consumer.fooooooo(); // run one iteration

  // Assert - nothing to check
  SUCCEED();
}

TEST(platform_consumer_suite, flush_on_destruction_success_saving) {
  // Arrange
  CPlatformStorageMock storage;
  IStorageService::callback_t classwide;

  // Expectations on calls
  EXPECT_CALL(storage, loadData(_));
  EXPECT_CALL(storage, registerCallback(_))
      .WillOnce(DoAll(SaveArg<0>(&classwide), Return(true)));
  // call lambda without error
  EXPECT_CALL(storage, storeDataWithCallbackProvided(_, _, _))
      .WillOnce(InvokeArgument<2>(0));

  // Act
  CPlatformConsumer consumer(&storage);
  consumer.fooooooo(); // run one iteration

  // Assert - nothing to check
  SUCCEED();
}