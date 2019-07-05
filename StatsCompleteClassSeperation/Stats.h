#pragma once
#include "ResourceUnits.h"
ELALogger *logger;
void GetValue(std::vector<ResourceUnits*> &resourceUnitsArray, ProcessFilter &pFilter, QueryProcessor &qProcessorInstance,std::vector<double> &result)
{
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
    qProcessorInstance.GetCount();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    qProcessorInstance.GetCount();
    for (int i=0;i<pFilter.instances.size();i++)
    {
      for (int j=0;j<resourceUnitArray[i].size();j++)
      {
        result[j] += resourceUnitArray[i][j]->ResolveCount();
      }
   }
    resourceUnitArray.clear();
}
void GetDiskStats(std::string path, std::string name)
{
  ProcessFilter pFilter(path, name);
  QueryProcessor queryProcessorInstance;
  queryProcessorInstance.Init();
  std::vector<ResourceUnits*> res;
  ResourceUnits *unit = new DISKReadBytesUnits(queryProcessorInstance);
  ResourceUnits * unit1 = new DISKWriteBytesUnits(queryProcessorInstance);
  ResourceUnits * unit2 = new DISKWriteIOPSUnits(queryProcessorInstance);
  ResourceUnits * unit3 = new DISKReadIOPSUnits(queryProcessorInstance);
  res.push_back(unit);
  res.push_back(unit1);
  res.push_back(unit2);
  res.push_back(unit3);
  bool value = true;
  while (value)
  {
    std::vector<double> result(res.size());
    GetValue(res, pFilter, queryProcessorInstance,result);
    logger->info("Disk Read Bytes : %v", result[0]);
    logger->info("Disk Write Bytes : %v", result[1]);
    logger->info("Disk Write IOPS : %v", result[2]);
    logger->info("Disk Read IOPS : %v", result[3]);
    logger->info("------%v", "");
  }
  getchar();
}
void GetCPUStats(std::string path, std::string name)
{
  ProcessFilter pFilter(path, name);
  QueryProcessor queryProcessorInstance;
  queryProcessorInstance.Init();
  std::vector<ResourceUnits*> res;
  ResourceUnits *unit = new CPUUnits(queryProcessorInstance);
  res.push_back(unit);
  bool value = true;
  while (value)
  {
    std::vector<double> result(res.size());
    GetValue(res, pFilter, queryProcessorInstance, result);
    logger->info("CPU Utilization : %v", result[0]);
  }
  getchar();
}
void GetRAMStats(std::string path, std::string name)
{
  ProcessFilter pFilter(path, name);
  QueryProcessor queryProcessorInstance;
  queryProcessorInstance.Init();
  std::vector<ResourceUnits*> res;
  ResourceUnits *unit = new RAMUnits(queryProcessorInstance);
  res.push_back(unit);
  bool value = true;
  while (value)
  {
    std::vector<double> result(res.size());
    GetValue(res, pFilter, queryProcessorInstance, result);
    logger->info("RAM Stats : %v", result[0]);
  }
  getchar();
}