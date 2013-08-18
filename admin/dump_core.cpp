/*
 * echo "| /<path>/dump_core %e %p %s %t" > /proc/sys/kernel/core_pattern
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <sys/stat.h>

using namespace std;

string LocaltimeFromSecs(time_t secsSinceEpoch)
{
  tm *pLocalTime = localtime(&secsSinceEpoch);
  char szLocalTime[128] = {0};
  int ret = strftime(szLocalTime, 
            sizeof(szLocalTime), "%Y_%2m_%2d_%2H_%2M_%2S", pLocalTime);
            
  if(0 == ret){
    return "unknow_time";
  }else{
    return szLocalTime;
  }
}

bool DumpCoreFile(const char *corePath)
{
  if (!corePath)
    return false;

  FILE *fp = fopen(corePath, "wb+");
  bool bReadFailed = false;
  while(1){
    char buf[1024] = {0};
    size_t itemCount = fread(buf, 1, sizeof(buf), stdin);
    fwrite(buf, 1, itemCount, fp);
    
    if(ferror(stdin)){
      bReadFailed = true;
      break;
    }  
    if(feof(stdin))
      break;
  }
  if(bReadFailed){
    ftruncate(fileno(fp), 0);
    fprintf(fp, "%d:%s\n", errno, strerror(errno));
  }
  
  fclose(fp);

  return bReadFailed == false;

}
// the format of args is "dump_core %e %p %s %t"
int main(int argc, char **args)
{
  if(5 != argc){
    return -1;
  }
  
  string sImageName = args[1];
  string sPid = args[2];
  string sSignalNum = args[3];
  string sLocalTime = LocaltimeFromSecs(atoi(args[4]));
  
  string sCoreName = "core_";
  sCoreName += sImageName + "_" + sPid + "_" + sSignalNum + "." + sLocalTime;
  char cwd[PATH_MAX] = {0};
  snprintf(cwd, PATH_MAX, "/proc/%s/cwd", sPid.c_str()); //argv[1] is pid
  chdir(cwd);
  
  DumpCoreFile(sCoreName.c_str());
  
  chmod(sCoreName.c_str(),  S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  return 0;
}
