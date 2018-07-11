#include "point.h"

MTypeId Point::id(0x00000900);
MObject Point::input_display;
MObject Point::input_box;
MObject Point::input_cross;
MObject Point::input_tick;
MObject Point::input_axis;
MObject Point::input_color;
MColorArray Point::_colors;

Point::Point() {}

void Point::postConstructor() {
    MObject self = thisMObject();
    MFnDependencyNode fn_node(self);
    fn_node.setName("pointShape#");

    _self = self;
    _update_attrs = true;
}

Point::~Point() {}

void* Point::creator() { return new Point(); }

MStatus Point::initialize() {
    MFnNumericAttribute nAttr;

    input_display = nAttr.create("display", "display", MFnNumericData::kBoolean, true);
    nAttr.setKeyable(true);
    addAttribute(input_display);

    input_box = nAttr.create("box", "box", MFnNumericData::kBoolean, false);
    nAttr.setKeyable(true);
    addAttribute(input_box);

    input_cross = nAttr.create("cross", "cross", MFnNumericData::kBoolean, true);
    nAttr.setKeyable(true);
    addAttribute(input_cross);

    input_tick = nAttr.create("tick", "tick", MFnNumericData::kBoolean, false);
    nAttr.setKeyable(true);
    addAttribute(input_tick);

    input_axis = nAttr.create("axis", "axis", MFnNumericData::kBoolean, false);
    nAttr.setKeyable(true);
    addAttribute(input_axis);

    MFnEnumAttribute eAttr;

    input_color = eAttr.create("color", "color", MFnData::kNumeric);

    eAttr.addField("Black", 0);
    eAttr.addField("Grey", 1);
    eAttr.addField("White", 2);
    eAttr.addField("Red", 3);
    eAttr.addField("Light red", 4);
    eAttr.addField("Dark red", 5);
    eAttr.addField("Green", 6);
    eAttr.addField("Light green", 7);
    eAttr.addField("Dark green", 8);
    eAttr.addField("Blue", 9);
    eAttr.addField("Light blue", 10);
    eAttr.addField("Dark blue", 11);
    eAttr.addField("Purple", 12);
    eAttr.addField("Magenta", 13);
    eAttr.addField("Brown", 14);
    eAttr.addField("Yellow", 15);
    eAttr.addField("Dark yellow", 16);
    eAttr.addField("Orange", 17);

    eAttr.setDefault(8);
    eAttr.setKeyable(true);
    eAttr.setStorable(true);
    addAttribute(input_color);

    _colors.append(MColor(0.0f, 0.0f, 0.0f));                                // black
    _colors.append(MColor(0.5f, 0.5f, 0.5f));                                // grey
    _colors.append(MColor(1.0f, 1.0f, 1.0f));                                // white
    _colors.append(MColor(1.0f, 0.0f, 0.0f));                                // red
    _colors.append(MColor(1.0f, 0.6899999976158142f, 0.6899999976158142f));  // light_red
    _colors.append(MColor(0.5f, 0.0f, 0.0f));                                // dark_red
    _colors.append(MColor(0.0f, 1.0f, 0.0f));                                // green
    _colors.append(MColor(0.5f, 1.0f, 0.5f));                                // light_green
    _colors.append(MColor(0.0f, 0.25f, 0.0f));                               // dark_green
    _colors.append(MColor(0.1889999955892563f, 0.6299999952316284f, 0.6299999952316284f));  // blue
    _colors.append(MColor(0.3919999897480011f, 0.8629999756813049f, 1.0f));    // light_blue
    _colors.append(MColor(0.0f, 0.01600000075995922f, 0.37599998712539673f));  // dark_blue
    _colors.append(MColor(0.25f, 0.0f, 0.25f));                                // purple
    _colors.append(MColor(1.0f, 0.0f, 1.0f));                                  // magenta
    _colors.append(MColor(0.75f, 0.2f, 0.0f));                                 // brown
    _colors.append(MColor(1.0f, 1.0f, 0.0f));                                  // yellow
    _colors.append(
        MColor(0.62117999792099f, 0.6299999952316284f, 0.1889999955892563f));  // dark_yellow
    _colors.append(MColor(1.0f, 0.5f, 0.0f));                                  // orange

    return MS::kSuccess;
}

bool Point::isBounded() const { return true; }

MBoundingBox Point::boundingBox() const {
    MBoundingBox bbox;
    bbox.expand(MVector(1.0, 0.0, 0.0));
    bbox.expand(MVector(-1.0, 0.0, 0.0));
    bbox.expand(MVector(0.0, 1.0, 0.0));
    bbox.expand(MVector(0.0, -1.0, 0.0));
    bbox.expand(MVector(0.0, 0.0, 1.0));
    bbox.expand(MVector(0.0, 0.0, -1.0));
    return bbox;
}

MStatus Point::compute(const MPlug& plug, MDataBlock& data) { return MS::kUnknownParameter; }

MStatus Point::setDependentsDirty(const MPlug& dirty_plug, MPlugArray& affected_plugs) {
    MString plug_name_MString = dirty_plug.partialName();
    std::string plug_name = plug_name_MString.asChar();
    if (plug_name == "display") {
        _update_attrs = true;
    } else if (plug_name == "box") {
        _update_attrs = true;
    } else if (plug_name == "cross") {
        _update_attrs = true;
    } else if (plug_name == "tick") {
        _update_attrs = true;
    } else if (plug_name == "axis") {
        _update_attrs = true;
    } else if (plug_name == "color") {
        _update_attrs = true;
    } else if (plug_name == "lpx") {
        _update_attrs = true;
    } else if (plug_name == "lpy") {
        _update_attrs = true;
    } else if (plug_name == "lpz") {
        _update_attrs = true;
    } else if (plug_name == "lsx") {
        _update_attrs = true;
    } else if (plug_name == "lsy") {
        _update_attrs = true;
    } else if (plug_name == "lsz") {
        _update_attrs = true;
    }
    return MS::kSuccess;
}

void Point::draw(M3dView& view, const MDagPath& mdag_path, M3dView::DisplayStyle display_style,
                 M3dView::DisplayStatus display_status) {
    if (Point::_update_attrs) {
        _display = MPlug(_self, Point::input_display).asBool();
        _box = MPlug(_self, Point::input_box).asBool();
        _cross = MPlug(_self, Point::input_cross).asBool();
        _tick = MPlug(_self, Point::input_tick).asBool();
        _axis = MPlug(_self, Point::input_axis).asBool();
        _color = MPlug(_self, Point::input_color).asShort();

        _tx = MPlug(_self, Point::localPositionX).asFloat();
        _ty = MPlug(_self, Point::localPositionY).asFloat();
        _tz = MPlug(_self, Point::localPositionZ).asFloat();

        _sx = MPlug(_self, Point::localScaleX).asFloat();
        _sy = MPlug(_self, Point::localScaleY).asFloat();
        _sz = MPlug(_self, Point::localScaleZ).asFloat();

        _update_attrs = false;
    }

    if (!_display) {
        return;
    }

    MColor color;
    switch (display_status) {
        case M3dView::kActive:
            color = MColor(1.0f, 1.0f, 1.0f);
            break;
        case M3dView::kLead:
            color = MColor(0.26f, 1.0f, 0.64f);
            break;
        case M3dView::kActiveAffected:
            color = MColor(0.783999979496f, 0.0f, 0.783999979496f);
            break;
        case M3dView::kTemplate:
            color = MColor(0.469999998808f, 0.469999998808f, 0.469999998808f);
            break;
        case M3dView::kActiveTemplate:
            color = MColor(1.0f, 0.689999997616f, 0.689999997616f);
            break;
        default:
            color = _colors[_color];
    }

    view.beginGL();

    if (_axis) {
        view.setDrawColor(MColor(1.0, 0, 0));
        view.drawText("x", MPoint(_sx + _tx, _ty, _tz), M3dView::kCenter);

        view.setDrawColor(MColor(0, 1.0, 0));
        view.drawText("y", MPoint(_tx, _sy + _ty, _tz), M3dView::kCenter);

        view.setDrawColor(MColor(0, 0, 1.0));
        view.drawText("z", MPoint(_tx, _ty, _sz + _tz), M3dView::kCenter);
    }

    glPushAttrib(GL_CURRENT_BIT);
    glBegin(GL_LINES);

    if (_box) {
        glColor3f(color.r, color.g, color.b);

        // Top rect
        glVertex3f(-_sx + _tx, _sy + _ty, -_sz + _tz);
        glVertex3f(_sx + _tx, _sy + _ty, -_sz + _tz);

        glVertex3f(_sx + _tx, _sy + _ty, -_sz + _tz);
        glVertex3f(_sx + _tx, _sy + _ty, _sz + _tz);

        glVertex3f(_sx + _tx, _sy + _ty, _sz + _tz);
        glVertex3f(-_sx + _tx, _sy + _ty, _sz + _tz);

        glVertex3f(-_sx + _tx, _sy + _ty, _sz + _tz);
        glVertex3f(-_sx + _tx, _sy + _ty, -_sz + _tz);

        // Bottom rect
        glVertex3f(-_sx + _tx, -_sy + _ty, -_sz + _tz);
        glVertex3f(_sx + _tx, -_sy + _ty, -_sz + _tz);

        glVertex3f(_sx + _tx, -_sy + _ty, -_sz + _tz);
        glVertex3f(_sx + _tx, -_sy + _ty, _sz + _tz);

        glVertex3f(_sx + _tx, -_sy + _ty, _sz + _tz);
        glVertex3f(-_sx + _tx, -_sy + _ty, _sz + _tz);

        glVertex3f(-_sx + _tx, -_sy + _ty, _sz + _tz);
        glVertex3f(-_sx + _tx, -_sy + _ty, -_sz + _tz);

        // Left rect
        glVertex3f(-_sx + _tx, -_sy + _ty, -_sz + _tz);
        glVertex3f(-_sx + _tx, _sy + _ty, -_sz + _tz);

        glVertex3f(-_sx + _tx, _sy + _ty, -_sz + _tz);
        glVertex3f(-_sx + _tx, _sy + _ty, _sz + _tz);

        glVertex3f(-_sx + _tx, _sy + _ty, _sz + _tz);
        glVertex3f(-_sx + _tx, -_sy + _ty, _sz + _tz);

        glVertex3f(-_sx + _tx, -_sy + _ty, _sz + _tz);
        glVertex3f(-_sx + _tx, -_sy + _ty, -_sz + _tz);

        // Right rect
        glVertex3f(_sx + _tx, -_sy + _ty, -_sz + _tz);
        glVertex3f(_sx + _tx, _sy + _ty, -_sz + _tz);

        glVertex3f(_sx + _tx, _sy + _ty, -_sz + _tz);
        glVertex3f(_sx + _tx, _sy + _ty, _sz + _tz);

        glVertex3f(_sx + _tx, _sy + _ty, _sz + _tz);
        glVertex3f(_sx + _tx, -_sy + _ty, _sz + _tz);

        glVertex3f(_sx + _tx, -_sy + _ty, _sz + _tz);
        glVertex3f(_sx + _tx, -_sy + _ty, -_sz + _tz);
    }

    if (_cross) {
        glColor3f(color.r, color.g, color.b);

        glVertex3f(_tx, -_sy + _ty, _tz);
        glVertex3f(_tx, _sy + _ty, _tz);

        glVertex3f(-_sx + _tx, _ty, _tz);
        glVertex3f(_sx + _tx, _ty, _tz);

        glVertex3f(_tx, _ty, -_sz + _tz);
        glVertex3f(_tx, _ty, _sz + _tz);
    }

    if (_tick) {
        glColor3f(color.r, color.g, color.b);

        glVertex3f((-_sx * 0.05f) + _tx, (_sy * 0.05f) + _ty, _tz);
        glVertex3f((_sx * 0.05f) + _tx, (-_sy * 0.05f) + _ty, _tz);

        glVertex3f((_sx * 0.05f) + _tx, (_sy * 0.05f) + _ty, _tz);
        glVertex3f((-_sx * 0.05f) + _tx, (-_sy * 0.05f) + _ty, _tz);

        glVertex3f(_tx, (_sy * 0.05f) + _ty, (-_sz * 0.05f) + _tz);
        glVertex3f(_tx, (-_sy * 0.05f) + _ty, (_sz * 0.05f) + _tz);

        glVertex3f(_tx, (_sy * 0.05f) + _ty, (_sz * 0.05f) + _tz);
        glVertex3f(_tx, (-_sy * 0.05f) + _ty, (-_sz * 0.05f) + _tz);

        glVertex3f((_sx * 0.05f) + _tx, _ty, (-_sz * 0.05f) + _tz);
        glVertex3f((-_sx * 0.05f) + _tx, _ty, (_sz * 0.05f) + _tz);

        glVertex3f((_sx * 0.05f) + _tx, _ty, (_sz * 0.05f) + _tz);
        glVertex3f((-_sx * 0.05f) + _tx, _ty, (-_sz * 0.05f) + _tz);
    }

    if (_axis) {
        glColor3f(color.r, color.g, color.b);

        if (display_status == M3dView::kDormant) {
            glColor3f(1.0f, 0.0f, 0.0f);
        }
        glVertex3f(_tx, _ty, _tz);
        glVertex3f(_sx + _tx, _ty, _tz);

        if (display_status == M3dView::kDormant) {
            glColor3f(0.0f, 1.0f, 0.0f);
        }
        glVertex3f(_tx, _ty, _tz);
        glVertex3f(_tx, _sy + _ty, _tz);

        if (display_status == M3dView::kDormant) {
            glColor3f(0.0f, 0.0f, 1.0f);
        }
        glVertex3f(_tx, _ty, _tz);
        glVertex3f(_tx, _ty, _sz + _tz);
    }

    glEnd();
    glPopAttrib();

    view.endGL();
}