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
#include "elalogger.h"
#include "QueryProcessing.h"
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
  QueryProcessing qProcessorLocalCopy;
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
    puts(path.c_str());
  }
public:
  ResourceUnit(QueryProcessing &qProcessorCopy) : factor(1)
  {
     qProcessorLocalCopy = qProcessorCopy;
  }
  ResourceUnit() : factor(1)
  {

  }
  double ResolveCount()
  {
    DWORD status = PdhGetFormattedCounterValue(hcounter, PDH_FMT_DOUBLE | PDH_FMT_NOCAP100, 0, &countervalue);
    if (status != ERROR_SUCCESS)
    {
      if (status == PDH_INVALID_ARGUMENT)
      {
        std::cout << "arg";
      }
      else if (status == PDH_INVALID_DATA)
      {
        std::cout << "data";
      }
      else if(status == PDH_INVALID_HANDLE)
      {
        std::cout << "handl";
      }
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

  ResourceUnit* SetFactor(double factor)
  {
    this->factor = factor;
    return this;
  }

  virtual void Start()
  {
    SetCounter();
    DWORD status = PdhAddCounterA(qProcessorLocalCopy.GetHQuery(), path.c_str(), 0, &hcounter);
    if (status != ERROR_SUCCESS)
    {
      logger->log("PdhAddCounterA %v", status);
      return;
    }
  }

};

class CPUUnit : public ResourceUnit
{
  virtual void Start()
  {
    SetCounter("% Processor Time");
    SetFactor(1.0 / std::thread::hardware_concurrency());
    ResourceUnit::Start();
  }
public :
  CPUUnit(QueryProcessing &qProcessorCopy):ResourceUnit(qProcessorCopy)
  {

  }
};

class RAMUnit : public ResourceUnit
{
  virtual void Start()
  {
    SetCounter("Working Set");
    SetFactor(1.0 / (1024 * 1024));
    ResourceUnit::Start();
  }
public:
  RAMUnit(QueryProcessing &qProcessorCopy) :ResourceUnit(qProcessorCopy)
  {

  }
};

class DISKReadIOPSUnit : public ResourceUnit
{
  virtual void Start()
  {
    SetCounter("IO Read Operations/sec");
    SetFactor(1.0);
    ResourceUnit::Start();
  }
public:
  DISKReadIOPSUnit(QueryProcessing &qProcessorCopy) :ResourceUnit(qProcessorCopy)
  {

  }
};

class DISKWriteIOPSUnit : public ResourceUnit
{
  virtual void Start()
  {
    SetCounter("IO Write Operations/sec");
    SetFactor(1.0);
    ResourceUnit::Start();
  }
public:
  DISKWriteIOPSUnit(QueryProcessing &qProcessorCopy) :ResourceUnit(qProcessorCopy)
  {

  }
};

class DISKReadBytesUnit : public ResourceUnit
{
  virtual void Start()
  {
    SetCounter("IO Read Bytes/sec");
    SetFactor(1.0 / (1024));
    ResourceUnit::Start();
  }
public:
  DISKReadBytesUnit(QueryProcessing &qProcessorCopy) :ResourceUnit(qProcessorCopy)
  {

  }
};

class DISKWriteBytesUnit : public ResourceUnit
{
  virtual void Start()
  {
    SetCounter("IO Write Bytes/sec");
    SetFactor(1.0 / (1024));
    ResourceUnit::Start();
  }
public:
  DISKWriteBytesUnit(QueryProcessing &qProcessorCopy) :ResourceUnit(qProcessorCopy)
  {

  }
};