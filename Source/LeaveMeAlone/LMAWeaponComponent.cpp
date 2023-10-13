// LeaveMeAlone Game by Netologiya. All RightsReserved.

#include "LMAWeaponComponent.h"
#include "GameFramework/Character.h"
#include "LMABaseWeapon.h"
#include "Animations/LMAReloadFinishedAnimNotify.h"
#include "LMADefaultCharacter.h"

// Sets default values for this component's properties
ULMAWeaponComponent::ULMAWeaponComponent() : fireIsPressed(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void ULMAWeaponComponent::Fire()
{
	fireIsPressed = true;
}

void ULMAWeaponComponent::FireEnd()
{
	fireIsPressed = false;
	Weapon->FireEnd();
}

void ULMAWeaponComponent::Reload()
{
	auto ch = Cast<ALMADefaultCharacter>(GetOwner());
	if (!CanReload() || ch->isSprintingNow())
	{
		return;
	}
	Weapon->ChangeClip();
	AnimReloading = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->PlayAnimMontage(ReloadMontage);
}


// Called when the game starts
void ULMAWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	InitAnimNotify();
}


// Called every frame
void ULMAWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (fireIsPressed)
	{
		if (Weapon && !AnimReloading)
		{
			Weapon->Fire();
		}
		else
		{
			Weapon->FireEnd();
		}
	}
}

void ULMAWeaponComponent::SpawnWeapon()
{
	Weapon = GetWorld()->SpawnActor<ALMABaseWeapon>(WeaponClass);
	if (Weapon)
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "r_Weapon_Socket");
		}
	}
}

void ULMAWeaponComponent::InitAnimNotify()
{
	if (!ReloadMontage) return;

	const auto &NotifiesEvents = ReloadMontage->Notifies;
	for (auto &NotifyEvent : NotifiesEvents)
	{
		auto ReloadFinish = Cast<ULMAReloadFinishedAnimNotify>(NotifyEvent.Notify);
		if (ReloadFinish)
		{
			ReloadFinish->OnNotifyReloadFinished.AddUObject(this, &ULMAWeaponComponent::OnNotifyReloadFinished);
			break;
		}
	}
}

void ULMAWeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh)
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (Character->GetMesh() == SkeletalMesh)
	{
		AnimReloading = false;
	}
}

bool ULMAWeaponComponent::CanReload() const
{
	return !AnimReloading;
}

