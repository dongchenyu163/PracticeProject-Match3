/** GitHelper **/

#include "GitHelper.h"

#include "GitPushPrivatePCH.h"

#include <string>
#include <iostream>
#include <cstdio>
#include <memory>

FString FGitHelper::ExecuteShellCommand(FString command)
{
	const char *cmd = TCHAR_TO_ANSI(*command);

#if PLATFORM_WINDOWS
	std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
#else if PLATFORM_LINUX
	std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
#endif
	
	if (!pipe)
	{
		return FString(TEXT("An error happend!"));
	}
	char buffer[128];
	std::string result = "";
	FString result2 = "";
	while (!feof(pipe.get()))
	{
		if (fgets(buffer, 128, pipe.get()) != NULL)
		{
			result += buffer;
		}
	}

	FString res(result.c_str());
	return res;
}

TArray<FString> FGitHelper::GetBranches()
{
	TArray<FString> outArray;

	FString workingDir = FPaths::GetPath(FPaths::GetProjectFilePath());

	FString command = FString::Printf(TEXT("git -C \"%s\" branch --list 2>&1"), *workingDir);

	if (FGitHelper::IsGitRepo(workingDir))
	{
		FString result = ExecuteShellCommand(command);

		if (!result.IsEmpty())
		{
			result.ParseIntoArrayLines(outArray, true);
			for (int32 i = 0; i < outArray.Num(); i++)
			{
				outArray[i].RemoveAt(0, 2);
			}

			UE_LOG(LogGitPush, Log, TEXT("GitPush: Got %d branches."), outArray.Num());
		}
	}

	return outArray;
}

TArray<FString> FGitHelper::GetRemoteHosts()
{
	FString workingDir = FPaths::GetPath(FPaths::GetProjectFilePath());

	FString command = FString::Printf(TEXT("git -C \"%s\" remote 2>&1"), *workingDir);
	FString result = ExecuteShellCommand(command);

	TArray<FString> outArray;
	result.ParseIntoArrayLines(outArray, true);

	UE_LOG(LogGitPush, Log, TEXT("GitPush: Got %d remote hosts"), outArray.Num());

	return outArray;
}

bool FGitHelper::IsGitRepo(FString path)
{
	FString gitPath = FPaths::Combine(*path, TEXT(".git"));

	return FPaths::DirectoryExists(gitPath);
}

GitPushReturn FGitHelper::PushCommit(FString remoteHostName, FString destinationBranch)
{
	// git push source:dest --porcelain
	FString workingDir = FPaths::GetPath(FPaths::GetProjectFilePath());

	FString command = FString::Printf(TEXT("git -C \"%s\" push %s %s --porcelain 2>&1"), *workingDir, *remoteHostName, *destinationBranch);
	FString result = FGitHelper::ExecuteShellCommand(command);

	GitPushReturn output;
	//Posible return stuff: "fatal", "error", "Everything up-to-date"
	output.bSuccessful = !(result.Contains(TEXT("fatal")) || result.Contains(TEXT("error")));
	output.consoleReturn = result;

	return output;
}

