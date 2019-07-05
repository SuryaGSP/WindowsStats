#pragma once
#include "ProcessFilter.h"
class ResourceUnits
{
protected:
  QueryProcessor queryProcessorInstance;
public:
  ResourceUnits(QueryProcessor &qProcessorCopy)
  {
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
  CPUUnits(QueryProcessor &qProcessorCopy) : ResourceUnits(qProcessorCopy)
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
  RAMUnits(QueryProcessor &qProcessorCopy) : ResourceUnits(qProcessorCopy)
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
  DISKReadIOPSUnits(QueryProcessor &qProcessorCopy) : ResourceUnits(qProcessorCopy)
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
  DISKWriteIOPSUnits(QueryProcessor &qProcessorCopy) : ResourceUnits(qProcessorCopy)
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
  DISKWriteBytesUnits(QueryProcessor &qProcessorCopy) : ResourceUnits(qProcessorCopy)
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
  DISKReadBytesUnits(QueryProcessor &qProcessorCopy) : ResourceUnits(qProcessorCopy)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKReadBytesUnit(queryProcessorInstance);
    stat->SetInstance(instance);
    return stat;
  }
};