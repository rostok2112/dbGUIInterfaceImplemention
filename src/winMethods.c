#include "../include/types.h"
#include <glib.h>

static Args3EventHandler *args3;
static Args4EventHandler *args4;

void showDlg(GtkDialog * dlg)
{
    gtk_widget_set_visible(dlg, true);
}

void hideDlg(GtkDialog * dlg)
{
    gtk_widget_set_visible(dlg, false);
}

void createWin(GtkWidget **window, guchar id [], guchar pathToBuilder [])
{

    GError *error = NULL;

    builder = gtk_builder_new ();
    if (!gtk_builder_add_from_file (builder, pathToBuilder, &error)) {

        g_critical ("Can't open file: %s", error->message);
        g_error_free (error);
    }

    gtk_builder_connect_signals (builder, NULL);

    *window = GTK_WIDGET (gtk_builder_get_object (builder, id));
    if (!(*window)  )
        g_critical ("Erron in fetching window");

}

void winMainSetEventHandlers(void)
{

    args4 = (Args4EventHandler *) malloc(sizeof(Args4EventHandler ));
    args4->arg1 = GTK_DIALOG(gtk_builder_get_object(builder, "dlgSelect"));
    args4->arg2 = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radioButtonSelectWithChilds"));
    args4->arg3 = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "comboBoxTables1"));
    args4->arg4 = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "mainTextArea"));


    if(!args4->arg1)
        g_critical ("Cant found dlgSelect");
    if(!args4->arg2)
        g_critical ("Cant found radioButtonSelectWithChilds");
    if(!args4->arg3)
        g_critical ("Cant found chckBoxTables1");
    if(!args4->arg4)
        g_critical ("Cant found mainTextArea");



    if(!g_signal_connect(G_OBJECT(gtk_builder_get_object (builder, "btnOk1")),
                         "clicked",
                         G_CALLBACK(onOkBtn1Clicked),
                         &args4 ))
        g_critical ("Cant bind handler btnOk1");

}

void winAuthSetEventHandlers(void)
{

    args3 = (Args3EventHandler *) malloc(sizeof(Args3EventHandler ));
    args3->arg1 = GTK_ENTRY(gtk_builder_get_object(builder, "form_Login"));
    args3->arg2 = GTK_ENTRY(gtk_builder_get_object(builder, "form_Pass"));
    args3->arg3 = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "dlgMsg"));


    if(!args3->arg1)
        g_critical ("Cant found form_Login");
    if(!args3->arg2)
        g_critical ("Cant found form_Pass");
    if(!args3->arg3)
        g_critical ("Cant found dlgMsg");



    if(!g_signal_connect(G_OBJECT(gtk_builder_get_object (builder, "btn_Login")),
                         "clicked",
                         G_CALLBACK(onBtnLoginClicked),
                         &args3 ))
        g_critical ("Cant bind handler btn_Login");

    if(!g_signal_connect(G_OBJECT(gtk_builder_get_object (builder, "btn_Register")),
                         "clicked",
                         G_CALLBACK(onBtnRegisterClicked),
                         &args3 ))
        g_critical ("Cant bind handler btn_Register");


    g_object_unref(builder);
}

void showMsg(GtkMessageDialog * msgDlg, guchar * msg)
{

    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(msgDlg)))));

    while(listChilds && !GTK_IS_TEXT_VIEW (listChilds->data))
        listChilds = listChilds->next;

    if(listChilds) {
        GtkTextBuffer * buf = GTK_TEXT_BUFFER(gtk_text_view_get_buffer (listChilds->data));
        gtk_text_buffer_set_text(buf,"", -1);
        gtk_text_buffer_insert_at_cursor(buf, msg, -1);
    }
    showDlg(GTK_DIALOG(msgDlg));
}
