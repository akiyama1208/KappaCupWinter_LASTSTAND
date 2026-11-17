/*!
* @brief	静的オブジェクト。
*/


#include "k2EngineLowPreCompile.h"
#include "physics/PhysicsStaticObject.h"

namespace nsK2EngineLow {
	PhysicsStaticObject::PhysicsStaticObject()
	{
	}

	PhysicsStaticObject::~PhysicsStaticObject()
	{
	}

	void PhysicsStaticObject::CreateFromModel(
		Model& model,
		const Matrix& worldMatrix,
		const float restitution)
	{
		m_meshCollider.CreateFromModel(model, worldMatrix);

		RigidBodyInitData rbInfo;
		rbInfo.collider = &m_meshCollider;
		rbInfo.mass = 0.0f;
		rbInfo.restitution = restitution;

		m_rigidBody.Init(rbInfo);
	}

	// 箱型の静的当たり判定を作成する。
	void PhysicsStaticObject::CreateBox(
		const Vector3& size,
		const Vector3& position,
		const float restitution)
	{
		m_boxCollider.Create(size);

		RigidBodyInitData rbInfo;
		rbInfo.pos = position;
		rbInfo.rot = Quaternion::Identity;
		rbInfo.collider = &m_boxCollider;
		rbInfo.mass = 0.0f;
		rbInfo.restitution = restitution;

		m_rigidBody.Init(rbInfo);
	}
}