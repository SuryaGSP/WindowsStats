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

#pragma comment(lib, "pdh.lib")

extern ELALogger *logger;
class ResourceUnit
{
  static PDH_HQUERY hQuery;
  PDH_HCOUNTER hcounter;
  PDH_FMT_COUNTERVALUE countervalue;
  double factor;
  std::string path;
  std::string counter;
  std::string instance;

  static void GetConterValue()
  {
    DWORD status = PdhCollectQueryData(hQuery);
    if (status != ERROR_SUCCESS)
    {
      logger->info("PdhCollectQueryData %v", status);
      return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    status = PdhCollectQueryData(hQuery);
    if (status != ERROR_SUCCESS)
    {
      logger->info("PdhCollectQueryData %v", status);
      return;
    }
    return;
  }

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
  ResourceUnit() : factor(1)
  {
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

  static void GetCount()
  {
    GetConterValue();
  }

  virtual void Start()
  {
    SetCounter();
    DWORD status = PdhAddCounterA(hQuery, path.c_str(), 0, &hcounter);
    if (status != ERROR_SUCCESS)
    {
      logger->log("PdhAddCounterA %v", status);
      return;
    }
  }

  static void Init()
  {
    DWORD status = PdhOpenQueryA(NULL, 0, &hQuery);
    if (status != ERROR_SUCCESS)
    {
      logger->log("PdhOpenQueryA %v", status);
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
};

class RAMUnit : public ResourceUnit
{
  virtual void Start()
  {
    SetCounter("Working Set");
    SetFactor(1.0 / (1024 * 1024));
    ResourceUnit::Start();
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
};

class DISKWriteIOPSUnit : public ResourceUnit
{
  virtual void Start()
  {
    SetCounter("IO Write Operations/sec");
    SetFactor(1.0);
    ResourceUnit::Start();
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
};

class DISKWriteBytesUnit : public ResourceUnit
{
  virtual void Start()
  {
    SetCounter("IO Write Bytes/sec");
    SetFactor(1.0 / (1024));
    ResourceUnit::Start();
  }
};