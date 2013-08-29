/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2013 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef __CompositorPassScene_H__
#define __CompositorPassScene_H__

#include "OgreHeaderPrefix.h"

#include "Compositor/Pass/OgreCompositorPass.h"
#include "Compositor/Pass/PassScene/OgreCompositorPassSceneDef.h"

namespace Ogre
{
	class RenderTarget;
	class Camera;
	class CompositorShadowNode;
	class CompositorWorkspace;

	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Effects
	*  @{
	*/

	/** Implementation of CompositorPass
		This implementation will perform main rendering, selecting several parameters
		(like viewport's visibility mask, first and last render queue to render) it
		will render the main scene. into the specified RenderTarget
    @author
		Matias N. Goldberg
    @version
        1.0
    */
	class _OgreExport CompositorPassScene : public CompositorPass
	{
	protected:
		CompositorShadowNode	*mShadowNode;
		Camera					*mCamera;
		bool					mUpdateShadowNode;

		CompositorWorkspace const *mWorkspace;

	public:
		/** Constructor
		@param definition
		@param defaultCamera
			Used when the definition's camera name is empty
		@param workspace
			Workspace that ultimately owns us
		@param target
			The RenderTarget we're supposed to draw to. Can be RenderWindow, RenderTexture, MRT, etc
		*/
		CompositorPassScene( const CompositorPassSceneDef *definition, Camera *defaultCamera,
								const CompositorWorkspace *workspace, RenderTarget *target );
		~CompositorPassScene();

		virtual void execute();

		void _setCustomCamera( Camera *camera )					{ mCamera = camera; }

		const CompositorPassSceneDef* getDefinition() const		{ return mDefinition; }

	private:
		CompositorPassSceneDef const *mDefinition;
	};

	/** @} */
	/** @} */
}

#include "OgreHeaderSuffix.h"

#endif