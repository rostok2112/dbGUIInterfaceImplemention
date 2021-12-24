#include "../include/types.h"

bool isAdm;
MYSQL *con;
MYSQL_RES *result;
GtkBuilder *builder;
GtkWidget *window;


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "ukr");
    system("chcp 1251");


    gtk_init(&argc, &argv);

    if (!(con  = mysql_init(NULL)))
        CLOSE_WITH_ERR(0,0)

        if (!mysql_real_connect(con, ADRESS, AUTH_USERNAME, AUTH_PASS,
                                AUTH_DB_NAME, PORT, NULL, 0))
            CLOSE_WITH_ERR(0,1)

            createWin (&window, "winAuthorization", "resource/winAuthorization.glade");
    winAuthSetEventHandlers();
    gtk_widget_show_all(window);

    gtk_main();
}
