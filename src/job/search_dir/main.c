/* NAppGUI Hello World */

#include "nappgui.h"
#include <stdlib.h>
typedef struct _app_t App;

struct _app_t
{
    Window *window;
    TextView *text;
    uint32_t clicks;
    RegEx *regex;

};

static void i_OnEditFilter(Layout* layout, Event* e)
{
    const EvText *p = event_params(e, EvText);
    Edit *edit = event_sender(e, Edit);
    EvTextFilter *filter = event_result(e, EvTextFilter);
    uint32_t i, j = 0, n = str_len_c(p->text);

    /* We only accept numbers in IP controls */
    char_t buf[256];

    int x = 0;
    while (p->text[x] != '\0')
    {
        buf[x] = p->text[x];
        ++x;
    }
    buf[x+1] = '\0';

    char_t *iter = buf;  
    for(i = 0; i < n; ++i)
    {
        uint32_t cp = unicode_to_u32(iter, ekUTF8);
        if (cp >= 1040 && cp <= 1071)
            filter->text[j++] = buf[i];

        // iter = unicode_next(iter, ekUTF8); 
        // if (iter == 0)
        // {
        //     break;
        // }
    }

    filter->text[j] = '\0';
    filter->apply = TRUE;
    
    Layout *sublayout = layout_get_layout(layout, 0, 0);

    /* We finish the input in first edit */
    // if (edit == layout_get_edit(sublayout, 0, 0))
    //     cell_focus(layout_cell(sublayout, 2, 0));
    
  
    uint32_t cp = unicode_to_u32(p->text, ekUTF8);
    // printf(cp);
    char_t buffer[256];
    itoa(cp, buffer, 10);
    buffer[10] = '\0';

    Label* uni_label = layout_get_label(sublayout, 2, 0);
    label_text(uni_label, buffer);
}

// static void i_OnButton(App *app, Event *e)
// {
//     String *msg = str_printf("Button click (%d)\n", app->clicks);
//     regex_match(app->regex, str[i])
//     textview_writef(app->text, tc(msg));
//     str_destroy(&msg);
//     app->clicks += 1;
//     unref(e);
// }

Panel *ip_input(App *app)
{
    Panel *panel = panel_create();
    Layout *layout1 = layout_create(7, 1);
    Layout *layout2 = layout_create(1, 3);
    Label *label1 = label_create();
    // Label *label2 = label_create();
    // Label *label3 = label_create();
    Edit *edit1 = edit_create();
    Edit *edit2 = edit_create();
    Button *button1 = button_push();
    label_text(label1, "UNICODE");
    // label_text(label2, ".");
    // label_text(label3, ".");
    button_text(button1, "Connect");
    edit_OnFilter(edit1, listener(layout2, i_OnEditFilter, Layout));
    edit_OnFilter(edit2, listener(layout2, i_OnEditFilter, Layout));
    // layout_label(layout1, label2, 3, 0);
    // layout_label(layout1, label3, 5, 0);
    layout_edit(layout1, edit1, 0, 0);
    layout_edit(layout1, edit2, 1, 0);
    layout_label(layout1, label1, 2, 0);

    layout_layout(layout2, layout1, 0, 0);
    layout_button(layout2, button1, 0, 1);
    layout_vmargin(layout2, 0, 5.f);
    layout_vmargin(layout2, 1, 5.f);
    layout_hsize(layout2, 0, 200.f);
    panel_layout(panel, layout2);
    return panel;
}


/*---------------------------------------------------------------------------*/

static void i_OnButton(App *app, Event *e)
{
    String *msg = str_printf("Button click (%d)\n", app->clicks);
    textview_writef(app->text, tc(msg));
    str_destroy(&msg);
    app->clicks += 1;
    unref(e);
}

/*---------------------------------------------------------------------------*/

static Panel *i_panel(App *app)
{
    Panel *panel = panel_create();
    Layout *layout = layout_create(1, 3);
    Label *label = label_create();
    Button *button = button_push();
    TextView *text = textview_create();
    app->text = text;
    label_text(label, "Hello!, I'm a label");
    button_text(button, "Click Me!");
    button_OnClick(button, listener(app, i_OnButton, App));
    layout_label(layout, label, 0, 0);
    layout_button(layout, button, 0, 1);
    layout_textview(layout, text, 0, 2);
    layout_hsize(layout, 0, 250);
    layout_vsize(layout, 2, 100);
    layout_margin(layout, 5);
    layout_vmargin(layout, 0, 5);
    layout_vmargin(layout, 1, 5);
    panel_layout(panel, layout);
    return panel;
}

/*---------------------------------------------------------------------------*/

static void i_OnClose(App *app, Event *e)
{
    osapp_finish();
    unref(app);
    unref(e);
}

/*---------------------------------------------------------------------------*/

static App *i_create(void)
{
    App *app = heap_new0(App);
    Panel *panel = ip_input(app);
    app->regex = regex_create(".*.txt");
    app->window = window_create(ekWINDOW_STD);
    window_panel(app->window, panel);
    window_title(app->window, "Hello, World!");
    window_origin(app->window, v2df(500, 200));
    window_OnClose(app->window, listener(app, i_OnClose, App));
    window_show(app->window);
    return app;
}

/*---------------------------------------------------------------------------*/

static void i_destroy(App **app)
{
    regex_destroy(&(*app)->regex);
    window_destroy(&(*app)->window);
    heap_delete(app, App);
}

/*---------------------------------------------------------------------------*/



#include "osmain.h"
osmain(i_create, i_destroy, "", App)