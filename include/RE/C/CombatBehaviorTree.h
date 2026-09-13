#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/C/CombatBehaviorAcquireResource.h"
#include "RE/C/CombatBehaviorChildSelector.h"
#include "RE/C/CombatBehaviorContextAcquireWeapon.h"
#include "RE/C/CombatBehaviorContextCloseMovement.h"
#include "RE/C/CombatBehaviorContextDodgeThreat.h"
#include "RE/C/CombatBehaviorContextFlankingMovement.h"
#include "RE/C/CombatBehaviorContextFlee.h"
#include "RE/C/CombatBehaviorContextMelee.h"
#include "RE/C/CombatBehaviorEquipContext.h"
#include "RE/C/CombatBehaviorFallbackSelector.h"
#include "RE/C/CombatBehaviorParallel.h"
#include "RE/C/CombatBehaviorRepeat.h"
#include "RE/C/CombatBehaviorThread.h"
#include "RE/C/CombatBehaviorTreeConditionalNode.h"
#include "RE/C/CombatBehaviorTreeCreateContextNode.h"
#include "RE/C/CombatBehaviorTreeNode.h"
#include "RE/C/CombatBehaviorTreeNodeObject.h"
#include "RE/C/CombatBehaviorTreeValueNodeT.h"
#include "RE/M/Misc.h"

namespace RE
{
	class Actor;

	class CombatBehaviorTree
	{
	public:
		inline static constexpr auto RTTI = RTTI_CombatBehaviorTree;
		inline static constexpr auto VTABLE = VTABLE_CombatBehaviorTree;

		class TreeBuilder
		{
		public:
			explicit TreeBuilder(CombatBehaviorTreeNode* a_node);
			CombatBehaviorTreeNode* GetNode();
			TreeBuilder&            operator[](const TreeBuilder& a_other);
			TreeBuilder&            operator,(const TreeBuilder& a_other);

			// members
			BSTArray<CombatBehaviorTreeNode*> nodeArray;  // 00
		};
		static_assert(sizeof(TreeBuilder) == 0x18);

		CombatBehaviorTree(const char* a_name);

		virtual void Initialize();  // 00

		void CreateTree(CombatBehaviorTreeNode* a_node);

		static TreeBuilder             AddNode(const char* a_name, CombatBehaviorTreeNode* a_node);
		static CombatBehaviorTreeNode* CreateLink(const char* a_name);
		static Actor*                  GetAttacker();
		static Actor*                  GetTarget();

		template <typename T>
		struct IsGameNode
		{
		private:
			static int detect(...);

			template <typename U>
			static decltype(std::declval<U>().Create()) detect(const U&);

		public:
			static constexpr bool value = std::is_same<CombatBehaviorTreeNode*, decltype(detect(std::declval<T>()))>::value;
		};

		template <typename Context, typename... Fields>
		class CreateContextImpl
		{
			using Node = CombatBehaviorTreeCreateContextNode<Context, Fields...>;

		public:
			template <typename... Args>
			[[nodiscard]] static Node* eval(Args&&... a_params)
			{
				if constexpr (IsGameNode<Node>::value)
					return static_cast<Node*>(Node::Create(std::forward<Args>(a_params)...));
				else
					return new Node(std::forward<Args>(a_params)...);
			}
		};

		template <typename Object, typename... Fields>
		[[nodiscard]] static auto CreateObject(auto&&... a_params)
		{
			using Node = CombatBehaviorTreeNodeObject<Object, Fields...>;

			if constexpr (Node::HAS_CREATE)
				return Node::Create(std::forward<decltype(a_params)>(a_params)...);
			else
				return new Node(std::forward<decltype(a_params)>(a_params)...);
		}

		template <typename Expr>
		[[nodiscard]] static auto CreateConditionalNode(auto&& a_expr, bool a_isSelector)
		{
			using Node = CombatBehaviorTreeConditionalNode<Expr>;

			if constexpr (Node::HAS_CREATE)
				return Node::Create(std::forward<decltype(a_expr)>(a_expr), a_isSelector);
			else
				return new Node(std::forward<decltype(a_expr)>(a_expr), a_isSelector);
		}

		template <typename Expr>
		static TreeBuilder AddConditionalSelectorNode(const char* a_name, auto&& a_expr, CombatBehaviorTreeNode* a_node)
		{
			auto condNode = CreateConditionalNode<Expr>(std::forward<decltype(a_expr)>(a_expr), true);
			char buf[260];
			sprintf_s(buf, 260, "ConditionalNode - %s", a_name);
			condNode->name = RE::BSFixedString(buf);
			condNode->AddChild(a_node);
			return AddNode(a_name, a_node);
		}

		template <typename Expr>
		static TreeBuilder AddConditionalSequenceNode(const char* a_name, auto&& a_expr, CombatBehaviorTreeNode* a_node)
		{
			auto condNode = CreateConditionalNode<Expr>(std::forward<decltype(a_expr)>(a_expr), false);
			char buf[260];
			sprintf_s(buf, 260, "ConditionalNode - %s", a_name);
			condNode->name = RE::BSFixedString(buf);
			condNode->AddChild(a_node);
			return AddNode(a_name, a_node);
		}

		template <typename Expr>
		static TreeBuilder AddRandomNode(const char* a_name, auto&& a_expr, CombatBehaviorTreeNode* a_node)
		{
			using MainExpr_t = CombatBehaviorExpression<CombatBehaviorFunc<bool (*)(float), Expr>>;

			auto randomNode = CreateConditionalNode<MainExpr_t>(MainExpr_t{ RandomBoolChance, { a_expr } }, true);
			char buf[260];
			sprintf_s(buf, 260, "ConditionalNode - %s", a_name);
			randomNode->name = RE::BSFixedString(buf);
			randomNode->AddChild(a_node);
			return AddNode(a_name, a_node);
		}

		template <typename T, typename Expr>
		[[nodiscard]] static auto CreateValueNodeT(auto&& a_expr)
		{
			return new CombatBehaviorTreeValueNodeT<T, Expr>(std::forward<decltype(a_expr)>(a_expr));
		}

		template <typename T, typename Expr>
		static TreeBuilder AddValueNodeT(const char* a_name, auto&& a_expr, CombatBehaviorTreeNode* a_node)
		{
			auto valueNode = CreateValueNodeT<T, Expr>(std::forward<decltype(a_expr)>(a_expr));
			a_node->name = a_name;
			char buf[260];
			sprintf_s(buf, 260, "ValueNode - %s", a_name);
			return AddNode(buf, valueNode);
		}

		// members
		BSFixedString           name;  // 08
		CombatBehaviorTreeNode* root;  // 10
	};
	static_assert(sizeof(CombatBehaviorTree) == 0x18);
}
