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
	RootComponent = MyStaticMesh; // ���ø����
	MyStaticMesh->SetCollisionProfileName(TEXT("Pawn")); // ������ײԤ������

	// ���ؾ�̬������Դ
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	// ���ز�����Դ
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));
	if (StaticMeshAsset.Succeeded() && MaterialAsset.Succeeded()) // �ж���Դ�Ƿ���سɹ�
	{
		MyStaticMesh->SetStaticMesh(StaticMeshAsset.Object); // ���þ�̬����
		MyStaticMesh->SetMaterial(0, MaterialAsset.Object); // ���ò���
		MyStaticMesh->SetWorldScale3D(FVector(0.5f));
	}

	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArm"));
	MySpringArm->SetupAttachment(GetStaticMeshComponent());
	MySpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f)); // ���������ת
	MySpringArm->TargetArmLength = 400.0f; // ����ҡ�۳���
	MySpringArm->bEnableCameraLag = true; // ���������ƽ������
	MySpringArm->CameraLagSpeed = 3.0f; // ���������ƽ�������ٶ�

	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamera"));
	MyCamera->SetupAttachment(GetSpringArmComponent());

	AutoPossessPlayer = EAutoReceiveInput::Player0; // ����Ĭ�ϳ������
	bUseControllerRotationYaw = true; // ����������ƫ������ת�̳�

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

	AddActorLocalOffset(Velocity * DeltaTime, true); // �ƶ�

	AddControllerYawInput(MouseInput.X); // ������������ת

	// �����ҡ��������ת
	FRotator NewSpringArmRotation = MySpringArm->GetRelativeRotation(); // ��ȡԭҡ����תֵ
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch + MouseInput.Y, -80.0f, 0.0f);
	MySpringArm->SetRelativeRotation(NewSpringArmRotation); // ������ҡ����תֵ
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

