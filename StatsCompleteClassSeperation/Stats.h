#pragma once
#include "ResourceUnits.h"
ELALogger *logger;
void GetValue(std::vector<ResourceUnits*> &resourceUnitsArray, ProcessFilter &pFilter, QueryProcessor &jTryingInstance)
{
  std::vector<double> result(resourceUnitsArray.size());
//  double* result = new double[resourceUnitsArray.size()];
  //std::vector<ResourceUnit*> resourceUnitArray;
  std::vector<std::vector<ResourceUnit *>> resourceUnitArray(pFilter.instances.size(),std::vector<ResourceUnit*>(resourceUnitsArray.size(),0));
  int i = 0;
  for (auto &instance : pFilter.instances)
  {
    int j = 0;
    for (auto& res : resourceUnitsArray)
    {
      ResourceUnit *stat = res->GetStat(instance);
      stat->Start();
      resourceUnitArray[i][j] = stat;
      j++;
    }
    i++;
  }
    jTryingInstance.GetCount();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    jTryingInstance.GetCount();
    for (int i=0;i<pFilter.instances.size();i++)
    {
      for (int j=0;j<resourceUnitArray[i].size();j++)
      {
        result[j] += resourceUnitArray[i][j]->ResolveCount();
   //     logger->info("%v %v", resourceUnitArray[i][j]->GetCounterPath() , resourceUnitArray[i][j]->ResolveCount());
      }
   }
    resourceUnitArray.clear();
  logger->info("Disk Read Bytes : %v", result[0]);
  logger->info("Disk Write Bytes : %v", result[1]);
  logger->info("Disk Write IOPS : %v", result[2]);
  logger->info("Disk Read IOPS : %v", result[3]);
  logger->info("------%v", "");
  /*for (int jInstance = 0; jInstance < resourceUnitsArray.size(); jInstance++)
  {
    logger->info("FInal Result : %v ", result[jInstance]);
  }*/
}
void GetDiskStats(std::string path, std::string name)
{
  QueryProcessor queryProcessorInstance;
  ProcessFilter pFilter(path, name, queryProcessorInstance);
  queryProcessorInstance.Init();
  std::vector<ResourceUnits*> res;
  ResourceUnits *unit = new DISKReadBytesUnits(pFilter, queryProcessorInstance);
  ResourceUnits * unit1 = new DISKWriteBytesUnits(pFilter, queryProcessorInstance);
  ResourceUnits * unit2 = new DISKWriteIOPSUnits(pFilter, queryProcessorInstance);
  ResourceUnits * unit3 = new DISKReadIOPSUnits(pFilter, queryProcessorInstance);
  res.push_back(unit);
  res.push_back(unit1);
  res.push_back(unit2);
  res.push_back(unit3);
  bool value = true;
  while (value)
  {
    GetValue(res, pFilter, queryProcessorInstance);
  }
  getchar();
}
void GetCPUStats(std::string path, std::string name)
{
  QueryProcessor queryProcessorInstance;
  ProcessFilter pFilter(path, name, queryProcessorInstance);
  queryProcessorInstance.Init();
  std::vector<ResourceUnits*> res;
  ResourceUnits *unit = new CPUUnits(pFilter, queryProcessorInstance);
  res.push_back(unit);
  bool value = true;
  while (value)
  {
    GetValue(res, pFilter, queryProcessorInstance);
  }
  getchar();
}
void GetRAMStats(std::string path, std::string name)
{
  QueryProcessor jTrying1;
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