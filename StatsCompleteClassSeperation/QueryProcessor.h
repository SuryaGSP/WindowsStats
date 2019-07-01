#pragma once
#include <Pdh.h>
#include "ELALogger.h"
extern ELALogger* logger;

class QueryProcessor
{
  void GetConterValue()
  {
    DWORD status = PdhCollectQueryData(hQuery);
    if (status != ERROR_SUCCESS)
    {
      logger->info("PdhCollectQueryData %v", status);
      return;
    }
    return;
  }
public:
  PDH_HQUERY hQuery;
  int n;
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
};