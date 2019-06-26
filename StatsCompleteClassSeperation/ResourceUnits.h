#pragma once
#include "ProcessFilter.h"
class ResourceUnits
{
  ProcessFilter pFilterCopy;
protected:
  justTrying jTrying;
public:
  ResourceUnits(ProcessFilter &pFilter,justTrying &jTryInstance)
  {
    pFilterCopy = pFilter;
    jTrying = jTryInstance;
  }
  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new ResourceUnit(jTrying);
    stat->SetInstance(instance);
    return stat;
  }
};

class CPUUnits : public ResourceUnits
{
public:
  CPUUnits(ProcessFilter &pFilter,justTrying &jTryInstance) : ResourceUnits(pFilter, jTryInstance)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new CPUUnit(jTrying);
    stat->SetInstance(instance);
    return stat;
  }
};

class RAMUnits : public ResourceUnits
{
public:
  RAMUnits(ProcessFilter &pFilter,justTrying &jTryInstance) : ResourceUnits(pFilter,jTryInstance)
  {
  }

  virtual ResourceUnit* GetStat(std::string instance)
  {

    ResourceUnit *stat = new RAMUnit(jTrying);
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKReadIOPSUnits : public ResourceUnits
{
public:
  DISKReadIOPSUnits(ProcessFilter &pFilter,justTrying &jTryInstance) : ResourceUnits(pFilter, jTryInstance)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKReadIOPSUnit(jTrying);
    stat->SetInstance(instance);
    return stat;
  }
};


class DISKWriteIOPSUnits : public ResourceUnits
{
public:
  DISKWriteIOPSUnits(ProcessFilter &pFilter,justTrying &jTryInstance) : ResourceUnits(pFilter, jTryInstance)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKWriteIOPSUnit(jTrying);
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKWriteBytesUnits : public ResourceUnits
{
public:
  DISKWriteBytesUnits(ProcessFilter &pFilter,justTrying &jTryInstance) : ResourceUnits(pFilter, jTryInstance)
  {
    pFilter.GetProcessPath();
  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKWriteBytesUnit(jTrying);
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKReadBytesUnits : public ResourceUnits
{
public:
  DISKReadBytesUnits(ProcessFilter &pFilter,justTrying &jTryInstance) : ResourceUnits(pFilter, jTryInstance)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKReadBytesUnit(jTrying);
    stat->SetInstance(instance);
    return stat;
  }
};