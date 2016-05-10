//#ifndef LOG1
//#define LOG1
//#endif
#ifdef LOG1
#include "log1.h"
#else
#include "log.h"
#endif

int logmain(int argc, char* argv[])
{
    try
    {
        FILELog::ReportingLevel() = FILELog::FromString(argv[1] ? argv[1] : "DEBUG1");
        FILE* pFile = fopen("debug.log", "a");
        Output2FILE::Stream() = pFile;

	    const int count = 3;
        FILE_LOG(logDEBUG) << "A loop with " << count << " iterations";
        for (int i = 0; i != count; ++i)
        {
	        FILE_LOG(logDEBUG1) << "the counter i = " << i;
        }
        FILE_LOG(logINFO) << "I am here ";
        return 0;

    }
    catch(const std::exception& e)
    {
        FILE_LOG(logERROR) << e.what();
    }
    return -1;
}
