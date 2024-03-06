// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintFunction.generated.h"

#pragma  pack(push,packing)
#pragma  pack(1)

USTRUCT(BlueprintType)
struct FPlayerBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyEngine")
	int32  memid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyEngine")
	int32 socketfd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyEngine")
	int32 state;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyEngine")
	int32 curhp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyEngine")
	int32 maxhp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyEngine")
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyEngine")
	FVector pos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyEngine")
	FRotator rot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyEngine")
	FString nick;

};
#pragma pack(pop,packing)

/**
 * 
 */
UCLASS()
class TCP_TEST_API UBlueprintFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static int32 AppUpdate();

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static int32 disConnect();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "MyEngine")
	static bool isSecurity();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "MyEngine")
   static int32 read_int8();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "MyEngine")
	static int32 read_int16();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "MyEngine")
       static int32 read_int32();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "MyEngine")
	static float read_float();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "MyEngine")
	static bool read_bool();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "MyEngine")
	static FVector read_FVector();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "MyEngine")
	static FRotator read_FRotator();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "MyEngine")
	static FString read_FString_len(int32 len);

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "MyEngine")
	static FString read_FString();

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "MyEngine")
	static FPlayerBase read_FPlayerBase();//

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_begin(int32 cmd);

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_end();

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_int8(int32 value);

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_int16(int32 value);

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_int32(int32 value);

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_float(float value);

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_bool(bool value);

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_FVector(FVector value);

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_FRotator(FRotator value);
	
	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_FString_len(FString value, int32 len);

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_FString(FString value);
	
};
