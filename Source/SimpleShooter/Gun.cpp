// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(GunParticle, GunMesh, TEXT("MuzzleFlashSocket"));
	//UGameplayStatics::SpawnEmitterAtLocation(this, TrailParticle, GunMesh->GetSocketLocation(TEXT("MuzzleFlashSocket")), GetActorRotation().GetInverse());
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("MuzzleFlashSocket"));

	FVector Location;
	FRotator Rotation;
	Cast<APawn>(GetOwner())->GetController()->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	bool res = GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECC_GameTraceChannel1, Params);
	UE_LOG(LogTemp, Warning, TEXT("result: %d"), res);
	if (res)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, HitResult.Location, (-Rotation.Vector()).Rotation());
		UGameplayStatics::SpawnSoundAtLocation(this, HitSound, HitResult.Location);

		FPointDamageEvent DamageEvent(Damage, HitResult, -Rotation.Vector(), nullptr);
		if (AActor* Actor = HitResult.GetActor())
		{
			Actor->TakeDamage(Damage, DamageEvent, Cast<APawn>(GetOwner())->GetController(), this);
		}
	}
	
}

