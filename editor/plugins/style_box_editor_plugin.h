/*************************************************************************/
/*  style_box_editor_plugin.h                                            */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef STYLE_BOX_EDITOR_PLUGIN_H
#define STYLE_BOX_EDITOR_PLUGIN_H

#include "editor/editor_inspector.h"
#include "editor/editor_node.h"
#include "scene/gui/option_button.h"
#include "scene/gui/texture_rect.h"
#include "scene/resources/style_box.h"

class StyleBoxPreview : public VBoxContainer {
	GDCLASS(StyleBoxPreview, VBoxContainer);

	Control *preview;
	Ref<StyleBox> stylebox;

	void _sb_changed();
	void _redraw();

protected:
	static void _bind_methods();

public:
	void edit(const Ref<StyleBox> &p_stylebox);

	StyleBoxPreview();
};

class StyleBoxQuadEditor : public EditorProperty {
	GDCLASS(StyleBoxQuadEditor, EditorProperty);

	Vector<String> properties;

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	void set_properties(Vector<String> p_properties);

	virtual Size2 get_minimum_size() const override;
	virtual void update_property() override;

	StyleBoxQuadEditor();
};

class ThemeStyleBoxEditor : public MarginContainer {
	GDCLASS(ThemeStyleBoxEditor, MarginContainer);

	Ref<StyleBox> edited_stylebox;

	Panel *main_bg;
	Button *close_button;
	Control *stylebox_preview;
	List<Label *> property_sections;
	List<Control *> property_editors;
	Map<Control *, Control *> property_icons;

	Label *background_props_label;
	HBoxContainer *background_color_hb;
	ColorPickerButton *background_color_picker;

	Label *border_props_label;
	HBoxContainer *border_color_hb;
	ColorPickerButton *border_color_picker;
	HBoxContainer *border_size_hb;
	SpinBox *border_size_t;
	SpinBox *border_size_r;
	SpinBox *border_size_b;
	SpinBox *border_size_l;
	HBoxContainer *border_blend_hb;
	CheckBox *border_blend;

	Label *corner_props_label;
	HBoxContainer *corner_radius_hb;
	SpinBox *corner_radius_tl;
	SpinBox *corner_radius_tr;
	SpinBox *corner_radius_bl;
	SpinBox *corner_radius_br;
	HBoxContainer *corner_detail_hb;
	SpinBox *corner_detail;

	Label *expand_props_label;
	HBoxContainer *expand_margin_hb;
	SpinBox *expand_margin_t;
	SpinBox *expand_margin_r;
	SpinBox *expand_margin_b;
	SpinBox *expand_margin_l;

	Label *margin_props_label;
	HBoxContainer *margin_hb;
	SpinBox *margin_t;
	SpinBox *margin_r;
	SpinBox *margin_b;
	SpinBox *margin_l;

	void _update_controls();
	void _draw_preview();
	SpinBox *_create_spinbox_editor(String p_property);
	void _create_control_icon(Control *p_control, const String p_base_icon, const String p_hl_icon);

	void _close_button_cbk();
	void _stylebox_property_changed(Variant p_value, String p_property);

protected:
	void _notification(int p_what);

public:
	void edit(Ref<StyleBox> p_stylebox);

	ThemeStyleBoxEditor();
};

class EditorInspectorPluginStyleBox : public EditorInspectorPlugin {
	GDCLASS(EditorInspectorPluginStyleBox, EditorInspectorPlugin);

public:
	virtual bool can_handle(Object *p_object) override;
	virtual void parse_begin(Object *p_object) override;
	virtual bool parse_property(Object *p_object, Variant::Type p_type, const String &p_path, PropertyHint p_hint, const String &p_hint_text, int p_usage, bool p_wide = false) override;
	virtual void parse_end() override;
};

class StyleBoxEditorPlugin : public EditorPlugin {
	GDCLASS(StyleBoxEditorPlugin, EditorPlugin);

public:
	virtual String get_name() const override { return "StyleBox"; }

	StyleBoxEditorPlugin(EditorNode *p_node);
};

#endif // STYLE_BOX_EDITOR_PLUGIN_H
