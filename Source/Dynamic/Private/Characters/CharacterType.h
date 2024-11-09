#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_unequipped UMETA(DisplayName = "Unequipped"),
	ECS_equipped_OneHandedWeapon UMETA(DisplayName = "equipped_OneHandedWeapon"),
	ECS_equipped_TwoHandedWeapon UMETA(DisplayName = "equipped_TwoHandedWeapon")
};