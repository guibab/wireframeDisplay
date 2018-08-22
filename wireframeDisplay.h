//-
// ==========================================================================
// Copyright 2015 Autodesk, Inc.  All rights reserved.
// Use of this software is subject to the terms of the Autodesk license agreement
// provided at the time of installation or download, or which otherwise
// accompanies this software in either electronic or hard copy form.
// ==========================================================================
//+

////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//
//
// This plug-in demonstrates how to draw a simple mesh like foot Print in an easy way.
//
// This easy way is supported in Viewport 2.0.
// In Viewport 2.0, MUIDrawManager can used to draw simple UI elements in method addUIDrawables().
//
// For comparison, you can reference a Maya Developer Kit sample named rawwireframeDisplayNode.
// In that sample, we draw the wireframeDisplay with OpenGL\DX in method
// rawwireframeDisplayDrawOverride::draw().
//
// Note the method
//   wireframeDisplay::draw()
// is only called in legacy default viewport to draw foot Print.
// while the methods
//   wireframeDisplayDrawOverride::prepareForDraw()
//   wireframeDisplayDrawOverride::addUIDrawables()
// are only called in Viewport 2.0 to prepare and draw foot Print.
//
////////////////////////////////////////////////////////////////////////

#include <maya/M3dView.h>
#include <maya/MColor.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MDistance.h>
#include <maya/MEulerRotation.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MPxLocatorNode.h>
#include <maya/MStatus.h>
#include <maya/MString.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MTypeId.h>
#include <maya/MVector.h>

// Viewport 2.0 includes
#include <assert.h>
#include <maya/MDrawContext.h>
#include <maya/MDrawRegistry.h>
#include <maya/MEventMessage.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MGlobal.h>
#include <maya/MHWGeometryUtilities.h>
#include <maya/MPointArray.h>
#include <maya/MPxDrawOverride.h>
#include <maya/MUserData.h>

#include <vector>

#define McheckErr(stat, msg)    \
    if (MS::kSuccess != stat) { \
        cerr << msg;            \
        return MS::kFailure;    \
    }

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Node implementation with standard viewport draw
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

class wireframeDisplay : public MPxLocatorNode {
   public:
    // wireframeDisplay(wireframeDisplayData& d)
    //	: data(d) {};
    wireframeDisplay();
    virtual ~wireframeDisplay();

    virtual MStatus compute(const MPlug& plug, MDataBlock& data);
    virtual void wireframeDisplay::postConstructor();
    virtual void draw(M3dView& view, const MDagPath& path, M3dView::DisplayStyle style,
                      M3dView::DisplayStatus status);
    // virtual MStatus         setDependentsDirty(const MPlug& dirty_plug, MPlugArray&
    // affected_plugs);

    virtual bool isBounded() const;
    virtual MBoundingBox boundingBox() const;
    virtual bool drawLast() const;
    virtual bool isTransparent() const;

    static void* creator();
    static MStatus initialize();

    static MObject _inMesh;
    // static  MObject         _inputColor;
    static MObject _inputAlpha;
    static MObject _lineWidth;
    static MObject _enableSmooth;

   public:
    static MTypeId id;
    static MString drawDbClassification;
    static MString drawRegistrantId;

   private:
    MObject _self;
    bool _update_attrs;

    // wireframeDisplayData&      data;
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Viewport 2.0 override implementation
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

class wireframeDisplayData : public MUserData {
   public:
    wireframeDisplayData() : MUserData(false){};  // don't delete after draw
    virtual ~wireframeDisplayData(){};

    virtual void get(const MObject&);
    virtual void getPlugs(const MObject&, bool getCol);

    MColor fColor;
    int lineWidth = 1;
    bool enableSmooth = true;
    float color[4] = {1.0f, 0.0f, 0.0f, 0.1f};
    float transparency = .5;
    MIntArray edgeVerticesIndices;
    MPointArray edgeVertices;

    MBoundingBox theBoundingBox;
    MObject inMesh;
    const float* mayaRawPoints;
    MHWRender::DisplayStatus displayStat;
};

class wireframeDisplayDrawOverride : public MHWRender::MPxDrawOverride {
   public:
    static MHWRender::MPxDrawOverride* Creator(const MObject& obj) {
        return new wireframeDisplayDrawOverride(obj);
    }

    virtual ~wireframeDisplayDrawOverride();

    virtual MHWRender::DrawAPI supportedDrawAPIs() const;

    virtual bool isBounded(const MDagPath& objPath, const MDagPath& cameraPath) const;

    virtual MBoundingBox boundingBox(const MDagPath& objPath, const MDagPath& cameraPath) const;

    virtual MUserData* prepareForDraw(const MDagPath& objPath, const MDagPath& cameraPath,
                                      const MHWRender::MFrameContext& frameContext,
                                      MUserData* oldData);

    virtual bool hasUIDrawables() const { return true; }
    virtual bool isTransparent() const { return true; }

    virtual void addUIDrawables(const MDagPath& objPath, MHWRender::MUIDrawManager& drawManager,
                                const MHWRender::MFrameContext& frameContext,
                                const MUserData* data);

    virtual bool traceCallSequence() const {
        // Return true if internal tracing is desired.
        return false;
    }
    virtual void handleTraceMessage(const MString& message) const {
        MGlobal::displayInfo("wireframeDisplayDrawOverride: " + message);

        // Some simple custom message formatting.
        fprintf(stderr, "wireframeDisplayDrawOverride: ");
        fprintf(stderr, message.asChar());
        fprintf(stderr, "\n");
    }

   private:
    wireframeDisplayDrawOverride(const MObject& obj);
    static void OnModelEditorChanged(void* clientData);

    wireframeDisplay* fwireframeDisplay;
    MCallbackId fModelEditorChangedCbId;
};
