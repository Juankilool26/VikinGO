#pragma once

#include <memory>
#include <array>
#include <vector>
#include "Composite.hpp"
#include "Decorator.hpp"




struct BehaviourTree
{
	BehaviourTree();
	~BehaviourTree() = default;
	bool run(MemoryRecord &,ARCS::ArrowComponent&,ARCS::PositionComponent &,ARCS::AIComponent &,ARCS::WeaponComponent &,MapComponent &);
	BehaviourTree(BehaviourTree&&) = default;

private:

	inline static constexpr std::size_t kNumTasks		 { 6 };
	inline static constexpr std::size_t kNumConditionals { 6 };
	inline static constexpr std::size_t kNumSequences	 { 6 };
	inline static constexpr std::size_t kNumSelectors	 { 2 };
	//inline static constexpr std::size_t kNumDecorators	 { 1 };

	using UPNode_t = std::unique_ptr<Node>;
	using UPComposite_t = std::unique_ptr<Composite>;
	using UPDecorator_t = std::unique_ptr<Decorator>;

	using VecUPTasks_t = std::vector<UPNode_t>;
	using VecUPConditionals_t = std::vector<UPNode_t>;
	//using VecUPDecorators_t = std::vector<UPDecorator_t>;

	using ArrayUPSequence_t = std::array<UPComposite_t, kNumSequences>;
	using ArrayUPSelector_t = std::array<UPComposite_t, kNumSelectors>;

	ArrayUPSequence_t sequences;
	ArrayUPSelector_t selectors;
	VecUPTasks_t tasks;
	VecUPConditionals_t conditionals;
	//VecUPDecorators_t decorators;
};
