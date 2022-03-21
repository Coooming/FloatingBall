#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class LEARN_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();

	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")
	class UStaticMeshComponent* MyStaticMesh; // ��̬�������

	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")
	class USpringArmComponent* MySpringArm; // �����ҡ�����

	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")
	class UCameraComponent* MyCamera; // ��������

	UPROPERTY(EditAnywhere, Category = "My Pawn Movement")
	float MaxSpeed; // �ƶ�������ٶȣ������¼�ֵ��������

	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent()
	{
		return MyStaticMesh;
	}

	FORCEINLINE USpringArmComponent* GetSpringArmComponent()
	{
		return MySpringArm;
	}

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// �����뺯��
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);
	FVector Velocity; // �ƶ��ٶȣ�����ǰ���¼��������ٶȵķ���ֵ

	void LookUp(float Value);
	void LookRight(float Value);
	FVector2D MouseInput; // �����������¼�ֵ
};

