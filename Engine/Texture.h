#include <DirectXMath.h>

class Texture{

private:
	ID3D11ShaderResourceView* mColorTexResourceView;
	ID3D11SamplerState* mColorTexSamplerState;

	int width;
	int height;
public:
	Texture();
	~Texture();

	//The functions here handle initializing and shutdown of the model's vertex and index buffers and model name
	bool Initialize();
	void Shutdown();
	//The Render function puts the model geometry on the video card to prepare it for drawing by the color shader.
	void Render();

	int getWidth() const;
	int getHeight() const;


};