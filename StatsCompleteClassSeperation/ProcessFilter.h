#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "ResourceUnit.h"
extern justTrying jInstance;
template<class T>
void PrintVector(std::vector<T> objects, std::string message)
{
  std::cout << message << ". Size : " << objects.size() << std::endl;
  for (auto &object : objects)
  {
    std::cout << object << std::endl;
  }
  std::cout << std::endl;
}
class ProcessFilter
{
  std::string process, processPath;
   std::vector<DWORD> pids;
  void FilterInstances(const std::vector<DWORD>& pids, std::vector<std::string>& thatinstances)
  {
    std::vector<std::string> thisinstances;
    for (auto &instance : thatinstances)
    {
      ResourceUnit stat;
//      ResourceUnit::Init();
      jInstance.Init();
      stat.SetCounter("ID Process");
      stat.SetInstance(instance);
      stat.Start();
//       ResourceUnit::GetCount();
      jInstance.GetCount();
      int pid = static_cast<int>(stat.ResolveCount());
      if (std::find(pids.begin(), pids.end(), pid) != pids.end())
      {
        thisinstances.push_back(instance);
      }
    }
    thatinstances = thisinstances;
  }
  void GetInstances(std::string thatprocess, std::vector<std::string>& instances)
  {
    std::size_t found = thatprocess.find_last_of(".");
    if (found != std::string::npos)
    {
      thatprocess = thatprocess.substr(0, found);
    }
    std::string wildcardPath = "\\Process(" + thatprocess + "*)\\ID Process";
    PDH_STATUS Status;
    char *EndOfPaths, *Paths = NULL;
    DWORD BufferSize = 0;

    Status = PdhExpandWildCardPath(NULL, wildcardPath.c_str(), Paths, &BufferSize, 0);
    while (Status == PDH_MORE_DATA)
    {
      Paths = (char*)malloc(BufferSize * sizeof(char));
      Status = PdhExpandWildCardPath(NULL, wildcardPath.c_str(), Paths, &BufferSize, 0);
    }

    if (Status != ERROR_SUCCESS)
    {
      printf("PdhExpandCounterPath failed with status 0x%x\n", Status);
      if (Paths) { free(Paths); }
    }

    if (Paths == NULL)
    {
      printf("The counter path %s cannot be expanded.\n", wildcardPath);
      if (Paths) { free(Paths); }
    }
    EndOfPaths = Paths + BufferSize;
    for (char* p = Paths; ((p != EndOfPaths) && (*p != L'\0')); p += strlen(p) + 1)
    {
      char thisinstance[MAX_PATH];
      DWORD bufSize = MAX_PATH;
      DWORD pSize = 0;
      PDH_STATUS status = PdhParseCounterPath(p, nullptr, &pSize, 0);

      if (status == static_cast<PDH_STATUS>(PDH_MORE_DATA))
      {
        std::vector<BYTE> pbuf(pSize);
        status = PdhParseCounterPath(p, reinterpret_cast<PDH_COUNTER_PATH_ELEMENTS *>(pbuf.data()), &pSize, 0);
        if (status == ERROR_SUCCESS)
        {
          PDH_COUNTER_PATH_ELEMENTS *pe = reinterpret_cast<PDH_COUNTER_PATH_ELEMENTS *>(pbuf.data());
          std::string newinstance(pe->szInstanceName);
          if (pe->dwInstanceIndex)
          {
            newinstance = newinstance + "#" + std::to_string(pe->dwInstanceIndex);
          }
          instances.push_back(newinstance);
        }
      }
    }
    if (Paths) { free(Paths); }
  }
  void FilterProcessIDs(std::string thatpath, std::string thatprocess, std::vector<DWORD>& thatpids)
  {
    std::vector<DWORD> thispids;
    for (DWORD pid : thatpids)
    {
      HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

      if (NULL != hProcess)
      {
        if (pid == 7476)
        {
          puts("aasdas");
        }
        HMODULE hMod;
        DWORD cbNeeded;
        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
        {
          char processName[MAX_PATH] = "";
          GetModuleBaseName(hProcess, hMod, processName, MAX_PATH);
          std::string thisprocess = std::string(processName);
          std::transform(thisprocess.begin(), thisprocess.end(), thisprocess.begin(), ::tolower);
          if (thisprocess == thatprocess)
          {
            char processPath[MAX_PATH] = "";
            GetModuleFileNameEx(hProcess, NULL, processPath, MAX_PATH);
            std::string thisPath = std::string(processPath);
            std::transform(thisPath.begin(), thisPath.end(), thisPath.begin(), ::tolower);
            if (thisPath.find(thatpath) != std::string::npos)
            {
              thispids.push_back(pid);
            }
          }
        }
        if (pid == 6020)
        {
          std::cout << GetLastError();
          puts("aasdas");
        }
      }
      CloseHandle(hProcess);
    }
    thatpids = thispids;
  }
  void GetProcessIDs(std::vector<DWORD>& pids)
  {
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    if (EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
      cProcesses = cbNeeded / sizeof(DWORD);
      for (unsigned int i = 0; i < cProcesses; i++)
      {
        if (aProcesses[i] != 0)
        {
          pids.push_back(aProcesses[i]);
        }
      }
    }
  }
public:
  std::vector<std::string> instances;
  void Start(std::string path, std::string processName)
  {
    processPath = path;
    process = processName;
    GetProcessIDs(pids);
    //PrintVector(pids, "Unfiltered PIDS");
    FilterProcessIDs(processPath, process, pids);
    PrintVector(pids, "Filtered PIDS");
    GetInstances(process, instances);
    PrintVector(instances, "Unfiltered Instances");
    FilterInstances(pids, instances);
    PrintVector(instances, "Filtered Instances");
  }
  void GetProcessPath()
  {
    std::cout << process << processPath;
  }
};


