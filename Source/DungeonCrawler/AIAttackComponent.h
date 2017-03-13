// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AIAttackComponent.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EAttackType : uint8
{
	AT_Melee 	UMETA(DisplayName = "Melee"),
	AT_Range 	UMETA(DisplayName = "Range"),
	AT_Magic	UMETA(DisplayName = "Magic")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONCRAWLER_API UAIAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIAttackComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	UPROPERTY(EditAnywhere)
		EAttackType AttackType;
};
