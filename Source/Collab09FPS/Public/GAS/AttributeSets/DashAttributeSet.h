// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "DashAttributeSet.generated.h"

/**
 * @class UDashAttributeSet
 * @brief The UDashAtrributeSet class is a subclass of UAttributeSet, used to define and manage gameplay attributes
 *        specific to the Dash ability in a game.
 *
 * UDashAtrributeSet extends the functionality of UAttributeSet provided by Unreal Engine. It serves as a container
 * for defining and managing gameplay attributes related to the Dash mechanic within the game. Custom attributes
 * and functionality specific to the Dash ability should be implemented in this class.
 *
 * This class is intended to be integrated with Unreal Engine's Gameplay Ability System (GAS) for managing and
 * modifying attributes based on gameplay logic.
 *
 * The attributes defined in this class can be used in gameplay to calculate effects, define thresholds, and
 * create character-specific modifications related to the Dash ability.
 *
 * Note:
 * - All attributes and methods impacting the Dash mechanic should be added as part of this class.
 */
UCLASS()
class COLLAB09FPS_API UDashAttributeSet : public UAttributeSet
{
public:
	// Attribute accessors
	#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
	
	// Constructor
	UDashAttributeSet();
	
	//*//
	// Ground dash speed
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Dash | ")
	FGameplayAttributeData GroundDashSpeed;
	
	// Ground Dash Speed Attribute Accessor
	ATTRIBUTE_ACCESSORS(UDashAttributeSet, GroundDashSpeed)

	//*//
	// Air dash speed
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Dash | ")
	FGameplayAttributeData AirDashSpeed;

	// Air Dash Speed Attribute Accessor
	ATTRIBUTE_ACCESSORS(UDashAttributeSet, AirDashSpeed)

	// Air dash cost
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Dash | ")
	FGameplayAttributeData AirDashStaminaCost;

	// Air Dash Stamina Cost Attribute Accessor
	ATTRIBUTE_ACCESSORS(UDashAttributeSet, AirDashStaminaCost)

	// Air dash cooldown
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Dash | ")
	FGameplayAttributeData AirDashCooldown;

	// Air dash cooldown Attribute Accessor
	ATTRIBUTE_ACCESSORS(UDashAttributeSet, AirDashCooldown)

	// Ground dash cost
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Dash | ")
	FGameplayAttributeData GroundDashStaminaCost;

	// Ground Dash stamina cost Attribute Accessor
	ATTRIBUTE_ACCESSORS(UDashAttributeSet, GroundDashStaminaCost)

	// Ground dash cooldown
	UPROPERTY(BlueprintReadOnly,
		Category="Attributes | Dash | ")
	FGameplayAttributeData GroundDashCooldown;

	// Ground dash cooldown Attribute Accessor
	ATTRIBUTE_ACCESSORS(UDashAttributeSet, GroundDashCooldown)


protected:
	void virtual PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
private:
	GENERATED_BODY()
};
