#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <gtk/gtk.h>

#include "mysql_includes/mysql.h"

#define HOST "192.168.0.101"
#define ADRESS "91.225.199.132"
#define PORT 3306
#define DB_NAME "2.1"
#define AUTH_DB_NAME "user_" DB_NAME
#define AUTH_TABLE "user_records"
#define AUTH_USERNAME "auth_user"
#define GUESTS_USERNAME "guests"
#define AUTH_PASS " "
#define GUESTS_PASS "123a"


#define CLOSE_WITH_ERR(ERR, CLOSE_SQL)  {                                          \
                                                                                   \
            fprintf(stderr, ERR ? "%d\n" : "%s\n",  ERR ? ERR: mysql_error(con));  \
            if(CLOSE_SQL)                                                          \
                mysql_close(con);                                                  \
            exit(ERR ? ERR: mysql_errno(con));                                     \
         }


typedef struct {
    void * arg1;
    void * arg2;
    void * arg3;
} Args3EventHandler;

typedef struct {
    void * arg1;
    void * arg2;
    void * arg3;
    void * arg4;
} Args4EventHandler;

extern bool isAdm;
extern MYSQL *con;
extern MYSQL_RES *result;
extern GtkBuilder * builder;
extern GtkWidget *window;
extern GtkDialog *dialog;

G_MODULE_EXPORT void onExit(GtkWidget * );
G_MODULE_EXPORT void onBtnLoginClicked(GtkButton *, Args3EventHandler **);
G_MODULE_EXPORT void onBtnRegisterClicked(GtkButton *, Args3EventHandler **);
G_MODULE_EXPORT void clear(GtkMenuItem *, GtkTextView *);
G_MODULE_EXPORT void onMenuItemClicked(GtkMenuItem *, GtkDialog *);
G_MODULE_EXPORT void onMenuItemSelectClicked(GtkMenuItem *, GtkDialog *);
G_MODULE_EXPORT void onCancelBtn1Clicked(GtkButton *, GtkDialog *);
G_MODULE_EXPORT void onOkBtn1Clicked(GtkButton *,  Args4EventHandler  **);
G_MODULE_EXPORT void onAdminMenuClicked(GtkMenuItem *,  GtkMessageDialog *);
G_MODULE_EXPORT void onMenuItemInsertClicked(GtkMenuItem *, GtkDialog *);
G_MODULE_EXPORT void onOkBtnInsertClicked(GtkButton *,  GtkDialog *);
G_MODULE_EXPORT void onOkBtnInsertInsertClicked(GtkButton *, GtkDialog *);
G_MODULE_EXPORT void onCancelBtnInsertInsertClicked(GtkButton *, GtkDialog *);
G_MODULE_EXPORT void onMenuItemDeleteClicked(GtkMenuItem *,  GtkDialog *);
G_MODULE_EXPORT void onOkBtnDeleteClicked(GtkButton *,  GtkDialog *);
G_MODULE_EXPORT void onMenuItemUpdateClicked(GtkMenuItem *, GtkDialog *);
G_MODULE_EXPORT void onOkBtnUpdateClicked(GtkButton *,  GtkDialog *);
G_MODULE_EXPORT void onOkBtnUpdateUpdateClicked(GtkButton *, GtkDialog *);
G_MODULE_EXPORT void onCancelBtnUpdateUpdateClicked(GtkButton *, GtkDialog *);
G_MODULE_EXPORT void onMenuItemLinkClicked(GtkMenuItem *,  GtkDialog *);
G_MODULE_EXPORT void onOkBtnLinkClicked(GtkButton *,  GtkDialog *);
G_MODULE_EXPORT void onOkBtnLinkRecordsClicked(GtkButton *,  GtkDialog *);
G_MODULE_EXPORT void onMenuItemPrivilegeClicked(GtkMenuItem *,  GtkDialog *);
G_MODULE_EXPORT void onOkBtnPrivilegeClicked(GtkButton *,  GtkDialog *);

void createWin(GtkWidget **, guchar[], guchar[]);
void showDlg(GtkDialog *);
void hideDlg(GtkDialog *);
void showMsg(GtkMessageDialog *, guchar *);

void winAuthSetEventHandlers(void);
void winMainSetEventHandlers(void);

bool createNewUserDB(guchar [], guchar [], bool);
bool checkUserDB(guchar [], guchar []);
bool loginUserDB(guchar [], guchar [], bool );
bool selectWithChildsDB(guchar[], guchar **);
bool selectDB(guchar []);
bool insertDB(guchar [], guchar []);
bool showTablesLikeNotLikeDB(guchar [], bool);
bool deleteDB(guchar [],  guchar [], guchar []);
bool updateDB(guchar [], guchar [], guchar [], guchar []);
bool linkDB(guchar [], guchar [], guchar [], guchar []);
bool createUserDBMS_DB(guchar [], guchar []);
bool grantAdminDBMS_DB(guchar []);

#endif // TYPES_H_INCLUDED
