#include <iostream>
#include "CustomAsserts.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"


  CustomAsserts::CustomAsserts() {
    testCount = 0;
    passedTests = 0;
  }

  void CustomAsserts::beginTestClass(const char* testName){
    std::cout << BLUE << "********  " << testName << "  ********" << RESET << std::endl;
  };

  void CustomAsserts::assertTrue(bool condition, const char* testName){
    testCount++;

    if (condition){
      std::cout << GREEN << "   OK | " << RESET << testName << std::endl;
      passedTests++;
    } else{
      std::cout << RED << "   FAILED | " << testName << RESET << std::endl;
    }
  }

  void CustomAsserts::endTestSession(){
    std::cout << BLUE << "\n\n********  " << passedTests << "/" << testCount << " tests passed  ********" << RESET << std::endl;
  }

