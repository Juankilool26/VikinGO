#include "BehaviourTree.hpp"
#include <RecordMemory/MemoryRecord.hpp>
#include <components/Position.hpp>
#include <components/AI.hpp>
#include <components/Weapon.hpp>
#include <components/Arrow.hpp>
#include <BehaviourTree/Conditionals/ArriveToPointPatrol.hpp>
#include <BehaviourTree/Conditionals/ObstacleInFront.hpp>
#include <BehaviourTree/Conditionals/PlayerIsInFront.hpp>
#include <BehaviourTree/Conditionals/PlayerIsLost.hpp>
#include <BehaviourTree/Conditionals/PlayerIsInactive.hpp>
#include <BehaviourTree/Conditionals/PlayerSensed.hpp>
#include <BehaviourTree/Tasks/AttackPlayer.hpp>
#include <BehaviourTree/Tasks/ChasePlayer.hpp>
#include <BehaviourTree/Tasks/DodgeObstacle.hpp>
#include <BehaviourTree/Tasks/FindTurningKeyPoint.hpp>
#include <BehaviourTree/Tasks/GoToNextPointPatrol.hpp>
#include <BehaviourTree/Tasks/KeepWalking.hpp>
#include <BehaviourTree/Decorators/LimitDistance.hpp>
#include "Sequence.hpp"
#include "Selector.hpp"



BehaviourTree::BehaviourTree()
{

	selectors = {
		std::make_unique<Selector>(),
		std::make_unique<Selector>()
	};

	sequences = {
		std::make_unique<Sequence>(),
		std::make_unique<Sequence>(),
		std::make_unique<Sequence>(),
		std::make_unique<Sequence>(),
		std::make_unique<Sequence>(),
		std::make_unique<Sequence>()
	};
	
	auto arriveToPointPatrol = std::make_unique<ArriveToPointPatrol>();
	auto obstacleInFront = std::make_unique<ObstacleInFront>();
	auto playerIsInFront = std::make_unique<PlayerIsInFront>();
	auto playerIsInactive = std::make_unique<PlayerIsInactive>();
	auto playerIsLost = std::make_unique<PlayerIsLost>();
	auto playerSensed = std::make_unique<PlayerSensed>();
	
	auto attackPlayer = std::make_unique<AttackPlayer>();
	auto chasePlayer = std::make_unique<ChasePlayer>();
	auto dodgeObstacle = std::make_unique<DodgeObstacle>();
	auto findTurningKeyPoint = std::make_unique<FindTurningKeyPoint>();
	auto goToNextPointPatrol = std::make_unique<GoToNextPointPatrol>();
	auto keepWalking = std::make_unique<KeepWalking>();
	


	// Create tree
	//playerIsClose->addChild(selectors[0].get());
	selectors[0]->addChild(sequences[0].get());
	selectors[0]->addChild(sequences[4].get());
	selectors[0]->addChild(sequences[5].get());
	selectors[0]->addChild(keepWalking.get());

	sequences[0]->addChild(playerSensed.get());
	sequences[0]->addChild(selectors[1].get());

	selectors[1]->addChild(sequences[1].get());
	selectors[1]->addChild(sequences[2].get());
	selectors[1]->addChild(sequences[3].get());

	sequences[1]->addChild(obstacleInFront.get());
	sequences[1]->addChild(dodgeObstacle.get());

	sequences[2]->addChild(playerIsInFront.get());
	sequences[2]->addChild(attackPlayer.get());

	sequences[3]->addChild(playerIsInactive.get());
	sequences[3]->addChild(chasePlayer.get());

	sequences[4]->addChild(playerIsLost.get());
	sequences[4]->addChild(findTurningKeyPoint.get());

	sequences[5]->addChild(arriveToPointPatrol.get());
	sequences[5]->addChild(goToNextPointPatrol.get());


	// Save leaves on vector
	conditionals.reserve(kNumConditionals);
	conditionals.push_back(std::move(arriveToPointPatrol));
	conditionals.push_back(std::move(obstacleInFront));
	conditionals.push_back(std::move(playerIsInFront));
	conditionals.push_back(std::move(playerIsInactive));
	conditionals.push_back(std::move(playerIsLost));
	conditionals.push_back(std::move(playerSensed));

	tasks.reserve(kNumTasks);
	tasks.push_back(std::move(attackPlayer));
	tasks.push_back(std::move(chasePlayer));
	tasks.push_back(std::move(dodgeObstacle));
	tasks.push_back(std::move(findTurningKeyPoint));
	tasks.push_back(std::move(goToNextPointPatrol));
	tasks.push_back(std::move(keepWalking));

	//decorators.reserve(kNumDecorators);
	//auto& playerIsClose = decorators.emplace_back(std::make_unique<LimitDistance>());

}




bool
BehaviourTree::run(MemoryRecord& mr, ARCS::ArrowComponent& arr, ARCS::PositionComponent& pos, ARCS::AIComponent& ai, ARCS::WeaponComponent& wp, MapComponent& map)
{	
	return selectors[0]->run(mr, arr, pos, ai, wp, map);
}
