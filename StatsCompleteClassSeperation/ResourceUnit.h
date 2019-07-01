#pragma once
#include <ctime>
#include <atomic>
#include <string>
#include <thread>
#include <sstream>

#ifdef WINDOWS
#include <Windows.h>
#include <Pdh.h>
#include <pdhmsg.h>
#include <Psapi.h>
#endif
#include "QueryProcessor.h"

#pragma comment(lib, "pdh.lib")
extern ELALogger *logger;
class ResourceUnit
{
  PDH_HCOUNTER hcounter;
  PDH_FMT_COUNTERVALUE countervalue;
  double factor;
  std::string path;
  std::string counter;
  std::string instance;
  QueryProcessor qProcessorInstance;

  void SetCounter()
  {
    if (path == "")
    {
      if (instance == "")
      {
        instance = LoggerUtil::GetModuleName();
      }
      std::ostringstream str;
      str << "\\Process(" << instance << ")\\" << counter;
      path = str.str();
    }
//    puts(path.c_str());
  }

public:
  int x = 20;
  ResourceUnit() : factor(1)
  {

  }
  ResourceUnit(QueryProcessor &qProcessorCopy) : factor(1)
  {
    qProcessorInstance = qProcessorCopy;
  }

  double ResolveCount()
  {
    DWORD status = PdhGetFormattedCounterValue(hcounter, PDH_FMT_DOUBLE | PDH_FMT_NOCAP100, 0, &countervalue);
    if (status != ERROR_SUCCESS)
    {
      logger->error("PdhGetFormattedCounterValue %v", status);
      return 0.0;
    }
    return countervalue.doubleValue * factor;
  }



  ResourceUnit* SetCounter(std::string countername)
  {
    this->counter = countername;
    return this;
  }

  ResourceUnit* SetInstance(std::string instance)
  {
    this->instance = instance;
    return this;
  }

  ResourceUnit* SetCounterPath(std::string counterpath)
  {
    path = counterpath;
    return this;
  }
  std::string GetCounterPath()
  {
    return path;
  }
  ResourceUnit* SetFactor(double factor)
  {
    this->factor = factor;
    return this;
  }

  virtual void Start()
  {
    SetCounter();
    DWORD status = PdhAddCounterA(qProcessorInstance.hQuery, path.c_str(), 0, &hcounter);
    if (status != ERROR_SUCCESS)
    {
      logger->log("PdhAddCounterA %v", status);
      return;
    }
  }
};

class CPUUnit : public ResourceUnit
{
public:
  CPUUnit()
  {

  }
  CPUUnit(QueryProcessor &qProcessorCopy) :ResourceUnit(qProcessorCopy)
  {

  }
  virtual void Start()
  {
    SetCounter("% Processor Time");
    SetFactor(1.0 / std::thread::hardware_concurrency());
    ResourceUnit::Start();
  }
};

class RAMUnit : public ResourceUnit
{
public:
  RAMUnit()
  {

  }
  RAMUnit(QueryProcessor &qProcessorCopy) :ResourceUnit(qProcessorCopy)
  {

  }
  virtual void Start()
  {
    SetCounter("Working Set");
    SetFactor(1.0 / (1024 * 1024));
    ResourceUnit::Start();
  }
};

class DISKReadIOPSUnit : public ResourceUnit
{
public:
  DISKReadIOPSUnit()
  {

  }
  DISKReadIOPSUnit(QueryProcessor &qProcessorCopy) :ResourceUnit(qProcessorCopy)
  {
    
  }
  virtual void Start()
  {
    SetCounter("IO Read Operations/sec");
    SetFactor(1.0);
    ResourceUnit::Start();
  }
};

class DISKWriteIOPSUnit : public ResourceUnit
{
public:
  DISKWriteIOPSUnit()
  {

  }
  DISKWriteIOPSUnit(QueryProcessor &qProcessorCopy) :ResourceUnit(qProcessorCopy)
  {

  }
  virtual void Start()
  {
    SetCounter("IO Write Operations/sec");
    SetFactor(1.0);
    ResourceUnit::Start();
  }
};

class DISKReadBytesUnit : public ResourceUnit
{
public:
  DISKReadBytesUnit()
  {

  }
  DISKReadBytesUnit(QueryProcessor &qProcessorCopy) :ResourceUnit(qProcessorCopy)
  {

  }
  virtual void Start()
  {
    SetCounter("IO Read Bytes/sec");
    SetFactor(1.0 / (1024));
    ResourceUnit::Start();
  }
};

class DISKWriteBytesUnit : public ResourceUnit
{
public:
  DISKWriteBytesUnit()
  {

  }
  DISKWriteBytesUnit(QueryProcessor &qProcessorCopy) :ResourceUnit(qProcessorCopy)
  {

  }
  virtual void Start()
  {
    SetCounter("IO Write Bytes/sec");
    SetFactor(1.0 / (1024));
    ResourceUnit::Start();
  }
};