#include <facade/Render/ManFacadeRender.hpp>
#include <facade/Physics/ManFacadePhysics.hpp>
#include <components/Entity.hpp>
#include <fstream>
#include <picoJSON/picojson.hpp>
#include <array>
#include <BehaviourTree/Conditionals/DartboardSensed.hpp>
#include <BehaviourTree/Tasks/ThrowArrow.hpp>
#include "GameObjectFactory.hpp"


SCH::FrequencyScheduler
GameObjectFactory::createArcherScheduler(unsigned int eyeFrame, unsigned int arrowFrame) const {
	SCH::FrequencyScheduler scheduler { };

	auto playerSeen { std::make_unique<DartboardSensed>() };
	auto throwArrow { std::make_unique<ThrowArrow>() };

	scheduler.addBehavior(std::move(playerSeen), eyeFrame,   0);
	scheduler.addBehavior(std::move(throwArrow), arrowFrame, 0);

	return scheduler;
}


GameObjectFactory::GameObjectFactory(ARCS::EntityManager& m_EntMan)
    : EntMan { m_EntMan }
{ }


ARCS::Entity&
GameObjectFactory::createEntityObject(glm::vec3 pos, glm::vec3 rot, std::string_view obj) const {
	auto& entity  { EntMan.createEntity() };
	auto& rendcmp { EntMan.addRenderComponent(entity)   };
	auto& poscmp  { EntMan.addPositionComponent(entity) };
	
	// Render component
	entity.rend = &rendcmp;
	//rendcmp.size = size;
	rendcmp.object = obj;

	// Position component
	entity.pos = &poscmp;
	poscmp.position = pos;
	poscmp.rotation = rot;

	return entity;
}


ARCS::Entity&
GameObjectFactory::createCollider(glm::vec3 position, glm::vec3 rotacion, glm::vec3 boundBoxNeg, glm::vec3 boundBoxPos) const{
	auto& entity  { createEntityObject(position, rotacion, "cube") };
	auto& colcmp  { EntMan.addCollisionComponent(entity) };

	// Collision component
	entity.col = &colcmp;
	colcmp.boxRoot.box = { {boundBoxNeg}, {boundBoxPos}};

	// Mask setter
	using CL = ARCS::CollisionComponent;
	colcmp.mask = CL::L_Obstacle;
	colcmp.properties = CL::P_IsSolid;

	//ManFacadeRender::GetInstance()->getFacade()->createAnimatedNode( entity );

	return entity;
}


ARCS::Entity&
GameObjectFactory::createPlayer(glm::vec3 position, glm::vec3 rotacion, std::string model, 
	int health, float spLinear, float spAngular, glm::vec3 boundBoxNeg, glm::vec3 boundBoxPos) const {

	auto& entity  { createEntityObject(position, rotacion, model) };
	auto& phycmp  { EntMan.addPhysicsComponent(entity)   };
	auto& inpcmp  { EntMan.addInputComponent(entity)     };
	auto& colcmp  { EntMan.addCollisionComponent(entity) };
	auto& healcmp { EntMan.addHealthComponent(entity)    };
	auto& sense   { EntMan.addSensorialPerceptionComponent(entity) };
	auto& weapon  { EntMan.addWeaponComponent(entity) };
	auto& depcmp  { EntMan.addVisualDepurationComponent(entity) };

	// Physics component
	entity.phy = &phycmp;
	phycmp.normalSpeed  = spLinear;
	phycmp.speedAngular = spAngular;
	phycmp.sprintSpeed  = spLinear + 4.f;

	// Input component
	entity.inp = &inpcmp;

	// Collision component
	entity.col = &colcmp;
	colcmp.boxRoot.box = { {boundBoxNeg}, {boundBoxPos}};
    //colcmp.boxRoot.childs = {
    //    { { {-0.5,-0.5,-0.5}, {0.5,0.5,0.5} }, false, {} }
    //};
	using CL = ARCS::CollisionComponent;
	colcmp.properties = CL::P_IsPlayer;

	// Health component
	entity.heal = &healcmp;
	healcmp.health = health;

	// Sense component
	entity.sens = &sense;
	sense.rSense.noise.box = { {-5, -5, -5}, {5, 5, 5} };

	// Weapon component
	entity.wc = &weapon;
	entity.wc->wpositionRelative = {-1,0,0};
	entity.wc->boxWeapon.box = { {-1, -1, -1}, {1, 1, 1} };

	// Create mesh
	ManFacadeRender::GetInstance()->getFacade()->createAnimatedNode( entity );

	// Visual depuration component for weapon
	entity.vd = &depcmp;
	ManFacadeRender::GetInstance()->getFacade()->createStaticNode(entity.vd->visualID[0], entity.vd->visualPos[0], entity.pos->rotation, entity.vd->visualObj[0]);
	ManFacadeRender::GetInstance()->getFacade()->setNoVisible(entity.vd->visualID[0]);
	ManFacadeRender::GetInstance()->getFacade()->setTransparent(entity.vd->visualID[0]);

    return entity;
}


ARCS::Entity&
GameObjectFactory::createEnemy(glm::vec3 position, glm::vec3 rotacion, std::string model, int health, glm::vec3 boundBoxNeg, glm::vec3 boundBoxPos) const {

    auto& entity  { createEntityObject(position, rotacion, model) };
	auto& phycmp  { EntMan.addPhysicsComponent(entity)   };
	auto& colcmp  { EntMan.addCollisionComponent(entity) };
	auto& healcmp { EntMan.addHealthComponent(entity)    };
	auto& aicmp   { EntMan.addAIComponent(entity)    };
	auto& sense   { EntMan.addSensorialPerceptionComponent(entity) };
	auto& behave  { EntMan.addBehaviourComponent(entity) };
	auto& weapon  { EntMan.addWeaponComponent(entity) };
	auto& lodcmp  { EntMan.addLoDComponent(entity) };
	auto& depcmp  { EntMan.addVisualDepurationComponent(entity) };

	// Collision component
	entity.col = &colcmp;
	colcmp.boxRoot.box = { boundBoxNeg, boundBoxPos };
    //colcmp.boxRoot.childs = {
    //    { { {-0.5,-0.5,-0.5}, {0.5,0.5,0.5} }, false, {} }
    //};
	using CL = ARCS::CollisionComponent;
	colcmp.mask = (CL::L_Enemy | CL::L_Obstacle);
	colcmp.properties = CL::P_IsEnemy;

	// Physics component
	entity.phy = &phycmp;
	phycmp.speedLinear = 2;
	phycmp.speedAngular = 200;
	phycmp.sprintSpeed  = phycmp.speedLinear + 3.2f;

	// Health component
	entity.heal = &healcmp;
	healcmp.health = health;

	// AI Component
	entity.ai = &aicmp;

	// Sense component
	entity.sens = &sense;
	entity.sens->rSense.vision.positionRelative = {5,0,0};
	entity.sens->rSense.vision.boxRootSup.box = { {-4,0.7,-4}, {5,1,5} };
	entity.sens->rSense.vision.boxRootInf.box = { {-4,-1,-4}, {5,0,5} };
	entity.sens->rSense.hearing.box = { {-3.5,-3.5,-3.5}, {3.5,3.5,3.5} };

	// Behaviour component
	entity.bh = &behave;

	// Weapon component
	entity.wc = &weapon;
	entity.wc->wpositionRelative = {0,0,1};
	entity.wc->boxWeapon.box = {{-0.5f,-0.5f,-0.5f}, {0.5f,0.5f,0.5f}};

	// LoD component
	entity.lod = &lodcmp;


	// Create entity mesh
	ManFacadeRender::GetInstance()->getFacade()->createAnimatedNode( entity );


	// Visual depuration component
	entity.vd = &depcmp;
	for (int i=0; i<entity.vd->kNumMaxObj; ++i) {
		ManFacadeRender::GetInstance()->getFacade()->createStaticNode(entity.vd->visualID[i], entity.vd->visualPos[i], entity.pos->rotation, entity.vd->visualObj[i]);
		ManFacadeRender::GetInstance()->getFacade()->setNoVisible(entity.vd->visualID[i]);
		ManFacadeRender::GetInstance()->getFacade()->setTransparent(entity.vd->visualID[i]);
	}

	return entity;
}


ARCS::Entity&
GameObjectFactory::createArcher(glm::vec3 position, glm::vec3 rotacion, std::string_view model, unsigned int eyeFrame, unsigned int arrowFrame) const {

    auto& entity  { createEntityObject(position, rotacion, model) };
	auto& phycmp  { EntMan.addPhysicsComponent(entity) };
	auto& aicmp   { EntMan.addAIComponent(entity) };
	auto& schcmp  { EntMan.addSchedulingComponent(entity) };
	auto& sense   { EntMan.addSensorialPerceptionComponent(entity) };
	auto& arrcmp  { EntMan.addArrowComponent(entity) };
	auto& depcmp  { EntMan.addVisualDepurationComponent(entity) };
	auto& healcmp { EntMan.addHealthComponent(entity) };

	// Physics component
	entity.phy = &phycmp;
	phycmp.speedAngular = 200;

	// AI Component
	entity.ai = &aicmp;

	// Scheduling Component
	entity.sch = &schcmp;
	schcmp.scheduler = createArcherScheduler(eyeFrame, arrowFrame);

	// Sense component
	entity.sens = &sense;
	entity.sens->rSense.vision.positionRelative = {5,0,0};
	entity.sens->rSense.vision.boxRootSup.box = { {-4,0.7,-4}, {5,1,5} };
	entity.sens->rSense.vision.boxRootInf.box = { {-4,-1,-4}, {5,0,5} };
	//entity.sens->rSense.hearing.box = { {-3.5,-3.5,-3.5}, {3.5,3.5,3.5} };
	entity.sens->rSense.hearing.box = { {-20,-10,-20}, {20,0,20} };

	// Health component
	entity.heal = &healcmp;
	healcmp.health = 1;

	// Arrow component
	entity.arr = &arrcmp;
	arrcmp.angle.y = 0.5f;
	arrcmp.velocity = 28;
	// 3/15
	// 3/20
	// 3/25

	// Arrow Entity
	auto& arrow { createEntityObject(entity.pos->position, rotacion, "media/models/flecha.obj") };
	arrcmp.arrowID = arrow.id;
	ManFacadeRender::GetInstance()->getFacade()->createAnimatedNode( arrow );

	// Weapon Arrow Components
	auto& arrwpcmp  { EntMan.addWeaponComponent(arrow) };
	arrow.wc = &arrwpcmp;
	arrwpcmp.boxWeapon.box = { {-0.2f,-0.2f,-0.2f}, {0.2f,0.2f,0.2f} };
	arrwpcmp.time2HitAgain = arrwpcmp.limitTime4Waiting;


	// Create entity mesh
	ManFacadeRender::GetInstance()->getFacade()->createAnimatedNode( entity );


	// Visual depuration component
	entity.vd = &depcmp;
	for (int i=1; i<entity.vd->kNumMaxObj; ++i) {
		ManFacadeRender::GetInstance()->getFacade()->createStaticNode(entity.vd->visualID[i], entity.vd->visualPos[i], entity.pos->rotation, entity.vd->visualObj[i]);
		ManFacadeRender::GetInstance()->getFacade()->setNoVisible(entity.vd->visualID[i]);
		ManFacadeRender::GetInstance()->getFacade()->setTransparent(entity.vd->visualID[i]);
	}

	return entity;
}


ARCS::Entity&
GameObjectFactory::createMannequin(glm::vec3 position, glm::vec3 rotacion, std::string model, int health, glm::vec3 boundBoxNeg, glm::vec3 boundBoxPos) const {

    auto& entity  { createEntityObject(position, rotacion, model) };
	auto& phycmp  { EntMan.addPhysicsComponent(entity)   };
	auto& colcmp  { EntMan.addCollisionComponent(entity) };
	auto& healcmp { EntMan.addHealthComponent(entity)    };

	// Collision component
	entity.col = &colcmp;
	colcmp.boxRoot.box = { boundBoxNeg, boundBoxPos };
    //colcmp.boxRoot.childs = {
    //    { { {-0.5,-0.5,-0.5}, {0.5,0.5,0.5} }, false, {} }
    //};
	using CL = ARCS::CollisionComponent;
	colcmp.mask = (CL::L_Enemy | CL::L_Obstacle);
	colcmp.properties = CL::P_IsEnemy;

	// Physics component
	entity.phy = &phycmp;
	phycmp.speedLinear  = 0.2f;
	phycmp.speedAngular = 4.0f;

	// Health component
	entity.heal = &healcmp;
	healcmp.health = health;

	//Physics system
	entity.phy = &phycmp;
	phycmp.speedLinear = 7;
	phycmp.speedAngular = 200;

	ManFacadeRender::GetInstance()->getFacade()->createAnimatedNode( entity );


	return entity;
}


ARCS::Entity&
GameObjectFactory::createObject(glm::vec3 position,glm::vec3 rotacion, std::string model,
				glm::vec3 boundBoxNeg, glm::vec3 boundBoxPos) const {

    auto& entity  { createEntityObject(position, rotacion, model) };
	auto& colcmp  { EntMan.addCollisionComponent(entity) };

	// Collision component
	entity.col = &colcmp;
	colcmp.boxRoot.box = { boundBoxNeg, boundBoxPos };
    //colcmp.boxRoot.childs = {
    //    { { {-0.5,-0.5,-0.5}, {0.5,0.5,0.5} }, false, {} }
    //};
	colcmp.mask = ARCS::CollisionComponent::L_Obstacle;
	colcmp.properties = ARCS::CollisionComponent::P_IsSolid;

	// Create mesh
	ManFacadeRender::GetInstance()->getFacade()->createAnimatedNode( entity );

	return entity;
}


ARCS::Entity&
GameObjectFactory::createCamera(ARCS::Entity& e, glm::vec3 position, glm::vec3 rotacion) const {
	//rotacion = glm::vec3(rotacion.x + 45.0f, rotacion.y + 45.0f, rotacion.z) + 45.0f;
	auto& entity { createEntityObject(position, rotacion, "") };
	auto& camcmp { EntMan.addCameraComponent(entity) };

	// Camera component
	entity.cam = &camcmp;
	camcmp.followEntityID = e.id;
	camcmp.lookat.x = 90;
	camcmp.calculateRelativeDistance(entity.pos->position, e.pos->position);

	// Create mesh
	ManFacadeRender::GetInstance()->getFacade()->createFPSCameraNode( entity );
	

	return entity;
}



ARCS::Entity& GameObjectFactory::loadLevelJSON(std::string_view filepath, int level, MapComponent& map) const{

	namespace pj = picojson;

	// Comprobamos si existe y por lo tanto abrimos el mapa que nos estan pasando
	std::ifstream file(filepath.data());
	if (!file) throw std::runtime_error("No se ha podido abrir el fichero JSON");

	// Leemos el fichero en memoria
	pj::value json;
	file >> json;
	std::string err { pj::get_last_error() };
	if (!err.empty()) throw std::runtime_error(err);

	// Leemos los valores minimos constantes de un nivel
	const auto& root 	 		 { json.get<pj::object>() };
	const auto& player   		 { root.at("player").get<pj::array>() };
	const auto& cabeceraObjetos	 { root.at("cabeceraObjetos").get<pj::array>() };
	const auto& numColliders 	 { root.at("Colliders").get<double>()};
	const auto& numKeyPoints 	 { root.at("KeyPoints").get<double>()};
	const auto& numAuxPoints 	 { root.at("AuxPoints").get<double>()};


	// Leemos y cargamos el player

	ARCS::Entity* playerAux { nullptr };

	std::string test = "yes";
	if(std::strcmp((player[0].get<std::string>()).c_str(),test.c_str())==0){

		// Recogemos todos los valores del JSON y los asignamos a las variables
		glm::vec3 position { (float) player[14].get<double>(), (float) player[15].get<double>(), -((float) player[16].get<double>()) };
		//glm::vec3 size     { (float) player[21].get<double>(), (float) player[22].get<double>(), (float) player[23].get<double>() };
		std::string model  { player[20].get<std::string>() };
		int health		   { (int) player[10].get<double>() };
		float spLinear	   { (float) player[12].get<double>() };
		float spAngular	   { (float) player[13].get<double>() };
		glm::vec3 posCamera { (float) player[1].get<double>(), (float) player[2].get<double>(), (float) player[3].get<double>() };
		glm::vec3 boundBoxNeg { (float) player[4].get<double>()/2, (float) player[5].get<double>(), (float) player[6].get<double>()/2 };
		glm::vec3 boundBoxPos { (float) player[7].get<double>()/2, (float) player[8].get<double>(), (float) player[9].get<double>()/2 };

		// Creamos el entity asociado al player y recogemos una referencia para crear la camara1
		playerAux = &createPlayer(position, glm::vec3{0,0,0}, model, health, spLinear, spAngular, boundBoxNeg, boundBoxPos);
		createCamera(*playerAux, posCamera, glm::vec3{0,0,0});
	}


	if(level == 0){	// Level Tutorial

		createMannequin(glm::vec3(-15.976,1.75,-7.2011), glm::vec3(0,4.79,0), "media/models/maniqui.obj", 5, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5));	
		createMannequin(glm::vec3(-10.667,1.75,-9.3644), glm::vec3(0,-28.3,0), "media/models/maniqui.obj", 5, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5));	
		createMannequin(glm::vec3(-12.417,1.75,-14.67), glm::vec3(0,-52.4,0), "media/models/maniqui.obj", 5, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5));
		
		auto& enemy { createEnemy(glm::vec3(11.908,1.75,-16.396), glm::vec3(0,0,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5))};
		enemy.ai->pointsPatrol.reserve(6);
		enemy.ai->pointsPatrol.emplace_back(11.908,1.75,-18.396);
		enemy.ai->pointsPatrol.emplace_back(11.908,1.75,-9.776);
		enemy.ai->pointsPatrol.emplace_back(6.5684,1.75,-7.5533);
		enemy.ai->pointsPatrol.emplace_back(4.5848,1.75,-16.576);
		enemy.ai->pointsPatrol.emplace_back(6.5684,1.75,-7.5533);
		enemy.ai->pointsPatrol.emplace_back(11.908,1.75,-9.776);
		enemy.phy->speedLinear = 1;
		enemy.phy->sprintSpeed = 2;
		//enemy.ai->target = enemy.ai->pointsPatrol[1];

		/* createMannequin(glm::vec3(-15.976,1.75,-7.2011), glm::vec3(0,4.79,0), glm::vec3(0,0,0), "maniqui", 6, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5));	
		createMannequin(glm::vec3(-10.667,1.75,-9.3644), glm::vec3(0,-28.3,0), glm::vec3(0,0,0), "maniqui", 6, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5));	
		createMannequin(glm::vec3(-12.417,1.75,-14.67), glm::vec3(0,-52.4,0), glm::vec3(0,0,0), "maniqui", 6, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5));
		
		auto& enemy { createEnemy(glm::vec3(11.908,1.75,-16.396), glm::vec3(0,0,0), glm::vec3(0,0,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5))};
		enemy.ai->pointsPatrol.reserve(6);
		enemy.ai->pointsPatrol.emplace_back(11.908,1.75,-18.396);
		enemy.ai->pointsPatrol.emplace_back(11.908,1.75,-9.776);
		enemy.ai->pointsPatrol.emplace_back(6.5684,1.75,-7.5533);
		enemy.ai->pointsPatrol.emplace_back(4.5848,1.75,-16.576);
		enemy.ai->pointsPatrol.emplace_back(6.5684,1.75,-7.5533);
		enemy.ai->pointsPatrol.emplace_back(11.908,1.75,-9.776);
		enemy.phy->speedLinear = 1;
		enemy.phy->sprintSpeed = 2;
		//enemy.ai->target = enemy.ai->pointsPatrol[1]; */

	} else if (level == 1) { // TODO: Level 1 easy tutorial
		auto& enemy { createArcher(glm::vec3(-37.008,7,10.933), glm::vec3(0,225,0), "media/models/arquero1.obj", 30, 200) };
		enemy.ai->pointsPatrol.reserve(1);
		enemy.ai->pointsPatrol.emplace_back(-37.008,7,10.933);

		auto& enemy2 { createArcher(glm::vec3(-61.538,7,10.933), glm::vec3(0,225,0), "media/models/arquero1.obj", 30, 200) };
		enemy2.ai->pointsPatrol.reserve(1);
		enemy2.ai->pointsPatrol.emplace_back(-61.538,7,10.933);

		auto& enemy3 { createArcher(glm::vec3(-49.756,7,-24.178), glm::vec3(0,225,0), "media/models/arquero1.obj", 30, 200) };
		enemy3.ai->pointsPatrol.reserve(1);
		enemy3.ai->pointsPatrol.emplace_back(-49.756,7,-24.178);

		auto& enemy4 { createArcher(glm::vec3(-26.982,7,-24.178), glm::vec3(0,225,0), "media/models/arquero1.obj", 30, 200) };
		enemy4.ai->pointsPatrol.reserve(1);
		enemy4.ai->pointsPatrol.emplace_back(-26.982,7,-24.178);

		auto& enemy5 { createEnemy(glm::vec3(-122.52,1.99,-5.9921), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy5.ai->pointsPatrol.reserve(6);
		enemy5.ai->pointsPatrol.emplace_back(-122.52,1.99,-5.9921);
		enemy5.ai->pointsPatrol.emplace_back(-124.53,1.99,-13.467);
		enemy5.ai->pointsPatrol.emplace_back(-131.99,1.99,-18.226);
		enemy5.ai->pointsPatrol.emplace_back(-137.94,1.99,-12.46);
		enemy5.ai->pointsPatrol.emplace_back(-132.86,1.99,-5.5955);
		enemy5.ai->pointsPatrol.emplace_back(-138.95,1.99,1.4977);
		enemy5.ai->pointsPatrol.emplace_back(-133.29,1.99,8.8563);
		enemy5.ai->pointsPatrol.emplace_back(-127.03,1.99,1.4428);
	
	} else if (level == 2) {
		auto& enemy { createEnemy(glm::vec3(66.625,1.99,-5.1287), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy.ai->pointsPatrol.reserve(6);
		enemy.ai->pointsPatrol.emplace_back(66.625,1.99,-5.1287);
		enemy.ai->pointsPatrol.emplace_back(53.041,1.99,-4.7757);
		enemy.ai->pointsPatrol.emplace_back(53.041,1.99,1.1087);
		enemy.ai->pointsPatrol.emplace_back(44.278,1.99,1.1087);
		enemy.ai->pointsPatrol.emplace_back(53.041,1.99,1.1087);
		enemy.ai->pointsPatrol.emplace_back(53.041,1.99,-4.7757);

		auto& enemy2 { createEnemy(glm::vec3(94.987,1.99,17.067), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy2.ai->pointsPatrol.reserve(1);
		enemy2.ai->pointsPatrol.emplace_back(94.987,1.99,17.067);

		auto& enemy3 { createEnemy(glm::vec3(78.638,1.99, 8.5193), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy3.ai->pointsPatrol.reserve(7);
		enemy3.ai->pointsPatrol.emplace_back(78.638,1.99,8.5193);
		enemy3.ai->pointsPatrol.emplace_back(78.638,1.99,18.078);
		enemy3.ai->pointsPatrol.emplace_back(78.638,1.99,5.4941);
		enemy3.ai->pointsPatrol.emplace_back(92.93,1.99,5.4941);
		enemy3.ai->pointsPatrol.emplace_back(92.93,1.99,17.965);
		enemy3.ai->pointsPatrol.emplace_back(92.93,1.99,5.4941);
		enemy3.ai->pointsPatrol.emplace_back(78.638,1.99,5.4941);

		auto& enemy4 { createEnemy(glm::vec3(100.54,1.99, -21.003), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy4.ai->pointsPatrol.reserve(6);
		enemy4.ai->pointsPatrol.emplace_back(100.54,1.99, -21.003);
		enemy4.ai->pointsPatrol.emplace_back(110.96,1.99, -21.003);
		enemy4.ai->pointsPatrol.emplace_back(110.96,1.99, -3.9558);
		enemy4.ai->pointsPatrol.emplace_back(110.96,1.99, -21.003);
		enemy4.ai->pointsPatrol.emplace_back(100.54,1.99, -21.003);
		enemy4.ai->pointsPatrol.emplace_back(100.54,1.99, -36.725);

		auto& enemy5 { createEnemy(glm::vec3(82.591,1.99, -28.773), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy5.ai->pointsPatrol.reserve(2);
		enemy5.ai->pointsPatrol.emplace_back(81.591,1.99, -28.773);
		enemy5.ai->pointsPatrol.emplace_back(93.96,1.99, -36.855);

	} else if (level == 3){
		auto& enemy { createEnemy(glm::vec3(-16.016,1.99,3.5221), glm::vec3(0,225,0), "media/models/blind.obj", 5, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
/* 		enemy5.ai->pointsPatrol.emplace_back(82.591,1.99, -28.773);
		enemy5.ai->pointsPatrol.emplace_back(94.96,1.99, -36.855);

	} else if (level == 2){
		auto& enemy { createEnemy(glm::vec3(-16.016,1.99,3.5221), glm::vec3(0,225,0), glm::vec3(0,0,0), "media/models/personajeBase.obj", 6, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) }; */
		enemy.sens->rSense.vision.boxRootSup.box = { {0,0,0}, {0,0,0} };
		enemy.sens->rSense.vision.boxRootInf.box = { {0,0,0}, {0,0,0} };
		enemy.sens->rSense.vision.positionRelative.y = 500;
		enemy.sens->rSense.hearing.box = { {-5,-5,-5}, {5,5,5} };
		enemy.ai->pointsPatrol.reserve(1);
		enemy.ai->pointsPatrol.emplace_back(-16.016,1.99,3.5221);

		auto& enemy2 { createEnemy(glm::vec3(2.5411,1.99,41.028), glm::vec3(0,225,0), "media/models/blind.obj", 5, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		// auto& enemy2 { createEnemy(glm::vec3(2.5411,1.99,-1.028), glm::vec3(0,225,0), glm::vec3(0,0,0), "media/models/personajeBase.obj", 6, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy2.sens->rSense.vision.boxRootSup.box = { {0,0,0}, {0,0,0} };
		enemy2.sens->rSense.vision.boxRootInf.box = { {0,0,0}, {0,0,0} };
		enemy2.sens->rSense.vision.positionRelative.y = 500;
		enemy2.sens->rSense.hearing.box = { {-5,-5,-5}, {5,5,5} };
		enemy2.ai->pointsPatrol.reserve(6);
		enemy2.ai->pointsPatrol.emplace_back(2.5411,1.99,41.028);
		enemy2.ai->pointsPatrol.emplace_back(2.5411,1.99,36.202);
		enemy2.ai->pointsPatrol.emplace_back(23.34,1.99,36.202);
		enemy2.ai->pointsPatrol.emplace_back(23.34,1.99,23.036);
		enemy2.ai->pointsPatrol.emplace_back(23.34,1.99,36.202);
		enemy2.ai->pointsPatrol.emplace_back(2.5411,1.99,36.202);

		auto& enemy3 { createEnemy(glm::vec3(53.335,1.99,8.1829), glm::vec3(0,225,0), "media/models/blind.obj", 5, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
/* 		enemy2.ai->pointsPatrol.emplace_back(2.5411,1.99,41.028);
		enemy2.ai->pointsPatrol.emplace_back(2.5411,1.99,36.202);
		enemy2.ai->pointsPatrol.emplace_back(23.34,1.99,36.202);
		enemy2.ai->pointsPatrol.emplace_back(23.34,1.99,23.036);
		enemy2.ai->pointsPatrol.emplace_back(23.34,1.99,36.202);
		enemy2.ai->pointsPatrol.emplace_back(2.5411,1.99,36.202);

		auto& enemy3 { createEnemy(glm::vec3(53.335,1.99,8.1829), glm::vec3(0,225,0), glm::vec3(0,0,0), "media/models/personajeBase.obj", 6, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) }; */
		enemy3.sens->rSense.vision.boxRootSup.box = { {0,0,0}, {0,0,0} };
		enemy3.sens->rSense.vision.boxRootInf.box = { {0,0,0}, {0,0,0} };
		enemy3.sens->rSense.vision.positionRelative.y = 500;
		enemy3.sens->rSense.hearing.box = { {-5,-5,-5}, {5,5,5} };
		enemy3.ai->pointsPatrol.reserve(1);
		enemy3.ai->pointsPatrol.emplace_back(53.335,1.99,-8.1829);

		auto& enemy4 { createEnemy(glm::vec3(30.658,1.99,-10.472), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy4.ai->pointsPatrol.reserve(11);
		enemy4.ai->pointsPatrol.emplace_back(30.658,1.99,-10.472);
		enemy4.ai->pointsPatrol.emplace_back(35.109,1.99,-10.472);
		enemy4.ai->pointsPatrol.emplace_back(35.109,1.99,-16.423);
		enemy4.ai->pointsPatrol.emplace_back(39.989,1.99,-10.472);
		enemy4.ai->pointsPatrol.emplace_back(39.989,1.99,-10.472);
		enemy4.ai->pointsPatrol.emplace_back(39.989,1.99,-13.986);
		enemy4.ai->pointsPatrol.emplace_back(45.486,1.99,-13.986);
		enemy4.ai->pointsPatrol.emplace_back(39.989,1.99,-13.986);
		enemy4.ai->pointsPatrol.emplace_back(39.989,1.99,-10.472);
		enemy4.ai->pointsPatrol.emplace_back(39.989,1.99,-10.472);
		enemy4.ai->pointsPatrol.emplace_back(30.658,1.99,-10.472);

		auto& enemy5 { createEnemy(glm::vec3(42.996,1.99,-21.834), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy5.ai->pointsPatrol.reserve(9);
		enemy5.ai->pointsPatrol.emplace_back(42.996,1.99,-21.834);
		enemy5.ai->pointsPatrol.emplace_back(42.996,1.99,-25.957);
		enemy5.ai->pointsPatrol.emplace_back(35.921,1.99,-25.957);
		enemy5.ai->pointsPatrol.emplace_back(35.921,1.99,-22.584);
		enemy5.ai->pointsPatrol.emplace_back(30.814,1.99,-22.584);
		enemy5.ai->pointsPatrol.emplace_back(35.921,1.99,-22.584);
		enemy5.ai->pointsPatrol.emplace_back(35.921,1.99,-25.957);
		enemy5.ai->pointsPatrol.emplace_back(42.996,1.99,-25.957);
		enemy5.ai->pointsPatrol.emplace_back(42.996,1.99,-21.834);
	}else if (level == 4){
		auto& enemy { createEnemy(glm::vec3(49.762,4.2,-116.56), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy.ai->pointsPatrol.reserve(6);
		enemy.ai->pointsPatrol.emplace_back(49.762,4.2,-116.56);
		enemy.ai->pointsPatrol.emplace_back(63.5,4.2,-116.56);
		enemy.ai->pointsPatrol.emplace_back(63.5,4.2,-114.53);
		enemy.ai->pointsPatrol.emplace_back(71.086,4.2,-114.53);
		enemy.ai->pointsPatrol.emplace_back(63.5,4.2,-114.53);
		enemy.ai->pointsPatrol.emplace_back(63.5,4.2,-116.56);

		auto& enemy2 { createEnemy(glm::vec3(63.459,4.2,-104.73), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy2.ai->pointsPatrol.reserve(8);
		enemy2.ai->pointsPatrol.emplace_back(63.459,4.2,-104.73);
		enemy2.ai->pointsPatrol.emplace_back(63.459,4.2,-101.85);
		enemy2.ai->pointsPatrol.emplace_back(61.358,4.2,-96.324);
		enemy2.ai->pointsPatrol.emplace_back(49.84,4.2,-96.285);
		enemy2.ai->pointsPatrol.emplace_back(61.358,4.2,-96.324);
		enemy2.ai->pointsPatrol.emplace_back(63.459,4.2,-101.85);
		enemy2.ai->pointsPatrol.emplace_back(63.459,4.2,-104.73);
		enemy2.ai->pointsPatrol.emplace_back(74.355,4.2,-104.73);

		auto& enemy3 { createEnemy(glm::vec3(14.268,4.3,-78.466), glm::vec3(0,225,0), "media/models/blind.obj", 5, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy3.sens->rSense.vision.boxRootSup.box = { {0,0,0}, {0,0,0} };
		enemy3.sens->rSense.vision.boxRootInf.box = { {0,0,0}, {0,0,0} };
		enemy3.sens->rSense.vision.positionRelative.y = 500;
		enemy3.sens->rSense.hearing.box = { {-5,-5,-5}, {5,5,5} };
		enemy3.ai->pointsPatrol.reserve(1);
		enemy3.ai->pointsPatrol.emplace_back(14.068,4.3,-78.466);

		auto& enemy4 { createEnemy(glm::vec3(-66.543,4.2,-70.52), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy4.ai->pointsPatrol.reserve(8);
		enemy4.ai->pointsPatrol.emplace_back(-66.543,4.2,-70.52);
		enemy4.ai->pointsPatrol.emplace_back(-66.543,4.2,-80.715);
		enemy4.ai->pointsPatrol.emplace_back(-52.977,4.2,-80.715);
		enemy4.ai->pointsPatrol.emplace_back(-52.977,4.2,-96.292);
		enemy4.ai->pointsPatrol.emplace_back(-52.977,4.2,-80.715);
		enemy4.ai->pointsPatrol.emplace_back(-40.836,4.2,-80.715);
		enemy4.ai->pointsPatrol.emplace_back(-66.543,4.2,-80.715);
		enemy4.ai->pointsPatrol.emplace_back(-66.543,4.2,-70.52);
		
		

		auto& enemy5 { createEnemy(glm::vec3(-52.977,4.2,-54.636), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy5.ai->pointsPatrol.reserve(7);
		enemy5.ai->pointsPatrol.emplace_back(-52.977,4.2,-54.636);
		enemy5.ai->pointsPatrol.emplace_back(-63.297,4.2,-54.636);
		enemy5.ai->pointsPatrol.emplace_back(-63.297,4.2,-43.043);
		enemy5.ai->pointsPatrol.emplace_back(-53.353,4.2,-43.043);
		enemy5.ai->pointsPatrol.emplace_back(-45.611,4.2,-45.943);
		enemy5.ai->pointsPatrol.emplace_back(-42.72,4.2,-50.591);
		enemy5.ai->pointsPatrol.emplace_back(-45.195,4.2,-54.56);
		
		auto& enemy6 { createEnemy(glm::vec3(-56.435,4.3,-61.187), glm::vec3(0,225,0), "media/models/blind.obj", 5, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy6.sens->rSense.vision.boxRootSup.box = { {0,0,0}, {0,0,0} };
		enemy6.sens->rSense.vision.boxRootInf.box = { {0,0,0}, {0,0,0} };
		enemy6.sens->rSense.vision.positionRelative.y = 500;
		enemy6.sens->rSense.hearing.box = { {-5,-5,-5}, {5,5,5} };
		enemy6.ai->pointsPatrol.reserve(4);
		enemy6.ai->pointsPatrol.emplace_back(-56.435,4.2,-61.187);
		enemy6.ai->pointsPatrol.emplace_back(-55.189,4.2,-69.087);
		enemy6.ai->pointsPatrol.emplace_back(-51.298,4.2,-76.402);
		enemy6.ai->pointsPatrol.emplace_back(-55.189,4.2,-69.087);
		
	} else if (level == 5){
		auto& enemy { createArcher(glm::vec3(-36.142,7,-73.09), glm::vec3(0,225,0), "media/models/arquero1.obj", 30, 200) };
		enemy.ai->pointsPatrol.reserve(1);
		enemy.ai->pointsPatrol.emplace_back(-36.142,7,-73.09);

		auto& enemy2 { createArcher(glm::vec3(-13.314,7,-85.200), glm::vec3(0,225,0), "media/models/arquero1.obj", 30, 200) };
		enemy2.ai->pointsPatrol.reserve(1);
		enemy2.ai->pointsPatrol.emplace_back(-13.314,7,-85.200);

		auto& enemy3 { createEnemy(glm::vec3(-44.853,1.4,58.97), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy3.ai->pointsPatrol.reserve(7);
		enemy3.ai->pointsPatrol.emplace_back(-44.853,1.4,58.97);
		enemy3.ai->pointsPatrol.emplace_back(-44.853,2.8,63.263);
		enemy3.ai->pointsPatrol.emplace_back(-52.826,2.8,63.263);
		enemy3.ai->pointsPatrol.emplace_back(-52.826,2.8,70.323);
		enemy3.ai->pointsPatrol.emplace_back(-41.515,2.8,70.323);
		enemy3.ai->pointsPatrol.emplace_back(-41.515,2.8,63.263);
		enemy3.ai->pointsPatrol.emplace_back(-44.853,2.8,63.263);

		auto& enemy4 { createEnemy(glm::vec3(-35.756,1.5,64.568), glm::vec3(0,225,0), "media/models/blind.obj", 5, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy4.sens->rSense.vision.boxRootSup.box = { {0,0,0}, {0,0,0} };
		enemy4.sens->rSense.vision.boxRootInf.box = { {0,0,0}, {0,0,0} };
		enemy4.sens->rSense.vision.positionRelative.y = 500;
		enemy4.sens->rSense.hearing.box = { {-5,-5,-5}, {5,5,5} };
		enemy4.ai->pointsPatrol.reserve(7);
		enemy4.ai->pointsPatrol.emplace_back(-35.756,2.8,64.568);
		enemy4.ai->pointsPatrol.emplace_back(-37.33,2.8,68.329);
		enemy4.ai->pointsPatrol.emplace_back(-41.791,2.8,71.129);
		enemy4.ai->pointsPatrol.emplace_back(-41.791,2.8,75.502);
		enemy4.ai->pointsPatrol.emplace_back(-34.181,2.8,75.502);
		enemy4.ai->pointsPatrol.emplace_back(-34.181,2.8,68.417);
		enemy4.ai->pointsPatrol.emplace_back(-37.33,2.8,68.329);
		
		auto& enemy5 { createEnemy(glm::vec3(27.411,1.5,14.383), glm::vec3(0,225,0), "media/models/blind.obj", 5, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy5.sens->rSense.vision.boxRootSup.box = { {0,0,0}, {0,0,0} };
		enemy5.sens->rSense.vision.boxRootInf.box = { {0,0,0}, {0,0,0} };
		enemy5.sens->rSense.vision.positionRelative.y = 500;
		enemy5.sens->rSense.hearing.box = { {-5,-5,-5}, {5,5,5} };
		enemy5.ai->pointsPatrol.reserve(4);
		enemy5.ai->pointsPatrol.emplace_back(27.411,2.8,14.383);
		enemy5.ai->pointsPatrol.emplace_back(17.146,2.8,14.383);
		enemy5.ai->pointsPatrol.emplace_back(17.146,2.8,20.597);
		enemy5.ai->pointsPatrol.emplace_back(21.869,2.8,14.383);

		auto& enemy6 { createEnemy(glm::vec3(35.077,1.5,17.746), glm::vec3(0,225,0), "media/models/blind.obj", 5, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy6.sens->rSense.vision.boxRootSup.box = { {0,0,0}, {0,0,0} };
		enemy6.sens->rSense.vision.boxRootInf.box = { {0,0,0}, {0,0,0} };
		enemy6.sens->rSense.vision.positionRelative.y = 500;
		enemy6.sens->rSense.hearing.box = { {-5,-5,-5}, {5,5,5} };
		enemy6.ai->pointsPatrol.reserve(10);
		enemy6.ai->pointsPatrol.emplace_back(35.077,2.8,17.746);
		enemy6.ai->pointsPatrol.emplace_back(29.283,2.8,17.746);
		enemy6.ai->pointsPatrol.emplace_back(29.283,2.8,22.406);
		enemy6.ai->pointsPatrol.emplace_back(25.504,2.8,22.406);
		enemy6.ai->pointsPatrol.emplace_back(25.504,2.8,26.925);
		enemy6.ai->pointsPatrol.emplace_back(21.222,2.8,26.925);
		enemy6.ai->pointsPatrol.emplace_back(21.222,2.8,22.222);
		enemy6.ai->pointsPatrol.emplace_back(24.875,2.8,19.005);
		enemy6.ai->pointsPatrol.emplace_back(29.031,2.8,19.005);
		enemy6.ai->pointsPatrol.emplace_back(29.283,2.8,17.746);


		auto& enemy7 { createEnemy(glm::vec3(-16.923,1.4,-81.074), glm::vec3(0,225,0), "media/models/patroler.obj", 3, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy7.ai->pointsPatrol.reserve(6);
		enemy7.ai->pointsPatrol.emplace_back(-16.923,1.4,-81.074);
		enemy7.ai->pointsPatrol.emplace_back(-16.923,1.4,-86.062);
		enemy7.ai->pointsPatrol.emplace_back(-25.538,1.4,-71.703);
		enemy7.ai->pointsPatrol.emplace_back(-19.795,1.4,-71.703);
		enemy7.ai->pointsPatrol.emplace_back(-19.795,1.4,-78.958);

		auto& enemy8 { createEnemy(glm::vec3(-11.482,1.5,-24.453), glm::vec3(0,225,0), "media/models/blind.obj", 5, glm::vec3(-0.5,-1,-0.5), glm::vec3(0.5,1,0.5)) };
		enemy8.sens->rSense.vision.boxRootSup.box = { {0,0,0}, {0,0,0} };
		enemy8.sens->rSense.vision.boxRootInf.box = { {0,0,0}, {0,0,0} };
		enemy8.sens->rSense.vision.positionRelative.y = 500;
		enemy8.sens->rSense.hearing.box = { {-5,-5,-5}, {5,5,5} };
		enemy8.ai->pointsPatrol.reserve(1);
		enemy8.ai->pointsPatrol.emplace_back(-11.482,1.4,-24.453);
	}


	// Leemos y cargamos todos los objetos
	for(unsigned int i = 0; i < cabeceraObjetos.size(); i++){
		std::string objetito = (cabeceraObjetos[i]).to_str();
		int cantThisobj = { (int) root.at(objetito).get<double>() };
		for(int j = 1; j <= cantThisobj; j++){
			std::string num  = std::to_string(j);
			std::string selectedObject = objetito + " " + num;
			// Recogemos todos los valores del JSON y los asignamos a las variables
			const auto& object { root.at(selectedObject).get<pj::array>() };
			glm::vec3 position { (float) object[0].get<double>(), (float) object[2].get<double>(), -((float) object[1].get<double>()) };
			glm::vec3 rotation { (float) object[3].get<double>(), (float) object[5].get<double>(), (float) object[4].get<double>() };
			std::string model = {root.at(objetito+"_path").get<std::string>()};
			rotation = glm::degrees(rotation);
			rotation.x = rotation.x-90;
/* 			glm::vec3 position { (float) object[0].get<double>(), (float) object[2].get<double>(), -((float) object[1].get<double>()) };
			glm::vec3 rotacion { (float) object[3].get<double>(), (float) object[5].get<double>(), (float) object[4].get<double>() };
			std::string model = {root.at(objetito+"_path").get<std::string>()};
			rotacion = glm::degrees(rotacion);
			rotacion.x = rotacion.x -90; */
			// Creamos el enemigo de esta iteracion del for
			//createObject(position, rotacion, glm::vec3{0,0,0}, model, glm::vec3{0,0,0}, glm::vec3{0,0,0});
			ManFacadeRender::GetInstance()->getFacade()->createStaticNode(position, rotation, model);
		}
	}

	// Leemos y cargamos todos los colliders del nivel
	for(int i = 1; i <= numColliders; i++){
		
		std::string num  = std::to_string(i);
		std::string selectedObject = "Collider " + num;

		// Recogemos todos los valores del JSON y los asignamos a las variables
		const auto& object { root.at(selectedObject).get<pj::array>() };
	    glm::vec3 position { (float) object[0].get<double>(), (float) object[2].get<double>(), -((float) object[1].get<double>()) };
		glm::vec3 bPos     { (float) object[3].get<double>(), (float) object[5].get<double>(), (float) object[4].get<double>() };
		//bPos = {(bPos.x/2), (bPos.y/2), (bPos.z/2)};
		glm::vec3 bNeg = -bPos;
		// Creamos el enemigo de esta iteracion del for
		createCollider(position, glm::vec3{0,0,0}, bNeg, bPos);
	}

	//Leemos y cargamos todos los keyPoints y los auxPoints

	for(int i = 1; i <= numKeyPoints; ++i){
		std::string num  = std::to_string(i);
		std::string selectedObject = "KeyPoint " + num;
		const auto& object { root.at(selectedObject).get<pj::array>() };
		map.addKeyPoint(glm::vec3((float) object[0].get<double>(), (float) object[2].get<double>(), -(float) object[1].get<double>()));
	}

	for(int i = 1; i <= numAuxPoints; ++i){
		std::string num  = std::to_string(i);
		std::string selectedObject = "AuxPoint " + num;
		const auto& object { root.at(selectedObject).get<pj::array>() };
		map.addAuxPoint(glm::vec3((float) object[0].get<double>(), (float) object[2].get<double>(), -(float) object[1].get<double>()));
		//ManFacadeRender::GetInstance()->getFacade()->createStaticNode(glm::vec3((float) object[0].get<double>(), (float) object[2].get<double>(), (float) object[1].get<double>()),glm::vec3(0,0,0), "media/models/personajeBase.obj.obj");
	} 
	
	return *playerAux;
}


//Pegar para cargar el lvl tutorial con la version 1.2 del Aesir_LVL_Export
/*
"Arbol_path": "arbolTutorial.obj",
"arbusto_path": "arbustoTutorial.obj",
"Roca_path": "rocaTutorial.obj",
"Runa_path": "runaTutorial.obj",
"Suelo_path": "sueloTutorial.obj",
"Tocon_path": "toconTutorial.obj",

"player": ["yes",1,2,0,
    -1,-1,-1,1,1,1,
    3,
    "yes",
    25,70,
    0,2,0,0,0,0,
    "cube.obj",2,2,2],
*/
