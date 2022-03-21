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
	class UStaticMeshComponent* MyStaticMesh; // 静态网格组件

	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")
	class USpringArmComponent* MySpringArm; // 摄像机摇臂组件

	UPROPERTY(VisibleAnywhere, Category = "My Pawn Components")
	class UCameraComponent* MyCamera; // 摄像机组件

	UPROPERTY(EditAnywhere, Category = "My Pawn Movement")
	float MaxSpeed; // 移动的最大速度，即轴事件值的扩大倍数

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

	// 绑定输入函数
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);
	FVector Velocity; // 移动速度，即当前轴事件结合最大速度的反馈值

	void LookUp(float Value);
	void LookRight(float Value);
	FVector2D MouseInput; // 鼠标输入的轴事件值
};

