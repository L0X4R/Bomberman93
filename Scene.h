#ifndef SCENE_H
#define SCENE_H

class Scene
{
protected:
	bool needReinit;

public:
	Scene();
	~Scene();

	void init();

	void reinit();

	virtual void render() = 0;

	virtual void update() = 0;

	virtual void initLevel();

	void setReinit(bool reload = true) { needReinit = reload; };
	bool getReinit() { return needReinit; };
};

#endif

