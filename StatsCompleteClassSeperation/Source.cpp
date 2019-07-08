  #pragma once
#include <iostream>
#include "ResourceUnitsHolder.h"
#include <thread>
int main()
{
  logger = new ELALogger();
  logger->Start();
  std::string path = "c:\\manageengine\\eventlog analyzer\\";
  std::string name = "java.exe"; 
  ResourceUnitsHolder* resourceUnitsHolder = new RAMStats(path, name);
  //ResourceUnitsHolder* resourceUnitsHolder = new CPUStats(path, name);
  //ResourceUnitsHolder* resourceUnitsHolder = new DiskReadStats(path, name);
  //ResourceUnitsHolder* resourceUnitsHolder = new DiskWriteStats(path, name);
  bool value = true;
  while (true)
  {
    resourceUnitsHolder->CaptureStats();
    std::cout << resourceUnitsHolder->GetRAMUsed() << std::endl;
    //std::cout << resourceUnitsHolder->GetCPUUsed() << std::endl;
    //std::cout << resourceUnitsHolder->GetReadIOPS() << " " << resourceUnitsHolder->GetReadThroughput() << std::endl;
    //std::cout << resourceUnitsHolder->GetWriteIOPS() << " " << resourceUnitsHolder->GetWriteThroughput() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  std::cin.get();
  return 0;
}