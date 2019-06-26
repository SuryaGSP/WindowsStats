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
#include "JustTrying.h"

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
  justTrying jTrying;

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
  int x = 20;
  ResourceUnit() : factor(1)
  {

  }
  ResourceUnit(justTrying &jTryInstance) : factor(1)
  {
    jTrying = jTryInstance;
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

  ResourceUnit* SetFactor(double factor)
  {
    this->factor = factor;
    return this;
  }

  virtual void Start()
  {
    SetCounter();
    DWORD status = PdhAddCounterA(jTrying.hQuery, path.c_str(), 0, &hcounter);
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
  CPUUnit(justTrying &jTryInstance) :ResourceUnit(jTryInstance)
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
  RAMUnit(justTrying &jTryInstance) :ResourceUnit(jTryInstance)
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
  DISKReadIOPSUnit(justTrying &jTryInstance) :ResourceUnit(jTryInstance)
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
  DISKWriteIOPSUnit(justTrying &jTryInstance) :ResourceUnit(jTryInstance)
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
  DISKReadBytesUnit(justTrying &jTryInstance) :ResourceUnit(jTryInstance)
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
  DISKWriteBytesUnit(justTrying &jTryInstance) :ResourceUnit(jTryInstance)
  {

  }
  virtual void Start()
  {
    SetCounter("IO Write Bytes/sec");
    SetFactor(1.0 / (1024));
    ResourceUnit::Start();
  }
};