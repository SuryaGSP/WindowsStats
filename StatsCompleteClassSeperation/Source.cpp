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
  std::thread t1(GetDiskStats, path, name);
  //std::thread t2(GetCPUStats, path, name);
  t1.join();
  //t2.join();
  return 0;
}