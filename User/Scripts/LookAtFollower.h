#include "../../Object/component.h"
#include "../../Object/Components/Camera/camera.h"

class LookAtFollower : public Component {
private:
	Camera* cam;
public:
	LookAtFollower(Camera* cam);
	void update();
};