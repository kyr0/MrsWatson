#include "TestRunner.h"
#include "AudioClock.h"

static int const TEST_BLOCKSIZE = 256;

static void _audioClockTestSetup(void) {
  initAudioClock();
}

static void _audioClockTestTeardown(void) {
  freeAudioClock();
}

static int _testInitAudioClock(void) {
  _assertIntEquals(getAudioClockCurrentFrame(), 0);
  _assertFalse(getAudioClockIsPlaying());
  _assertFalse(getAudioClockTransportChanged());
  return 0;
}

static int _testAdvanceAudioClock(void) {
  advanceAudioClock(TEST_BLOCKSIZE);
  _assertIntEquals(getAudioClockCurrentFrame(), TEST_BLOCKSIZE);
  _assert(getAudioClockIsPlaying());
  _assert(getAudioClockTransportChanged());
  return 0;
}

static int _testStopAudioClock(void) {
  advanceAudioClock(TEST_BLOCKSIZE);
  stopAudioClock();
  _assertFalse(getAudioClockIsPlaying());
  _assert(getAudioClockTransportChanged())
  return 0;
}

static int _testRestartAudioClock(void) {
  advanceAudioClock(TEST_BLOCKSIZE);
  stopAudioClock();
  advanceAudioClock(TEST_BLOCKSIZE);
  _assert(getAudioClockIsPlaying());
  _assert(getAudioClockTransportChanged());
  _assertIntEquals(getAudioClockCurrentFrame(), TEST_BLOCKSIZE * 2);
  return 0;
}

static int _testAdvanceClockMulitpleTimes(void) {
  int i;
  for(i = 0; i < 100; i++) {
    advanceAudioClock(TEST_BLOCKSIZE);
  }
  _assert(getAudioClockIsPlaying());
  _assertFalse(getAudioClockTransportChanged());
  _assertIntEquals(getAudioClockCurrentFrame(), TEST_BLOCKSIZE * 100);
  return 0;
}

TestSuite addAudioClockTests(void);
TestSuite addAudioClockTests(void) {
  TestSuite testSuite = newTestSuite("AudioClock", _audioClockTestSetup, _audioClockTestTeardown);
  addTest(testSuite, "Initialization", _testInitAudioClock);
  addTest(testSuite, "Advance clock", _testAdvanceAudioClock);
  addTest(testSuite, "Stop clock", _testStopAudioClock);
  addTest(testSuite, "Restart clock", _testRestartAudioClock);
  addTest(testSuite, "Multiple advance", _testAdvanceClockMulitpleTimes);
  return testSuite;
}
