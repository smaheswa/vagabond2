// Copyright (C) 2021 Helen Ginn

#ifndef __Slip__SnowGL__
#define __Slip__SnowGL__

#include <vagabond/utils/glm_import.h>
#include <GLES3/gl32.h>

#include "HasRenderables.h"

class SnowGL : public HasRenderables
{
public:
	SnowGL();
	virtual ~SnowGL();
	
	void setDims(int w, int h)
	{
		_w = w;
		_h = h;
		updateProjection();
	}
	
	int width()
	{
		return _w;
	}
	
	int height()
	{
		return _h;
	}
	
	void preparePanels(int n);
	void addPanel();
	
	void rotate(double x, double y, double z);
	void setInvertZ(bool z)
	{
		_invertZ = z;
	}
	
	void setAcceptsFocus(bool accepts)
	{
		_acceptsFocus = accepts;
	}
	
	void setZNear(double near)
	{
		_zNear = near;
		updateProjection();
	}
	
	void setZFar(double far)
	{
		_zFar = far;
		updateProjection();
	}
	
	float getTime()
	{
		return _time;
	}
	
	glm::mat4x4 getModel()
	{
		return _model;
	}
	
	glm::vec3 getCentre()
	{
		return _centre;
	}
	
	glm::mat4x4 getProjection()
	{
		return _proj;
	}

	void saveImage(std::string filename);

	glm::vec3 transformPosByModel(glm::vec3 pos)
	{
		glm::vec3 newPos = glm::vec3(_model * glm::vec4(pos, 1.));
		return newPos;
	}
	
	glm::mat4x4 lightMat()
	{
		return _lightMat;
	}
	
	GLuint depthMap()
	{
		return _depthMap;
	}
	
	GLuint getOverrideProgram();
	
	size_t sceneTextureCount()
	{
		return _sceneMapCount;
	}
	
	GLuint sceneTexture(int i)
	{
		return _sceneMap[i];
	}
	
	GLuint sceneDepth()
	{
		return _sceneDepth;
	}
	
	void pause();
	void restartTimer();
	
	void updateProjection(float side = 0.5);

	bool checkErrors(std::string what = "");
	virtual void render();
protected:
	void shadowProgram();
	void prepareShadowBuffer();
	void preparePingPongBuffers(int w_over = -1, int h_over = -1);
	void prepareRenderToTexture(size_t count);
	void resizeTextures(int w_over = -1, int h_over = -1);
	void renderShadows();
	void renderScene();

	virtual void resizeGL(int w, int h);
	void convertCoords(double *x, double *y);

	virtual void changeProjectionForLight(int i) {};

	void zoom(float x, float y, float z);
	void updateCamera();
	void setupCamera();
	void time();

	GLuint _depthMap;
	GLuint _depthFbo;

	GLuint _sceneMap[8];
	GLuint _sceneDepth;
	GLuint _sceneFbo;
	size_t _sceneMapCount;
	
	GLuint _pingPongMap[2];
	GLuint _pingPongFbo[2];
	
	float _camAlpha, _camBeta, _camGamma;
	float _zNear;
	float _zFar;
	float _time;
	bool _invertZ;

	glm::vec3 _centre;
	glm::vec3 _translation;
	glm::vec3 _transOnly;
	glm::vec3 _totalCentroid;

	glm::mat4x4 _lightMat;
	glm::mat4x4 _model;
	glm::mat4x4 _proj;
	glm::mat4x4 _unproj;
	
	GLuint _shadowProgram;
	
	Renderable *_shadowObj;

	double _a; double _r; double _g; double _b;

	double _lastX; double _lastY;
	double _shadowing;
	bool _left;
	bool _right;
	bool _controlPressed;
	bool _shiftPressed;
	bool _acceptsFocus;
	
	int _w;
	int _h;
	
	static bool _setup;
};


#endif
