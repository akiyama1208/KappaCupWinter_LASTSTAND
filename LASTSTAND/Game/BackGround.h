#pragma once
class BackGround : public IGameObject
{
public:
	BackGround() {}
	~BackGround() {}

public:
	bool Start() override;
	void Render(RenderContext& rc) override;

private:
	ModelRender m_modelRender;
	PhysicsStaticObject m_pos;
	PhysicsStaticObject physicsStaticObject;
};



