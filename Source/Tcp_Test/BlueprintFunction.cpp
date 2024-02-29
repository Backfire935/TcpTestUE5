// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintFunction.h"

#include "AppManager.h"

int32 UBlueprintFunction::AppUpdate()
{
	app::onUpdate();
	return 0;
}

int32 UBlueprintFunction::disConnect()
{
	if(app::__TcpClient != nullptr)
	{
		app::__TcpClient->disconnectServer(6000, "blue close");
		return 0;
	}
	return -1;
}

int32 UBlueprintFunction::isSecurity()
{
	if(app::__TcpClient == nullptr) return false;
	uint8 state = app::__TcpClient->getData()->state;
	if(state < func::C_ConnectSecure) return false;
	return true;
}

int32 UBlueprintFunction::read_int8()
{
	int8 temp = 0;
	app::__TcpClient->read(temp);
	return temp;
}

int32 UBlueprintFunction::read_int16()
{
	uint16 temp = 0;
	app::__TcpClient->read(temp);
	return temp;
}

int32 UBlueprintFunction::read_int32()
{
	int32 temp = 0;
	app::__TcpClient->read(temp);
	return temp;
}

float UBlueprintFunction::read_float()
{
	float temp = 0;
	app::__TcpClient->read(temp);
	return temp;
}

bool UBlueprintFunction::read_bool()
{
	bool temp = 0;
	app::__TcpClient->read(temp);
	return temp;
}

FVector UBlueprintFunction::read_FVector()
{
	FVector temp;
	app::__TcpClient->read(&temp, sizeof(FVector));
	return temp;
}

FRotator UBlueprintFunction::read_FRotator()
{
	FRotator temp;
	app::__TcpClient->read(&temp, sizeof(FRotator));
	return temp;
}

FString UBlueprintFunction::read_FString_len(int32 len)
{
	uint8* cc = (uint8*)FMemory::Malloc(len);//分配内存
	app::__TcpClient->read(cc, len);//读取数据
	FString value = UTF8_TO_TCHAR(cc);//转换成FString
	FMemory::Free(cc);//释放内存
	return value;
}

FString UBlueprintFunction::read_FString()
{
	int len = 0;
	app::__TcpClient->read(len);//读取长度
	if(len < 1 || len >1024*1024*5)return "";//如果长度小于1或者大于5M，返回空
	
	uint8* cc = (uint8*)FMemory::Malloc(len);//分配内存
	app::__TcpClient->read(cc, len);//读取数据
	FString value = UTF8_TO_TCHAR(cc);//转换成FString
	FMemory::Free(cc);//释放内存
	return value;//返回数据
}

//封包
void UBlueprintFunction::send_begin(int32 cmd)
{
	app::__TcpClient->begin(cmd);
}

void UBlueprintFunction::send_end(int32 cmd)
{
	app::__TcpClient->end();
}

void UBlueprintFunction::send_int8(int32 value)
{
	app::__TcpClient->sss((int8)value);
}

void UBlueprintFunction::send_int16(int32 value)
{
	app::__TcpClient->sss((int16)value);
}

void UBlueprintFunction::send_int32(int32 value)
{
	app::__TcpClient->sss(value);
}

void UBlueprintFunction::send_float(float value)
{
	app::__TcpClient->sss(value);
}

void UBlueprintFunction::send_bool(bool value)
{
	app::__TcpClient->sss(value);
}

void UBlueprintFunction::send_FVector(FVector value)
{
	app::__TcpClient->sss(&value, sizeof(FVector));
}

void UBlueprintFunction::send_FRotator(FRotator value)
{
	app::__TcpClient->sss(&value, sizeof(FRotator));
}

//发送字符串
void UBlueprintFunction::send_FString_len(FString value, int32 len)
{
	TCHAR *pdata = value.GetCharArray().GetData();
	uint8* cc = (uint8*)TCHAR_TO_UTF8(pdata);

	int size = value.GetCharArray().Num();//获取长度
	if(size > len) size = len;//如果长度大于len，设置为len
	app ::__TcpClient->sss(cc, size);//发送数据
	if(size == len) return;//如果相等，直接返回

	int a = size -len;//计算差值
	uint8* cc2 = (uint8*)FMemory::Malloc(a);//分配内存
	app::__TcpClient->sss(cc2, a);//发送数据 这句想不明白
	
	FMemory::Free(cc2);//释放内存
}

//发送字符串
void UBlueprintFunction::send_FString(FString value)
{
	TCHAR *pdata = value.GetCharArray().GetData();
	uint8* cc = (uint8*)TCHAR_TO_UTF8(pdata);
	int size = value.GetCharArray().Num();//获取长度
	app::__TcpClient->sss(size);//发送长度
	app::__TcpClient->sss(cc, size);//发送数据
}
