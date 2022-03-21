#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class LEARN_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyActor();

	UPROPERTY(VisibleAnywhere, Category = "My Actor Components")
	UStaticMeshComponent* MyStaticMesh; // С��ľ�̬�������ָ��

	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Vector")
	FVector InitLocation; // С�����ɵĳ�ʼλ��

	UPROPERTY(VisibleInstanceOnly, Category = "My Actor Properties | Vector")
	FVector PlacedLocation; // С��һ��ʼ�����õ�λ��

	UPROPERTY(EditDefaultsOnly, Category = "My Actor Properties | Vector")
	bool bGotoInitLoaction; // �����Ƿ�������С��ʱ�����ƶ����趨�ĳ�ʼλ��

	UPROPERTY(VisibleDefaultsOnly, Category = "My Actor Properties | Vector")
	FVector WorldOrigin; // ����ԭ��λ��

	UPROPERTY(EditAnywhere, Category = "My Actor Properties | Vector", meta = (ClampMin = -500.0f, ClampMax = 500.0f, UIMin = -500.0f, UIMax = 500.0f))
	FVector TickLocationOffset; // С��ÿ֡��λ��

	UPROPERTY(EditAnywhere, Category = "My Actor Properties | Vector")
	bool bShouldMove; // ����С���Ƿ�ÿ֡�ƶ�

	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")
	FVector InitForce; // ��С��ʩ�ӵĳ�ʼ��

	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")
	FVector InitTorque; // ��С��ʩ�ӵĳ�ʼ����

	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")
	bool bAccelChange; // �����Ƿ�����������Ϊ���ٶȸı䣬���Ƿ��������

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};

