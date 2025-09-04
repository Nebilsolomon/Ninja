

#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequipped   UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHanded UMETA(DisplayName = "Equipped One-Handed"),
	ECS_EquippedTwoHanded UMETA(DisplayName = "Equipped Two-Handed")
};



