// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

// ����� �������� �� ��������� ������
class UCameraComponent;
/*
	������������ ��� ��������������� ���������� ���������� ������ �
	���������, ����� ��� ���������� ��������
*/
class USpringArmComponent;

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALMADefaultCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float YRotation = -75.0f;	// �������� �� ������� ������ �� ��� Y.
	float ArmLength = 1400.0f;	// �������� �� ����� �������.
	float FOV = 55.0f;			// �������� �� ���� ������ ������.

	void MoveForward(float Value);	// �������� ��������� �� ��� X
	void MoveRight(float Value);	// �������� ��������� �� ��� Y

	float zoomMin = 500.0f;
	float zoomMax = 1500.0f;
	void CameraZoom(const float value);
};