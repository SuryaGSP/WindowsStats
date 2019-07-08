#pragma once
#include "ResourceUnits.h"
ELALogger *logger;
class ResourceUnitsHolder
{
protected:
  std::string processPath;
  std::string processName;
  ProcessFilter* processFilter;
  QueryProcessor* queryProcessor;
  double diskWriteIOPS;
  double diskWriteThroughput;
  double diskReadIOPS;
  double diskReadThroughput;
  double ramUsed;
  double cpuUsed;
  void GetValue(const std::vector<ResourceUnits*> &resourceUnitsArray, std::vector<double> &result)
  {
    std::vector<std::vector<ResourceUnit *>> resourceUnitVector(processFilter->instances.size(), std::vector<ResourceUnit*>(resourceUnitsArray.size(), 0));
    int i = 0;
    for (auto &instance : processFilter->instances)
    {
      int j = 0;
      for (auto& res : resourceUnitsArray)
      {
        ResourceUnit *stat = res->GetStat(instance);
        stat->Start();
        resourceUnitVector[i][j] = stat;
        j++;
      }
      i++;
    }
    queryProcessor->GetCount();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    queryProcessor->GetCount();
    for (int i = 0; i < processFilter->instances.size(); i++)
    {
      for (int j = 0; j < resourceUnitVector[i].size(); j++)
      {
        result[j] += resourceUnitVector[i][j]->ResolveCount();
      }
    }
    resourceUnitVector.clear();
  }
public:
  ResourceUnitsHolder(std::string path, std::string name)
  {
    processPath = path;
    processName = name;
    diskWriteIOPS = 0.0;
    diskWriteThroughput = 0.0;
    diskReadIOPS = 0.0;
    diskReadThroughput = 0.0;
    ramUsed = 0.0;
    cpuUsed = 0.0;
  }
  virtual void CaptureStats()
  {
  }
  double GetCPUUsed()
  {
    return cpuUsed;
  }
  double GetRAMUsed()
  {
    return ramUsed;
  }
  double GetReadIOPS()
  {
    return diskReadIOPS;
  }
  double GetReadThroughput()
  {
    return diskReadThroughput;
  }
  double GetWriteIOPS()
  {
    return diskWriteIOPS;
  }
  double GetWriteThroughput()
  {
    return diskWriteThroughput;
  }
};

class DiskWriteStats : public ResourceUnitsHolder
{
public:
  DiskWriteStats(std::string path, std::string name) : ResourceUnitsHolder(path,name)
  {
  }
  void CaptureStats()
  {
    processFilter = new ProcessFilter(processPath, processName);
    queryProcessor = new QueryProcessor();
    std::vector<ResourceUnits*> resourceUnitsVector;
    ResourceUnits *unit = new DISKWriteBytesUnits(queryProcessor);
    ResourceUnits *unit1 = new DISKWriteIOPSUnits(queryProcessor);
    resourceUnitsVector.push_back(unit);
    resourceUnitsVector.push_back(unit1);
    std::vector<double> result(resourceUnitsVector.size());
    GetValue(resourceUnitsVector, result);
    diskWriteThroughput = result[0];
    diskWriteIOPS = result[1];
  }
};

class DiskReadStats : public ResourceUnitsHolder
{
public:
  DiskReadStats(std::string path, std::string name) : ResourceUnitsHolder(path, name)
  {
  }
  void CaptureStats()
  {
    processFilter = new ProcessFilter(processPath, processName);
    queryProcessor = new QueryProcessor();
    std::vector<ResourceUnits*> resourceUnitsVector;
    ResourceUnits *unit = new DISKReadBytesUnits(queryProcessor);
    ResourceUnits * unit1 = new DISKReadIOPSUnits(queryProcessor);
    resourceUnitsVector.push_back(unit);
    resourceUnitsVector.push_back(unit1);
    std::vector<double> result(resourceUnitsVector.size());
    GetValue(resourceUnitsVector, result);
    diskReadThroughput = result[0];
    diskReadIOPS = result[1];
  }
};

class RAMStats : public ResourceUnitsHolder
{
public:
  RAMStats(std::string path, std::string name) : ResourceUnitsHolder(path, name)
  {
  }
  void CaptureStats()
  {
    processFilter = new ProcessFilter(processPath, processName);
    queryProcessor = new QueryProcessor();
    std::vector<ResourceUnits*> resourceUnitsVector;
    ResourceUnits *unit = new RAMUnits(queryProcessor);
    resourceUnitsVector.push_back(unit);
    std::vector<double> result(resourceUnitsVector.size());
    GetValue(resourceUnitsVector, result);
    ramUsed = result[0];
  }
};


class CPUStats : public ResourceUnitsHolder
{
public:
  CPUStats(std::string path, std::string name) : ResourceUnitsHolder(path, name)
  {
  }
  void CaptureStats()
  {
    processFilter = new ProcessFilter(processPath, processName);
    queryProcessor = new QueryProcessor();
    std::vector<ResourceUnits*> resourceUnitsVector;
    ResourceUnits *unit = new CPUUnits(queryProcessor);
    resourceUnitsVector.push_back(unit);
    std::vector<double> result(resourceUnitsVector.size());
    GetValue(resourceUnitsVector, result);
    cpuUsed = result[0];
  }
};