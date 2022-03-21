#include "MyActor.h"
#include "Components/StaticMeshComponent.h"

AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true; // 设置是否每帧调用Tick，不需要时关闭可提升性能

	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh")); // 创建静态网格组件
	
	InitLocation = FVector(0.0f);
	PlacedLocation = FVector(0.0f);
	bGotoInitLoaction = false;
	WorldOrigin = FVector(0.0f);
	TickLocationOffset = FVector(0.0f);
	bShouldMove = false;

	InitForce = FVector(0.0f);
	InitTorque = FVector(0.0f);
	bAccelChange = false;
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	PlacedLocation = GetActorLocation();
	
	if (bGotoInitLoaction)
	{
		SetActorLocation(InitLocation);
	}

	// MyStaticMesh->AddForce(InitForce, "NAME_None", bAccelChange);
	// MyStaticMesh->AddTorque(InitTorque, "NAME_None", bAccelChange);
}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldMove)
	{
		FHitResult HitResult;
		AddActorLocalOffset(TickLocationOffset * DeltaTime, true, &HitResult);
		// UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Z: %f"), HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z);
	}
}

