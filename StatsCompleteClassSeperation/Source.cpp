#pragma once
#include <iostream>
#include "ResourceUnits.h"
ELALogger *logger;
PDH_HQUERY ResourceUnit::hQuery;
int main()
{
  logger = new ELALogger();
  logger->Start();
  std::string path = "c:\\manageengine\\eventlog analyzer\\";
  std::string name = "java.exe"; 
  ProcessFilter* pFilter = new ProcessFilter();
  pFilter->Start(path,name);
  std::vector<ResourceUnits*> res;
  ResourceUnits *unit = new DISKReadBytesUnits(*pFilter);
  ResourceUnits * unit1 = new DISKWriteBytesUnits(*pFilter);
  ResourceUnits * unit2 = new DISKWriteIOPSUnits(*pFilter);
  ResourceUnits * unit3 = new DISKReadIOPSUnits(*pFilter);
  res.push_back(unit);
  res.push_back(unit1);
  res.push_back(unit2);
  res.push_back(unit3);
}