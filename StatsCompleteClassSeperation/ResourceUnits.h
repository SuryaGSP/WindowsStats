#pragma once
#include "ProcessFilter.h"
class ResourceUnits
{
  ProcessFilter pFilterCopy;
public:
  ResourceUnits(ProcessFilter &pFilter)
  {
    pFilterCopy = pFilter;
  }
  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new ResourceUnit();
    stat->SetInstance(instance);
    return stat;
  }
};

class CPUUnits : public ResourceUnits
{
public:
  CPUUnits(ProcessFilter &pFilter) : ResourceUnits(pFilter)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new CPUUnit();
    stat->SetInstance(instance);
    return stat;
  }
};

class RAMUnits : public ResourceUnits
{
public:
  RAMUnits(ProcessFilter &pFilter) : ResourceUnits(pFilter)
  {
  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new RAMUnit();
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKReadIOPSUnits : public ResourceUnits
{
public:
  DISKReadIOPSUnits(ProcessFilter &pFilter) : ResourceUnits(pFilter)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKReadIOPSUnit();
    stat->SetInstance(instance);
    return stat;
  }
};


class DISKWriteIOPSUnits : public ResourceUnits
{
public:
  DISKWriteIOPSUnits(ProcessFilter &pFilter) : ResourceUnits(pFilter)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKWriteIOPSUnit();
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKWriteBytesUnits : public ResourceUnits
{
public:
  DISKWriteBytesUnits(ProcessFilter &pFilter) : ResourceUnits(pFilter)
  {
    pFilter.GetProcessPath();
  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKWriteBytesUnit();
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKReadBytesUnits : public ResourceUnits
{
public:
  DISKReadBytesUnits(ProcessFilter &pFilter) : ResourceUnits(pFilter)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKReadBytesUnit();
    stat->SetInstance(instance);
    return stat;
  }
};