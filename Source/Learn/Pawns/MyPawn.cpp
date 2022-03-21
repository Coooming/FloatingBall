#include "MyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"

AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	MyStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyStaticMesh"));
	RootComponent = MyStaticMesh; // 设置根组件
	MyStaticMesh->SetCollisionProfileName(TEXT("Pawn")); // 设置碰撞预设类型

	// 加载静态网格资源
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	// 加载材质资源
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));
	if (StaticMeshAsset.Succeeded() && MaterialAsset.Succeeded()) // 判断资源是否加载成功
	{
		MyStaticMesh->SetStaticMesh(StaticMeshAsset.Object); // 设置静态网格
		MyStaticMesh->SetMaterial(0, MaterialAsset.Object); // 设置材质
		MyStaticMesh->SetWorldScale3D(FVector(0.5f));
	}

	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
	MySpringArm->SetupAttachment(GetStaticMeshComponent());
	MySpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); // 设置相对旋转
	MySpringArm->TargetArmLength = 400.0f; // 设置摇臂长度
	MySpringArm->bEnableCameraLag = true; // 开启摄像机平滑跟随
	MySpringArm->CameraLagSpeed = 3.0f; // 设置摄像机平滑跟随速度

	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	MyCamera->SetupAttachment(GetSpringArmComponent());

	AutoPossessPlayer = EAutoReceiveInput::Player0; // 设置默认持有玩家
	bUseControllerRotationYaw = true; // 开启控制器偏航角旋转继承

	MaxSpeed = 100.0f;
	Velocity = FVector::ZeroVector;
}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(Velocity * DeltaTime, true); // 移动

	AddControllerYawInput(MouseInput.X); // 控制器左右旋转

	// 摄像机摇臂上下旋转
	FRotator NewSpringArmRotation = MySpringArm->GetRelativeRotation(); // 获取原摇臂旋转值
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch + MouseInput.Y, -80.0f, 0.0f);
	MySpringArm->SetRelativeRotation(NewSpringArmRotation); // 设置新摇臂旋转值
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &AMyPawn::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyPawn::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMyPawn::LookRight);
}

void AMyPawn::MoveForward(float Value)
{
	Velocity.X = FMath::Clamp(Value, -1.0f, 1.0f) * MaxSpeed;
}

void AMyPawn::MoveRight(float Value)
{
	Velocity.Y = FMath::Clamp(Value, -1.0f, 1.0f) * MaxSpeed;
}

void AMyPawn::MoveUp(float Value)
{
	Velocity.Z = FMath::Clamp(Value, -1.0f, 1.0f) * MaxSpeed;
}

void AMyPawn::LookUp(float Value)
{
	MouseInput.Y = FMath::Clamp(Value, -1.0f, 1.0f);
}

void AMyPawn::LookRight(float Value)
{
	MouseInput.X = FMath::Clamp(Value, -1.0f, 1.0f);
}

