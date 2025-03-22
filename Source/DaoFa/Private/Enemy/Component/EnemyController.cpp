#include "Enemy/Component/EnemyController.h"
#include "Enemy/Component/EnemyTrace.h"
#include "Enemy/Component/EnemyRotator.h"
#include "Enemy/Component/EnemyBehavior.h"
// Sets default values for this component's properties
UEnemyController::UEnemyController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	EnemyTrace = CreateDefaultSubobject<UEnemyTrace>(TEXT("EnemyTrace"));
	EnemyRotator = CreateDefaultSubobject<UEnemyRotator>(TEXT("EnemyRotator"));

	EnemyRotator->InitEnemyRotator(EnemyTrace);	

}

// Called when the game starts
void UEnemyController::BeginPlay()
{
	Super::BeginPlay();


	InitEnemyController(UEnemyBehavior::StaticClass());
	// ...
}

// Called every frame
void UEnemyController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemyController::InitEnemyController(TSubclassOf<UEnemyBehavior> InEnemyBehavior)
{
	EnemyBehavior = NewObject<UEnemyBehavior>(this, InEnemyBehavior);
	EnemyBehavior->RegisterComponent();
	EnemyBehavior->InitEnemyBehavior(EnemyTrace);
}

