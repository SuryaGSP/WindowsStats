#pragma once
#include "ResourceUnits.h"
ELALogger *logger;
void GetValue(std::vector<ResourceUnits*> &resourceUnitsArray, ProcessFilter &pFilter, justTrying &jTryingInstance)
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
  //logger->info("Disk Read Bytes : %v", result[0]);
  //logger->info("Disk Write Bytes : %v", result[1]);
  //logger->info("Disk Write IOPS : %v", result[2]);
  //logger->info("Disk Read IOPS : %v", result[3]);
  //logger->info("------%v", "");
  for (int jInstance = 0; jInstance < resourceUnitsArray.size(); jInstance++)
  {
    logger->info("%v", result[jInstance]);
  }
}
void GetDiskStats(std::string path, std::string name)
{
  justTrying jTrying1;
  ProcessFilter pFilter(path, name, jTrying1);
  jTrying1.Init();
  std::vector<ResourceUnits*> res;
  ResourceUnits *unit = new DISKReadBytesUnits(pFilter, jTrying1);
  ResourceUnits * unit1 = new DISKWriteBytesUnits(pFilter, jTrying1);
  ResourceUnits * unit2 = new DISKWriteIOPSUnits(pFilter, jTrying1);
  ResourceUnits * unit3 = new DISKReadIOPSUnits(pFilter, jTrying1);
  res.push_back(unit);
  res.push_back(unit1);
  res.push_back(unit2);
  res.push_back(unit3);
  bool value = true;
  while (value)
  {
    GetValue(res, pFilter, jTrying1);
  }
  getchar();
}
void GetCPUStats(std::string path, std::string name)
{
  justTrying jTrying1;
  ProcessFilter pFilter(path, name, jTrying1);
  jTrying1.Init();
  std::vector<ResourceUnits*> res;
  ResourceUnits *unit = new CPUUnits(pFilter, jTrying1);
  res.push_back(unit);
  bool value = true;
  while (value)
  {
    GetValue(res, pFilter, jTrying1);
  }
  getchar();
}
void GetRAMStats(std::string path, std::string name)
{
  justTrying jTrying1;
  ProcessFilter pFilter(path, name, jTrying1);
  jTrying1.Init();
  std::vector<ResourceUnits*> res;
  ResourceUnits *unit = new RAMUnits(pFilter, jTrying1);
  res.push_back(unit);
  bool value = true;
  while (value)
  {
    GetValue(res, pFilter, jTrying1);
  }
  getchar();
}