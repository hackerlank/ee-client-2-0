//-----------------------------------------------------------------------------
// Torque Forest Kit
// Copyright (C) Sickhead Games, LLC
//-----------------------------------------------------------------------------

#ifndef _IMPOSTERRENDERMGR_H_
#define _IMPOSTERRENDERMGR_H_

#ifndef _RENDERBINMANAGER_H_
#include "renderInstance/renderBinManager.h"
#endif
#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif
#ifndef _MATTEXTURETARGET_H_
#include "materials/matTextureTarget.h"
#endif

class TSLastDetail;
class GFXTextureObject;
class RenderPrePassMgr;
struct ImposterRenderInst;


/// This is the vertex definition used for TSLastDetail 
/// based imposter billboard geometry.
GFXDeclareVertexFormat( ImposterVertex )
{
   /// .xyz = imposter center
   /// .w = billboard corner index
   Point4F center;

   /// .x = half size
   /// .y = alpha fade out
   /// .z = object scale
   Point3F miscParams;

   /// .xyzw = object orientation quaternion
   Point4F rotQuat;
};


/// This is a special render manager for processing single 
/// billboard imposters typically generated by the tsLastDetail
/// class.  It tries to render them in large batches with as 
/// few state changes as possible.  For an example of use see 
/// TSLastDetail::render().
class RenderImposterMgr : public RenderBinManager
{
protected:
    
   typedef RenderBinManager Parent;

   const U32 mImposterBatchSize;

   static U32 smRendered;
   static U32 smBatches;
   static U32 smDrawCalls;
   static U32 smPolyCount;
   static U32 smRTChanges;

   struct ShaderState
   {
      ShaderState();
      ~ShaderState();

      bool init( const String &shaderName, const GFXStateBlockDesc *desc );

      void _onLMActivate( const char*, bool activate )
      {
         if ( activate && mShader )
            mShader = NULL;
      }

      GFXShaderRef mShader;

      MatTextureTargetRef mLightTarget;

      GFXStateBlockRef mSB;

      GFXShaderConstBufferRef mConsts;

      GFXShaderConstHandle *mWorldViewProjectSC;
      GFXShaderConstHandle *mCamPosSC;
      GFXShaderConstHandle *mCamRightSC;
      GFXShaderConstHandle *mCamUpSC;
      GFXShaderConstHandle *mSunDirSC;
      GFXShaderConstHandle *mFogDataSC;
      GFXShaderConstHandle *mParamsSC;
      GFXShaderConstHandle *mUVsSC;
      GFXShaderConstHandle *mLightColorSC;
      GFXShaderConstHandle *mAmbientSC;
      GFXShaderConstHandle *mLightTexRT;   
   };

   ShaderState mPrePassShaderState;

   ShaderState mDiffuseShaderState;

   GFXPrimitiveBufferHandle mIB;

   GFXVertexBufferHandle<ImposterVertex> mVB;
 
   void _innerRender( const SceneState *state, ShaderState &shaderState );

   void _renderPrePass( const SceneState *state, RenderPrePassMgr *prePassBin, bool startPrePass );

public:

   static const RenderInstType RIT_Imposter;

   RenderImposterMgr();
   RenderImposterMgr( F32 renderOrder, F32 processAddOrder );
   virtual ~RenderImposterMgr();

   // ConsoleObject
   DECLARE_CONOBJECT(RenderImposterMgr);
   static void initPersistFields();

   // RenderBinManager
   virtual void render( SceneState *state );
   virtual void sort();
};


/// This is a render instance for a TSLastDetail based imposter.
/// @see TSLastDetail
/// @see RenderImposterMgr
struct ImposterRenderInst : public RenderInst
{
   /// The detail object for this imposter.
   TSLastDetail *detail;

   /// The world space center point of the object which
   /// is used as the center of the imposter.
   Point3F center;

   /// The orientation of the object being impostered
   /// stored in a quaternion.
   QuatF rotQuat;

   /// The object scale to apply to the imposter.
   F32 scale;

   /// The half size of the imposter billboard.
   F32 halfSize;

   /// The alpha fade amount for this imposter.
   F32 alpha;

   /// Helper for setting this instance to a default state.
   void clear()
   {
      dMemset( this, 0, sizeof( ImposterRenderInst ) );
      type = RenderImposterMgr::RIT_Imposter;
   }
};

#endif // _TSIMPOSTERRENDERMGR_H_
