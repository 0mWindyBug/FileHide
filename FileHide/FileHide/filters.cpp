#include <main.h>

// role : filter out our files from query buffers before returned to requestor program 
FLT_POSTOP_CALLBACK_STATUS
FilehidePostDirectoryControl(
	_Inout_ PFLT_CALLBACK_DATA Data,
	_In_ PCFLT_RELATED_OBJECTS FltObjects,
	_In_opt_ PVOID CompletionContext,
	_In_ FLT_POST_OPERATION_FLAGS Flags
)

{
	UNREFERENCED_PARAMETER(CompletionContext);
	UNREFERENCED_PARAMETER(FltObjects);
	PFLT_PARAMETERS Params = &Data->Iopb->Parameters;
	NTSTATUS status;
	
	if (Flags & FLTFL_POST_OPERATION_DRAINING)
		return FLT_POSTOP_FINISHED_PROCESSING;


	// if the operation failed just exit 
	if (!NT_SUCCESS(Data->IoStatus.Status))
		return FLT_POSTOP_FINISHED_PROCESSING;

	// get file name info
	FilterFileNameInformation fileNameInfo(Data);
	if (!fileNameInfo.Get()) {
		return FLT_POSTOP_FINISHED_PROCESSING;
	}

	if (!NT_SUCCESS(fileNameInfo.Parse()))
		return FLT_POSTOP_FINISHED_PROCESSING;

	status = STATUS_SUCCESS;
	UNICODE_STRING TargetDirectory = RTL_CONSTANT_STRING(TARGET_DIRECTORY);
	if (RtlCompareUnicodeString(&TargetDirectory, &fileNameInfo.Get()->FinalComponent, TRUE))
		return FLT_POSTOP_FINISHED_PROCESSING;

	DbgPrint("[*] target directory %wZ has been queried\n", fileNameInfo.Get()->FinalComponent);

	switch (Params->DirectoryControl.QueryDirectory.FileInformationClass)
	{
	case FileFullDirectoryInformation:
		status = FilterFileFullDirectoryInformation((PFILE_FULL_DIR_INFORMATION)Params->DirectoryControl.QueryDirectory.DirectoryBuffer,fileNameInfo.Get());
		break;
	case FileBothDirectoryInformation:
		status = FilterFileBothDirectoryInformation((PFILE_BOTH_DIR_INFORMATION)Params->DirectoryControl.QueryDirectory.DirectoryBuffer, fileNameInfo.Get());
		break;
	case FileDirectoryInformation:
		status = FilterFileDirectoryInformation((PFILE_DIRECTORY_INFORMATION)Params->DirectoryControl.QueryDirectory.DirectoryBuffer, fileNameInfo.Get());
		break;
	case FileIdFullDirectoryInformation:
		status = FilterFileIdFullDirectoryInformation((PFILE_ID_FULL_DIR_INFORMATION)Params->DirectoryControl.QueryDirectory.DirectoryBuffer, fileNameInfo.Get());
		break;
	case FileIdBothDirectoryInformation:
		status = FilterFileIdBothDirectoryInformation((PFILE_ID_BOTH_DIR_INFORMATION)Params->DirectoryControl.QueryDirectory.DirectoryBuffer, fileNameInfo.Get());
		break;
	case FileNamesInformation:
		status = FilterFileNamesInformation((PFILE_NAMES_INFORMATION)Params->DirectoryControl.QueryDirectory.DirectoryBuffer, fileNameInfo.Get());
		break;
	}

	Data->IoStatus.Status = status;
	

	return FLT_POSTOP_FINISHED_PROCESSING;

}



// role : filter out uninteresting controls from post operation 
FLT_PREOP_CALLBACK_STATUS
FilehidePreDirectoryControl(
	_Inout_ PFLT_CALLBACK_DATA Data,
	_In_ PCFLT_RELATED_OBJECTS FltObjects,
	_Flt_CompletionContext_Outptr_ PVOID* CompletionContext
)

{
	UNREFERENCED_PARAMETER(Data);
	UNREFERENCED_PARAMETER(FltObjects);
	UNREFERENCED_PARAMETER(CompletionContext);


	if (Data->Iopb->MinorFunction != IRP_MN_QUERY_DIRECTORY)
		return FLT_PREOP_SUCCESS_NO_CALLBACK;

	switch (Data->Iopb->Parameters.DirectoryControl.QueryDirectory.FileInformationClass)
	{
	case FileIdFullDirectoryInformation:
	case FileIdBothDirectoryInformation:
	case FileBothDirectoryInformation:
	case FileDirectoryInformation:
	case FileFullDirectoryInformation:
	case FileNamesInformation:
		break;
	default:
		return FLT_PREOP_SUCCESS_NO_CALLBACK;
	}

	return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}






