//-----------------------------------------------------------------------------
// Torque Game Engine
// Copyright (C) GarageGames.com, Inc.
//-----------------------------------------------------------------------------
#ifndef _MATERIALPARAMETERS_H_
#define _MATERIALPARAMETERS_H_

#ifndef _GFXSHADER_H_
#include "gfx/gfxShader.h"
#endif

///
/// Similar class to GFXShaderConsts, but this is to describe generic material parameters.  
/// 
class MaterialParameterHandle
{
public:
   virtual ~MaterialParameterHandle() {}
   virtual const String& getName() const = 0;
   // This is similar to GFXShaderConstHandle, but a Material will always return a handle when
   // asked for one.  Even if it doesn't have that material parameter.  This is because after a
   // reInitMaterials call, the constants can change underneath the MatInstance.
   // Note: GFXShaderConstHandle actually works this way too, now.
   virtual bool isValid() const = 0;
   /// Returns -1 if this handle does not point to a Sampler.
   virtual S32 getSamplerRegister( U32 pass ) const = 0;
};

class MaterialParameters
{
public:
   MaterialParameters()
   {
      VECTOR_SET_ASSOCIATION( mShaderConstDesc );
   }
   virtual ~MaterialParameters() {}

   /// Returns our list of shader constants, the material can get this and just set the constants it knows about
   virtual const Vector<GFXShaderConstDesc>& getShaderConstDesc() const { return mShaderConstDesc; }

   /// @name Set shader constant values
   /// @{
   /// Actually set shader constant values
   /// @param name Name of the constant, this should be a name contained in the array returned in getShaderConstDesc,
   /// if an invalid name is used, it is ignored.
   virtual void set(MaterialParameterHandle* handle, const F32 f) {}
   virtual void set(MaterialParameterHandle* handle, const Point2F& fv) {}
   virtual void set(MaterialParameterHandle* handle, const Point3F& fv) {}
   virtual void set(MaterialParameterHandle* handle, const Point4F& fv) {}
   virtual void set(MaterialParameterHandle* handle, const ColorF& fv) {}
   virtual void set(MaterialParameterHandle* handle, const S32 f) {}
   virtual void set(MaterialParameterHandle* handle, const Point2I& fv) {}
   virtual void set(MaterialParameterHandle* handle, const Point3I& fv) {}
   virtual void set(MaterialParameterHandle* handle, const Point4I& fv) {}
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<F32>& fv) {}
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<Point2F>& fv) {}
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<Point3F>& fv) {}
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<Point4F>& fv) {}
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<S32>& fv) {}
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<Point2I>& fv) {}
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<Point3I>& fv) {}
   virtual void set(MaterialParameterHandle* handle, const AlignedArray<Point4I>& fv) {}
   virtual void set(MaterialParameterHandle* handle, const MatrixF& mat, const GFXShaderConstType matrixType = GFXSCT_Float4x4) {}
   virtual void set(MaterialParameterHandle* handle, const MatrixF* mat, const U32 arraySize, const GFXShaderConstType matrixType = GFXSCT_Float4x4) {}

   /// Returns the alignment value for the constType in bytes.
   virtual U32 getAlignmentValue(const GFXShaderConstType constType) { return 0; }

protected:   
   Vector<GFXShaderConstDesc> mShaderConstDesc;
};

#endif
