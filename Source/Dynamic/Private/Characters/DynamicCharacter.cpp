// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DynamicCharacter.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include  "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapons/Weapon.h"


ADynamicCharacter::ADynamicCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	DynamicInputMappingContext = CreateDefaultSubobject<UInputMappingContext>("DynamicInputMappingContext");
	
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;

	//Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetupAttachment(GetRootComponent());
	
	CameraView = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraView->SetupAttachment(CameraBoom);
	
}


void ADynamicCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))	
		{
			Subsystem->AddMappingContext(DynamicInputMappingContext,1);
		}
	}
	
}

void ADynamicCharacter::Move(const FInputActionValue& Value)
{
	if(ActionState != EActionState::EAS_unocuupied) return;
	const FVector2d MovementVector = Value.Get<FVector2D>();

	FRotator Rotation = Controller->GetControlRotation();
	
	FRotator YawRotation = FRotator(0.0f,Rotation.Yaw,0.0f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection,MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection,MovementVector.X);
}

void ADynamicCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookDirection = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookDirection.X);
	AddControllerPitchInput(LookDirection.Y);
}

void ADynamicCharacter::Jump()
{
	ACharacter::Jump();
}

void ADynamicCharacter::PickUp()
{
	if(AWeapon *OverlappingWeapon = Cast<AWeapon>(OverlappingItem))
	{
		OverlappingWeapon->Equip(GetMesh(),"WeaponSocket");
		CharacterState = ECharacterState::ECS_equipped_OneHandedWeapon;
		OverlappingItem = nullptr;
		EquippedWeapon = OverlappingWeapon;
	}
	else
	{
		if(CanDisArm())
		{
			PlayArmWeaponMontage("Unequip");
			CharacterState = ECharacterState::ECS_unequipped;
			ActionState = EActionState::EAS_HandlingWeapon;
		}
		else if(CanArm())
		{
			PlayArmWeaponMontage("Equip");
			CharacterState = ECharacterState::ECS_equipped_OneHandedWeapon;
			ActionState = EActionState::EAS_HandlingWeapon;
		}
	}

}

void ADynamicCharacter::Attack()
{
		if(CanAttack())
		{
			PlayAttackMontage();
			ActionState = EActionState::EAS_Attacking;
		}
}

bool ADynamicCharacter::CanArm()
{
	return (ActionState == EActionState::EAS_unocuupied && CharacterState == ECharacterState::ECS_unequipped && EquippedWeapon);

}

bool ADynamicCharacter::CanDisArm()
{
	return (ActionState == EActionState::EAS_unocuupied  && CharacterState != ECharacterState::ECS_unequipped);
}

bool ADynamicCharacter::CanAttack()
{
	return CharacterState != ECharacterState::ECS_unequipped && ActionState == EActionState::EAS_unocuupied;
}

void ADynamicCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_unocuupied;
}

void ADynamicCharacter::PlayArmWeaponMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance)
	{
		AnimInstance->Montage_Play(ArmWeaponMontage);
		AnimInstance->Montage_JumpToSection(SectionName,ArmWeaponMontage);
	}
}

void ADynamicCharacter::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if(AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		int32 Selection = FMath::RandRange(0,2);
		FName SectionName = FName();
		
		switch (Selection)
		{
		case 0:
			SectionName = FName("Attack01");
			break;
		case 1:
			SectionName = FName("Attack02");
			break;
		case 2 :
			SectionName = FName("Attack03");
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName,AttackMontage);
	}

}

void ADynamicCharacter::DisArm()
{
	if(EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(),"WeaponEquipSocket");
	}
}

void ADynamicCharacter::Arm()
{
	if(EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(),"WeaponSocket");
	}
}

void ADynamicCharacter::FinishEquipping()
{
	ActionState = EActionState::EAS_unocuupied;
}

void ADynamicCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if(EquippedWeapon && EquippedWeapon->GetWeaponBox())
	{
		EquippedWeapon->IgnoreActors.Empty();
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
	}
}


void ADynamicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADynamicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move,ETriggerEvent::Triggered,this,&ADynamicCharacter::Move);
		EnhancedInputComponent->BindAction(IA_Look,ETriggerEvent::Triggered,this,&ADynamicCharacter::Look);
		EnhancedInputComponent->BindAction(IA_Jump,ETriggerEvent::Started,this,&ADynamicCharacter::Jump);
		EnhancedInputComponent->BindAction(IA_PickUp,ETriggerEvent::Started,this,&ADynamicCharacter::PickUp);
		EnhancedInputComponent->BindAction(IA_Attack,ETriggerEvent::Started,this,&ADynamicCharacter::Attack);
	}

}

