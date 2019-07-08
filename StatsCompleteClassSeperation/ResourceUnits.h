#pragma once
#include "ProcessFilter.h"
class ResourceUnits
{
protected:
  QueryProcessor *queryProcessor;
public:
  ResourceUnits(QueryProcessor *queryProcessor)
  {
    this->queryProcessor = queryProcessor;
  }
  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new ResourceUnit(queryProcessor);
    stat->SetInstance(instance);
    return stat;
  }
};

class CPUUnits : public ResourceUnits
{
public:
  CPUUnits(QueryProcessor *queryProcessor) : ResourceUnits(queryProcessor)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new CPUUnit(queryProcessor);
    stat->SetInstance(instance);
    return stat;
  }
};

class RAMUnits : public ResourceUnits
{
public:
  RAMUnits(QueryProcessor *queryProcessor) : ResourceUnits(queryProcessor)
  {
  }

  virtual ResourceUnit* GetStat(std::string instance)
  {

    ResourceUnit *stat = new RAMUnit(queryProcessor);
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKReadIOPSUnits : public ResourceUnits
{
public:
  DISKReadIOPSUnits(QueryProcessor *queryProcessor) : ResourceUnits(queryProcessor)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKReadIOPSUnit(queryProcessor);
    stat->SetInstance(instance);
    return stat;
  }
};


class DISKWriteIOPSUnits : public ResourceUnits
{
public:
  DISKWriteIOPSUnits(QueryProcessor *queryProcessor) : ResourceUnits(queryProcessor)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKWriteIOPSUnit(queryProcessor);
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKWriteBytesUnits : public ResourceUnits
{
public:
  DISKWriteBytesUnits(QueryProcessor *queryProcessor) : ResourceUnits(queryProcessor)
  {
  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKWriteBytesUnit(queryProcessor);
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKReadBytesUnits : public ResourceUnits
{
public:
  DISKReadBytesUnits(QueryProcessor *queryProcessor) : ResourceUnits(queryProcessor)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKReadBytesUnit(queryProcessor);
    stat->SetInstance(instance);
    return stat;
  }
};