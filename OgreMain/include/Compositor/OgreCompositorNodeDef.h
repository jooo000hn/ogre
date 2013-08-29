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

#ifndef __CompositorNodeDef_H__
#define __CompositorNodeDef_H__

#include "OgreHeaderPrefix.h"
#include "Compositor/OgreTextureDefinition.h"
#include "Compositor/Pass/OgreCompositorPassDef.h"

namespace Ogre
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Effects
	*  @{
	*/

	typedef vector<uint32>::type				ChannelMappings;
	typedef vector<CompositorTargetDef>::type	CompositorTargetDefVec;

	/** Compositor nodes are the core subject of compositing.
		TODO: Describe!!!
	@remarks
		We own the local textures, so it's our job to destroy them
	@author
		Matias N. Goldberg
    @version
        1.0
    */
	class _OgreExport CompositorNodeDef : public TextureDefinitionBase
	{
	protected:
		friend class CompositorNode;

		IdString	mName;

		/** Tells where to grab the RenderTarget from for the output channel.
			They can come either from an input channel, or from local textures.
			The first 30 bits indicate the channel #, the last 30th & 31sts bit are used
			to determine whether it comes from the input channel, the local texture, or
			it is global.
		*/
		ChannelMappings			mOutChannelMapping;
		CompositorTargetDefVec	mTargetPasses;

	public:
		CompositorNodeDef( IdString name ) : TextureDefinitionBase( TEXTURE_LOCAL ), mName( mName ) {}

		IdString getName() const							{ return mName; }

		/// See http://www.research.att.com/~bs/bs_faq2.html#overloadderived
		using TextureDefinitionBase::getTextureSource;
		/** Retrieves in which container to look for when wanting to know the output texture
			using the mappings from input/local texture -> output.
		@param outputChannel [in]
			The output channel we want to know about
		@param index [out]
			The index at the container in which the texture associated with the output channel
			is stored
		@param textureSource [out]
			Where to get this texture from
		*/
		void getTextureSource( size_t outputChannel, size_t &index, TextureSource &textureSource ) const;

		/** Reserves enough memory for all passes (efficient allocation, better than using
			linked lists or other containers with two level of indirections)
		@remarks
			Calling this function is not obligatory, but recommended
		@param numPasses
			The number of passes expected to contain.
		*/
		void setNumTargetPass( size_t numPasses )			{ mTargetPasses.reserve( numPasses ); }

		/** Adds a new Target pass.
		@remarks
			WARNING: Calling this function may invalidate all previous returned pointers
			unless you've properly called setNumTargetPass
		@param renderTargetName
			We need the full name, not just the hash; so we can check whether it has the global_ prefix
		*/
		CompositorTargetDef* addTargetPass( const String &renderTargetName );

		/** Issues warnings about correct usage except if serious setup errors show up, and
			finalize whatever we couldn't do because not all definitions were loaded when
			we were created.
		*/
		virtual void _validateAndFinish(void);
	};

	/** @} */
	/** @} */
}

#include "OgreHeaderSuffix.h"

#endif