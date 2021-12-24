#include "../include/types.h"


G_MODULE_EXPORT void onCancelTestTest(GtkButton * btn, GtkDialog * dlg){


    g_free(g_object_get_data(dlg, "tableName"));
    gtk_widget_destroy(GTK_WIDGET(dlg));
}

G_MODULE_EXPORT void onOkTestTest(GtkButton * btn, GtkDialog * dlg)
{



     GtkBox  *  boxMain  = GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)));

    selectDB(g_object_get_data(dlg, "tableName"));

    MYSQL_FIELD  * field = NULL;
    guchar * values = g_strdup("null, "), bufStr = NULL;
    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(boxMain));

    int i = 0;
    while((field =  mysql_fetch_field(result))) {

        switch(field->type) {
            case FIELD_TYPE_DECIMAL:
                ;
            case FIELD_TYPE_FLOAT:
                ;
            case FIELD_TYPE_DOUBLE:
                ;
            case FIELD_TYPE_SHORT:
                ;
            case FIELD_TYPE_INT24:
                ;
            case FIELD_TYPE_LONG:
                if(GTK_IS_SPIN_BUTTON(listChilds) && i++)
                    listChilds = listChilds->next;
                while(!GTK_IS_SPIN_BUTTON(listChilds))
                    listChilds = listChilds->next;

                if(listChilds){
                    bufStr = values;
                    values = g_strdup_printf("%s%g, ", values, gtk_spin_button_get_value(listChilds->data));
                    g_free(bufStr);

                }
                break;
            case FIELD_TYPE_TINY:
                if(field->length == 1){

                if(GTK_IS_CHECK_BUTTON(listChilds) && i++)
                    listChilds = listChilds->next;
                while(!GTK_IS_CHECK_BUTTON(listChilds))
                    listChilds = listChilds->next;

                if(listChilds){
                    bufStr = values;
                    values = g_strdup_printf("%s%d, ", values, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(listChilds->data)));
                    g_free(bufStr);

                }

                }

                else {
                    if(GTK_IS_SPIN_BUTTON(listChilds) && i++)
                    listChilds = listChilds->next;
                while(!GTK_IS_SPIN_BUTTON(listChilds))
                    listChilds = listChilds->next;

                if(listChilds){
                    bufStr = values;
                    values = g_strdup_printf("%s%g, ", values, gtk_spin_button_get_value(listChilds->data));
                    g_free(bufStr);
                }
                }
                break;
            case FIELD_TYPE_LONGLONG:
                if(field->flags & PRI_KEY_FLAG);
                else {
                   if(GTK_IS_SPIN_BUTTON(listChilds) && i++)
                    listChilds = listChilds->next;
                while(!GTK_IS_SPIN_BUTTON(listChilds))
                    listChilds = listChilds->next;

                if(listChilds){
                    bufStr = values;
                    values = g_strdup_printf("%s%g, ", values, gtk_spin_button_get_value(listChilds->data));
                    g_free(bufStr);

                }
                }
                break;
            case FIELD_TYPE_STRING - 1:
                ;
            case FIELD_TYPE_STRING:
                if(GTK_IS_ENTRY(listChilds) && i++)
                    listChilds = listChilds->next;
                while(!GTK_IS_ENTRY(listChilds))
                    listChilds = listChilds->next;

                if(listChilds){
                    bufStr = values;
                    values = g_strdup_printf("%s'%s', ", values, gtk_spin_button_get_value(listChilds->data));
                    g_free(bufStr);

                }
                break;
            default:
                ;
        }

    }

insertDB(g_object_get_data(dlg, "tableName"), values);

g_free(values);



    g_free(g_object_get_data(dlg, "tableName"));
    gtk_widget_destroy(GTK_WIDGET(dlg));
}

G_MODULE_EXPORT void onOkTest(GtkButton * btn, GtkDialog * parentDlg)
{

    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(parentDlg)))));

    guchar *  tableName = NULL;
    guint  fieldCount = 0;
    while(listChilds && !GTK_IS_BOX(listChilds->data) )
        listChilds = listChilds->next;
    if(listChilds) {

        listChilds = gtk_container_get_children( GTK_CONTAINER(GTK_BOX(listChilds->data)));
        while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data) )
            listChilds = listChilds->next;
        if(listChilds) {
            tableName = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(listChilds->data));

        }
    }

    selectDB(tableName);
    fieldCount = mysql_num_fields(result);

guchar * bufStr = g_strdup_printf("Добавление: %s", tableName);


    GtkDialog * dlg = gtk_dialog_new_with_buttons(bufStr,
                      parentDlg,(GtkDialogFlags)(GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT),
                      "Ok", GTK_RESPONSE_ACCEPT,
                      "Cancel", GTK_RESPONSE_REJECT,
                      NULL);

    g_free(bufStr);
    g_object_set_data(dlg, "tableName", tableName);
    GtkBox  *  boxMain  = GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)));

    MYSQL_FIELD  * field = NULL;

    while((field =  mysql_fetch_field(result))) {
        GtkWidget * buf = NULL;
        GtkAdjustment *adjustment;

        switch(field->type) {
            case FIELD_TYPE_DECIMAL:
                ;
            case FIELD_TYPE_FLOAT:
                ;
            case FIELD_TYPE_DOUBLE:
                ;
            case FIELD_TYPE_SHORT:
                ;
            case FIELD_TYPE_INT24:
                ;
            case FIELD_TYPE_LONG:
                bufStr = g_strconcat(field->name, ":", NULL);
                gtk_container_add(GTK_CONTAINER(boxMain), gtk_label_new(bufStr));
                adjustment = gtk_adjustment_new (0.0, 0.0, pow(10, field->length + 1) - 1, 1.0, 5.0, 0.0);
                buf = gtk_spin_button_new (adjustment, 1.0, 0);
                gtk_spin_button_set_numeric(buf, true);
                g_free(bufStr);
                break;
            case FIELD_TYPE_TINY:
                if(field->length == 1)
                    buf =  gtk_check_button_new_with_label(field->name);
                else {
                    bufStr = g_strconcat(field->name, ":", NULL);
                    gtk_container_add(GTK_CONTAINER(boxMain), gtk_label_new(bufStr));
                    adjustment = gtk_adjustment_new (0.0, 0.0, pow(10, field->length + 1) - 1, 1.0, 5.0, 0.0);
                    buf = gtk_spin_button_new (adjustment, 1.0, 0);
                    gtk_spin_button_set_numeric(buf, true);
                    g_free(bufStr);
                }
                break;
            case FIELD_TYPE_LONGLONG:
                if(field->flags & PRI_KEY_FLAG)
                    buf = NULL;
                else {
                    bufStr = g_strconcat(field->name, ":", NULL);
                    gtk_container_add(GTK_CONTAINER(boxMain), gtk_label_new(bufStr));
                    adjustment = gtk_adjustment_new (0.0, 0.0, pow(10, field->length + 1) - 1, 1.0, 5.0, 0.0);
                    buf = gtk_spin_button_new (adjustment, 1.0, 0);
                    gtk_spin_button_set_numeric(buf, true);
                    g_free(bufStr);
                }
                break;
            case FIELD_TYPE_STRING - 1:
                ;
            case FIELD_TYPE_STRING:
                bufStr = g_strconcat(field->name, ":", NULL);
                gtk_container_add(GTK_CONTAINER(boxMain), gtk_label_new(bufStr));
                buf = gtk_entry_new();
                g_free(bufStr);
                break;
            default:
                buf = NULL;
                ;
        }

        buf ? gtk_container_add(GTK_CONTAINER(boxMain),  buf) : NULL;
    }

    listChilds  =  gtk_container_get_children(GTK_CONTAINER(GTK_BUTTON_BOX(gtk_dialog_get_action_area(dlg))));
    if(GTK_IS_BUTTON(listChilds->data) && !g_strcmp0(gtk_label_get_text(gtk_bin_get_child (listChilds->data)), "Ok"))
        g_signal_connect(GTK_BUTTON(listChilds->data), "clicked", G_CALLBACK(onOkTestTest), dlg);
    listChilds = listChilds->next;
    if(GTK_IS_BUTTON(listChilds->data) && !g_strcmp0(gtk_label_get_text(gtk_bin_get_child(listChilds->data)), "Cancel"))
        g_signal_connect(GTK_BUTTON(listChilds->data), "clicked", G_CALLBACK(onCancelTestTest), dlg);
    gtk_widget_hide(parentDlg);

    gtk_widget_show_all(dlg);

}


G_MODULE_EXPORT void onTest(GtkMenuItem * menuItem, GtkDialog * dlg)
{
    gtk_widget_set_visible(GTK_WIDGET(menuItem), false);
    gtk_widget_set_visible(GTK_WIDGET(menuItem), true);
    gtk_menu_item_deselect(menuItem);

    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data) )
        listChilds = listChilds->next;
    if(listChilds) {

        listChilds = gtk_container_get_children( GTK_CONTAINER(GTK_BOX(listChilds->data)));
        while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data) )
            listChilds = listChilds->next;
        if(listChilds) {
            if(!showTablesLikeNotLikeDB("%\\_%", false))
                return;
            guint countTables = mysql_num_rows(result);
            for(int cntTable = 0; cntTable < countTables; cntTable++)
                gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(listChilds->data), mysql_fetch_row(result)[0]);
            mysql_free_result(result);
        }
    }
    showDlg(dlg);

}


G_MODULE_EXPORT void onOkBtnPrivilegeClicked(GtkButton * btn,  GtkDialog *  dlg)
{

    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data))
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data))
            listChilds = listChilds->next;
        if(listChilds) {
            guchar * userRecord = gtk_combo_box_text_get_active_text( GTK_COMBO_BOX_TEXT(listChilds->data));

            guchar *  idUser = strstr(userRecord, "id") + strlen("id") + 1;
            idUser =   g_strndup( idUser, strchr(idUser, ':')- (char *)idUser);

            guchar *  loginUser = strstr(userRecord, "login") + strlen("login") + 1;
            loginUser =   g_strndup(loginUser, strchr(loginUser, ':')- (char *)loginUser);

            guchar *  passwrdUser = strstr(userRecord, "passwrd") + strlen("passwrd") + 1;
            passwrdUser =   g_strndup(passwrdUser, strchr(passwrdUser, ':')- (char *)passwrdUser);

            while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data))
                listChilds = listChilds->next;
            if(listChilds) {
                guchar * setValue = g_strdup_printf("`%s` = '%d'", "isAdmin",  gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(listChilds->data)));

                if(!updateDB(AUTH_TABLE, setValue, "id", idUser)) {
                    mysql_select_db(con, DB_NAME);
                    free(setValue);
                    free(userRecord);
                    free(idUser);
                    free(loginUser);
                    free(passwrdUser);

                    return;
                }
                if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(listChilds->data)))//if isAdmin
                    if(!createUserDBMS_DB(loginUser, passwrdUser) || !grantAdminDBMS_DB(loginUser)) {
                        free(setValue);
                        free(userRecord);
                        free(idUser);
                        free(loginUser);
                        free(passwrdUser);

                        return;
                    } else;
                else if(!dropUserDBMS_DB(loginUser)) {
                    free(setValue);
                    free(userRecord);
                    free(idUser);
                    free(loginUser);
                    free(passwrdUser);
                    return;
                }

                free(setValue);
            }

            free(userRecord);
            free(idUser);
            free(loginUser);
            free(passwrdUser);
        }
    }
    mysql_select_db(con, DB_NAME);
    hideDlg(dlg);
}



G_MODULE_EXPORT void onMenuItemPrivilegeClicked(GtkMenuItem * menuItem,  GtkDialog *  dlg)
{
    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data))
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data))
            listChilds = listChilds->next;
        if(listChilds) {
            gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(listChilds->data));

            mysql_select_db(con, AUTH_DB_NAME);

            if(!selectTableDB(AUTH_TABLE, false, NULL)) {
                mysql_select_db(con, DB_NAME);
                return;
            }

            guchar * str_buf1 = NULL;
            guchar * str_buf2 = NULL;

            guint countRecords = mysql_num_rows(result);

            for(int cntRow = 0; cntRow < countRecords; cntRow++) {

                MYSQL_ROW row_Record = mysql_fetch_row(result);
                guint countFields = mysql_num_fields(result);

                MYSQL_FIELD * record_Fields = mysql_fetch_fields(result);
                for(int cntField = 0; cntField < countFields; cntField++) {
                    str_buf2 = str_buf1;
                    str_buf1 = str_buf1 = g_strdup_printf("%s%s%s:%s", str_buf1 ? str_buf1 : "", str_buf1 ? ":" : "",record_Fields[cntField].name, row_Record[cntField]);
                    free(str_buf2);
                }
                gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(listChilds->data), str_buf1);
                free(str_buf1);
                str_buf1 = NULL;

            }
            mysql_free_result(result);
        }
    }
    showDlg(dlg);
}


G_MODULE_EXPORT void onOkBtnLinkRecordsClicked(GtkButton * btn,  GtkDialog *  dlg)
{

    GList *  listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_GRID(listChilds->data))
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_GRID(listChilds->data)));

        while (listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data))

            listChilds = listChilds->next;

        GtkComboBoxText *comboChild= listChilds->data;

        do
            if(listChilds)
                listChilds = listChilds->next;
        while (listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data));

        GtkComboBoxText *comboParent= listChilds->data;

        if(comboChild && comboParent) {

            guchar * recordParent = gtk_combo_box_text_get_active_text(comboParent);
            guchar * recordChild  = gtk_combo_box_text_get_active_text(comboChild);

            guchar * nameTableParent =   g_strndup(recordParent, strchr (recordParent, ':') - (char *)recordParent);
            guchar * nameTableChild  =   g_strndup(recordChild, strchr (recordChild, ':') - (char *) recordChild);

            guchar * valueFieldParent = strchr(strchr(strchr(recordParent,  ':') + 1,  ':'), ' ' ) + 1;
            valueFieldParent = g_strndup(valueFieldParent, strchr(valueFieldParent, ' ') -  (char *)valueFieldParent);

            guchar * valueFieldChild = strchr(strchr(strchr(recordChild,  ':') + 1,  ':'), ' ' ) + 1;
            valueFieldChild = g_strndup(valueFieldChild, strchr(valueFieldChild, ' ') -  (char *)valueFieldChild);

            linkDB(nameTableParent, nameTableChild, valueFieldParent, valueFieldChild);

            free(recordParent);
            free(recordChild);
            free(nameTableParent);
            free(nameTableChild);
            free(valueFieldParent);
            free(valueFieldChild);
        }
    }
    hideDlg(dlg);
}
G_MODULE_EXPORT void onOkBtnLinkClicked(GtkButton * btn,  GtkDialog *  dlg)
{

    GtkWidget * dlgPast = btn;
    while(dlgPast && !GTK_IS_DIALOG(dlgPast))
        dlgPast =  gtk_widget_get_parent(dlgPast);

    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlgPast)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data) )
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data) )
            listChilds = listChilds->next;

        if(listChilds) {
            guchar * linkName = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(listChilds->data));
            guchar * parentName = g_strndup(linkName, (strchr(linkName, '_') - (char *)linkName) );
            guchar * childName = g_strndup(strchr(linkName, '_') + 1, strchr(linkName, '\0') - strchr(linkName, '_' ));

            listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));


            while(listChilds && !GTK_IS_GRID(listChilds->data))
                listChilds = listChilds->next;

            if(listChilds) {

                listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_GRID(listChilds->data)));

                while (listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data))
                    listChilds = listChilds->next;

                GtkComboBoxText *comboChild= listChilds->data;

                do
                    if(listChilds)
                        listChilds = listChilds->next;
                while (listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data));

                GtkComboBoxText *comboParent= listChilds->data;

                if(comboChild && comboParent) {

                    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(comboParent));

                    guchar * str_buf1 = NULL;
                    guchar * str_buf2 = NULL;

                    selectTableDB(parentName, false, NULL);
                    guint countRecords = mysql_num_rows(result);

                    for(int cntRow = 0; cntRow < countRecords; cntRow++) {
                        str_buf1 = g_strdup_printf("%s: ", parentName);

                        MYSQL_ROW row_Record = mysql_fetch_row(result);
                        guint countFields = mysql_num_fields(result);

                        MYSQL_FIELD * record_Fields = mysql_fetch_fields(result);
                        for(int cntField = 0; cntField < countFields; cntField++) {

                            str_buf2 = str_buf1;
                            str_buf1 = str_buf1 = g_strdup_printf("%s%s: %s ", str_buf1 ? str_buf1 : "", record_Fields[cntField].name, row_Record[cntField]);
                            free(str_buf2);

                        }
                        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboParent), str_buf1);
                        free(str_buf1);
                        str_buf1 = NULL;

                    }

                    mysql_free_result(result);

                    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(comboChild));

                    str_buf1 = NULL;
                    str_buf2 = NULL;

                    selectTableDB(childName, false, NULL);
                    countRecords = mysql_num_rows(result);

                    for(int cntRow = 0; cntRow < countRecords; cntRow++) {
                        str_buf1 = g_strdup_printf("%s: ", childName);
                        MYSQL_ROW row_Record = mysql_fetch_row(result);
                        guint countFields = mysql_num_fields(result);

                        MYSQL_FIELD * record_Fields = mysql_fetch_fields(result);

                        for(int cntField = 0; cntField < countFields; cntField++) {

                            str_buf2 = str_buf1;
                            str_buf1 = str_buf1 = g_strdup_printf("%s%s: %s ", str_buf1 ? str_buf1 : "", record_Fields[cntField].name, row_Record[cntField]);
                            free(str_buf2);

                        }
                        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboChild), str_buf1);
                        free(str_buf1);
                        str_buf1 = NULL;
                    }
                    mysql_free_result(result);
                }
            }
            free(linkName);
            free(parentName);
            free(childName);
        }

    }

    hideDlg(GTK_DIALOG(dlgPast));
    showDlg(dlg);
}

G_MODULE_EXPORT void onMenuItemLinkClicked(GtkMenuItem * menuItem,  GtkDialog *  dlg)
{
    gtk_widget_set_visible(GTK_WIDGET(menuItem), false);
    gtk_widget_set_visible(GTK_WIDGET(menuItem), true);
    gtk_menu_item_deselect(menuItem);

    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data) )
        listChilds = listChilds->next;

    if(listChilds) {

        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data) )
            listChilds = listChilds->next;

        if(listChilds) {

            gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(listChilds->data));

            if(!showTablesLikeNotLikeDB("%\\_%", true))
                return;

            guint countTables = mysql_num_rows(result);


            for(int cntTable = 0; cntTable < countTables; cntTable++)
                gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(listChilds->data), mysql_fetch_row(result)[0]);

            mysql_free_result(result);
        }
    }
    showDlg(dlg);
}


G_MODULE_EXPORT void onOkBtnUpdateArchClicked(GtkButton * btn,  GtkDialog *  dlg)
{

    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));
    while(listChilds && !GTK_IS_BOX(listChilds->data))
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data), g_strcmp0(gtk_widget_get_name(GTK_WIDGET(listChilds)), "combo"));
        listChilds = listChilds->next;
        if(listChilds) {

            guchar * record = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(listChilds->data));
            guchar * buf_ptr = strchr(record, ' ') +1;
            guchar * id = g_strndup(buf_ptr, strchr(buf_ptr, ' ') - (char *) buf_ptr );

            guchar * setValue = g_strdup_printf("`%s` = '%s', ", "id", id);
            guchar * buf;


            while(listChilds && !GTK_IS_ENTRY(listChilds->data))
                listChilds = listChilds->next;
            if(listChilds) {
                buf = setValue;
                setValue =  g_strdup_printf("%s`%s` = '%s', ", setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                            gtk_entry_get_text(GTK_ENTRY(listChilds->data))) ;
                free(buf);


                while(listChilds && !GTK_IS_SPIN_BUTTON(listChilds->data))
                    listChilds = listChilds->next;

                if(listChilds) {
                    buf = setValue;
                    setValue =  g_strdup_printf("%s`%s` = '%d', ", setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                                gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(listChilds->data)));
                    free(buf);

                    do
                        if(listChilds)
                            listChilds = listChilds->next;
                    while(listChilds && !GTK_IS_SPIN_BUTTON(listChilds->data));

                    if(listChilds) {

                        buf = setValue;
                        setValue =  g_strdup_printf("%s`%s` = '%d', ", setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                                    gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(listChilds->data)));
                        free(buf);

                        while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data))
                            listChilds = listChilds->next;

                        if(listChilds) {

                            buf = setValue;
                            setValue =  g_strdup_printf("%s`%s` = '%d', ", setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                                        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(listChilds->data))));
                            free(buf);

                            do
                                if(listChilds)
                                    listChilds = listChilds->next;
                            while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data));

                            if(listChilds) {

                                buf = setValue;
                                setValue =  g_strdup_printf("%s`%s` = '%d', ", setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                                            gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(listChilds->data))));
                                free(buf);

                                do
                                    if(listChilds)
                                        listChilds = listChilds->next;
                                while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data));


                                if(listChilds) {

                                    buf = setValue;
                                    setValue =  g_strdup_printf("%s`%s` = '%d', ", setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                                                gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(listChilds->data))));
                                    free(buf);

                                    do
                                        if(listChilds)
                                            listChilds = listChilds->next;
                                    while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data));

                                    if(listChilds) {

                                        buf = setValue;
                                        setValue =  g_strdup_printf("%s`%s` = '%d', ", setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                                                    gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(listChilds->data))));
                                        free(buf);

                                        do
                                            if(listChilds)
                                                listChilds = listChilds->next;
                                        while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data));

                                        if(listChilds) {
                                            buf = setValue;
                                            setValue =  g_strdup_printf("%s`%s` = '%d'", setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                                                        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(listChilds->data))));
                                            free(buf);

                                            updateDB("процессорна архітектура", setValue, "id", id);
                                            free(setValue);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            free(record);
            free(id);
        }
    }
    hideDlg(dlg);
}

G_MODULE_EXPORT void onOkBtnUpdateFamilyClicked(GtkButton * btn,  GtkDialog *  dlg)
{
    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data))
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data) && g_strcmp0(gtk_widget_get_name(GTK_WIDGET(listChilds)), "combo"))
            listChilds = listChilds->next;
        if(listChilds) {

            guchar * record = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(listChilds->data));
            guchar * buf_ptr = strchr(record, ' ') +1;
            guchar * id = g_strndup(buf_ptr, strchr(buf_ptr, ' ') - (char *) buf_ptr );

            guchar * setValue = g_strdup_printf("`%s` = '%s', ", "id", id);
            guchar * buf;

            while(listChilds && !GTK_IS_ENTRY(listChilds->data))
                listChilds = listChilds->next;
            if(listChilds) {
                buf = setValue;
                setValue =  g_strdup_printf("%s`%s` = '%s', ", setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                            gtk_entry_get_text(GTK_ENTRY(listChilds->data))) ;
                free(buf);

                while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data))
                    listChilds = listChilds->next;
                if(listChilds) {
                    buf = setValue;
                    setValue =  g_strdup_printf("%s`%s` = '%s', ",  setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                                gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(listChilds->data)));
                    free(buf);

                    while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data))
                        listChilds = listChilds->next;
                    if(listChilds) {

                        buf = setValue;
                        setValue =  g_strdup_printf("%s`%s` = '%d'",  setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                                    gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(listChilds->data))));
                        free(buf);

                        updateDB("сімейство архітектур", setValue, "id", id);
                        free(setValue);
                    }
                }
            }

            free(record);
            free(id);
        }
    }

    hideDlg(dlg);
}

G_MODULE_EXPORT void onOkBtnUpdateCompanyClicked(GtkButton * btn,  GtkDialog *  dlg)
{
    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data))
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data))
            listChilds = listChilds->next;
        if(listChilds) {

            guchar * record = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(listChilds->data));
            guchar * buf_ptr = strchr(record, ' ') +1;
            guchar * id = g_strndup(buf_ptr, strchr(buf_ptr, ' ') - (char *) buf_ptr );

            guchar * setValue = g_strdup_printf("`%s` = '%s', ", "id", id);
            guchar * buf;

            while(listChilds && !GTK_IS_ENTRY(listChilds->data))
                listChilds = listChilds->next;
            if(listChilds) {

                buf = setValue;
                setValue = g_strdup_printf("%s`%s` = '%s'", setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                           gtk_entry_get_text(GTK_ENTRY(listChilds->data)));
                free(buf);

                updateDB("компанія-розробник архітектури", setValue, "id", id);
                free(setValue);
            }
            free(record);
            free(id);
        }
    }
    hideDlg(dlg);
}



G_MODULE_EXPORT void onOkBtnUpdateDirectoryClicked(GtkButton * btn,  GtkDialog *  dlg)
{

    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data))
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data))
            listChilds = listChilds->next;
        if(listChilds) {

            guchar * record = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(listChilds->data));
            guchar * buf_ptr = strchr(record, ' ') +1;
            guchar * id = g_strndup(buf_ptr, strchr(buf_ptr, ' ') - (char *) buf_ptr );

            guchar * setValue = g_strdup_printf("`%s` = '%s', ", "id", id);
            guchar * buf;

            while(listChilds && !GTK_IS_ENTRY(listChilds->data))
                listChilds = listChilds->next;
            if(listChilds) {

                buf = setValue;
                setValue = g_strdup_printf("%s`%s` = '%s'", setValue, gtk_widget_get_name(GTK_WIDGET(listChilds->data)),
                                           gtk_entry_get_text(GTK_ENTRY(listChilds->data)));
                free(buf);

                updateDB("довідник архітектур пк", setValue, "id", id);
                free(setValue);

            }
            free(record);
            free(id);
        }
    }
    hideDlg(dlg);
}


G_MODULE_EXPORT void onOkBtnUpdateClicked(GtkButton * btn,  GtkDialog *  dlg)
{
    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BUTTON_BOX (listChilds->data) &&   g_strcmp0(gtk_widget_get_name(GTK_WIDGET(listChilds->data)), "radioBtns")  )
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(listChilds->data));

        while(listChilds && !gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON( GTK_RADIO_BUTTON(listChilds->data) )))
            listChilds = listChilds->next;
        if(listChilds) {
            GtkDialog * choosedDlg =  gtk_builder_get_object(builder, gtk_widget_get_name(GTK_WIDGET(listChilds->data)));
            guchar * nameTable =  gtk_button_get_label(GTK_BUTTON(listChilds->data));

            listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(choosedDlg)))));

            while(listChilds && !GTK_IS_BOX (listChilds->data))
                listChilds = listChilds->next;
            if(listChilds) {
                listChilds =  gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));
                while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data) )
                    listChilds = listChilds->next;

                if(listChilds) {

                    gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(listChilds->data));

                    guchar * str_buf1 = NULL;
                    guchar * str_buf2 = NULL;

                    selectTableDB(nameTable, false, NULL);
                    guint countRecords = mysql_num_rows(result);

                    for(int cntRow = 0; cntRow < countRecords; cntRow++) {

                        MYSQL_ROW row_Record = mysql_fetch_row(result);
                        guint countFields = mysql_num_fields(result);

                        MYSQL_FIELD * record_Fields = mysql_fetch_fields(result);
                        for(int cntField = 0; cntField < countFields; cntField++) {

                            str_buf2 = str_buf1;
                            str_buf1 = str_buf1 = g_strdup_printf("%s%s: %s ", str_buf1 ? str_buf1 : "", record_Fields[cntField].name, row_Record[cntField]);
                            free(str_buf2);

                        }
                        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(listChilds->data), str_buf1);
                        free(str_buf1);
                        str_buf1 = NULL;
                    }
                    mysql_free_result(result);
                }
            }
            hideDlg(dlg);
            showDlg(choosedDlg);
        }
    }
}

G_MODULE_EXPORT void onOkBtnDeleteClicked(GtkButton * btn,  GtkDialog *  dlg)
{
    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data) )
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data) )
            listChilds = listChilds->next;
        if(listChilds) {

            guchar * record = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(listChilds->data));
            guchar * buf_ptr = (strchr (record, ':'));
            guchar * nameTable = g_strndup(record, buf_ptr - record);
            buf_ptr++;
            guchar * nameField =  g_strndup(strchr(buf_ptr, ' ') + 1, strchr(buf_ptr, ':') - strchr(buf_ptr, ' ')  - 1);
            buf_ptr = strchr(strchr(buf_ptr, ':'), ' ')  + 1;
            guchar * fieldValue = g_strndup(buf_ptr, strchr(buf_ptr, ' ') - (char *)buf_ptr );
            deleteDB(nameTable, nameField, fieldValue);

            free(record);
            free(nameTable);
            free(nameField);
            free(fieldValue);

        }
    }
    hideDlg(dlg);
}

G_MODULE_EXPORT void onMenuItemDeleteClicked(GtkMenuItem * menuItem,  GtkDialog *  dlg)
{

    gtk_widget_set_visible(GTK_WIDGET(menuItem), false);
    gtk_widget_set_visible(GTK_WIDGET(menuItem), true);
    gtk_menu_item_deselect(menuItem);

    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data) )
        listChilds = listChilds->next;

    if(listChilds) {

        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data) )
            listChilds = listChilds->next;

        if(listChilds) {

            gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(listChilds->data));

            if(!showTablesLikeNotLikeDB("%\\_%", false))
                return;

            MYSQL_RES * res_buf = result;

            guint countTables = mysql_num_rows(res_buf);

            MYSQL_ROW row_Table;

            guchar * str_buf1 = NULL;
            guchar * str_buf2 = NULL;
            for(int cntTable = 0; cntTable < countTables; cntTable++) {
                row_Table = mysql_fetch_row(res_buf);

                selectTableDB(row_Table[0], false, NULL);
                guint countRecords = mysql_num_rows(result);

                for(int cntRow = 0; cntRow < countRecords; cntRow++) {
                    str_buf1 = g_strdup_printf("%s: ", row_Table[0]);

                    MYSQL_ROW row_Record = mysql_fetch_row(result);
                    guint countFields = mysql_num_fields(result);

                    MYSQL_FIELD * record_Fields = mysql_fetch_fields(result);
                    for(int cntField = 0; cntField < countFields; cntField++) {

                        str_buf2 = str_buf1;
                        str_buf1 = str_buf1 = g_strdup_printf("%s%s: %s ", str_buf1, record_Fields[cntField].name, row_Record[cntField]);
                        free(str_buf2);
                    }
                    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(listChilds->data), str_buf1);
                    free(str_buf1);
                    str_buf1 = NULL;
                }
                mysql_free_result(result);
            }
            mysql_free_result(res_buf);
        }
    }
    showDlg(dlg);
}

G_MODULE_EXPORT void onOkBtnInsertArchClicked(GtkButton * btn,  GtkDialog *  dlg)
{
    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data) )
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_ENTRY(listChilds->data) )
            listChilds = listChilds->next;
        if(listChilds) {
            guchar * values = g_strdup_printf("null, '%s'", gtk_entry_get_text(GTK_ENTRY(listChilds->data)));
            guchar * buf;

            while(listChilds && !GTK_IS_SPIN_BUTTON(listChilds->data))
                listChilds = listChilds->next;

            if(listChilds) {

                buf = values;
                values = g_strdup_printf("%s, %d", values, gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(listChilds->data)));
                free(buf);

                do
                    if(listChilds)
                        listChilds = listChilds->next;
                while(listChilds && !GTK_IS_SPIN_BUTTON(listChilds->data));

                if(listChilds) {

                    buf = values;

                    values = g_strdup_printf("%s, %d", values, gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(listChilds->data)));
                    free(buf);

                    while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data))
                        listChilds = listChilds->next;

                    if(listChilds) {

                        buf = values;
                        values = g_strdup_printf("%s, %d", values, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(listChilds->data))));
                        free(buf);

                        do
                            if(listChilds)
                                listChilds = listChilds->next;
                        while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data));

                        if(listChilds) {

                            buf = values;
                            values = g_strdup_printf("%s, %d", values, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(listChilds->data))));
                            free(buf);

                            do
                                if(listChilds)
                                    listChilds = listChilds->next;
                            while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data));


                            if(listChilds) {

                                buf = values;
                                values = g_strdup_printf("%s, %d", values, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(listChilds->data))));
                                free(buf);

                                do
                                    if(listChilds)
                                        listChilds = listChilds->next;
                                while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data));

                                if(listChilds) {

                                    buf = values;
                                    values = g_strdup_printf("%s, %d", values, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(listChilds->data))));
                                    free(buf);

                                    do
                                        if(listChilds)
                                            listChilds = listChilds->next;
                                    while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data));

                                    if(listChilds) {
                                        buf = values;
                                        values = g_strdup_printf("%s, %d", values, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(listChilds->data))));
                                        free(buf);

                                        insertDB("процессорна архітектура", values);
                                        free(values);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    hideDlg(dlg);
}



G_MODULE_EXPORT void onOkBtnInsertFamilyClicked(GtkButton * btn,  GtkDialog *  dlg)
{
    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data))
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        if(listChilds) {

            while(listChilds && !GTK_IS_ENTRY(listChilds->data))
                listChilds = listChilds->next;

            if(listChilds) {

                guchar * values = g_strdup_printf("null, '%s'", gtk_entry_get_text(GTK_ENTRY(listChilds->data)));
                guchar * buf;

                while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data))
                    listChilds = listChilds->next;
                if(listChilds) {
                    buf = values;
                    values = g_strdup_printf("%s, '%s'", values, gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(listChilds->data)));
                    free(buf);

                    while(listChilds && !GTK_IS_CHECK_BUTTON(listChilds->data))
                        listChilds = listChilds->next;
                    if(listChilds) {

                        buf = values;
                        values = g_strdup_printf("%s, %d", values, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GTK_CHECK_BUTTON(listChilds->data))));
                        free(buf);

                        insertDB("сімейство архітектур", values);
                        free(values);
                    }
                }
            }
        }
    }
    hideDlg(dlg);
}

G_MODULE_EXPORT void onOkBtnInsertCompanyClicked(GtkButton * btn,  GtkDialog *  dlg)
{
    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data))
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_ENTRY(listChilds->data))
            listChilds = listChilds->next;
        if(listChilds) {
            guchar * values = g_strdup_printf("null, '%s'", gtk_entry_get_text(GTK_ENTRY(listChilds->data)));

            insertDB("компанія-розробник архітектури", values);
            free(values);
        }
    }
    hideDlg(dlg);
}


G_MODULE_EXPORT void onOkBtnInsertDirectoryClicked(GtkButton * btn,  GtkDialog *  dlg)
{
    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BOX(listChilds->data))
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(listChilds->data)));

        while(listChilds && !GTK_IS_ENTRY(listChilds->data))
            listChilds = listChilds->next;
        if(listChilds) {
            guchar * values = g_strdup_printf("null, '%s'", gtk_entry_get_text(GTK_ENTRY(listChilds->data)));

            insertDB("довідник архітектур пк", values);
            free(values);
        }
    }
    hideDlg(dlg);
}

G_MODULE_EXPORT void onOkBtnInsertClicked(GtkButton * btn,  GtkDialog *  dlg)
{
    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_BUTTON_BOX (listChilds->data) &&   g_strcmp0(gtk_widget_get_name(GTK_WIDGET(listChilds->data)), "radioBtns")  )
        listChilds = listChilds->next;

    if(listChilds) {
        listChilds = gtk_container_get_children(GTK_CONTAINER(listChilds->data));

        while(listChilds && !gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON( GTK_RADIO_BUTTON(listChilds->data) )))
            listChilds = listChilds->next;
        if(listChilds) {
            GtkDialog * choosedDlg =  gtk_builder_get_object(builder, gtk_widget_get_name(GTK_WIDGET(listChilds->data)));
            hideDlg(dlg);
            showDlg(choosedDlg);
        }
    }
}

G_MODULE_EXPORT void onAdminMenuClicked(GtkMenuItem * menuItem,  GtkMessageDialog * msgDlg)
{

    if(!isAdm) {
        gtk_menu_item_deselect(menuItem);
        gtk_widget_set_visible(gtk_menu_item_get_submenu(menuItem), false);
        showMsg(msgDlg, "Доступ запрещен. Нету прав администратора !");
    }
}


G_MODULE_EXPORT void onOkBtn1Clicked(GtkButton * btn,  Args4EventHandler  **args)
{
    /* arg1  dlgSelect, arg2  radioButtonSelectWithChilds, arg3  comboBoxTables1, arg4  mainTextArea */

    clear(NULL, (GtkTextView *)(*args)->arg4);

    GtkTextBuffer * buf  =  gtk_text_view_get_buffer((GtkTextView *)(*args)->arg4);
    if(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON((GtkRadioButton *)(*args)->arg2))) {
m:        selectTableDB(gtk_combo_box_text_get_active_text((GtkComboBoxText *)(*args)->arg3),
                    false, NULL);

        if(mysql_num_rows(result)) {
            int num_fields = mysql_num_fields(result);
            MYSQL_ROW row;
            MYSQL_FIELD *  field;

            while((field = mysql_fetch_field(result))) {
                gtk_text_buffer_insert_at_cursor(buf, field->name, field->name_length);
                gtk_text_buffer_insert_at_cursor(buf, " ", -1);
            }
            gtk_text_buffer_insert_at_cursor(buf, "\n", -1);

            while ((row = mysql_fetch_row(result))) {
                for(int i = 0; i < num_fields; i++) {
                    gtk_text_buffer_insert_at_cursor(buf, row[i] ? row[i] : "NULL", -1);
                    gtk_text_buffer_insert_at_cursor(buf, " ", -1);
                }
                gtk_text_buffer_insert_at_cursor(buf, "\n", -1);
            }
        } else gtk_text_buffer_insert_at_cursor(buf, "Записи отсутствуют.\n", -1);
    } else {
        guchar * bufLn = g_strdup_printf("%s\\_%%", gtk_combo_box_text_get_active_text((GtkComboBoxText *)(*args)->arg3));
        if(!showTablesLikeNotLikeDB(bufLn, true)) {
            free(bufLn);
            return;
        }

        if(mysql_num_rows(result)) {
            guchar * res = NULL;
            selectTableDB(gtk_combo_box_text_get_active_text((GtkComboBoxText *)(*args)->arg3),
                        gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON((GtkRadioButton *)(*args)->arg2)), &res);
                        if(res)
            gtk_text_buffer_insert_at_cursor(buf, res, -1);
                        else goto m;
        } else {
            free(bufLn);
            mysql_free_result(result);

            goto m;
        }
        free(bufLn);
    }
    gtk_text_buffer_insert_at_cursor(buf, "\n", -1);
    hideDlg((GtkDialog *)(*args)->arg1);
}

G_MODULE_EXPORT void onCancelBtn1Clicked(GtkButton * btn, GtkDialog * dlg )
{
    hideDlg(dlg);
}

G_MODULE_EXPORT void onMenuItemSelectClicked(GtkMenuItem * menuItem, GtkDialog * dlg )
{
    gtk_widget_set_visible(GTK_WIDGET(menuItem), false);
    gtk_widget_set_visible(GTK_WIDGET(menuItem), true);
    gtk_menu_item_deselect(menuItem);

    GList * listChilds = gtk_container_get_children(GTK_CONTAINER(GTK_BOX(gtk_bin_get_child(GTK_BIN(dlg)))));

    while(listChilds && !GTK_IS_COMBO_BOX_TEXT(listChilds->data) )
        listChilds = listChilds->next;
    if(listChilds) {

        if(!showTablesLikeNotLikeDB("%\\_%", false))
            return;

        guint countTables = mysql_num_rows(result);

        for(int cntTable = 0; cntTable < countTables; cntTable++)
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(listChilds->data), mysql_fetch_row(result)[0]);
        mysql_free_result(result);
    }
    showDlg(dlg);
}


G_MODULE_EXPORT void onMenuItemClicked(GtkMenuItem * menuItem, GtkDialog * dlg )
{
    gtk_widget_set_visible(GTK_WIDGET(menuItem), false);
    gtk_widget_set_visible(GTK_WIDGET(menuItem), true);
    gtk_menu_item_deselect(menuItem);
    showDlg(dlg);
}

G_MODULE_EXPORT void clear(GtkMenuItem * menuItem, GtkTextView * textArea )
{
    if(menuItem) {
        gtk_widget_set_visible(GTK_WIDGET(menuItem), false);
        gtk_widget_set_visible(GTK_WIDGET(menuItem), true);
        gtk_menu_item_deselect(menuItem);
    }

    gtk_text_buffer_set_text (gtk_text_view_get_buffer(textArea), "", -1);
}


G_MODULE_EXPORT void onExit(GtkWidget * window)
{
    g_object_unref(builder);
    gtk_main_quit();
    exit(0);
}


#define OFFSET_ID 0
#define OFFSET_LOGIN OFFSET_ID + 1
#define OFFSET_PASSWRD OFFSET_LOGIN + 1
#define OFFSET_IS_ADMIN OFFSET_PASSWRD + 1


G_MODULE_EXPORT void onBtnLoginClicked(GtkButton *btn, Args3EventHandler  **forms)
{
    /* arg1 form_Login, arg2  form_Pas, arg3 dlgMsg */

    if(! checkUserDB(gtk_entry_get_text( (*forms)->arg1), gtk_entry_get_text( (*forms)->arg2))) {
        showMsg((*forms)->arg3, "Учетной записи не обнаружено");

        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if(!row) {
        showMsg((*forms)->arg3, "Учетной записи не обнаружено");

        return;
    }

    if(g_ascii_strtoull (row[OFFSET_IS_ADMIN], NULL, 0))
        if(loginUserDB(row[OFFSET_LOGIN], row[OFFSET_PASSWRD], g_ascii_strtoull (row[OFFSET_IS_ADMIN], NULL, 0))) {
            mysql_free_result(result);
            free(*forms);
            *forms = NULL;
            gtk_window_close(window);
            createWin(&window,"winMain", "resource/winMain.glade");
            winMainSetEventHandlers();
            gtk_widget_show_all(window);
            return;
        } else
            showMsg((*forms)->arg3, "Не удалось войти");

    else if(loginUserDB(NULL, NULL, 0)) {
        mysql_free_result(result);
        free(*forms);
        *forms = NULL;
        gtk_window_close(window);
        createWin(&window,"winMain", "resource/winMain.glade");
        winMainSetEventHandlers();
        gtk_widget_show_all(window);
        return;
    } else
        showMsg((*forms)->arg3, "Не удалось войти");

    mysql_free_result(result);
}

G_MODULE_EXPORT void onBtnRegisterClicked(GtkButton *btn, Args3EventHandler **forms)
{
    /* arg1 form_Login, arg2  form_Pas, arg3 dlgMsg */

    if(! createNewUserDB(gtk_entry_get_text( (*forms)->arg1), gtk_entry_get_text( (*forms)->arg2), 0)) {
        showMsg((*forms)->arg3, "Логин занят");

        return;
    }

    if(loginUserDB(NULL, NULL, 0)) {
        free(*forms);
        *forms = NULL;
        gtk_window_close(window);
        createWin(&window,"winMain", "resource/winMain.glade");
        winMainSetEventHandlers();
        gtk_widget_show_all(window);
        return;
    } else
        showMsg((*forms)->arg3, "Не удалось войти");
}
