#pragma once
#include <iostream>
#include "ResourceUnits.h"
ELALogger *logger;
void GetValue(std::vector<ResourceUnits*> &resourceUnitsArray, ProcessFilter &pFilter, justTrying jTryingInstance)
{
  std::vector<ResourceUnit*> resourceUnitArray;
  double* result = new double[resourceUnitsArray.size()];
  int iInstance = 0;
  for (int jInstance1 = 0; jInstance1 < resourceUnitsArray.size(); jInstance1++)
  {
    result[jInstance1] = 0.0;
  }

  for (auto &instance : pFilter.instances)
  {
    resourceUnitArray.clear();
    for (auto& res : resourceUnitsArray)
    {
      ResourceUnit *stat = res->GetStat(instance);
      stat->Start();
      resourceUnitArray.push_back(stat);
    }
    jTryingInstance.GetCount();
    for (auto& res : resourceUnitArray)
    {
      result[iInstance] = result[iInstance] + res->ResolveCount();
      iInstance++;
    }
    iInstance = 0;
  }
  logger->info("Disk Read Bytes : %v", result[0]);
  logger->info("Disk Write Bytes : %v", result[1]);
  logger->info("Disk Write IOPS : %v", result[2]);
  logger->info("Disk Read IOPS : %v", result[3]);
  logger->info("------%v", "");
  /*for (int jInstance = 0; jInstance < arrayCount; jInstance++)
  {
    logger->info("%v",result[jInstance]);
  }*/
}
int main()
{
  logger = new ELALogger();
  logger->Start();
  std::string path = "c:\\manageengine\\eventlog analyzer\\";
  std::string name = "java.exe"; 
  justTrying jTrying1;
  ProcessFilter pFilter;
  pFilter.Start(path,name,jTrying1);
  std::vector<ResourceUnits*> res;
  ResourceUnits *unit = new DISKReadBytesUnits(pFilter);
  ResourceUnits * unit1 = new DISKWriteBytesUnits(pFilter);
  ResourceUnits * unit2 = new DISKWriteIOPSUnits(pFilter);
  ResourceUnits * unit3 = new DISKReadIOPSUnits(pFilter);
  res.push_back(unit);
  res.push_back(unit1);
  res.push_back(unit2);
  res.push_back(unit3);
  bool value = true;
  while (value)
  {
    GetValue(res,pFilter,jTrying1);
  }
  getchar();
  return 0;
}