// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintFunction.generated.h"

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

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static int32 isSecurity();

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
   static int32 read_int8();

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static int32 read_int16();

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
       static int32 read_int32();

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static float read_float();

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static bool read_bool();

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static FVector read_FVector();

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static FRotator read_FRotator();

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static FString read_FString_len(int32 len);

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static FString read_FString();

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_begin(int32 cmd);

	UFUNCTION(BlueprintCallable, Category = "MyEngine")
	static void send_end(int32 cmd);

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
