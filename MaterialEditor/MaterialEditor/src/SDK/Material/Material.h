#pragma once
#include "../Includes/Includes.h"

class IMaterialVar
{
public:
	typedef unsigned long FourCC;

	char *m_pStringVal;
	int m_intVal;
	Vector4D m_VecVal;

	uint8_t m_Type;
	uint8_t m_nNumVectorComps;
	uint8_t m_bFakeMaterialVar;
	uint8_t m_nTempIndex;
	//CUtlSymbol m_Name;

public:
	virtual ITexture			*GetTextureValue(void) = 0;
	virtual char const			*GetName(void) const = 0;
	virtual MaterialVarSym_t	GetNameAsSymbol() const = 0;
	virtual void				SetFloatValue(float val) = 0;
	virtual void				SetIntValue(int val) = 0;
	virtual void				SetStringValue(char const *val) = 0;
	virtual char const			*GetStringValue(void) const = 0;
	virtual void				SetFourCCValue(FourCC type, void *pData) = 0;
	virtual void				GetFourCCValue(FourCC *type, void **ppData) = 0;
	virtual void				SetVecValue(float const *val, int numcomps) = 0;
	virtual void				SetVecValue(float x, float y) = 0;
	virtual void				SetVecValue(float x, float y, float z) = 0;
	virtual void				SetVecValue(float x, float y, float z, float w) = 0;
	virtual void				GetLinearVecValue(float *val, int numcomps) const = 0;
	virtual void				SetTextureValue(ITexture *) = 0;
	virtual IMaterial			*GetMaterialValue(void) = 0;
	virtual void				SetMaterialValue(IMaterial *) = 0;
	virtual bool				IsDefined() const = 0;
	virtual void				SetUndefined() = 0;
	virtual void				SetMatrixValue(VMatrix const &matrix) = 0;
	virtual const				VMatrix &GetMatrixValue() = 0;
	virtual bool				MatrixIsIdentity() const = 0;
	virtual void				CopyFrom(IMaterialVar *pMaterialVar) = 0;
	virtual void				SetValueAutodetectType(char const *val) = 0;
	virtual IMaterial			*GetOwningMaterial() = 0;
	virtual void				SetVecComponentValue(float fVal, int nComponent) = 0;
	virtual int					GetIntValueInternal(void) const = 0;
	virtual float				GetFloatValueInternal(void) const = 0;
	virtual float const			*GetVecValueInternal() const = 0;
	virtual void				GetVecValueInternal(float *val, int numcomps) const = 0;
	virtual int					VectorSizeInternal() const = 0;
};

class IMaterial
{
public:
	virtual const char				*GetName() const = 0;
	virtual const char				*GetTextureGroupName() const = 0;
	virtual PreviewImageRetVal_t	GetPreviewImageProperties(int *width, int *height, ImageFormat *imageFormat, bool *isTranslucent) const = 0;
	virtual PreviewImageRetVal_t	GetPreviewImage(unsigned char *data, int width, int height, ImageFormat imageFormat) const = 0;
	virtual int						GetMappingWidth() = 0;
	virtual int						GetMappingHeight() = 0;
	virtual int						GetNumAnimationFrames() = 0;
	virtual bool					InMaterialPage(void) = 0;
	virtual	void					GetMaterialOffset(float *pOffset) = 0;
	virtual void					GetMaterialScale(float *pScale) = 0;
	virtual IMaterial				*GetMaterialPage(void) = 0;
	virtual IMaterialVar			*FindVar(const char *varName, bool *found, bool complain = true) = 0;
	virtual void					IncrementReferenceCount(void) = 0;
	virtual void					DecrementReferenceCount(void) = 0;
	virtual int 					GetEnumerationID(void) const = 0;
	virtual void					GetLowResColorSample(float s, float t, float *color) const = 0;
	virtual void					RecomputeStateSnapshots() = 0;
	virtual bool					IsTranslucent() = 0;
	virtual bool					IsAlphaTested() = 0;
	virtual bool					IsVertexLit() = 0;
	virtual VertexFormat_t			GetVertexFormat() const = 0;
	virtual bool					HasProxy(void) const = 0;
	virtual bool					UsesEnvCubemap(void) = 0;
	virtual bool					NeedsTangentSpace(void) = 0;
	virtual bool					NeedsPowerOfTwoFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool					NeedsFullFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool					NeedsSoftwareSkinning(void) = 0;
	virtual void					AlphaModulate(float alpha) = 0;
	virtual void					ColorModulate(float r, float g, float b) = 0;
	virtual void					SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) = 0;
	virtual bool					GetMaterialVarFlag(MaterialVarFlags_t flag) const = 0;
	virtual void					GetReflectivity(Vector &reflect) = 0;
	virtual bool					GetPropertyFlag(MaterialPropertyTypes_t type) = 0;
	virtual bool					IsTwoSided() = 0;
	virtual void					SetShader(const char *pShaderName) = 0;
	virtual int						GetNumPasses(void) = 0;
	virtual int						GetTextureMemoryBytes(void) = 0;
	virtual void					Refresh() = 0;
	virtual bool					NeedsLightmapBlendAlpha(void) = 0;
	virtual bool					NeedsSoftwareLighting(void) = 0;
	virtual int						ShaderParamCount() const = 0;
	virtual IMaterialVar			**GetShaderParams(void) = 0;
	virtual bool					IsErrorMaterial() const = 0;
	virtual void					SetUseFixedFunctionBakedLighting(bool bEnable) = 0;
	virtual float					GetAlphaModulation() = 0;
	virtual void					GetColorModulation(float *r, float *g, float *b) = 0;
	virtual MorphFormat_t			GetMorphFormat() const = 0;
};