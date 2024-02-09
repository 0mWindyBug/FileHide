#include <main.h>


#pragma prefast(disable:__WARNING_ENCODE_MEMBER_FUNCTION_POINTER, "Not valid for kernel mode drivers")


PFLT_FILTER gFilterHandle;


CONST FLT_OPERATION_REGISTRATION Callbacks[] = {
    {IRP_MJ_DIRECTORY_CONTROL,NULL,FilehidePreDirectoryControl,FilehidePostDirectoryControl},
    { IRP_MJ_OPERATION_END }
};



CONST FLT_REGISTRATION FilterRegistration = {

    sizeof(FLT_REGISTRATION),         //  Size
    FLT_REGISTRATION_VERSION,           //  Version
    0,                                  //  Flags

    nullptr,                               //  Context
    Callbacks,                          //  Operation callbacks

    FilehideUnload,                           //  MiniFilterUnload

    FilehideInstanceSetup,                    //  InstanceSetup
    nullptr,            //  InstanceQueryTeardown
    nullptr,            //  InstanceTeardownStart
    nullptr,         //  InstanceTeardownComplete

    nullptr,                               //  GenerateFileName
    nullptr,                               //  GenerateDestinationFileName
    nullptr                                //  NormalizeNameComponent

};



NTSTATUS
FilehideInstanceSetup(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
)

{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);
    UNREFERENCED_PARAMETER(VolumeDeviceType);
    UNREFERENCED_PARAMETER(VolumeFilesystemType);

    PAGED_CODE();



    return STATUS_SUCCESS;
}



/*************************************************************************
    MiniFilter initialization and unload routines.
*************************************************************************/

NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)



{
    NTSTATUS status;
    UNREFERENCED_PARAMETER(RegistryPath);

    status = FltRegisterFilter(DriverObject,
        &FilterRegistration,
        &gFilterHandle);



    FLT_ASSERT(NT_SUCCESS(status));

    if (NT_SUCCESS(status)) {

        status = FltStartFiltering(gFilterHandle);

        if (!NT_SUCCESS(status)) {

            FltUnregisterFilter(gFilterHandle);
        }
    }
    DbgPrint("[*] Filehide loaded\n");
    return status;
}

NTSTATUS
FilehideUnload(
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
)

{
    UNREFERENCED_PARAMETER(Flags);
    FltUnregisterFilter(gFilterHandle);
    DbgPrint("[*] Filehide unloaded\n");
    return STATUS_SUCCESS;
}
