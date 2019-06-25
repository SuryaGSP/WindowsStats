#pragma once
#include <iostream>
#include "ResourceUnits.h"

ELALogger *logger;
void GetValue(std::vector<ResourceUnits*> &resourceUnitsArray, QueryProcessing &qLocalCopy, ProcessFilter &pFilter)
{
  std::vector<ResourceUnit*> resourceUnitArray;
  double* result = new double[resourceUnitsArray.size()];
  int iInstance = 0;
  for (int jInstance = 0; jInstance < resourceUnitsArray.size(); jInstance++)
  {
    result[jInstance] = 0.0;
  }
  const std::vector<std::string> &instances =  pFilter.GetInstance();
  for (auto &instance : instances)
  {
    resourceUnitArray.clear();
    for (auto& res : resourceUnitsArray)
    {
      ResourceUnit *stat = res->GetStat(instance);
      stat->Start();
      resourceUnitArray.push_back(stat);
    }
    qLocalCopy.GetCount();
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
  QueryProcessing* qProcessor = new QueryProcessing();
  ProcessFilter* pFilter = new ProcessFilter();
  pFilter->Start(path,name);
  std::vector<ResourceUnits*> res;
  ResourceUnits *unit = new DISKReadBytesUnits(*pFilter,*qProcessor);
  ResourceUnits * unit1 = new DISKWriteBytesUnits(*pFilter, *qProcessor);
  ResourceUnits * unit2 = new DISKWriteIOPSUnits(*pFilter, *qProcessor);
  ResourceUnits * unit3 = new DISKReadIOPSUnits(*pFilter, *qProcessor);
  res.push_back(unit);
  res.push_back(unit1);
  res.push_back(unit2);
  res.push_back(unit3);
  bool value = true;
  while (value)
  {
    GetValue(res,*qProcessor,*pFilter);
  }
  getchar();
}