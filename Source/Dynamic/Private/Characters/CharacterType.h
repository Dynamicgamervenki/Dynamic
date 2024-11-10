#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_unequipped UMETA(DisplayName = "Unequipped"),
	ECS_equipped_OneHandedWeapon UMETA(DisplayName = "equipped_OneHandedWeapon"),
	ECS_equipped_TwoHandedWeapon UMETA(DisplayName = "equipped_TwoHandedWeapon")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_unocuupied UMETA(DisplayName = "Unocuupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_HandlingWeapon UMETA(DisplayName = "HandlingWeapon")
};
