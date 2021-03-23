/*************************************************************************/
/*  style_box_editor_plugin.cpp                                          */
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

#include "style_box_editor_plugin.h"

#include "editor/editor_scale.h"

void StyleBoxPreview::_sb_changed() {
	preview->update();
}

void StyleBoxPreview::_redraw() {
	if (stylebox.is_valid()) {
		Rect2 preview_rect = preview->get_rect();

		// Re-adjust preview panel to fit all drawn content
		Rect2 draw_rect = stylebox->get_draw_rect(preview_rect);
		preview_rect.size -= draw_rect.size - preview_rect.size;
		preview_rect.position -= draw_rect.position - preview_rect.position;

		preview->draw_style_box(stylebox, preview_rect);
	}
}

void StyleBoxPreview::_bind_methods() {
}

void StyleBoxPreview::edit(const Ref<StyleBox> &p_stylebox) {
	if (stylebox.is_valid()) {
		stylebox->disconnect("changed", callable_mp(this, &StyleBoxPreview::_sb_changed));
	}

	stylebox = p_stylebox;
	if (p_stylebox.is_valid()) {
		preview->add_theme_style_override("panel", stylebox);
		stylebox->connect("changed", callable_mp(this, &StyleBoxPreview::_sb_changed));
	}

	_sb_changed();
}

StyleBoxPreview::StyleBoxPreview() {
	preview = memnew(Control);
	preview->set_custom_minimum_size(Size2(0, 150 * EDSCALE));
	preview->set_clip_contents(true);
	preview->connect("draw", callable_mp(this, &StyleBoxPreview::_redraw));
	add_margin_child(TTR("Preview:"), preview);
}

void StyleBoxQuadEditor::_notification(int p_what) {
	//
}

void StyleBoxQuadEditor::_bind_methods() {
	//
}

void StyleBoxQuadEditor::set_properties(Vector<String> p_properties) {
	properties = p_properties;
}

Size2 StyleBoxQuadEditor::get_minimum_size() const {
	return Size2(0, 100);
}

void StyleBoxQuadEditor::update_property() {
	//
}

StyleBoxQuadEditor::StyleBoxQuadEditor() {
	HBoxContainer *main_hb = memnew(HBoxContainer);
	set_bottom_editor(main_hb);

	EditorSpinSlider *first_prop = memnew(EditorSpinSlider);
	first_prop->set_h_size_flags(SIZE_EXPAND_FILL);
	main_hb->add_child(first_prop);

	EditorSpinSlider *second_prop = memnew(EditorSpinSlider);
	second_prop->set_h_size_flags(SIZE_EXPAND_FILL);
	main_hb->add_child(second_prop);

	EditorSpinSlider *third_prop = memnew(EditorSpinSlider);
	third_prop->set_h_size_flags(SIZE_EXPAND_FILL);
	main_hb->add_child(third_prop);

	EditorSpinSlider *fourth_prop = memnew(EditorSpinSlider);
	fourth_prop->set_h_size_flags(SIZE_EXPAND_FILL);
	main_hb->add_child(fourth_prop);
}

void ThemeStyleBoxEditor::_update_controls() {
	Ref<StyleBoxEmpty> sb_empty = edited_stylebox;
	Ref<StyleBoxLine> sb_line = edited_stylebox;
	Ref<StyleBoxFlat> sb_flat = edited_stylebox;
	Ref<StyleBoxTexture> sb_texture = edited_stylebox;

	if (sb_flat.is_valid()) {
		background_props_label->show();
		background_color_hb->show();
		background_color_picker->set_pick_color(sb_flat->get_bg_color());

		border_props_label->show();
		border_color_hb->show();
		border_color_picker->set_pick_color(sb_flat->get_border_color());
		border_size_hb->show();
		border_size_t->set_value(sb_flat->get_border_width(SIDE_TOP));
		border_size_r->set_value(sb_flat->get_border_width(SIDE_RIGHT));
		border_size_b->set_value(sb_flat->get_border_width(SIDE_BOTTOM));
		border_size_l->set_value(sb_flat->get_border_width(SIDE_LEFT));
		border_blend_hb->show();
		border_blend->set_pressed(sb_flat->get_border_blend());

		corner_props_label->show();
		corner_radius_hb->show();
		corner_radius_tl->set_value(sb_flat->get_corner_radius(CORNER_TOP_LEFT));
		corner_radius_tr->set_value(sb_flat->get_corner_radius(CORNER_TOP_RIGHT));
		corner_radius_bl->set_value(sb_flat->get_corner_radius(CORNER_BOTTOM_LEFT));
		corner_radius_br->set_value(sb_flat->get_corner_radius(CORNER_BOTTOM_RIGHT));
		corner_detail_hb->show();
		corner_detail->set_value(sb_flat->get_corner_detail());

		expand_props_label->show();
		expand_margin_hb->show();
		expand_margin_t->set_value(sb_flat->get_expand_margin_size(SIDE_TOP));
		expand_margin_r->set_value(sb_flat->get_expand_margin_size(SIDE_RIGHT));
		expand_margin_b->set_value(sb_flat->get_expand_margin_size(SIDE_BOTTOM));
		expand_margin_l->set_value(sb_flat->get_expand_margin_size(SIDE_LEFT));

		margin_props_label->show();
		margin_hb->show();
		margin_t->set_value(sb_flat->get_default_margin(SIDE_TOP));
		margin_r->set_value(sb_flat->get_default_margin(SIDE_RIGHT));
		margin_b->set_value(sb_flat->get_default_margin(SIDE_BOTTOM));
		margin_l->set_value(sb_flat->get_default_margin(SIDE_LEFT));
	} else {
		background_props_label->hide();
		background_color_hb->hide();

		border_props_label->hide();
		border_color_hb->hide();
		border_size_hb->hide();
		border_blend_hb->hide();

		corner_props_label->hide();
		corner_radius_hb->hide();
		corner_detail_hb->hide();

		expand_props_label->hide();
		expand_margin_hb->hide();
		margin_props_label->hide();
		margin_hb->hide();
	}

	stylebox_preview->update();
}

void ThemeStyleBoxEditor::_draw_preview() {
	stylebox_preview->draw_style_box(edited_stylebox, Rect2(Point2(0, 0), stylebox_preview->get_size()));
}

SpinBox *ThemeStyleBoxEditor::_create_spinbox_editor(String p_property) {
	SpinBox *editor = memnew(SpinBox);
	editor->set_h_size_flags(SIZE_EXPAND_FILL);
	editor->connect("value_changed", callable_mp(this, &ThemeStyleBoxEditor::_stylebox_property_changed), varray(p_property));
	property_editors.push_back(editor);

	return editor;
}

void ThemeStyleBoxEditor::_create_control_icon(Control *p_control, const String p_base_icon, const String p_hl_icon) {
	if (property_icons.has(p_control)) {
		return;
	}

	CenterContainer *icon_mc = memnew(CenterContainer);
	icon_mc->set_custom_minimum_size(Size2(32, 32) * EDSCALE);
	icon_mc->set_stretch_ratio(2.0);

	TextureRect *icon = memnew(TextureRect);
	icon->set_custom_minimum_size(Size2(32, 32) * EDSCALE);
	icon->set_stretch_mode(TextureRect::STRETCH_KEEP_CENTERED);
	icon->set_meta("_editor_icon", p_base_icon);
	icon->set_texture(get_theme_icon(p_base_icon, "EditorIcons"));
	icon->set_modulate(Color(0.35, 0.35, 0.35));
	icon_mc->add_child(icon);

	TextureRect *icon_hl = memnew(TextureRect);
	icon_hl->set_custom_minimum_size(Size2(32, 32) * EDSCALE);
	icon_hl->set_stretch_mode(TextureRect::STRETCH_KEEP_CENTERED);
	icon_hl->set_meta("_editor_icon", p_hl_icon);
	icon_hl->set_texture(get_theme_icon(p_hl_icon, "EditorIcons"));
	icon_mc->add_child(icon_hl);

	p_control->get_parent()->add_child(icon_mc);
	p_control->get_parent()->move_child(icon_mc, p_control->get_index());
	property_icons[p_control] = icon_mc;
}

void ThemeStyleBoxEditor::_close_button_cbk() {
	hide();
}

void ThemeStyleBoxEditor::_stylebox_property_changed(Variant p_value, String p_property) {
	edited_stylebox->set(p_property, p_value);
	stylebox_preview->update();
}

void ThemeStyleBoxEditor::edit(Ref<StyleBox> p_stylebox) {
	if (edited_stylebox == p_stylebox) {
		return;
	}

	edited_stylebox = p_stylebox;
	_update_controls();
}

void ThemeStyleBoxEditor::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_READY:
		case NOTIFICATION_THEME_CHANGED: {
			main_bg->add_theme_style_override("panel", get_theme_stylebox("bg", "Tree"));
			close_button->set_icon(get_theme_icon("Close", "EditorIcons"));

			Color icon_hl_color = get_theme_color("accent_color", "Editor");
			icon_hl_color.set_s(0.9);
			icon_hl_color.set_v(0.9);

			for (Map<Control *, Control *>::Element *E = property_icons.front(); E; E = E->next()) {
				Control *icon_mc = E->get();

				TextureRect *icon = Object::cast_to<TextureRect>(icon_mc->get_child(0));
				icon->set_texture(get_theme_icon(icon->get_meta("_editor_icon"), "EditorIcons"));

				TextureRect *icon_hl = Object::cast_to<TextureRect>(icon_mc->get_child(1));
				icon_hl->set_texture(get_theme_icon(icon_hl->get_meta("_editor_icon"), "EditorIcons"));
				icon_hl->set_modulate(icon_hl_color);
			}

			Ref<StyleBoxFlat> section_style = memnew(StyleBoxFlat);
			section_style->set_bg_color(get_theme_color("prop_subsection", "Editor"));
			section_style->set_default_margin(SIDE_LEFT, 4.0 * EDSCALE);

			for (List<Label *>::Element *E = property_sections.front(); E; E = E->next()) {
				Label *section_label = E->get();
				section_label->add_theme_style_override("normal", section_style);
			}

			Ref<StyleBoxFlat> line_edit_style = get_theme_stylebox("normal", "LineEdit")->duplicate();
			if (line_edit_style.is_valid()) {
				line_edit_style->set_bg_color(get_theme_color("dark_color_3", "Editor"));
			}

			Ref<StyleBoxFlat> color_picker_style = get_theme_stylebox("normal", "Button")->duplicate();
			if (color_picker_style.is_valid()) {
				color_picker_style->set_bg_color(get_theme_color("dark_color_3", "Editor"));
			}

			for (List<Control *>::Element *E = property_editors.front(); E; E = E->next()) {
				SpinBox *spinbox_editor = Object::cast_to<SpinBox>(E->get());
				if (spinbox_editor) {
					spinbox_editor->get_line_edit()->add_theme_style_override("normal", line_edit_style);
				}
				ColorPickerButton *color_picker_editor = Object::cast_to<ColorPickerButton>(E->get());
				if (color_picker_editor) {
					color_picker_editor->add_theme_style_override("normal", color_picker_style);
				}
			}
		} break;
	}
}

ThemeStyleBoxEditor::ThemeStyleBoxEditor() {
	main_bg = memnew(Panel);
	add_child(main_bg);

	MarginContainer *main_mc = memnew(MarginContainer);
	main_mc->add_theme_constant_override("margin_top", 6.0 * EDSCALE);
	main_mc->add_theme_constant_override("margin_right", 4.0 * EDSCALE);
	main_mc->add_theme_constant_override("margin_bottom", 6.0 * EDSCALE);
	main_mc->add_theme_constant_override("margin_left", 4.0 * EDSCALE);
	add_child(main_mc);

	VBoxContainer *main_vb = memnew(VBoxContainer);
	main_vb->set_h_size_flags(SIZE_EXPAND_FILL);
	main_mc->add_child(main_vb);

	//// Preview.
	CenterContainer *stylebox_preview_cc = memnew(CenterContainer);
	main_vb->add_child(stylebox_preview_cc);
	stylebox_preview = memnew(Control);
	stylebox_preview->set_custom_minimum_size(Size2(120, 120) * EDSCALE);
	stylebox_preview_cc->add_child(stylebox_preview);
	stylebox_preview->connect("draw", callable_mp(this, &ThemeStyleBoxEditor::_draw_preview));

	//// Background.
	background_props_label = memnew(Label);
	background_props_label->set_text(TTR("Background Properties"));
	main_vb->add_child(background_props_label);
	background_props_label->hide();
	property_sections.push_back(background_props_label);

	background_color_hb = memnew(HBoxContainer);
	main_vb->add_child(background_color_hb);
	background_color_hb->hide();
	Label *background_color_label = memnew(Label);
	background_color_label->set_h_size_flags(SIZE_EXPAND_FILL);
	background_color_label->set_text(TTR("Color"));
	background_color_hb->add_child(background_color_label);
	background_color_picker = memnew(ColorPickerButton);
	background_color_picker->set_h_size_flags(SIZE_EXPAND_FILL);
	background_color_hb->add_child(background_color_picker);
	background_color_picker->connect("color_changed", callable_mp(this, &ThemeStyleBoxEditor::_stylebox_property_changed), varray("bg_color"));
	property_editors.push_back(background_color_picker);

	//// Border.
	border_props_label = memnew(Label);
	border_props_label->set_text(TTR("Border Properties"));
	main_vb->add_child(border_props_label);
	border_props_label->hide();
	property_sections.push_back(border_props_label);

	border_color_hb = memnew(HBoxContainer);
	main_vb->add_child(border_color_hb);
	border_color_hb->hide();
	Label *border_color_label = memnew(Label);
	border_color_label->set_h_size_flags(SIZE_EXPAND_FILL);
	border_color_label->set_text(TTR("Color"));
	border_color_hb->add_child(border_color_label);
	border_color_picker = memnew(ColorPickerButton);
	border_color_picker->set_h_size_flags(SIZE_EXPAND_FILL);
	border_color_hb->add_child(border_color_picker);
	border_color_picker->connect("color_changed", callable_mp(this, &ThemeStyleBoxEditor::_stylebox_property_changed), varray("border_color"));
	property_editors.push_back(border_color_picker);

	border_size_hb = memnew(HBoxContainer);
	main_vb->add_child(border_size_hb);
	border_size_hb->hide();
	border_size_t = _create_spinbox_editor("border_width_top");
	border_size_hb->add_child(border_size_t);
	_create_control_icon(border_size_t, "StyleBoxBorder", "StyleBoxBorderTop");
	border_size_r = _create_spinbox_editor("border_width_right");
	border_size_hb->add_child(border_size_r);
	_create_control_icon(border_size_r, "StyleBoxBorder", "StyleBoxBorderRight");
	border_size_b = _create_spinbox_editor("border_width_bottom");
	border_size_hb->add_child(border_size_b);
	_create_control_icon(border_size_b, "StyleBoxBorder", "StyleBoxBorderBottom");
	border_size_l = _create_spinbox_editor("border_width_left");
	border_size_hb->add_child(border_size_l);
	_create_control_icon(border_size_l, "StyleBoxBorder", "StyleBoxBorderLeft");

	border_blend_hb = memnew(HBoxContainer);
	main_vb->add_child(border_blend_hb);
	border_blend_hb->hide();
	border_blend = memnew(CheckBox);
	border_blend->set_h_size_flags(SIZE_EXPAND_FILL);
	border_blend->set_text(TTR("Blend"));
	border_blend_hb->add_child(border_blend);
	border_blend->connect("toggled", callable_mp(this, &ThemeStyleBoxEditor::_stylebox_property_changed), varray("border_blend"));

	//// Corner.
	corner_props_label = memnew(Label);
	corner_props_label->set_text(TTR("Corner Properties"));
	main_vb->add_child(corner_props_label);
	corner_props_label->hide();
	property_sections.push_back(corner_props_label);

	corner_radius_hb = memnew(HBoxContainer);
	main_vb->add_child(corner_radius_hb);
	corner_radius_hb->hide();
	corner_radius_tl = _create_spinbox_editor("corner_radius_top_left");
	corner_radius_hb->add_child(corner_radius_tl);
	_create_control_icon(corner_radius_tl, "StyleBoxCorner", "StyleBoxCornerTopLeft");
	corner_radius_tr = _create_spinbox_editor("corner_radius_top_right");
	corner_radius_hb->add_child(corner_radius_tr);
	_create_control_icon(corner_radius_tr, "StyleBoxCorner", "StyleBoxCornerTopRight");
	corner_radius_bl = _create_spinbox_editor("corner_radius_bottom_left");
	corner_radius_hb->add_child(corner_radius_bl);
	_create_control_icon(corner_radius_bl, "StyleBoxCorner", "StyleBoxCornerBottomLeft");
	corner_radius_br = _create_spinbox_editor("corner_radius_bottom_right");
	corner_radius_hb->add_child(corner_radius_br);
	_create_control_icon(corner_radius_br, "StyleBoxCorner", "StyleBoxCornerBottomRight");

	corner_detail_hb = memnew(HBoxContainer);
	main_vb->add_child(corner_detail_hb);
	corner_detail_hb->hide();
	Label *corner_detail_label = memnew(Label);
	corner_detail_label->set_h_size_flags(SIZE_EXPAND_FILL);
	corner_detail_label->set_text(TTR("Detail"));
	corner_detail_hb->add_child(corner_detail_label);
	corner_detail = _create_spinbox_editor("corner_detail");
	corner_detail_hb->add_child(corner_detail);

	//// Expand Margin.
	expand_props_label = memnew(Label);
	expand_props_label->set_text(TTR("Expand"));
	main_vb->add_child(expand_props_label);
	expand_props_label->hide();
	property_sections.push_back(expand_props_label);

	expand_margin_hb = memnew(HBoxContainer);
	main_vb->add_child(expand_margin_hb);
	expand_margin_hb->hide();
	expand_margin_t = _create_spinbox_editor("expand_margin_top");
	expand_margin_hb->add_child(expand_margin_t);
	_create_control_icon(expand_margin_t, "StyleBoxExpandTopBase", "StyleBoxExpandTop");
	expand_margin_r = _create_spinbox_editor("expand_margin_right");
	expand_margin_hb->add_child(expand_margin_r);
	_create_control_icon(expand_margin_r, "StyleBoxExpandRightBase", "StyleBoxExpandRight");
	expand_margin_b = _create_spinbox_editor("expand_margin_bottom");
	expand_margin_hb->add_child(expand_margin_b);
	_create_control_icon(expand_margin_b, "StyleBoxExpandBottomBase", "StyleBoxExpandBottom");
	expand_margin_l = _create_spinbox_editor("expand_margin_left");
	expand_margin_hb->add_child(expand_margin_l);
	_create_control_icon(expand_margin_l, "StyleBoxExpandLeftBase", "StyleBoxExpandLeft");

	//// Content Margin/Padding.
	margin_props_label = memnew(Label);
	margin_props_label->set_text(TTR("Margin"));
	main_vb->add_child(margin_props_label);
	margin_props_label->hide();
	property_sections.push_back(margin_props_label);

	margin_hb = memnew(HBoxContainer);
	main_vb->add_child(margin_hb);
	margin_hb->hide();
	margin_t = _create_spinbox_editor("content_margin_top");
	margin_hb->add_child(margin_t);
	_create_control_icon(margin_t, "StyleBoxMargin", "StyleBoxMarginTop");
	margin_r = _create_spinbox_editor("content_margin_right");
	margin_hb->add_child(margin_r);
	_create_control_icon(margin_r, "StyleBoxMargin", "StyleBoxMarginRight");
	margin_b = _create_spinbox_editor("content_margin_bottom");
	margin_hb->add_child(margin_b);
	_create_control_icon(margin_b, "StyleBoxMargin", "StyleBoxMarginBottom");
	margin_l = _create_spinbox_editor("content_margin_left");
	margin_hb->add_child(margin_l);
	_create_control_icon(margin_l, "StyleBoxMargin", "StyleBoxMarginLeft");

	//// Additional controls.
	close_button = memnew(Button);
	close_button->set_v_size_flags(0);
	close_button->set_h_size_flags(SIZE_SHRINK_END);
	close_button->set_flat(true);
	main_mc->add_child(close_button);
	close_button->connect("pressed", callable_mp(this, &ThemeStyleBoxEditor::_close_button_cbk));
}

bool EditorInspectorPluginStyleBox::can_handle(Object *p_object) {
	return Object::cast_to<StyleBox>(p_object) != nullptr;
}

void EditorInspectorPluginStyleBox::parse_begin(Object *p_object) {
	Ref<StyleBox> sb = Ref<StyleBox>(Object::cast_to<StyleBox>(p_object));

	StyleBoxPreview *preview = memnew(StyleBoxPreview);
	preview->edit(sb);
	add_custom_control(preview);
}

bool EditorInspectorPluginStyleBox::parse_property(Object *p_object, Variant::Type p_type, const String &p_path, PropertyHint p_hint, const String &p_hint_text, int p_usage, bool p_wide) {
	if (p_path.begins_with("border_width_") && p_object->is_class("StyleBox")) {
		StyleBoxQuadEditor *editor = memnew(StyleBoxQuadEditor);
		Vector<String> properties;
		properties.push_back("border_width_top");
		properties.push_back("border_width_right");
		properties.push_back("border_width_bottom");
		properties.push_back("border_width_left");
		editor->set_properties(properties);

		add_property_editor_for_multiple_properties("", properties, editor);
		return true;
	}

	return false;
}

void EditorInspectorPluginStyleBox::parse_end() {
}

StyleBoxEditorPlugin::StyleBoxEditorPlugin(EditorNode *p_node) {
	Ref<EditorInspectorPluginStyleBox> inspector_plugin;
	inspector_plugin.instance();
	add_inspector_plugin(inspector_plugin);
}
