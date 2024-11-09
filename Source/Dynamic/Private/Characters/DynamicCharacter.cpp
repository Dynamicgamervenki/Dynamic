// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DynamicCharacter.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include  "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
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
		OverlappingWeapon->SetActorEnableCollision(false);
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
	}

}

