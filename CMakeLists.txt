cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("High_Level_Operations")

add_executable (High_Level_Operations 
"High_Level_Operations_Main.cpp"
"Thread_Operations/_Thread.cpp"
"Thread_Operations/_Thread.h"
"Variable_Operations/_Variable.cpp"
"Variable_Operations/_Variable.h"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET High_Level_Operations PROPERTY CXX_STANDARD 20)
endif()

include_directories(.)
include_directories(Communication_Operations)
include_directories(Compression_Operations)
include_directories(Encryption_Operations)
include_directories(Log_Operations)
include_directories(Serialization_Operaions)
include_directories(Socket_Operations)
include_directories(Thread_Operations)
include_directories(Time_Operations)
include_directories(Variable_Operations)