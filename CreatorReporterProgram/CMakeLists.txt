cmake_minimum_required(VERSION 3.15)
project(CreatorReporterProgram)

set(CMAKE_CXX_STANDARD 14)

add_executable(CreatorReporterProgram main.cpp Include/Employee.h "IO Classes/FilePrinter.cpp" "IO Classes/FilePrinter.h" "IO Classes/InputClass.cpp" "IO Classes/InputClass.h" "Process Maintaince/ProcessMaintainer.cpp" "Process Maintaince/ProcessMaintainer.h" Creation/Creator.cpp Creation/Creator.h Reporting/Reporter.cpp Reporting/Reporter.h Reporting/SalaryCounter.cpp Reporting/SalaryCounter.h "Process Maintaince/RunnableProgram.cpp" "Process Maintaince/RunnableProgram.h")