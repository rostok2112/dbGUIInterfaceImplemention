#include "../include/types.h"

bool dropUserDBMS_DB(guchar login[])
{

    guchar * query = g_strdup_printf("DROP USER '%s'@'%%'",
                                      login);
    printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));

    if (mysql_query(con, query)) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    } else {
        g_free(query);
        return true;
    }

}

bool grantAdminDBMS_DB(guchar login[])
{
    guchar * query = g_strdup_printf("GRANT ALL PRIVILEGES ON * . * TO '%s'@'%%' WITH GRANT OPTION;",
                                      login);
    printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));

    if (mysql_query(con, query)) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    } else {
        g_free(query);
        return true;
    }

    return true;
}
/*creating new DBMS user*/
bool createUserDBMS_DB(guchar login[], guchar passwrd[])
{

    guchar * query = g_strdup_printf("CREATE USER '%s'@'%%' IDENTIFIED BY '%s'",
                                      login, passwrd);
    printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));

    if (mysql_query(con, query)) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    } else {
        printf("Norm");
        g_free(query);
        return true;
    }
}


bool linkDB(guchar nameTableParent[], guchar nameTableChild[], guchar valueFieldParent[], guchar valueFieldChild[])
{

    guchar * query =  g_strdup_printf("INSERT INTO `%s_%s` VALUES(null, '%s', '%s')",
                                       nameTableParent, nameTableChild, valueFieldParent, valueFieldChild );
    printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));

    if (mysql_query(con, query)) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    } else {
        g_free(query);
        return true;
    }
}



bool updateDB(guchar nameTable[], guchar setValue [], guchar fieldName [], guchar fieldValue[])
{

    guchar * query =  g_strdup_printf("UPDATE `%s`  SET %s WHERE `%s` = '%s'",
                                       nameTable, setValue, fieldName, fieldValue);
    printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));

    if (mysql_query(con, query)) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    } else {
        g_free(query);
        return true;
    }

}

bool deleteDB(guchar nameTable[],  guchar fieldName [], guchar fieldValue[])
{

    guchar * query =  g_strdup_printf("DELETE  FROM `%s` WHERE `%s` = '%s'",
                                       nameTable, fieldName, fieldValue);
    printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));

    if (mysql_query(con, query)) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    } else {
        g_free(query);
        return true;
    }
}



bool showTablesLikeNotLikeDB(guchar pattern[], bool like)
{

    guchar * query =  g_strdup_printf("SELECT table_name FROM INFORMATION_SCHEMA.TABLES WHERE table_schema = '%s' AND table_name %s LIKE '%s'",
                                       DB_NAME, like ? "" : "NOT", pattern);
    printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));

    if (mysql_query(con, query)) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    } else if(!(result = mysql_store_result(con))) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    } else {
        g_free(query);
        return true;
    }


}


bool insertDB(guchar nameTable [], guchar values[])
{


    guchar * query =  g_strdup_printf("INSERT INTO `%s` VALUES(%s)",
                                       nameTable,  values);
    printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));

    if (mysql_query(con, query)) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    }

    else {
        g_free(query);
        return true;
    }

}


bool selectDB(guchar nameTable[])
{
    guchar * query =  g_strdup_printf("SELECT * FROM `%s`",
                                      nameTable);
    printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));
    if (mysql_query(con, query)) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    } else if(!(result = mysql_store_result(con))) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    } else {
        g_free(query);
        return true;
    }

}

bool selectWithChildsDB(guchar  nameTable[], guchar ** res)
{

    guchar * query = g_strdup_printf("%s\\_%%",
                                     nameTable);


    showTablesLikeNotLikeDB(query, true); // returns names of links tables of parent table

    g_free(query);

    MYSQL_RES * res_buf  = result;
    guint countLinksTable = mysql_num_rows(res_buf);


    for(int i = 0; i < countLinksTable; i++) {

        MYSQL_ROW row = mysql_fetch_row(res_buf);

        guchar * buf_1 = g_strdup(row[0]);                     // a name of links table of parent table

        guchar * buf_2 = strchr(buf_1, '_') + 1;               // a name of second linked (child) table name



        query = g_strdup_printf("SELECT DISTINCT `%s`.`id` FROM `%s` INNER JOIN `%s` ON `%s`.`id`= `%s`.`id_%s`", // returns all IDs of parent rows that has childs
                                nameTable, nameTable, buf_1, nameTable, buf_1, nameTable);
        printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));


        if (mysql_query(con, query)) {
            fprintf(stderr,  "%s\n",   mysql_error(con));
            g_free(query);
            return false;
        }

        result = mysql_store_result(con);
        guint countParentRows = mysql_num_rows(result);        // num of parent rows that has childs


        guint64   *parentIDs   = (guint64 *) malloc(sizeof(guint64 ) *  countParentRows);



        for(int i = 0; i < countParentRows; i++ ) {
            row = mysql_fetch_row(result);
            parentIDs[i] = g_ascii_strtoull (row[0], NULL, 0);
        }

        mysql_free_result(result);
        g_free(query);

        guchar * bufLn = NULL;

        for(int i = 0; i < countParentRows; i++) {
            query = g_strdup_printf("SELECT * FROM `%s` WHERE `id` = %d",
                                    nameTable, parentIDs[i]);
            printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));

            mysql_query(con, query);
            result = mysql_store_result(con);
            MYSQL_FIELD * field;
            while((field = mysql_fetch_field(result))) {
                if(*res) {
                    bufLn = (*res);
                    if( ( *(strchr(*res, '\0') - 1) )  == '\n' )
                        (*res) = g_strdup_printf("%s%s", (*res), field->name);
                    else
                        (*res) = g_strdup_printf("%s %s", (*res), field->name);
                    g_free(bufLn);
                } else (*res) = g_strdup(field->name);


            }
            bufLn = (*res);
            (*res) = g_strdup_printf("%s\n", (*res));
            g_free(bufLn);


            int num_fields = mysql_num_fields(result);

            while ((row = mysql_fetch_row(result))) {
                for(int i = 0; i < num_fields; i++) {
                    bufLn = (*res);
                    if( ( *(strchr(*res, '\0') - 1) )  == '\n' )
                        (*res) = g_strdup_printf("%s%s", (*res), row[i] ? row[i] : "NULL");
                    else
                        (*res) = g_strdup_printf("%s %s", (*res), row[i] ? row[i] : "NULL");
                    g_free(bufLn);

                }
                bufLn = (*res);
                (*res) = g_strdup_printf("%s\n", (*res));
                g_free(bufLn);

            }

            mysql_free_result(result);
            g_free(query);

            query = g_strdup_printf("SELECT * FROM `%s` INNER JOIN `%s` ON `%s`.`id` = `%s`.`id_%s` WHERE `%s`.`id_%s` = %d",
                                    buf_2,  buf_1, buf_2, buf_1, buf_2, buf_1, nameTable, parentIDs[i]);
            printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));

            mysql_query(con, query);
            result = mysql_store_result(con);
            while((field = mysql_fetch_field(result))) {
                if(*res) {
                    bufLn = (*res);
                    if( ( *(strchr(*res, '\0') - 1) )  == '\n' )
                        (*res) = g_strdup_printf("%s%s", (*res), field->name);
                    else
                        (*res) = g_strdup_printf("%s %s", (*res), field->name);
                    g_free(bufLn);
                } else (*res) = g_strdup(field->name);

            }
            bufLn = (*res);
            (*res) = g_strdup_printf("%s\n", (*res));
            g_free(bufLn);


            num_fields = mysql_num_fields(result);

            while ((row = mysql_fetch_row(result))) {
                for(int i = 0; i < num_fields; i++) {
                    bufLn = (*res);
                    if( ( *(strchr(*res, '\0') - 1) )  == '\n' )
                        (*res) = g_strdup_printf("%s%s", (*res), row[i] ? row[i] : "NULL");
                    else
                        (*res) = g_strdup_printf("%s %s", (*res), row[i] ? row[i] : "NULL");
                    g_free(bufLn);

                }
                bufLn = (*res);
                (*res) = g_strdup_printf("%s\n", (*res));
                g_free(bufLn);
            }

            bufLn = (*res);
            (*res) = g_strdup_printf("%s\n", (*res));
            g_free(bufLn);

            g_free(query);
        }
    }
    mysql_free_result(res_buf);
    return true;
}


bool createNewUserDB(guchar  login[], guchar passwrd[], bool isAdmin)
{

    guchar * query =  g_strdup_printf("INSERT INTO `user_records` VALUES(null,'%s','%s',%d)",
                                       g_locale_to_utf8(login, -1, NULL, NULL, NULL),
                                       g_locale_to_utf8(passwrd, -1, NULL, NULL, NULL),
                                       isAdmin);
    printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));
    if (mysql_query(con, query)) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    }

    else {
        g_free(query);
        return true;
    }

}

bool checkUserDB(guchar  login[], guchar passwrd[])
{

    guchar * query =  g_strdup_printf("SELECT *  FROM  `user_records` WHERE `login` = '%s' AND `passwrd` = '%s'",
                                       g_locale_to_utf8(login, -1, NULL, NULL, NULL),
                                       g_locale_to_utf8(passwrd, -1, NULL, NULL, NULL));
    printf("%s\n", g_locale_from_utf8(query, -1, NULL, NULL, NULL));

    if (mysql_query(con, query)) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        return false;
    }

    else if(!(result = mysql_store_result(con))) {
        fprintf(stderr,  "%s\n",   mysql_error(con));
        g_free(query);
        return false;
    } else {
        g_free(query);
        return true;

    }
}

bool loginUserDB(guchar  login[], guchar passwrd[], bool isAdmin)
{
    isAdm = isAdmin;

    if(isAdmin)
        return !mysql_change_user(con, login, passwrd, DB_NAME);
    else
        return !mysql_change_user(con, GUESTS_USERNAME, GUESTS_PASS, DB_NAME);
}
