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
	UStaticMeshComponent* MyStaticMesh; // 小球的静态网格组件指针

	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Vector")
	FVector InitLocation; // 小球生成的初始位置

	UPROPERTY(VisibleInstanceOnly, Category = "My Actor Properties | Vector")
	FVector PlacedLocation; // 小球一开始被放置的位置

	UPROPERTY(EditDefaultsOnly, Category = "My Actor Properties | Vector")
	bool bGotoInitLoaction; // 设置是否在生成小球时将其移动到设定的初始位置

	UPROPERTY(VisibleDefaultsOnly, Category = "My Actor Properties | Vector")
	FVector WorldOrigin; // 世界原点位置

	UPROPERTY(EditAnywhere, Category = "My Actor Properties | Vector", meta = (ClampMin = -500.0f, ClampMax = 500.0f, UIMin = -500.0f, UIMax = 500.0f))
	FVector TickLocationOffset; // 小球每帧的位移

	UPROPERTY(EditAnywhere, Category = "My Actor Properties | Vector")
	bool bShouldMove; // 设置小球是否每帧移动

	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")
	FVector InitForce; // 给小球施加的初始力

	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")
	FVector InitTorque; // 给小球施加的初始力矩

	UPROPERTY(EditInstanceOnly, Category = "My Actor Properties | Physics")
	bool bAccelChange; // 设置是否将力和力矩视为加速度改变，即是否忽略质量

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};

