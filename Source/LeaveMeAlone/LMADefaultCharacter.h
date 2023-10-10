// LeaveMeAlone Game by Netologiya. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMADefaultCharacter.generated.h"

// будет отвечать за компонент камеры
class UCameraComponent;
/*
	используется для автоматического управления поведением камеры в
	ситуациях, когда она становится закрытой
*/
class USpringArmComponent;
class ULMAHealthComponent;	// здоровье
class UAnimMontage;	// класс анимационного монтажа

UCLASS()
class LEAVEMEALONE_API ALMADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALMADefaultCharacter();
	
	UFUNCTION()
	ULMAHealthComponent* GetHealthComponent() const { return HealthComponent; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Health")
	ULMAHealthComponent* HealthComponent;

	UPROPERTY()
	UDecalComponent* CurrentCursor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	UMaterialInterface* CursorMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cursor")
	FVector CursorSize = FVector(20.0f, 40.0f, 40.0f);
	
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* DeathMontage;	// указатель на анимацию

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float YRotation = -75.0f;	// отвечает за поворот камеры по оси Y.
	float ArmLength = 1400.0f;	// отвечает за длину штатива.
	float FOV = 55.0f;			// отвечает за поле зрения камеры.

	void MoveForward(float Value);	// движение персонажа по оси X
	void MoveRight(float Value);	// движение персонажа по оси Y
	
	void OnDeath();
	void OnHealthChanged(float NewHealth);

	void RotationPlayerOnCursor();
};
