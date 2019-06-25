#pragma once
#include "ProcessFilter.h"
#include "QueryProcessing.h"
class ResourceUnits
{
  ProcessFilter pFilterCopy;
protected:
  QueryProcessing qProcessorCopy;
public:
  ResourceUnits(ProcessFilter &pFilter,QueryProcessing &qProcessor)
  {
    pFilterCopy = pFilter;
    qProcessorCopy = qProcessor;
  }
  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new ResourceUnit(qProcessorCopy);
    stat->SetInstance(instance);
    return stat;
  }
};

class CPUUnits : public ResourceUnits
{
public:
  CPUUnits(ProcessFilter &pFilter, QueryProcessing &qProcessor) : ResourceUnits(pFilter, qProcessor)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new CPUUnit(qProcessorCopy);
    stat->SetInstance(instance);
    return stat;
  }
};

class RAMUnits : public ResourceUnits
{
public:
  RAMUnits(ProcessFilter &pFilter, QueryProcessing &qProcessor) : ResourceUnits(pFilter, qProcessor)
  {
  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new RAMUnit(qProcessorCopy);
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKReadIOPSUnits : public ResourceUnits
{
public:
  DISKReadIOPSUnits(ProcessFilter &pFilter, QueryProcessing &qProcessor) : ResourceUnits(pFilter, qProcessor)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKReadIOPSUnit(qProcessorCopy);
    stat->SetInstance(instance);
    return stat;
  }
};


class DISKWriteIOPSUnits : public ResourceUnits
{
public:
  DISKWriteIOPSUnits(ProcessFilter &pFilter, QueryProcessing &qProcessor) : ResourceUnits(pFilter, qProcessor)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKWriteIOPSUnit(qProcessorCopy);
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKWriteBytesUnits : public ResourceUnits
{
public:
  DISKWriteBytesUnits(ProcessFilter &pFilter, QueryProcessing &qProcessor) : ResourceUnits(pFilter, qProcessor)
  {
    pFilter.GetProcessPath();
  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKWriteBytesUnit(qProcessorCopy);
    stat->SetInstance(instance);
    return stat;
  }
};

class DISKReadBytesUnits : public ResourceUnits
{
public:
  DISKReadBytesUnits(ProcessFilter &pFilter, QueryProcessing &qProcessor) : ResourceUnits(pFilter,qProcessor)
  {

  }

  virtual ResourceUnit* GetStat(std::string instance)
  {
    ResourceUnit *stat = new DISKReadBytesUnit(qProcessorCopy);
    stat->SetInstance(instance);
    return stat;
  }
};