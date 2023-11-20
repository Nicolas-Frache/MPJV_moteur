#pragma once
class CustomAsserts
{
public:
  int testCount;
  int passedTests;

  CustomAsserts();
  void beginTestClass(const char* testName);
  void assertTrue(bool condition, const char* testName);
  void endTestSession();

};

