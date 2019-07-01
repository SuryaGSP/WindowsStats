#pragma once
#include "ProcessFilter.h"
class ResourceUnits
{
  ProcessFilter pFilterInstance;
protected:
  QueryProcessor queryProcessorInstance;
public:
  ResourceUnits(ProcessFilter &pFilterCopy,QueryProcessor &qProcessorCopy)
  {
    pFilterInstance = pFilterCopy;
    queryProcessorInstance = qProcessorCopy;
  }
  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new ResourceUnit(queryProcessorInstance);
    stat->SetInstance(instance);
    return stat;
  }
};

class CPUUnits : public ResourceUnits
{
public:
  CPUUnits(ProcessFilter &pFilterCopy,QueryProcessor &qProcessorCopy) : ResourceUnits(pFilterCopy, qProcessorCopy)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new CPUUnit(queryProcessorInstance);
    stat->SetInstance(instance);
    return stat;
  }
};

class RAMUnits : public ResourceUnits
{
public:
  RAMUnits(ProcessFilter &pFilterCopy,QueryProcessor &qProcessorCopy) : ResourceUnits(pFilterCopy, qProcessorCopy)
  {
  }

  virtual ResourceUnit* GetStat(std::string instance)
  {

    ResourceUnit *stat = new RAMUnit(queryProcessorInstance);
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKReadIOPSUnits : public ResourceUnits
{
public:
  DISKReadIOPSUnits(ProcessFilter &pFilterCopy,QueryProcessor &qProcessorCopy) : ResourceUnits(pFilterCopy, qProcessorCopy)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKReadIOPSUnit(queryProcessorInstance);
    stat->SetInstance(instance);
    return stat;
  }
};


class DISKWriteIOPSUnits : public ResourceUnits
{
public:
  DISKWriteIOPSUnits(ProcessFilter &pFilterCopy,QueryProcessor &qProcessorCopy) : ResourceUnits(pFilterCopy, qProcessorCopy)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKWriteIOPSUnit(queryProcessorInstance);
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKWriteBytesUnits : public ResourceUnits
{
public:
  DISKWriteBytesUnits(ProcessFilter &pFilterCopy,QueryProcessor &qProcessorCopy) : ResourceUnits(pFilterCopy, qProcessorCopy)
  {
  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKWriteBytesUnit(queryProcessorInstance);
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKReadBytesUnits : public ResourceUnits
{
public:
  DISKReadBytesUnits(ProcessFilter &pFilterCopy,QueryProcessor &qProcessorCopy) : ResourceUnits(pFilterCopy, qProcessorCopy)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKReadBytesUnit(queryProcessorInstance);
    stat->SetInstance(instance);
    return stat;
  }
};