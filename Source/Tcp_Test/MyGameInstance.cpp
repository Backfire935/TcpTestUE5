// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include"Engine/World.h"
#include"AppManager.h"

UMyGameInstance* __AppGameInstance = nullptr;

int UMyGameInstance::AppInitGameInstance()
{
	auto MyWorld = GetWorld();
	__AppGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

	app::run();
	return 0;
}

int32 UMyGameInstance::GetTimeSeconds()
{
	int32 ftime = GetWorld()->GetTimeSeconds() * 1000;//获取当前时间
	return ftime;
}

void UMyGameInstance::Shutdown()
{
	if(app::__TcpClient != NULL)
	{
		app::__TcpClient->setThread(true);
		app::__TcpClient->disconnectServer(8000, "shutdown");
	}

	Super::Shutdown();
}

