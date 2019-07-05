#pragma once
#include <iostream>
#include "Stats.h"
#include <thread>
int main()
{
  logger = new ELALogger();
  logger->Start();
  std::string path = "c:\\manageengine\\eventlog analyzer\\";
  std::string name = "java.exe"; 
  GetDiskStats(path, name);
  return 0;
}