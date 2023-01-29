/*
 * NAppGUI Cross-platform C SDK
 * 2015-2023 Francisco Garcia Collado
 * MIT Licence
 * https://nappgui.com/en/legal/license.html
 *
 * File: textview.h
 * https://nappgui.com/en/gui/textview.html
 *
 */

/* Text view */

#include "gui.hxx"

__EXTERN_C

_gui_api TextView *textview_create(void);

_gui_api void textview_size(TextView *view, const S2Df size);

_gui_api void textview_clear(TextView *view);

_gui_api uint32_t textview_printf(TextView *view, const char_t *format, ...);

_gui_api void textview_writef(TextView *view, const char_t *text);

_gui_api void textview_rtf(TextView *view, Stream *rtf_in);

_gui_api void textview_units(TextView *view, const uint32_t units);

_gui_api void textview_family(TextView *view, const char_t *family);

_gui_api void textview_fsize(TextView *view, const real32_t size);

_gui_api void textview_fstyle(TextView *view, const uint32_t fstyle);

_gui_api void textview_color(TextView *view, const color_t color);

_gui_api void textview_bgcolor(TextView *view, const color_t color);

_gui_api void textview_pgcolor(TextView *view, const color_t color);

_gui_api void textview_halign(TextView *view, const align_t align);

_gui_api void textview_lspacing(TextView *view, const real32_t scale);

_gui_api void textview_bfspace(TextView *view, const real32_t space);

_gui_api void textview_afspace(TextView *view, const real32_t space);

_gui_api void textview_scroll_down(TextView *view);

_gui_api void textview_editable(TextView *view, const bool_t is_editable);

__END_C
