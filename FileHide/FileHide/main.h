#pragma once
#include <fltKernel.h>
#include <dontuse.h>
#include <ntddk.h>
#include <filters.h>
#include <mutex.h>
#include <hide.h>
#include <filenameinfo.h>
#include <autolock.h>


#define TAG 'FHFL'
#define TARGET_DIRECTORY L"ToHide"
#define TARGET_FILE      L"Hidden.sys"


extern PFLT_FILTER gFilterHandle;

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, FilehideUnload)
#pragma alloc_text(PAGE, FilehideInstanceSetup)

#endif