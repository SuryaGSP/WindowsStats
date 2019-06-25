#pragma once
#include <Pdh.h>
#include "ELALogger.h"
extern ELALogger* logger;
class QueryProcessing
{
  PDH_HQUERY hQuery;
  void GetConterValue()
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
public:
  void GetCount()
  {
    GetConterValue();
  }
  
  void Init()
  {
    DWORD status = PdhOpenQueryA(NULL, 0, &hQuery);
    if (status != ERROR_SUCCESS)
    {
      logger->log("PdhOpenQueryA %v", status);
      return;
    }
  }

  PDH_HQUERY GetHQuery()
  {
    return hQuery;
  }
};
